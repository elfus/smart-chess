//===-- smart-chess/ChessPiece.cpp ------------------------------*- C++ -*-===//
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
/// \file ChessPiece.cpp
/// \brief The class in charge of representing chess pieces.
///
//===----------------------------------------------------------------------===//

#include "ChessPiece.h"
#include "BoardState.h"
#include <vector>

using namespace std;

namespace sch {

std::ostream& operator << (std::ostream& os, PieceType t)
{
	switch(t) {
	case PieceType::WHITE_KING : os << "WHITE_KING"; break;
	case PieceType::WHITE_QUEEN : os << "WHITE_QUEEN"; break;
	case PieceType::WHITE_BISHOP : os << "WHITE_BISHOP"; break;
	case PieceType::WHITE_ROOK : os << "WHITE_ROOK"; break;
	case PieceType::WHITE_KNIGHT : os << "WHITE_KNIGHT"; break;
	case PieceType::WHITE_PAWN : os << "WHITE_PAWN"; break;

	case PieceType::BLACK_KING : os << "BLACK_KING"; break;
	case PieceType::BLACK_QUEEN : os << "BLACK_QUEEN"; break;
	case PieceType::BLACK_BISHOP : os << "BLACK_BISHOP"; break;
	case PieceType::BLACK_ROOK : os << "BLACK_ROOK"; break;
	case PieceType::BLACK_KNIGHT : os << "BLACK_KNIGHT"; break;
	case PieceType::BLACK_PAWN : os << "BLACK_PAWN"; break;
	case PieceType::UNDEFINED: os << "UNDEFINED"; break;
	}
	return os;
}

    ChessPiece::ChessPiece(BoardPosition p, PieceType color)
            : mPieceType(color),  mPosition(p),
              mSelected(false), mMovedOnce(false) {

    }

ChessPiece::~ChessPiece() {
	// TODO Auto-generated destructor stub
}

ChessPiece::ChessPiece(const ChessPiece& rhs) {
	copy(rhs);
}

ChessPiece& ChessPiece::operator = (const ChessPiece& rhs) {
	copy(rhs);
	return *this;
}

void ChessPiece::copy(const ChessPiece& rhs) {
	mPieceType = rhs.mPieceType;
	mPosition = rhs.mPosition;
	mSelected = rhs.mSelected;
	mMovedOnce = rhs.mMovedOnce;
}

bool ChessPiece::isWhite() const{
	switch(mPieceType) {
	case PieceType::WHITE_KING:
	case PieceType::WHITE_QUEEN:
	case PieceType::WHITE_BISHOP:
	case PieceType::WHITE_KNIGHT:
	case PieceType::WHITE_ROOK:
	case PieceType::WHITE_PAWN:
		return true;
	default:
		return false;
	}
}

bool ChessPiece::isBlack() const{
	return !isWhite();
}

std::vector<BoardPosition> ChessPiece::getHorizontalVerticalMoves(const BoardState& s) const {
	vector<BoardPosition> moves;
	BoardPosition current = getBoardPosition();

	for(int r = current.row-1; r >= 0; --r) {
		BoardPosition p(Row(r), current.column);
		if(s.hasPieceAt(p)) {
			if(isWhite() != s.getPieceAt(p)->isWhite())
				moves.push_back(p);
			break;
		}
		moves.push_back(p);
	}

	for(int r = current.row+1; r < Row::MAX_ROW; ++r) {
		BoardPosition p(Row(r), current.column);
		if(s.hasPieceAt(p)) {
			if(isWhite() != s.getPieceAt(p)->isWhite())
				moves.push_back(p);
			break;
		}
		moves.push_back(p);
	}

	for(int c = current.column-1; c >= 0; --c) {
		BoardPosition p(current.row, Column(c));
		if(s.hasPieceAt(p)) {
			if(isWhite() != s.getPieceAt(p)->isWhite())
				moves.push_back(p);
			break;
		}
		moves.push_back(p);
	}

	for(int c = current.column+1; c < Column::MAX_COL; ++c) {
		BoardPosition p(current.row, Column(c));
		if(s.hasPieceAt(p)) {
			if(isWhite() != s.getPieceAt(p)->isWhite())
				moves.push_back(p);
			break;
		}
		moves.push_back(p);
	}
	return moves;
}

std::vector<BoardPosition> ChessPiece::getDiagonalMoves(const BoardState& s) const {
	vector<BoardPosition> moves;
	BoardPosition current = getBoardPosition();

	for(int r = current.row-1, c = current.column-1; r >= 0 && c >=0; --r, --c) {
		BoardPosition p(static_cast<Row>(r), static_cast<Column>(c));
		if(s.hasPieceAt(p)) {
			if(isWhite() != s.getPieceAt(p)->isWhite())
				moves.push_back(p);
			break;
		}
		moves.push_back(p);
	}

	for(int r = current.row+1, c = current.column-1;
			r < Row::MAX_ROW && c >= 0; ++r, --c) {
		BoardPosition p(static_cast<Row>(r), static_cast<Column>(c));
		if(s.hasPieceAt(p)) {
			if(isWhite() != s.getPieceAt(p)->isWhite())
				moves.push_back(p);
			break;
		}
		moves.push_back(p);
	}

	for(int r = current.row-1, c = current.column+1;
			r >= 0 && c < Column::MAX_COL; --r,  ++c) {
		BoardPosition p(static_cast<Row>(r), static_cast<Column>(c));
		if(s.hasPieceAt(p)) {
			if(isWhite() != s.getPieceAt(p)->isWhite())
				moves.push_back(p);
			break;
		}
		moves.push_back(p);
	}

	for(int r = current.row+1, c = current.column+1;
			r < Row::MAX_ROW && c < Column::MAX_COL; ++r,  ++c) {
		BoardPosition p(static_cast<Row>(r), static_cast<Column>(c));
		if(s.hasPieceAt(p)) {
			if(isWhite() != s.getPieceAt(p)->isWhite())
				moves.push_back(p);
			break;
		}
		moves.push_back(p);
	}
	return moves;
}

vector<BoardPosition> King::getPossibleMoves(const BoardState& s) const {
	vector<BoardPosition> moves;
	BoardPosition p0 = getBoardPosition();

	BoardPosition p1(Row(p0.row - 1), Column(p0.column - 1));
	BoardPosition p2(Row(p0.row - 1), Column(p0.column));
	BoardPosition p3(Row(p0.row - 1), Column(p0.column + 1));
	BoardPosition p4(Row(p0.row), Column(p0.column - 1));
	BoardPosition p5(Row(p0.row), Column(p0.column + 1));
	BoardPosition p6(Row(p0.row + 1), Column(p0.column - 1));
	BoardPosition p7(Row(p0.row + 1), Column(p0.column));
	BoardPosition p8(Row(p0.row + 1), Column(p0.column + 1));

	if(s.isValidPosition(p1)) {
		if(!s.hasPieceAt(p1) || (s.hasPieceAt(p1) && isWhite() != s.getPieceAt(p1)->isWhite()))
			moves.push_back(p1);
	}

	if(s.isValidPosition(p2)) {
		if(!s.hasPieceAt(p2) || (s.hasPieceAt(p2) && isWhite() != s.getPieceAt(p2)->isWhite()))
			moves.push_back(p2);
	}

	if(s.isValidPosition(p3)) {
		if(!s.hasPieceAt(p3) || (s.hasPieceAt(p3) && isWhite() != s.getPieceAt(p3)->isWhite()))
			moves.push_back(p3);
	}

	if(s.isValidPosition(p4)) {
		if(!s.hasPieceAt(p4) || (s.hasPieceAt(p4) && isWhite() != s.getPieceAt(p4)->isWhite()))
			moves.push_back(p4);
	}

	if(s.isValidPosition(p5)) {
		if(!s.hasPieceAt(p5) || (s.hasPieceAt(p5) && isWhite() != s.getPieceAt(p5)->isWhite()))
			moves.push_back(p5);
	}

	if(s.isValidPosition(p6)) {
		if(!s.hasPieceAt(p6) || (s.hasPieceAt(p6) && isWhite() != s.getPieceAt(p6)->isWhite()))
			moves.push_back(p6);
	}

	if(s.isValidPosition(p7)) {
		if(!s.hasPieceAt(p7) || (s.hasPieceAt(p7) && isWhite() != s.getPieceAt(p7)->isWhite()))
			moves.push_back(p7);
	}

	if(s.isValidPosition(p8)) {
		if(!s.hasPieceAt(p8) || (s.hasPieceAt(p8) && isWhite() != s.getPieceAt(p8)->isWhite()))
			moves.push_back(p8);
	}

	return moves;
}

vector<BoardPosition> Queen::getPossibleMoves(const BoardState& s) const {
	vector<BoardPosition> moves_1 = getHorizontalVerticalMoves(s);
	vector<BoardPosition> moves_2 = getDiagonalMoves(s);
	vector<BoardPosition> moves;
	moves.insert(moves.end(), moves_1.begin(), moves_1.end());
	moves.insert(moves.end(), moves_2.begin(), moves_2.end());
	return moves;
}

vector<BoardPosition> Rook::getPossibleMoves(const BoardState& s) const {
	vector<BoardPosition> moves = getHorizontalVerticalMoves(s);
	return moves;
}

vector<BoardPosition> Bishop::getPossibleMoves(const BoardState& s) const {
	vector<BoardPosition> moves = getDiagonalMoves(s);
	return moves;
}

vector<BoardPosition> Knight::getPossibleMoves(const BoardState& s) const {
	vector<BoardPosition> moves;
	BoardPosition p0 = getBoardPosition();

	BoardPosition p1(Row(p0.row - 2), Column(p0.column - 1));
	BoardPosition p2(Row(p0.row - 2), Column(p0.column + 1));
	BoardPosition p3(Row(p0.row - 1), Column(p0.column - 2));
	BoardPosition p4(Row(p0.row - 1), Column(p0.column + 2));
	BoardPosition p5(Row(p0.row + 1), Column(p0.column - 2));
	BoardPosition p6(Row(p0.row + 1), Column(p0.column + 2));
	BoardPosition p7(Row(p0.row + 2), Column(p0.column - 1));
	BoardPosition p8(Row(p0.row + 2), Column(p0.column + 1));

	if(s.isValidPosition(p1)) {
		if(!s.hasPieceAt(p1) || (s.hasPieceAt(p1) && isWhite() != s.getPieceAt(p1)->isWhite()))
			moves.push_back(p1);
	}

	if(s.isValidPosition(p2)) {
		if(!s.hasPieceAt(p2) || (s.hasPieceAt(p2) && isWhite() != s.getPieceAt(p2)->isWhite()))
			moves.push_back(p2);
	}

	if(s.isValidPosition(p3)) {
		if(!s.hasPieceAt(p3) || (s.hasPieceAt(p3) && isWhite() != s.getPieceAt(p3)->isWhite()))
			moves.push_back(p3);
	}

	if(s.isValidPosition(p4)) {
		if(!s.hasPieceAt(p4) || (s.hasPieceAt(p4) && isWhite() != s.getPieceAt(p4)->isWhite()))
			moves.push_back(p4);
	}

	if(s.isValidPosition(p5)) {
		if(!s.hasPieceAt(p5) || (s.hasPieceAt(p5) && isWhite() != s.getPieceAt(p5)->isWhite()))
			moves.push_back(p5);
	}

	if(s.isValidPosition(p6)) {
		if(!s.hasPieceAt(p6) || (s.hasPieceAt(p6) && isWhite() != s.getPieceAt(p6)->isWhite()))
			moves.push_back(p6);
	}

	if(s.isValidPosition(p7)) {
		if(!s.hasPieceAt(p7) || (s.hasPieceAt(p7) && isWhite() != s.getPieceAt(p7)->isWhite()))
			moves.push_back(p7);
	}

	if(s.isValidPosition(p8)) {
		if(!s.hasPieceAt(p8) || (s.hasPieceAt(p8) && isWhite() != s.getPieceAt(p8)->isWhite()))
			moves.push_back(p8);
	}

	return moves;
}

vector<BoardPosition> Pawn::getPossibleMoves(const BoardState& s) const {
	vector<BoardPosition> moves;
	int direction = 0;
	// @note For the moment we assume white player is always at the bottom.
	if(isWhite())
		direction = -1;
	else
		direction = 1;
	BoardPosition pos = getBoardPosition();

	BoardPosition pos_1(Row(pos.row + direction), pos.column);
	if(s.hasPieceAt(pos_1) == false) {
		moves.push_back(pos_1);

		if(!mMovedOnce) {
			BoardPosition pos_2(Row(pos.row + (direction*2)), pos.column);
			if(s.hasPieceAt(pos_2) == false)
				moves.push_back(pos_2);
		}
	}

	BoardPosition pos_3(Row(pos.row + direction), Column(pos.column-1));
	if(s.hasPieceAt(pos_3) && isWhite() != s.getPieceAt(pos_3)->isWhite())
		moves.push_back(pos_3);

	BoardPosition pos_4(Row(pos.row + direction), Column(pos.column+1));
	if(s.hasPieceAt(pos_4) && isWhite() != s.getPieceAt(pos_4)->isWhite())
		moves.push_back(pos_4);

	return moves;
}


} /* namespace sch */
