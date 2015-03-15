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
#include "BoardController.h"
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

	if(mController->gameInProgress())
	 return mController->getState()->getSquareAt(BoardPosition(Row(j), Column(i)));
	cerr << "WARNING: BoardView::calculateSquare: BoardState unavailable, creating new BoardSquare" << endl;
	return mController->getState()->getSquareAt(BoardPosition(static_cast<Row>(j), static_cast<Column>(i)));
}

bool BoardView::clickReleased(GdkEventButton* event)
{
	if(mController->gameInProgress()) {
		if(event->button == 1)  {// 1 is left mouse
			if(event->x > mBoardWidth || event->y > mBoardHeight) {
				cerr << "Warning: Received click on invalid coordinate:"
					 << event->x << ", " << event->y << endl;
				return false;
			}
			BoardSquare s = calculateSquare(event->x, event->y);
			mSignalClickReleased(s);
		}
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
	ctx->save();
	ctx->paint();
	ctx->restore();

	if(p.isSelected()) {
		// Draw a fancy blue square when the piece is selected
		const double LINE_W = 8.0;
		const double orig_x = 0 + mSquareWidth*pos.column + (LINE_W/2);
		const double orig_y = 0 + mSquareHeight*pos.row + (LINE_W/2);
		ctx->save();
		ctx->set_source_rgba(0, 0.0, 0.9, 1.0);
		ctx->set_line_width(LINE_W);
		ctx->set_line_join(Cairo::LINE_JOIN_MITER);
		ctx->move_to(orig_x, orig_y);
		ctx->line_to(orig_x+mSquareWidth-LINE_W, orig_y);
		ctx->line_to(orig_x+mSquareWidth-LINE_W, orig_y+mSquareHeight-LINE_W);
		ctx->line_to(orig_x, orig_y+mSquareHeight-LINE_W);
		ctx->close_path();
		ctx->stroke();
		ctx->restore();
		// draw the possible squares that this piece can move to
		vector<BoardPosition> options = p.getPossibleMoves(*mController->getState());

		ctx->set_source_rgba(0, 0.0, 0.9, 0.75);
		for(BoardPosition p : options) {
			ctx->save();
			const double x = 0 + mSquareWidth*p.column;
			const double y = 0 + mSquareHeight*p.row;
			ctx->rectangle(x,y, mSquareWidth, mSquareHeight);
			ctx->fill();
			ctx->stroke();
			ctx->restore();
		}
	}

	ctx->restore();
}

void BoardView::force_redraw() {
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
}

bool BoardView::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
	Gtk::Allocation allocation = get_allocation();
	mBoardWidth = allocation.get_width();
	mBoardHeight = allocation.get_height();

	drawSquares(ctx, mBoardWidth, mBoardHeight);

	// @todo Remove mState variable from this class
	if(mController->gameInProgress()) {
		auto mState = mController->getState();
		auto black_pieces = mState->getBlackPieces();
		assert(black_pieces.size() == 16);
		for(auto p : black_pieces)
			drawPiece(ctx, *p);

		auto white_pieces = mState->getWhitePieces();
		assert(white_pieces.size() == 16);
		for(auto p : white_pieces)
			drawPiece(ctx, *p);
	}

	return true;
}

std::ostream& operator <<(std::ostream& os, Row r)
{
	switch (r) {
	case Row::ONE: os << 1; break;
	case Row::TWO: os << 2; break;
	case Row::THREE: os << 3; break;
	case Row::FOUR: os << 4; break;
	case Row::FIVE: os << 5; break;
	case Row::SIX: os << 6; break;
	case Row::SEVEN: os << 7; break;
	case Row::EIGHT: os << 8; break;
	default:
		os << "<Invalid BoardRow(" << int(r) << ")>";
		break;
	}
	return os;
}
std::ostream& operator <<(std::ostream& os, Column c)
{
	switch(c) {
	case Column::A: os << "A"; break;
	case Column::B: os << "B"; break;
	case Column::C: os << "C"; break;
	case Column::D: os << "D"; break;
	case Column::E: os << "E"; break;
	case Column::F: os << "F"; break;
	case Column::G: os << "G"; break;
	case Column::H: os << "H"; break;
	default:
		os << "<Invalid BoardColumn(" << int(c) << ")>";
		break;
	}
	return os;
}

std::ostream& operator <<(std::ostream& os, Move m)
{
	os << "Move : "<<m.piece->getPieceType() << " to "
		<< m.final_pos.column << m.final_pos.row << endl;
	return os;
}

} /* namespace sch */
