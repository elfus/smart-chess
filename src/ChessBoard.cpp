//===-- smart-chess/ChessBoard.cpp ------------------------------*- C++ -*-===//
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
/// \file ChessBoard.cpp
/// \brief The class in charge of drawing the chess board on the gui.
///
//===----------------------------------------------------------------------===//
#include "ChessBoard.h"
#include <iostream>
#include <assert.h>
#include <gdkmm.h>

using namespace std;

namespace sch {

ChessBoard::ChessBoard() : Gtk::DrawingArea(){
	set_vexpand();
	set_size_request(MIN_BOARD_W, MIN_BOARD_H);
	set_events(Gdk::EventMask::BUTTON_PRESS_MASK | Gdk::EventMask::BUTTON_RELEASE_MASK);

	signal_button_release_event().connect(sigc::mem_fun(*this,&ChessBoard::clickReleased));
}

ChessBoard::~ChessBoard() {
	cerr << "ChessBoard Destructor" << endl;
}

sigc::signal<void, ChessBoard::Row, ChessBoard::Column>
ChessBoard::getSignalClickedReleased()
{
	return mSignalClickReleased;
}


tuple<ChessBoard::Row, ChessBoard::Column>
ChessBoard::calculateSquare(double x, double y)
{
	int  i = 0, j = 0;
	bool found = false;
	for(; i < SQUARE_NUM; ++i) {
		if((i*mSquareWidth) < x && x <= ((i*mSquareWidth) + mSquareWidth)) {
			for(; j < SQUARE_NUM; ++j) {
				if((j*mSquareHeight) < y &&
					y <= ((j*mSquareHeight) +mSquareHeight)) {
					found = true;
					break;
				}
			}
		}
		if(found)
			break;
	}
	assert( i < SQUARE_NUM );
	assert( j < SQUARE_NUM);
	return make_tuple(Row(j), Column(i));
}

bool ChessBoard::clickReleased(GdkEventButton* event)
{
	if(event->button == 1)  {// 1 is left mouse
		if(event->x > mBoardWidth || event->y > mBoardHeight) {
			cerr << "Warning: Received click on invalid coordinate:"
				 << event->x << ", " << event->y << endl;
			return false;
		}
		auto s = calculateSquare(event->x, event->y);
		mSignalClickReleased(get<0>(s), get<1>(s));
	}

	return false;
}

void ChessBoard::drawSquares(const Cairo::RefPtr<Cairo::Context>& ctx,
		int board_width, int board_height)
{
	mSquareWidth = board_width / SQUARE_NUM;
	mSquareHeight = board_height / SQUARE_NUM;
	int x = 0, y = 0;
	ctx->set_source_rgb(1.0, 1.0, 1.0);
	bool is_white = true;
	for(int i=0; i < SQUARE_NUM; ++i) {
		x = i * mSquareWidth;
		for(int j=0; j < SQUARE_NUM; ++j) {
			if(is_white) {
				ctx->set_source_rgb(1.0, 1.0, 1.0);
				is_white = false;
			}
			else {
				ctx->set_source_rgb(.3, .3, .3);
				is_white = true;
			}
			y = j * mSquareHeight;
			ctx->rectangle(x,y, mSquareWidth, mSquareHeight);
			ctx->fill();
		}
		if(is_white) {
			ctx->set_source_rgb(1.0, 1.0, 1.0);
			is_white = false;
		}
		else {
			ctx->set_source_rgb(.3, .3, .3);
			is_white = true;
		}
	}
}

void ChessBoard::drawFigure(const Cairo::RefPtr<Cairo::Context>& ctx,
		const Glib::ustring& path, Row row, Column col)
{
	Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file(path);
	image = image->scale_simple(mSquareWidth, mSquareHeight, Gdk::InterpType::INTERP_HYPER);
	Gdk::Cairo::set_source_pixbuf(ctx, image, 0 + mSquareWidth*col, 0 + mSquareHeight*row);
	ctx->paint();
}

bool ChessBoard::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
	Gtk::Allocation allocation = get_allocation();
	mBoardWidth = allocation.get_width();
	mBoardHeight = allocation.get_height();

	drawSquares(ctx, mBoardWidth, mBoardHeight);

	drawFigure(ctx, "data/pawnw.gif", Row::EIGHT, Column::A);

	return true;
}

std::ostream& operator <<(std::ostream& os, ChessBoard::Row r)
{
	switch (r) {
	case ChessBoard::Row::ONE: os << 1; break;
	case ChessBoard::Row::TWO: os << 2; break;
	case ChessBoard::Row::THREE: os << 3; break;
	case ChessBoard::Row::FOUR: os << 4; break;
	case ChessBoard::Row::FIVE: os << 5; break;
	case ChessBoard::Row::SIX: os << 6; break;
	case ChessBoard::Row::SEVEN: os << 7; break;
	case ChessBoard::Row::EIGHT: os << 8; break;
	}
	return os;
}
std::ostream& operator <<(std::ostream& os, ChessBoard::Column c)
{
	switch(c) {
	case ChessBoard::Column::A: os << "A"; break;
	case ChessBoard::Column::B: os << "B"; break;
	case ChessBoard::Column::C: os << "C"; break;
	case ChessBoard::Column::D: os << "D"; break;
	case ChessBoard::Column::E: os << "E"; break;
	case ChessBoard::Column::F: os << "F"; break;
	case ChessBoard::Column::G: os << "G"; break;
	case ChessBoard::Column::H: os << "H"; break;
	}
	return os;
}

} /* namespace sch */
