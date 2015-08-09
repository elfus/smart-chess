//===-- smart-chess/SmartChessWindow.h --------------------------*- C++ -*-===//
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
/// \file SmartChessWindow.h
/// \brief The main window for the game.
///
//===----------------------------------------------------------------------===//

#ifndef SMARTCHESSWINDOW_H_
#define SMARTCHESSWINDOW_H_

#include <gtkmm/window.h>
#include <gtkmm/menubar.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/box.h>
#include <gtkmm/toggleaction.h>
#include "BoardController.h"
#include "BoardView.h"
#include "BoardState.h"
#include "GRadioColorGroup.h"

namespace Gtk {
class Builder;
class ComboBoxText;
class Grid;
class Window;
}

namespace sch { // sch stands for Smart Chess :)

class SmartChessWindow : public Gtk::Window {
public:

	SmartChessWindow();

	virtual ~SmartChessWindow();
private:
    const unsigned ROW_COUNT = 3;
    const unsigned COLUMN_COUNT = 3;

	BoardController     mBoardController;
    Glib::RefPtr<Gtk::UIManager> mUIManager;
    Gtk::Widget *mLogArea;
    Gtk::Widget *mOptionsGrid;
    BoardView   *mView;


	Gtk::ComboBoxText *mCbt1 {nullptr};
	Gtk::ComboBoxText *mCbt2 {nullptr};

    GRadioColorGroup* rcg1 {nullptr};
    GRadioColorGroup* rcg2 {nullptr};

    Gtk::Statusbar*	  mStatusBar {nullptr};
    sigc::connection	mAIPlayerConnection;
    sigc::connection	mBoardViewConnection;

    void onBoardStateUpdate(const BoardState& state);
    void onStartGame();
    void onEndGame();
    void onResetGame();
    void onQuit();
    void onAbout();
    void onToggleShowLogArea(Glib::RefPtr<Gtk::ToggleAction> toggleAction);
    void onToggleShowOptionsArea(Glib::RefPtr<Gtk::ToggleAction> toggleAction);

    Glib::RefPtr<Gtk::ActionGroup> createActionGroup();

    Glib::RefPtr<Gtk::UIManager> createUIManager(Glib::RefPtr<Gtk::ActionGroup> &ptr);

    /**
     * Creates, configures and returns a Gtk::manage'd Gtk::Grid
     */
    Gtk::Grid *createMainGrid() const;
    Gtk::MenuBar *createMenuBar();
    Gtk::Widget *createNotificationBar();
    BoardView *createBoardView() const;

    Gtk::Box *createLogArea();

    Gtk::Grid * createOptionsArea();

    Gtk::Grid *createSuboptionsArea();

    bool validGameOptions(std::string &error_msg);
};

} /* namespace sch */

#endif /* SMARTCHESSWINDOW_H_ */
