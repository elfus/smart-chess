//===-- smart-chess/BoardView.cpp ------------------------------*- C++ -*-===//
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
/// \file BoardView.cpp
/// \brief The class in charge of drawing the chess board on the gui.
///
//===----------------------------------------------------------------------===//
#include "BoardView.h"
#include "BoardState.h"
#include "ChessPiece.h"
#include <iostream>
#include <assert.h>
#include <gdkmm.h>

using namespace std;

namespace sch {

BoardView::BoardView() : Gtk::DrawingArea(){
	set_vexpand();
	set_size_request(MIN_BOARD_W, MIN_BOARD_H);
	set_events(Gdk::EventMask::BUTTON_PRESS_MASK | Gdk::EventMask::BUTTON_RELEASE_MASK);

	signal_button_release_event().connect(sigc::mem_fun(*this,&BoardView::clickReleased));
}

BoardView::~BoardView() {
	cerr << "ChessBoard Destructor" << endl;
}

sigc::signal<void, BoardSquare>
BoardView::getSignalClickedReleased()
{
	return mSignalClickReleased;
}


BoardSquare BoardView::calculateSquare(double x, double y)
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
	return BoardSquare(BoardRow(j), BoardColumn(i));
}

bool BoardView::clickReleased(GdkEventButton* event)
{
	if(event->button == 1)  {// 1 is left mouse
		if(event->x > mBoardWidth || event->y > mBoardHeight) {
			cerr << "Warning: Received click on invalid coordinate:"
				 << event->x << ", " << event->y << endl;
			return false;
		}
		BoardSquare s = calculateSquare(event->x, event->y);
		mSignalClickReleased(s);
	}

	return false;
}

void BoardView::drawSquares(const Cairo::RefPtr<Cairo::Context>& ctx,
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

void BoardView::drawPiece(const Cairo::RefPtr<Cairo::Context>& ctx, const ChessPiece& p)
{
	ctx->save();
	auto image = p.getImage();
	image = image->scale_simple(mSquareWidth, mSquareHeight, Gdk::InterpType::INTERP_HYPER);
	BoardPosition pos = p.getPosition();
	Gdk::Cairo::set_source_pixbuf(ctx, image, 0 + mSquareWidth*pos.column, 0 + mSquareHeight*pos.row);
	ctx->paint();
	ctx->restore();
}

bool BoardView::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
	Gtk::Allocation allocation = get_allocation();
	mBoardWidth = allocation.get_width();
	mBoardHeight = allocation.get_height();

	drawSquares(ctx, mBoardWidth, mBoardHeight);

	if(mState) {
		auto black_pieces = mState->getBlackPieces();
		assert(!black_pieces.empty());
		for(auto p : black_pieces)
			drawPiece(ctx, *p);

		auto white_pieces = mState->getWhitePieces();
		assert(!white_pieces.empty());
		for(auto p : white_pieces)
			drawPiece(ctx, *p);
	}

	return true;
}

std::ostream& operator <<(std::ostream& os, BoardRow r)
{
	switch (r) {
	case BoardRow::ONE: os << 1; break;
	case BoardRow::TWO: os << 2; break;
	case BoardRow::THREE: os << 3; break;
	case BoardRow::FOUR: os << 4; break;
	case BoardRow::FIVE: os << 5; break;
	case BoardRow::SIX: os << 6; break;
	case BoardRow::SEVEN: os << 7; break;
	case BoardRow::EIGHT: os << 8; break;
	}
	return os;
}
std::ostream& operator <<(std::ostream& os, BoardColumn c)
{
	switch(c) {
	case BoardColumn::A: os << "A"; break;
	case BoardColumn::B: os << "B"; break;
	case BoardColumn::C: os << "C"; break;
	case BoardColumn::D: os << "D"; break;
	case BoardColumn::E: os << "E"; break;
	case BoardColumn::F: os << "F"; break;
	case BoardColumn::G: os << "G"; break;
	case BoardColumn::H: os << "H"; break;
	}
	return os;
}

} /* namespace sch */
