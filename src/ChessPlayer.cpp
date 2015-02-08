//===-- smart-chess/ChessPlayer.cpp -----------------------------*- C++ -*-===//
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
/// \file ChessPlayer.cpp
/// \brief
///
//===----------------------------------------------------------------------===//

#include "ChessPlayer.h"
#include "BoardState.h"

namespace sch {

ChessPlayer::ChessPlayer() {
	// TODO Auto-generated constructor stub

}

ChessPlayer::~ChessPlayer() {
	// TODO Auto-generated destructor stub
}

Human::Human() {

}

Human::~Human() {

}

Move Human::makeMove(BoardState state) {

}

Algorithm::Algorithm() {

}

Algorithm::~Algorithm() {

}

Move Algorithm::makeMove(BoardState state) {
	assert(state.getCurrentPlayer() == getColor());

	std::vector<std::shared_ptr<ChessPiece>> pieces;

	if(getColor() == PlayerColor::WHITE_PLAYER) {
		pieces = state.getWhitePieces();
	} else {
		pieces = state.getBlackPieces();
	}

	std::vector<BoardPosition> moves;
	std::shared_ptr<ChessPiece> the_piece {nullptr};

	for(auto piece : pieces) {
		moves = piece->getPossibleMoves(state);
		if(!moves.empty()) {
			the_piece = piece;
			break;
		}
	}

	return Move(the_piece, moves[0]);
}


} /* namespace sch */
