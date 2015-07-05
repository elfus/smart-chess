//===-- smart-chess/SmartChessWindow.cpp ------------------------*- C++ -*-===//
//
// This file is part of smart-chess, a chess game meant to provide an easy
// interface to experiment, learn and implement Artificial Intelligence
// algorithms.
//
// Copyright (c) 2014 Adrián Ortega García <adrianog(dot)sw(at)gmail(dot)com>
// All rights reserved.
//
// smart-chess is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// smart-chess is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with smart-chess (See file COPYING for details).
// If not, see <http://www.gnu.org/licenses/>.
//
//===----------------------------------------------------------------------===//
///
/// \file SmartChessWindow.cpp
/// \brief The main window for the game.
///
//===----------------------------------------------------------------------===//

#include "SmartChessWindow.h"
#include <iostream>
#include <gtkmm/aspectframe.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toggleaction.h>

using namespace std;

namespace sch {

	SmartChessWindow::SmartChessWindow() : mLogArea(nullptr), mOptionsGrid(nullptr) {
		Gtk::Grid* main_grid = createMainGrid();
		add(*main_grid);

        Gtk::MenuBar* menu_bar = createMenuBar();
        main_grid->attach(*menu_bar, 0, 0, COLUMN_COUNT, 1);

        mOptionsGrid = createOptionsArea();
        main_grid->attach(*mOptionsGrid, 0, 1, 1, 1);

		BoardView* view = createBoardView();
		main_grid->attach(*view, COLUMN_COUNT/2, ROW_COUNT/2, 1, 1);

        mLogArea = createLogArea();
        main_grid->attach(*mLogArea, COLUMN_COUNT-1, ROW_COUNT/2, 1, 1);

        Gtk::Widget* notification_bar = createNotificationBar();
        main_grid->attach(*notification_bar, 0, ROW_COUNT-1, COLUMN_COUNT, 1);

		show_all_children();
	}

    BoardView *SmartChessWindow::createBoardView() const {
        return manage(new BoardView());
    }

    Gtk::Grid * SmartChessWindow::createMainGrid() const {
        Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());
        grid->set_row_homogeneous(false);
        grid->set_column_homogeneous(false);
        grid->set_vexpand();
        grid->set_hexpand();

        for(unsigned i = 0; i < ROW_COUNT; ++i)
            grid->insert_row(i);

        for(unsigned i = 0; i < COLUMN_COUNT; ++i)
            grid->insert_column(i);

        return grid;
    }

    Gtk::Box * SmartChessWindow::createOptionsArea() {
        Gtk::Box*options = Gtk::manage(new Gtk::VBox(Gtk::ORIENTATION_VERTICAL));
        options->set_vexpand();
        options->set_hexpand(false);

        Gtk::Button* b = Gtk::manage(new Gtk::Button("Start"));
        b->set_hexpand(false);
        options->pack_start(*b, Gtk::PACK_SHRINK, 1);

        b = Gtk::manage(new Gtk::Button("End"));
        b->set_hexpand(false);
        options->pack_start(*b, Gtk::PACK_SHRINK, 1);

        b = Gtk::manage(new Gtk::Button("Reset"));
        b->set_hexpand(false);
        options->pack_start(*b, Gtk::PACK_SHRINK, 1);

//        mBoardController->setOptionsGrid(options);

        return options;
    }

    SmartChessWindow::SmartChessWindow(BaseObjectType* cobject,
            const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::Window(cobject),
      mBoardState(),
      mBoardController(new BoardController){
        Gtk::Grid* grid = nullptr;
        builder->get_widget("MainGrid", grid);

        Gtk::AspectFrame* af;
        builder->get_widget("AspectFrameBoard", af);
        af->set_vexpand();
        af->set_hexpand();

        Gtk::Statusbar * bar = nullptr;
        builder->get_widget("StatusBar", bar);
        bar->push("Welcome to Smart Chess!",1);
        mBoardController->setStatusbar(bar);

        Gtk::Grid* options_grid{nullptr};
        builder->get_widget("OptionsGrid", options_grid);
        mBoardController->setOptionsGrid(options_grid);
        // setup the buttons that control the game
        Gtk::Button *b = nullptr;
        builder->get_widget("StartButton", b);
        assert(b);
        b->signal_clicked().connect(sigc::mem_fun(*mBoardController, &BoardController::startGame));
        b = nullptr;

        builder->get_widget("EndButton", b);
        assert(b);
        b->signal_clicked().connect(sigc::mem_fun(*mBoardController, &BoardController::endGame));
        b = nullptr;

        builder->get_widget("ResetButton", b);
        assert(b);
        b->signal_clicked().connect(sigc::mem_fun(*mBoardController, &BoardController::resetGame));
        b = nullptr;

        // Make sure the color ius mutually exclusive
        vector<Gtk::Widget*> children = options_grid->get_children();
        Gtk::ComboBoxText *player {nullptr};
        // Start the game with some default options
        for(Gtk::Widget*& ptr : children) {
            if(ptr->get_name() == "ColorComboBox1") {
                mCbt1 = dynamic_cast<Gtk::ComboBoxText*>(ptr);
                mCbt1->set_active_text("White");
            }
            if(ptr->get_name() == "ColorComboBox2") {
                mCbt2 = dynamic_cast<Gtk::ComboBoxText*>(ptr);
                mCbt2->set_active_text("Black");
            }
            if(ptr->get_name() == "PlayerComboBox1") {
                player = dynamic_cast<Gtk::ComboBoxText*>(ptr);
                player->set_active_text("Human");
            }
            if(ptr->get_name() == "PlayerComboBox2") {
                player = dynamic_cast<Gtk::ComboBoxText*>(ptr);
                player->set_active_text("Algorithm");
            }
        }
        assert(mCbt1 && mCbt2);
        mCbt1->signal_changed().connect(sigc::mem_fun(*this, &SmartChessWindow::player1ColorChanged));
        mCbt2->signal_changed().connect(sigc::mem_fun(*this, &SmartChessWindow::player2ColorChanged));

        show_all_children();

        // start a game
        mBoardController->startGame();
    }

    SmartChessWindow::~SmartChessWindow() {
        cerr << "SmartChessWindow Destructor" << endl;
    }

    void SmartChessWindow::player1ColorChanged()
    {
        cout << "Player 1 color changed" << endl;
        if(mCbt1->get_active_text() == "White")
            mCbt2->set_active_text("Black");

        if(mCbt1->get_active_text() == "Black")
                mCbt2->set_active_text("White");
    }

    void SmartChessWindow::player2ColorChanged()
    {
        cout << "Player 2 color changed" << endl;
        if(mCbt2->get_active_text() == "White")
            mCbt1->set_active_text("Black");

        if(mCbt2->get_active_text() == "Black")
                mCbt1->set_active_text("White");
    }


    Gtk::MenuBar *SmartChessWindow::createMenuBar() {
        Glib::RefPtr<Gtk::ActionGroup> action_group = createActionGroup();

        mUIManager = createUIManager(action_group);

        Gtk::Widget* menu_bar = mUIManager->get_widget("/MenuBar");
        if(nullptr == menu_bar)
            cerr << "Could not create the menu bar" << endl;

        menu_bar->set_hexpand(false);
        menu_bar->set_vexpand(false);

        return dynamic_cast<Gtk::MenuBar*>(Gtk::manage(menu_bar));
    }

    Gtk::Widget *SmartChessWindow::createNotificationBar() const {
        Gtk::Box* statusbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        statusbox->set_vexpand(false);
        statusbox->set_hexpand();

        Gtk::Statusbar* statusbar = Gtk::manage(new Gtk::Statusbar());
        statusbar->set_vexpand(false);
        statusbar->set_hexpand();
        statusbox->add(*statusbar);

        Gtk::ProgressBar* progressbar = Gtk::manage(new Gtk::ProgressBar());
        progressbar->set_hexpand(false);
        progressbar->set_vexpand(false);
        statusbox->add(*progressbar);

        return statusbox;
    }

    void SmartChessWindow::onQuit() {
        hide();
    }

    Glib::RefPtr<Gtk::ActionGroup> SmartChessWindow::createActionGroup() {
        auto action_group = Gtk::ActionGroup::create();

        action_group->add(Gtk::Action::create("MenuFile", "_File"));
        action_group->add(Gtk::Action::create_with_icon_name("Quit", "application-exit", "_Quit", "Quits the application"),
                          Gtk::AccelKey("<control>q"), sigc::mem_fun(*this, &SmartChessWindow::onQuit));

        action_group->add(Gtk::Action::create("MenuView", "_View"));
        Glib::RefPtr<Gtk::ToggleAction> toggleAction = Gtk::ToggleAction::create("HideLogArea", "_Hide Log Area");
        toggleAction->set_active(false);
        action_group->add(toggleAction, Gtk::AccelKey("<control>h"),
                          sigc::bind(
                                  sigc::mem_fun(*this, &SmartChessWindow::onToggleHideLogArea),
                                  toggleAction
                                  )
                          );

        action_group->add(Gtk::Action::create("MenuHelp", "_Help"));
        action_group->add(Gtk::Action::create_with_icon_name("About", "help-about", "_About", "Display information about Smart Chess"),
                          sigc::mem_fun(*this, &SmartChessWindow::onAbout));

        return action_group;
    }

    Glib::RefPtr<Gtk::UIManager> SmartChessWindow::createUIManager(
            Glib::RefPtr<Gtk::ActionGroup> &action_group) {
        auto ui_manager = Gtk::UIManager::create();

        ui_manager->insert_action_group(action_group);
        add_accel_group(ui_manager->get_accel_group());

        Glib::ustring ui_info =
                "<ui>"
                "  <menubar name='MenuBar'>"
                "    <menu action='MenuFile'>"
                "      <separator/>"
                "      <menuitem action='Quit'/>"
                "    </menu>"
                "       <menu action='MenuView'>"
                "           <menuitem action='HideLogArea' />"
                "       </menu>"
                "       <menu action='MenuHelp'>"
                "           <menuitem action='About' />"
                "       </menu>"
                "  </menubar>"
                "  <toolbar  name='ToolBar'>"
                "    <toolitem action='Quit'/>"
                "  </toolbar>"
                "</ui>";

        ui_manager->add_ui_from_string(ui_info);
        return ui_manager;
    }

    void SmartChessWindow::onAbout() {

    }


    Gtk::Box *SmartChessWindow::createLogArea() {
        Gtk::Box * box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
        box->set_vexpand();
        box->set_hexpand(false);

        Gtk::TextView* pTextView = Gtk::manage(new Gtk::TextView(Gtk::TextBuffer::create()));
        pTextView->set_vexpand();
        pTextView->set_hexpand(false);

        Gtk::ScrolledWindow* scrolledWindow = Gtk::manage(new Gtk::ScrolledWindow());
        scrolledWindow->set_vexpand();
        scrolledWindow->set_hexpand(false);
        scrolledWindow->add(*pTextView);

        box->pack_end(*scrolledWindow);

        return box;
    }

    void SmartChessWindow::onToggleHideLogArea(
            Glib::RefPtr<Gtk::ToggleAction> toggleAction) {
        if(mLogArea == nullptr)
            return;

        if(toggleAction->get_active())
            mLogArea->hide();
        else
            mLogArea->show_all();
    }

} /* namespace sch */
