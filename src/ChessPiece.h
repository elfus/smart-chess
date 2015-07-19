//===-- smart-chess/ChessPiece.h --------------------------------*- C++ -*-===//
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
/// \file ChessPiece.h
/// \brief The class in charge of representing chess pieces.
///
//===----------------------------------------------------------------------===//

#ifndef CHESSPIECE_H_
#define CHESSPIECE_H_

#include "BoardView.h"
#include "Util.h"
#include <gdkmm.h>
#include <map>

namespace sch {

std::ostream& operator << (std::ostream& os, PieceType t);

class BoardState;

class ChessPiece {
public:
	ChessPiece(BoardPosition p, PieceType color);

	virtual ~ChessPiece();
	ChessPiece(const ChessPiece& rhs);
	ChessPiece& operator = (const ChessPiece& rhs);

	bool isWhite() const;
	bool isBlack() const;

	BoardPosition getBoardPosition() const { return mPosition; }
	PieceType getPieceType() const { return mPieceType; }

	void setSelected(bool s = true) { mSelected = s;}
	bool isSelected() const { return mSelected; }

	virtual std::vector<BoardPosition> getPossibleMoves(const BoardState& s) const = 0;
	bool canMove(const BoardState& s) const { return getPossibleMoves(s).size(); }

protected:
	PieceType mPieceType;
    BoardPosition mPosition;
	bool mSelected; //!< If selected by the user

	// Used internally to detect special conditions for each piece which
	// movement depends on whether the piece has been moved or not
	bool mMovedOnce;

	std::vector<BoardPosition> getHorizontalVerticalMoves(const BoardState& s) const;
	std::vector<BoardPosition> getDiagonalMoves(const BoardState& s) const;

	friend class BoardState; // BoardState accesses the setPosition method.
	void setPosition(BoardPosition pos) { mPosition = pos; mMovedOnce = true;}

private:
	void copy(const ChessPiece& rhs);
};

class King : public ChessPiece{
public:
	King(BoardPosition p, PieceType t) : ChessPiece(p, t){ }
	King(const King& k) : ChessPiece(k) {}

	virtual std::vector<BoardPosition> getPossibleMoves(const BoardState& s) const;
};

class Queen : public ChessPiece {
public:
	Queen(BoardPosition p, PieceType t) : ChessPiece(p, t) {}
	Queen(const Queen& k) : ChessPiece(k) {}

	virtual std::vector<BoardPosition> getPossibleMoves(const BoardState& s) const;
};

class Rook : public ChessPiece {
public:
	Rook(BoardPosition p, PieceType t) : ChessPiece(p, t) {}
	Rook(const Rook& k) : ChessPiece(k) {}

	virtual std::vector<BoardPosition> getPossibleMoves(const BoardState& s) const;
};

class Bishop : public ChessPiece {
public:
	Bishop(BoardPosition p, PieceType t) : ChessPiece(p, t) {}
	Bishop(const Bishop& k) : ChessPiece(k) {}

	virtual std::vector<BoardPosition> getPossibleMoves(const BoardState& s) const;
};

class Knight : public ChessPiece {
public:
	Knight(BoardPosition p, PieceType t) : ChessPiece(p, t) {}
	Knight(const Knight& k) : ChessPiece(k) {}

	virtual std::vector<BoardPosition> getPossibleMoves(const BoardState& s) const;
};

class Pawn : public ChessPiece {
public:
	Pawn(BoardPosition p, PieceType t) : ChessPiece(p, t) {}
	Pawn(const Pawn& k) : ChessPiece(k) {}

	virtual std::vector<BoardPosition> getPossibleMoves(const BoardState& s) const;
};

} /* namespace sch */

#endif /* CHESSPIECE_H_ */
