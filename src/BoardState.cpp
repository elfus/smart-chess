//===-- smart-chess/BoardState.cpp -------------------------------*- C++ -*-===//
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
/// \file BoardState.cpp
/// \brief The class representing a single game or match.
///
//===----------------------------------------------------------------------===//

#include "BoardState.h"
#include "ChessPiece.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace sch {

BoardState::BoardState()
: mWhitePieces(), mBlackPieces(), mSquares() {
	reset();
	cout << "BoardState Constructor" << endl;
}

BoardState::~BoardState() {
	cout << "BoardState Destructor" << endl;
}

void BoardState::initWhitePieces() {
	mWhitePieces.push_back(make_shared<King>(BoardPosition(ONE, E), PieceType::WHITE_KING));
	mWhitePieces.push_back(make_shared<Queen>(BoardPosition(ONE, D), PieceType::WHITE_QUEEN));
	mWhitePieces.push_back(make_shared<Knight>(BoardPosition(ONE, B), PieceType::WHITE_KNIGHT));
	mWhitePieces.push_back(make_shared<Knight>(BoardPosition(ONE, G), PieceType::WHITE_KNIGHT));
	mWhitePieces.push_back(make_shared<Rook>(BoardPosition(FOUR, D), PieceType::WHITE_ROOK));
	mWhitePieces.push_back(make_shared<Rook>(BoardPosition(ONE, H),PieceType::WHITE_ROOK));
	mWhitePieces.push_back(make_shared<Bishop>(BoardPosition(ONE, C), PieceType::WHITE_BISHOP));
	mWhitePieces.push_back(make_shared<Bishop>(BoardPosition(ONE, F), PieceType::WHITE_BISHOP));

	for(int i=0; i<MAX_COL; ++i)
		mWhitePieces.push_back(make_shared<Pawn>(BoardPosition(TWO, Column(i)), PieceType::WHITE_PAWN));
}

void BoardState::initBlackPieces() {
	mBlackPieces.push_back(make_shared<King>(BoardPosition(EIGHT, E), PieceType::BLACK_KING));
	mBlackPieces.push_back(make_shared<Queen>(BoardPosition(EIGHT, D), PieceType::BLACK_QUEEN));
	mBlackPieces.push_back(make_shared<Knight>(BoardPosition(EIGHT, B), PieceType::BLACK_KNIGHT));
	mBlackPieces.push_back(make_shared<Knight>(BoardPosition(EIGHT, G), PieceType::BLACK_KNIGHT));
	mBlackPieces.push_back(make_shared<Rook>(BoardPosition(EIGHT, A), PieceType::BLACK_ROOK));
	mBlackPieces.push_back(make_shared<Rook>(BoardPosition(EIGHT, H), PieceType::BLACK_ROOK));
	mBlackPieces.push_back(make_shared<Bishop>(BoardPosition(EIGHT, C), PieceType::BLACK_BISHOP));
	mBlackPieces.push_back(make_shared<Bishop>(BoardPosition(EIGHT, F), PieceType::BLACK_BISHOP));
	for(int i=0; i<8; ++i)
		mBlackPieces.push_back(make_shared<Pawn>(BoardPosition(SEVEN, Column(i)), PieceType::BLACK_PAWN));
}

void BoardState::initSquares() {
	for(int i = 0; i < Column::MAX_COL; ++i) {
		for(int j = 0; j < Row::MAX_ROW; ++j) {
			mSquares.push_back(BoardSquare(BoardPosition(Row(j),Column(i))));
		}
	}
}


void BoardState::bindPiecesToSquares()
{
	for(auto p : mWhitePieces) {
		for(auto& s : mSquares) {
			if(s.mPosition == p->getPosition())
				s.setPiece(p);
		}
	}

	for(auto p : mBlackPieces) {
		for(auto& s : mSquares) {
			if(s.mPosition == p->getPosition())
				s.setPiece(p);
		}
	}
}

void BoardState::reset() {
	mSquares.clear();
	initSquares();
	mWhitePieces.clear();
	initWhitePieces();
	mBlackPieces.clear();
	initBlackPieces();
	bindPiecesToSquares();
	assert(!mWhitePieces.empty());
	assert(!mBlackPieces.empty());
}

bool BoardState::isValidPosition(BoardPosition pos)
{
	for(auto& s : mSquares) {
		if(s.mPosition == pos)
			return true;
	}
	return false;
}

shared_ptr<ChessPiece> BoardState::getPieceAt(BoardPosition pos)
{
	shared_ptr<ChessPiece> piece(nullptr);
	try {
		piece = getSquareAt(pos).getPiece();
	} catch (const BoardPositionException& e) {
		cerr << "WARNING[BoardState::getPieceAt]: " << e.what() << endl;
	}
	return piece;
}

bool BoardState::hasPieceAt(BoardPosition pos)
{
	try {
		if(getSquareAt(pos).hasPiece())
			return true;
	} catch(const BoardPositionException& e) {
		cerr << "WARNING: " << e.what() << endl;
	}
	return false;
}

BoardSquare BoardState::getSquareAt(BoardPosition pos)
{
	for(auto& s : mSquares) {
		if(s.mPosition == pos)
			return s;
	}
	throw BoardPositionException(pos);
}

} /* namespace sch */
