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

using namespace std;

namespace sch {

BoardState::BoardState(std::shared_ptr<BoardView>& board)
: mBoardView(board), mSquares() {
	reset();
}

BoardState::~BoardState() {
	cerr << "ChessGame Destructor" << endl;
}

void BoardState::initWhitePieces() {
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new King));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Queen));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Knight));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Knight));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Rook));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Rook));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Bishop));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Bishop));
	for(int i=0; i<8; ++i)
		mWhitePieces.push_back(shared_ptr<ChessPiece>(new Pawn));
}

void BoardState::initBlackPieces() {
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new King));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Queen));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Knight));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Knight));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Rook));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Rook));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Bishop));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Bishop));
	for(int i=0; i<8; ++i)
		mWhitePieces.push_back(shared_ptr<ChessPiece>(new Pawn));
}

void BoardState::initSquares() {
	for(int i = 0; i < BoardColumn::MAX_COL; ++i) {
		for(int j = 0; j < BoardRow::MAX_ROW; ++j) {
			mSquares.push_back(BoardSquare(BoardRow(j),BoardColumn(i)));
		}
	}
}


void BoardState::start() {

}

void BoardState::end() {

}

void BoardState::reset() {
	mSquares.clear();
	initSquares();
	mWhitePieces.clear();
	initWhitePieces();
	mBlackPieces.clear();
	initBlackPieces();
}

} /* namespace sch */
