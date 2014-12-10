//===-- smart-chess/BoardView.h --------------------------------*- C++ -*-===//
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
/// \file BoardView.h
/// \brief The class in charge of drawing the chess board on the gui.
///
//===----------------------------------------------------------------------===//

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <gtkmm/drawingarea.h>
#include "Util.h"

namespace sch {

class ChessPiece;
class BoardController;

class BoardView: public Gtk::DrawingArea {
public:


	BoardView();
	virtual ~BoardView();

	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);

	sigc::signal<void, BoardSquare> getSignalClickedReleased();

	void setBoardController(std::shared_ptr<BoardController> c) { mController = c; }

	void force_redraw();
private:
	static const int SQUARE_NUM = 8;
	static const int MIN_BOARD_W = 400;
	static const int MIN_BOARD_H = MIN_BOARD_W;

	int mBoardWidth;
	int mBoardHeight;
	int mSquareWidth;
	int mSquareHeight;
	std::shared_ptr<BoardController> mController;

	sigc::signal<void, BoardSquare> mSignalClickReleased;

	void drawSquares(const Cairo::RefPtr<Cairo::Context>& ctx,
			int board_width, int board_height);

	bool clickReleased(GdkEventButton* event);

	void drawPiece(const Cairo::RefPtr<Cairo::Context>& ctx, const ChessPiece& p);


	BoardSquare calculateSquare(double x, double y);
};


} /* namespace sch */

#endif /* CHESSBOARD_H_ */
