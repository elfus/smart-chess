//===-- smart-chess/ChessGame.h ---------------------------------*- C++ -*-===//
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
/// \file ChessGame.h
/// \brief The class representing a single game or match.
///
//===----------------------------------------------------------------------===//

#ifndef CHESSGAME_H_
#define CHESSGAME_H_

#include <memory>
#include "ChessBoard.h"

namespace sch {

class ChessBoard;

class ChessGame {
public:
	ChessGame(std::shared_ptr<ChessBoard>& board);
	~ChessGame();

	void start();
	void end();
	void reset();

	void chessBoardClicked(ChessBoard::Row, ChessBoard::Column);
private:
	std::shared_ptr<ChessBoard> mBoard;
};

} /* namespace sch */

#endif /* CHESSGAME_H_ */
