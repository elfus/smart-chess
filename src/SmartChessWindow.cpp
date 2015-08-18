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

#include "Util.h"
#include "SmartChessWindow.h"
#include <iostream>
#include <gtkmm/aspectframe.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/messagedialog.h>
#include <glibmm.h>

using namespace std;

namespace sch {

	SmartChessWindow::SmartChessWindow()
	: mLogArea(nullptr), mOptionsGrid(nullptr), mSubOptionsGrid(nullptr) {
		Gtk::Grid* main_grid = createMainGrid();
		add(*main_grid);

        Gtk::MenuBar* menu_bar = createMenuBar();
        main_grid->attach(*menu_bar, 0, 0, COLUMN_COUNT, 1);

        mOptionsGrid = createOptionsArea();
        main_grid->attach(*mOptionsGrid, 0, 1, 1, 1);

		mView = createBoardView();
		main_grid->attach(*mView, COLUMN_COUNT/2, ROW_COUNT/2, 1, 1);

        mLogArea = createLogArea();
        main_grid->attach(*mLogArea, COLUMN_COUNT-1, ROW_COUNT/2, 1, 1);

        Gtk::Widget* notification_bar = createNotificationBar();
        main_grid->attach(*notification_bar, 0, ROW_COUNT-1, COLUMN_COUNT, 1);

        mBoardController.signalBoardStateUpdated().connect(
                            sigc::mem_fun(*this, &SmartChessWindow::onBoardStateUpdate));

		show_all_children();
	}

    BoardView *SmartChessWindow::createBoardView() const {
        BoardView *pBoardView = manage(new BoardView());
        pBoardView->set_hexpand();
        return pBoardView;
    }

    Gtk::Grid * SmartChessWindow::createMainGrid() const {
        Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());
        grid->set_row_homogeneous(false);
        grid->set_column_homogeneous(false);
        grid->set_vexpand();
        grid->set_hexpand();

        for(auto i : IntRange(ROW_COUNT))
            grid->insert_row(i);

        for(auto i : IntRange(COLUMN_COUNT))
            grid->insert_column(i);

        return grid;
    }

    Gtk::Grid * SmartChessWindow::createOptionsArea() {
        const int OPTIONS_ROWS = 4;
        Gtk::Grid* options = Gtk::manage(new Gtk::Grid());
        options->set_vexpand();
        options->set_hexpand(false);
        options->insert_column(0);

        for(auto i : IntRange(OPTIONS_ROWS))
            options->insert_row(i);

        Gtk::Button* b = Gtk::manage(new Gtk::Button("Start"));
        b->set_hexpand(false);
        b->signal_clicked().connect(sigc::mem_fun(this, &SmartChessWindow::onStartGame));
        options->attach(*b, 0, 0, 1, 1);

        b = Gtk::manage(new Gtk::Button("End"));
        b->set_hexpand(false);
        b->signal_clicked().connect(sigc::mem_fun(this, &SmartChessWindow::onEndGame));
        options->attach(*b, 0, 1, 1, 1);

        b = Gtk::manage(new Gtk::Button("Reset"));
        b->set_hexpand(false);
        b->signal_clicked().connect(sigc::mem_fun(this, &SmartChessWindow::onResetGame));
        options->attach(*b, 0, 2, 1, 1);

        auto suboptions = createSuboptionsArea();
        options->attach(*suboptions, 0, 3, 1, 1);

        return options;
    }

    Gtk::Grid *SmartChessWindow::createSuboptionsArea() {
        const int SUBOPTIONS_ROWS = 3;
        const int SUBOPTIONS_COLS = 3;
        const int MARGIN = 1;

        mSubOptionsGrid = Gtk::manage(new Gtk::Grid());
        mSubOptionsGrid->set_vexpand();
        mSubOptionsGrid->set_hexpand(false);
        mSubOptionsGrid->set_column_homogeneous(true);
        mSubOptionsGrid->insert_column(0);

        for(auto i : IntRange(SUBOPTIONS_COLS))
            mSubOptionsGrid->insert_column(i);

        for(auto i : IntRange(SUBOPTIONS_ROWS))
            mSubOptionsGrid->insert_row(i);

        Gtk::Label* p1 = Gtk::manage(new Gtk::Label("Player 1"));
        p1->set_margin_left(MARGIN);
        p1->set_margin_right(MARGIN);
        mSubOptionsGrid->attach(*p1, 0, 0, 1, 1);

        Gtk::Label* vs = Gtk::manage(new Gtk::Label("V.S."));
        vs->set_margin_left(MARGIN);
        vs->set_margin_right(MARGIN);
        mSubOptionsGrid->attach(*vs, 1, 0, 1, 1);

        Gtk::Label* p2 = Gtk::manage(new Gtk::Label("Player 2"));
        p2->set_margin_left(MARGIN);
        p2->set_margin_right(MARGIN);
        mSubOptionsGrid->attach(*p2, 2, 0, 1, 1);

        mCbt1 = Gtk::manage(new Gtk::ComboBoxText());
        mCbt1->append("Human");
        mCbt1->append("A.I.");
        mCbt1->set_active(0);
        mSubOptionsGrid->attach(*mCbt1, 0, 1, 1, 1);

        mCbt2 = Gtk::manage(new Gtk::ComboBoxText());
        mCbt2->append("Human");
        mCbt2->append("A.I.");
        mCbt2->set_active(1);
        mSubOptionsGrid->attach(*mCbt2, 2, 1, 1, 1);

        rcg1 = Gtk::manage(new GRadioColorGroup());
        mSubOptionsGrid->attach(*rcg1, 0, 2, 1, 1);

        rcg2 = Gtk::manage(new GRadioColorGroup());
        mSubOptionsGrid->attach(*rcg2, 2, 2, 1, 1);

        rcg1->signalClickedWhite().connect(sigc::mem_fun(rcg2, &GRadioColorGroup::setBlack));
        rcg1->signalClickedBlack().connect(sigc::mem_fun(rcg2, &GRadioColorGroup::setWhite));
        rcg2->signalClickedWhite().connect(sigc::mem_fun(rcg1, &GRadioColorGroup::setBlack));
        rcg2->signalClickedBlack().connect(sigc::mem_fun(rcg1, &GRadioColorGroup::setWhite));
        rcg1->setWhite();
        rcg2->setBlack();
        return mSubOptionsGrid;
    }

    SmartChessWindow::~SmartChessWindow() {
        cerr << "SmartChessWindow Destructor" << endl;
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

    Gtk::Widget *SmartChessWindow::createNotificationBar() {
        Gtk::Box* statusbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        statusbox->set_vexpand(false);
        statusbox->set_hexpand();

        mStatusBar = Gtk::manage(new Gtk::Statusbar());
        mStatusBar->set_vexpand(false);
        mStatusBar->set_hexpand();
        statusbox->add(*mStatusBar);

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
        Glib::RefPtr<Gtk::ToggleAction> toggleOptionsAction = Gtk::ToggleAction::create("ShowOptionsArea", "_Options Area");
        toggleOptionsAction->set_active(true);
        action_group->add(toggleOptionsAction, Gtk::AccelKey("<control>o"),
                          sigc::bind(
                                  sigc::mem_fun(*this,
                                                &SmartChessWindow::onToggleShowOptionsArea),
                                  toggleOptionsAction
                          )
        );

        Glib::RefPtr<Gtk::ToggleAction> toggleAction = Gtk::ToggleAction::create("ShowLogArea", "_Log Area");
        toggleAction->set_active(true);
        action_group->add(toggleAction, Gtk::AccelKey("<control>l"),
                          sigc::bind(
                                  sigc::mem_fun(*this,
                                                &SmartChessWindow::onToggleShowLogArea),
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
                "           <menuitem action='ShowOptionsArea' />"
                "           <menuitem action='ShowLogArea' />"
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
        Gtk::AboutDialog dialog;
        dialog.set_program_name("Smart chess");
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

    void SmartChessWindow::onToggleShowLogArea(
            Glib::RefPtr<Gtk::ToggleAction> toggleAction) {
        if(mLogArea == nullptr)
            return;

        if(toggleAction->get_active())
            mLogArea->show_all();
        else
            mLogArea->hide();
    }


    void SmartChessWindow::onToggleShowOptionsArea(
            Glib::RefPtr<Gtk::ToggleAction> toggleAction) {
        if(toggleAction->get_active())
            mOptionsGrid->show_all();
        else
            mOptionsGrid->hide();
    }

    void SmartChessWindow::onStartGame() {
        cout << "SmartChessWindow::onStartGame" << endl;
        string err;
        if(validGameOptions(err)) {
        	/// @todo when we have more algorithms we will have to create a factory method
        	ChessPlayer* player1 = (mCbt1->get_active_text() == "Human") ? static_cast<ChessPlayer*>(new Human(rcg1->getColor())) : new Algorithm(rcg1->getColor());
        	ChessPlayer* player2 = (mCbt2->get_active_text() == "Human") ? static_cast<ChessPlayer*>(new Human(rcg2->getColor())) : new Algorithm(rcg2->getColor());

        	if(typeid(*player1) != typeid(Human)) {
        		mAIPlayerConnection = Glib::signal_idle().connect(sigc::mem_fun(mBoardController, &BoardController::mainGameLogic));
        	}

        	// When an A.I. clicks on the board, we should connect it to this signal
        	if(typeid(*player1) == typeid(Human) ||  typeid(*player2) == typeid(Human)) {
        		mBoardViewConnection = mView->signalClickedReleased().connect(sigc::mem_fun(mBoardController, &BoardController::chessBoardClicked));
        	}

            mBoardController.startGame(player1, player2);

            mSubOptionsGrid->set_sensitive(false);
        } else {
            Gtk::MessageDialog dialog(err, false, Gtk::MESSAGE_ERROR);
            dialog.run();
        }
    }

    void SmartChessWindow::onEndGame() {
        cout << "SmartChessWindow::onEndGame" << endl;
        if(mAIPlayerConnection) mAIPlayerConnection.disconnect();
        if(mBoardViewConnection) mBoardViewConnection.disconnect();
        mBoardController.endGame();
        mSubOptionsGrid->set_sensitive();
    }

    void SmartChessWindow::onResetGame() {
        cout << "SmartChessWindow::onResetGame" << endl;
        onEndGame();
        onStartGame();
    }

    bool SmartChessWindow::validGameOptions(std::string &error_msg) {
        auto valid = true;

        if(mCbt1->get_active_text().empty()) {
            error_msg += "Choose a player type for player 1. ";
            valid = false;
        }

        if(mCbt2->get_active_text().empty()) {
            error_msg += "\nChoose a player type for player 2. ";
            valid = false;
        }

        return valid;
    }

    void SmartChessWindow::onBoardStateUpdate(const BoardState& state) {
        cout << "BoardState Updated" << endl;
        stringstream ss;
        ss << state.getCurrentPlayer() << "'s turn";
        mStatusBar->pop();
        mStatusBar->push(ss.str());
        mView->force_redraw(state);
    }
} /* namespace sch */
