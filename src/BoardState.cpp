//===-- smart-chess/BoardState.cpp -------------------------------*- C++ -*-===//
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
/// \file BoardState.cpp
/// \brief The class representing a single game or match.
///
//===----------------------------------------------------------------------===//

#include "BoardState.h"
#include <iostream>

using namespace std;

namespace sch {

BoardState::BoardState(std::shared_ptr<BoardView>& board)
: mBoard(board), mSquares() {
	mBoard->getSignalClickedReleased().
			connect(sigc::mem_fun(*this, &BoardState::chessBoardClicked));
	for(int i = 0; i < BoardView::Column::MAX_COL; ++i) {
		for(int j = 0; j < BoardView::Row::MAX_ROW; ++j) {
			mSquares.push_back(BoardView::Square(
					BoardView::Row(j),BoardView::Column(i)));
		}
	}
}

BoardState::~BoardState() {
	cerr << "ChessGame Destructor" << endl;
}

void BoardState::chessBoardClicked(BoardView::Square s)
{
	cout << "clicked: " << s.row << " " << s.column << endl;
}

void BoardState::start() {

}

void BoardState::end() {

}

void BoardState::reset() {

}

} /* namespace sch */
