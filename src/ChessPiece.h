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

enum class ImageType {
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

class ChessPiece {
public:
	ChessPiece(BoardPosition p, ImageType color)
	: mImageType(color),  mImage(images[mImageType]), mPosition(p) {}
	virtual ~ChessPiece();

	bool isWhite() {
		switch(mImageType) {
		case ImageType::WHITE_KING:
		case ImageType::WHITE_QUEEN:
		case ImageType::WHITE_BISHOP:
		case ImageType::WHITE_KNIGHT:
		case ImageType::WHITE_ROOK:
		case ImageType::WHITE_PAWN:
			return true;
		default:
			return false;
		}
	}
	bool isBlack() { return !isWhite(); }
	Glib::RefPtr<Gdk::Pixbuf> getImage() const { return mImage; }
	void setPosition(BoardPosition pos) { mPosition = pos; }
	BoardPosition getPosition() const { return mPosition; }

	static void loadImages();
protected:
	static std::map<ImageType, Glib::RefPtr<Gdk::Pixbuf>> images;

	ImageType mImageType;
	Glib::RefPtr<Gdk::Pixbuf> mImage;
	BoardPosition mPosition;
};

class King : public ChessPiece{
public:
	King(BoardPosition p, ImageType t) : ChessPiece(p, t){ }
};

class Queen : public ChessPiece {
public:
	Queen(BoardPosition p, ImageType t) : ChessPiece(p, t) {}
};

class Rook : public ChessPiece {
public:
	Rook(BoardPosition p, ImageType t) : ChessPiece(p, t) {}
};

class Bishop : public ChessPiece {
public:
	Bishop(BoardPosition p, ImageType t) : ChessPiece(p, t) {}
};

class Knight : public ChessPiece {
public:
	Knight(BoardPosition p, ImageType t) : ChessPiece(p, t) {}
};

class Pawn : public ChessPiece {
public:
	Pawn(BoardPosition p, ImageType t) : ChessPiece(p, t) {}
};

} /* namespace sch */

#endif /* CHESSPIECE_H_ */
