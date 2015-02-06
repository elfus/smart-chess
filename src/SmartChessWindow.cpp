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

} /* namespace sch */
