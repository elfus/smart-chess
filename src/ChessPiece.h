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

enum class PieceType {
	WHITE_KING,
	BLACK_KING,
	WHITE_QUEEN,
	BLACK_QUEEN,
	WHITE_ROOK,
	BLACK_ROOK,
	WHITE_BISHOP,
	BLACK_BISHOP,
	WHITE_KNIGHT,
	BLACK_KNIGHT,
	WHITE_PAWN,
	BLACK_PAWN,
	UNDEFINED
};

std::ostream& operator << (std::ostream& os, PieceType t);

class BoardState;

class ChessPiece {
public:
	ChessPiece(BoardPosition p, PieceType color)
	: mPieceType(color),  mImage(images[mPieceType]), mPosition(p),
	  mSelected(false){}
	virtual ~ChessPiece();

	bool isWhite();
	bool isBlack();
	Glib::RefPtr<Gdk::Pixbuf> getImage() const { return mImage; }
	void setPosition(BoardPosition pos) { mPosition = pos; }
	BoardPosition getPosition() const { return mPosition; }
	PieceType getPieceType() const { return mPieceType; }

	void setSelected(bool s = true) { mSelected = s;}
	bool isSelected() const { return mSelected; }

	virtual std::vector<BoardPosition> getPossibleMoves(BoardState s) const = 0;

	static void loadImages();
protected:
	static std::map<PieceType, Glib::RefPtr<Gdk::Pixbuf>> images;

	PieceType mPieceType;
	Glib::RefPtr<Gdk::Pixbuf> mImage;
	BoardPosition mPosition;
	bool mSelected; // Selected by the user
};

class King : public ChessPiece{
public:
	King(BoardPosition p, PieceType t) : ChessPiece(p, t){ }

	virtual std::vector<BoardPosition> getPossibleMoves(BoardState s) const;
};

class Queen : public ChessPiece {
public:
	Queen(BoardPosition p, PieceType t) : ChessPiece(p, t) {}

	virtual std::vector<BoardPosition> getPossibleMoves(BoardState s) const;
};

class Rook : public ChessPiece {
public:
	Rook(BoardPosition p, PieceType t) : ChessPiece(p, t) {}

	virtual std::vector<BoardPosition> getPossibleMoves(BoardState s) const;
};

class Bishop : public ChessPiece {
public:
	Bishop(BoardPosition p, PieceType t) : ChessPiece(p, t) {}

	virtual std::vector<BoardPosition> getPossibleMoves(BoardState s) const;
};

class Knight : public ChessPiece {
public:
	Knight(BoardPosition p, PieceType t) : ChessPiece(p, t) {}

	virtual std::vector<BoardPosition> getPossibleMoves(BoardState s) const;
};

class Pawn : public ChessPiece {
public:
	Pawn(BoardPosition p, PieceType t) : ChessPiece(p, t) {}

	virtual std::vector<BoardPosition> getPossibleMoves(BoardState s) const;
};

} /* namespace sch */

#endif /* CHESSPIECE_H_ */
