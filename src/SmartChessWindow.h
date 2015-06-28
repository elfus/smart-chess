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
#include "BoardController.h"
#include "BoardView.h"
#include "BoardState.h"

namespace Gtk {
class Builder;
class ComboBoxText;
class Grid;
class Window;
}

namespace sch { // sch stands for Smart Chess :)

class SmartChessWindow : public Gtk::Window {
public:
	SmartChessWindow(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& builder);

	SmartChessWindow();

	virtual ~SmartChessWindow();
private:
    const unsigned ROW_COUNT = 3;
    const unsigned COLUMN_COUNT = 3;

    /**
     * Creates, configures and returns a Gtk::manage'd Gtk::Grid
     */
    Gtk::Grid * configureMainGrid();

	std::unique_ptr<Gtk::Grid> mMainGrid;
	std::shared_ptr<BoardView> mBoardView;
	std::shared_ptr<BoardState> mBoardState;
	std::shared_ptr<BoardController> mBoardController;

	Gtk::ComboBoxText *mCbt1 {nullptr};
	Gtk::ComboBoxText *mCbt2 {nullptr};

	void player1ColorChanged();
	void player2ColorChanged();
};

} /* namespace sch */

#endif /* SMARTCHESSWINDOW_H_ */
