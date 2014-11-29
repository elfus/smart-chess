//===-- smart-chess/BoardState.h --------------------------------*- C++ -*-===//
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
/// \file BoardState.h
/// \brief The class representing a single game or match.
///
//===----------------------------------------------------------------------===//

#ifndef CHESSGAME_H_
#define CHESSGAME_H_

#include <vector>
#include <memory>
#include "BoardView.h"

namespace sch {

class BoardState {
public:
	BoardState(std::shared_ptr<BoardView>& board);
	~BoardState();

	void start();
	void end();
	void reset();

	void chessBoardClicked(BoardView::Square);
private:
	std::shared_ptr<BoardView> mBoard;
	std::vector<BoardView::Square> mSquares;
};

} /* namespace sch */

#endif /* CHESSGAME_H_ */
