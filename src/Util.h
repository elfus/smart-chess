//===-- smart-chess/Util.h --------------------------------*- C++ -*-===//
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
/// \file Util.h
/// \brief Several helper types, structs and classes
///
//===----------------------------------------------------------------------===//

#ifndef UTIL_H_
#define UTIL_H_

#include <sstream>

namespace sch
{
enum Row {
	MAX_ROW = 8,
	ONE = 7,
	TWO = 6,
	THREE = 5,
	FOUR = 4,
	FIVE = 3,
	SIX = 2,
	SEVEN = 1,
	EIGHT = 0
};

enum Column {
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	MAX_COL
};

enum class PlayerColor {
	WHITE_PLAYER,
	BLACK_PLAYER
};

enum class PlayerType {
	HUMAN_PLAYER,
	ALGORITHM_PLAYER
};

struct BoardPosition {
	Row row;
	Column column;
	BoardPosition(Row r, Column c) : row(r), column(c) {}

	bool operator ==(const BoardPosition& that) const {
		return row == that.row && column == that.column;
	}
};

class ChessPiece;

struct BoardSquare {
	BoardSquare(BoardPosition pos) : mPosition(pos), piece(nullptr){}
	BoardPosition mPosition;

	void setPiece(std::shared_ptr<ChessPiece> p) { piece = p; }
	bool hasPiece() const { return piece.operator bool(); }
	std::shared_ptr<ChessPiece> getPiece() const{
		return piece;
	}

	std::shared_ptr<ChessPiece> removePiece() {
		std::shared_ptr<ChessPiece> tmp = piece;
		piece = nullptr;
		return tmp;
	}

private:
	std::shared_ptr<ChessPiece> piece;
};

std::ostream& operator <<(std::ostream& os, Row r);
std::ostream& operator <<(std::ostream& os, Column c);

class ChessException : public std::exception{
public:
	virtual const char * what() const noexcept { return mMsg.c_str(); }
protected:
	std::string mMsg;
};

class BoardPositionException : public ChessException {
public:
	BoardPositionException(BoardPosition p) : mPos(p) {
		std::stringstream ss;
		ss << "Invalid BoardPosition at row:" << mPos.row << ", columm: " << mPos.column;
		mMsg = ss.str();
	}
private:
	BoardPosition mPos;
};

}



#endif /* UTIL_H_ */
