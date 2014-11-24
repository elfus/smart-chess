//===-- smart-chess/ChessBoard.h --------------------------------*- C++ -*-===//
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
/// \file ChessBoard.h
/// \brief The class in charge of drawing the chess board on the gui.
///
//===----------------------------------------------------------------------===//

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <gtkmm/drawingarea.h>
#include <tuple>

namespace sch {

class ChessBoard: public Gtk::DrawingArea {
public:
	enum Row {
		ONE = 7,
		TWO = 6,
		THREE = 5,
		FOUR = 4,
		FIVE = 3,
		SIX = 2,
		SEVEN = 1,
		EIGHT = 0
	};

	enum Column {
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H
	};

	ChessBoard();
	virtual ~ChessBoard();

	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);

	sigc::signal<void, Row, Column> getSignalClickedReleased();

private:
	static const int SQUARE_NUM = 8;
	static const int MIN_BOARD_W = 400;
	static const int MIN_BOARD_H = MIN_BOARD_W;

	int mBoardWidth;
	int mBoardHeight;
	int mSquareWidth;
	int mSquareHeight;

	sigc::signal<void, Row, Column> mSignalClickReleased;

	void drawSquares(const Cairo::RefPtr<Cairo::Context>& ctx,
			int board_width, int board_height);

	bool clickReleased(GdkEventButton* event);

	void drawFigure(const Cairo::RefPtr<Cairo::Context>& ctx,
			const Glib::ustring& path, Row row, Column col);

	std::tuple<Row,Column> calculateSquare(double x, double y);
};

std::ostream& operator <<(std::ostream& os, ChessBoard::Row r);
std::ostream& operator <<(std::ostream& os, ChessBoard::Column c);


} /* namespace sch */

#endif /* CHESSBOARD_H_ */
