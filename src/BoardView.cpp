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
BoardView::signalClickedReleased()
{
	return mSignalClickReleased;
}


BoardSquare BoardView::calculateSquare(double x, double y)
{
	int  i = 0, j = 0;
	bool found = false;
	const int BORDER = BORDER_WIDTH/2;

	if(x < BORDER || y < BORDER || x > (SQUARE_NUM*mSquareWidth) + BORDER
		|| y > (SQUARE_NUM*mSquareHeight) + BORDER) {
		clog << "Invalid square clicked" << endl;
		return BoardSquare(BoardPosition());
	}

	for(i=0; i < SQUARE_NUM; ++i) {
		if( ((i*mSquareWidth)+BORDER) < x && x <= ((i*mSquareWidth)+BORDER + mSquareWidth)) {
			for(j=0; j < SQUARE_NUM; ++j) {
				if(((j*mSquareHeight)+BORDER) < y &&
					y <= ((j*mSquareHeight) +BORDER+mSquareHeight) ) {
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

}

bool BoardView::clickReleased(GdkEventButton* event)
{
    if(event->button == 1)  {// 1 is left mouse
        if(event->x > mBoardWidth || event->y > mBoardHeight) {
            cerr << "Warning: Received click on invalid coordinate:"
                 << event->x << ", " << event->y << endl;
            return false;
        }
//        BoardSquare s = calculateSquare(event->x, event->y);
//        // notifiy when we have a square with a valid position
//        if(s.mPosition.isValid())
//            mSignalClickReleased(s);
    }

	return false;
}

void BoardView::drawBorders(const Cairo::RefPtr<Cairo::Context>& ctx,
				int board_width, int board_height)
{
	ctx->save();
	// draw the main background
	ctx->move_to(0,0);
	ctx->set_source_rgb(0.6, 0.6, 1.0);
	ctx->set_line_width(BORDER_WIDTH);
	ctx->rectangle(0,0, board_width, board_height);
	ctx->fill();
	ctx->stroke();

	// Draw the text
	ctx->set_source_rgb(0.0, 0.0, 0.0);
	mSquareWidth = (board_width-BORDER_WIDTH) / SQUARE_NUM;
	mSquareHeight = (board_height-BORDER_WIDTH) / SQUARE_NUM;

	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	// http://developer.gnome.org/pangomm/unstable/classPango_1_1Layout.html

	// Position the text on top of the board
	for(int i = Column::A; i <Column::MAX_COL; ++i) {
		stringstream ss;
		ss << static_cast<Column>(i);
		Glib::RefPtr<Pango::Layout> layout = create_pango_layout(ss.str());
		layout->set_font_description(font);
		int text_width;
		int text_height;
		//get the text dimensions (it updates the variables -- by reference)
		layout->get_pixel_size(text_width, text_height);

		// top part
		ctx->move_to((BORDER_WIDTH/2) + (mSquareWidth/2) + mSquareWidth*i - (text_width/2),
				 (text_height/2));
		layout->show_in_cairo_context(ctx);

		// bottom part
		ctx->move_to((BORDER_WIDTH/2) + (mSquareWidth/2) + mSquareWidth*i - (text_width/2),
				board_height - (BORDER_WIDTH/2) + (text_height/2));
			layout->show_in_cairo_context(ctx);
	}

	// Position the text on top of the board
	for(int i = 0; i <Row::MAX_ROW; ++i) {
		stringstream ss;
		ss << static_cast<Row>(i);
		Glib::RefPtr<Pango::Layout> layout = create_pango_layout(ss.str());
		layout->set_font_description(font);
		int text_width;
		int text_height;
		//get the text dimensions (it updates the variables -- by reference)
		layout->get_pixel_size(text_width, text_height);

		// top part
		ctx->move_to((text_width), (BORDER_WIDTH/2) + (mSquareHeight/2) + mSquareHeight*i - (text_height/2));
		layout->show_in_cairo_context(ctx);

		// bottom part
		ctx->move_to(board_width - (BORDER_WIDTH/2) + (text_width),
				(BORDER_WIDTH/2) + (mSquareHeight/2) + mSquareHeight*i - (text_height/2));
		layout->show_in_cairo_context(ctx);
	}

	ctx->restore();
}

void BoardView::drawSquares(const Cairo::RefPtr<Cairo::Context>& ctx,
		int board_width, int board_height)
{
	board_width -= BORDER_WIDTH;
	board_height -= BORDER_WIDTH;
	mSquareWidth = board_width / SQUARE_NUM;
	mSquareHeight = board_height / SQUARE_NUM;
	int x = BORDER_WIDTH, y = BORDER_WIDTH;
	bool is_white = true;

	ctx->set_source_rgb(1.0, 1.0, 1.0);
	for(int i=0; i < SQUARE_NUM; ++i) {
		x = (i * mSquareWidth) + (BORDER_WIDTH/2);
		for(int j=0; j < SQUARE_NUM; ++j) {
			if(is_white) {
				ctx->set_source_rgb(1.0, 1.0, 1.0);
				is_white = false;
			}
			else {
				ctx->set_source_rgb(.3, .3, .3);
				is_white = true;
			}
			y = (j * mSquareHeight) + (BORDER_WIDTH/2);
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
	auto image = ImageLoader::instance().getImage(p.getPieceType());
	image = image->scale_simple(mSquareWidth, mSquareHeight, Gdk::InterpType::INTERP_HYPER);
	BoardPosition pos = p.getBoardPosition();
	Gdk::Cairo::set_source_pixbuf(ctx, image, (BORDER_WIDTH/2) + mSquareWidth*pos.column, (BORDER_WIDTH/2) + mSquareHeight*pos.row);
	ctx->save();
	ctx->paint();
	ctx->restore();

	if(p.isSelected()) {
		// Draw a fancy blue square when the piece is selected
		const double LINE_W = 8.0;
		const double orig_x = (BORDER_WIDTH/2) + mSquareWidth*pos.column + (LINE_W/2);
		const double orig_y = (BORDER_WIDTH/2) + mSquareHeight*pos.row + (LINE_W/2);
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
//		vector<BoardPosition> options = p.getPossibleMoves(*mController->getState());
//
//		ctx->set_source_rgba(0, 0.0, 0.9, 0.75);
//		for(BoardPosition p : options) {
//			ctx->save();
//			const double x = (BORDER_WIDTH/2) + mSquareWidth*p.column;
//			const double y = (BORDER_WIDTH/2) + mSquareHeight*p.row;
//			ctx->rectangle(x,y, mSquareWidth, mSquareHeight);
//			ctx->fill();
//			ctx->stroke();
//			ctx->restore();
//		}
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

	drawBorders(ctx, mBoardWidth, mBoardHeight);
	drawSquares(ctx, mBoardWidth, mBoardHeight);

	// @todo Remove mState variable from this class
//	if(mController && mController->gameInProgress()) {
//		auto mState = mController->getState();
//		auto black_pieces = mState->getBlackPieces();
//		assert(black_pieces.size() == 16);
//		for(auto p : black_pieces)
//			drawPiece(ctx, *p);
//
//		auto white_pieces = mState->getWhitePieces();
//		assert(white_pieces.size() == 16);
//		for(auto p : white_pieces)
//			drawPiece(ctx, *p);
//	}

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
