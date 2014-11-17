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

using namespace std;

namespace sch {

SmartChessWindow::SmartChessWindow(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(cobject), mMainGrid(nullptr), mChessBoard(new ChessBoard){
	Gtk::Grid* grid = nullptr;
	builder->get_widget("MainGrid", grid);
	if(grid)
		mMainGrid.reset(grid);

	mChessBoard->show();
	mMainGrid->attach(*mChessBoard,1,1,1,1);
}

SmartChessWindow::~SmartChessWindow() {
	cerr << "Destructor" << endl;
}

} /* namespace sch */
