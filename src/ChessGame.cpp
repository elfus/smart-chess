//===-- smart-chess/ChessGame.cpp -------------------------------*- C++ -*-===//
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
/// \file ChessGame.cpp
/// \brief The class representing a single game or match.
///
//===----------------------------------------------------------------------===//

#include "ChessGame.h"
#include <iostream>

using namespace std;

namespace sch {

ChessGame::ChessGame(std::shared_ptr<ChessBoard>& board)
: mBoard(board) {
	mBoard->getSignalClickedReleased().
			connect(sigc::mem_fun(*this, &ChessGame::chessBoardClicked));
}

ChessGame::~ChessGame() {
	cerr << "ChessGame Destructor" << endl;
}

void ChessGame::chessBoardClicked(ChessBoard::Row row, ChessBoard::Column col)
{
	cout << "clicked: " << row << " " << col << endl;
}

void ChessGame::start() {

}

void ChessGame::end() {

}

void ChessGame::reset() {

}

} /* namespace sch */
