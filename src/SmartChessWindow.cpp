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
#include <gtkmm/button.h>
#include <gtkmm/statusbar.h>

using namespace std;

namespace sch {

SmartChessWindow::SmartChessWindow(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(cobject), mMainGrid(nullptr),
  mBoardView(new BoardView),
  mBoardState(),
  mBoardController(new BoardController){
	Gtk::Grid* grid = nullptr;
	builder->get_widget("MainGrid", grid);
	if(grid)
		mMainGrid.reset(grid);

	Gtk::AspectFrame* af;
	builder->get_widget("AspectFrameBoard", af);
	af->set_vexpand();
	af->set_hexpand();

	af->add(*mBoardView);

	mBoardView->getSignalClickedReleased().connect(
		sigc::mem_fun(*mBoardController,&BoardController::chessBoardClicked));

	mBoardView->setBoardController(mBoardController);
	mBoardController->setBoardView(mBoardView);

	Gtk::Statusbar * bar = nullptr;
	builder->get_widget("StatusBar", bar);
	bar->push("Welcome to Smart Chess!",1);
	mBoardController->setStatusbar(bar);

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
	show_all_children();

	// start a game
	mBoardController->startGame();
}

SmartChessWindow::~SmartChessWindow() {
	cerr << "SmartChessWindow Destructor" << endl;
}

} /* namespace sch */
