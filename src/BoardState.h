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
#include <assert.h>
#include "ChessPiece.h"

namespace sch {

class BoardState {
public:
	BoardState();
	~BoardState();

	auto getWhitePieces() -> std::vector<std::shared_ptr<ChessPiece>> {
		return mWhitePieces;
	}

	auto getBlackPieces() -> std::vector<std::shared_ptr<ChessPiece>> {
		return mBlackPieces;
	}

	void move(std::shared_ptr<ChessPiece> ptr, BoardPosition pos);
	void capture(std::shared_ptr<ChessPiece> capturer, std::shared_ptr<ChessPiece> hostage);

	std::shared_ptr<ChessPiece> getPieceAt(BoardPosition pos) const;
	const BoardSquare& getSquareAt(BoardPosition pos) const;

	bool hasPieceAt(const BoardPosition& pos) const;
	bool isValidPosition(BoardPosition pos) const;

private:
	std::vector<std::shared_ptr<ChessPiece>> mWhitePieces;
	std::vector<std::shared_ptr<ChessPiece>> mBlackPieces;
	std::vector<std::shared_ptr<ChessPiece>> mWhiteHostages;
	std::vector<std::shared_ptr<ChessPiece>> mBlackHostages;
	std::vector<BoardSquare> mSquares;

	void initWhitePieces();
	void initBlackPieces();
	void initSquares();
	void bindPiecesToSquares();
	void reset();
};

} /* namespace sch */

#endif /* CHESSGAME_H_ */
