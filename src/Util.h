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
#include <memory>

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

struct BoardPosition {
	Row row;
	Column column;
	BoardPosition(Row r, Column c) : row(r), column(c) {}
	BoardPosition(const BoardPosition& rhs) : row(rhs.row), column(rhs.column) {}
	BoardPosition() : row(Row::MAX_ROW), column(Column::MAX_COL) {}
	bool operator ==(const BoardPosition& that) const {
		return row == that.row && column == that.column;
	}
	bool isValid() const {
		return row != Row::MAX_ROW && column != Column::MAX_COL;
	}
};

class ChessPiece;

struct BoardSquare {
	BoardSquare(BoardPosition pos) : mPosition(pos), piece(nullptr){}
	BoardSquare(const BoardSquare& rhs) : mPosition(rhs.mPosition),
			piece(rhs.piece) {}

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

struct Move {
	std::shared_ptr<ChessPiece> piece; // The piece we want to move
	BoardPosition final_pos; // The final position where the piece will be moved
	Move(std::shared_ptr<ChessPiece> p, BoardPosition pos) : piece(p), final_pos(pos) {}
};

std::ostream& operator <<(std::ostream& os, Row r);
std::ostream& operator <<(std::ostream& os, Column c);
std::ostream& operator <<(std::ostream& os, Move m);

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

    /**
     * Helper class to be used in a range based for. It will iterate from 0 to
     * N-1 element. Where N is the parameter used to construct a IntRange.
     */
    class IntRange {
    public:
        class Iterator {
        friend class IntRange;
        public:
            int operator*() const { return mValue; }
            const Iterator& operator++() {++mValue; return *this;}
            Iterator operator++(int) { Iterator copy(*this); ++mValue; return copy;}

            bool operator==(const Iterator& rhs) { return mValue == rhs.mValue;}
            bool operator!=(const Iterator& rhs) { return mValue != rhs.mValue;}

        protected:
            Iterator(int value) : mValue(value) {}

        private:
            int mValue;
        };
        IntRange(int N) : mBegin(0), mEnd(N) {}

        Iterator begin() { return mBegin;};
        Iterator end() {return mEnd;};

    private:
        Iterator mBegin;
        Iterator mEnd;
    };

}



#endif /* UTIL_H_ */
