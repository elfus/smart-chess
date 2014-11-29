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

void BoardState::updateView() {
	// @todo erase previous frame
	mBoardView->setBoardState(shared_ptr<BoardState>(this));
}

void BoardState::initWhitePieces() {
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new King(BoardPosition(ONE, E), ImageType::WHITE_KING)));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Queen(BoardPosition(ONE, D), ImageType::WHITE_QUEEN)));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Knight(BoardPosition(ONE, B), ImageType::WHITE_KNIGHT)));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Knight(BoardPosition(ONE, G), ImageType::WHITE_KNIGHT)));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Rook(BoardPosition(ONE, A), ImageType::WHITE_ROOK)));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Rook(BoardPosition(ONE, H),ImageType::WHITE_ROOK)));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Bishop(BoardPosition(ONE, C), ImageType::WHITE_BISHOP)));
	mWhitePieces.push_back(shared_ptr<ChessPiece>(new Bishop(BoardPosition(ONE, F), ImageType::WHITE_BISHOP)));
	for(int i=0; i<MAX_COL; ++i)
		mWhitePieces.push_back(shared_ptr<ChessPiece>(new Pawn(BoardPosition(TWO, BoardColumn(i)), ImageType::WHITE_PAWN)));
}

void BoardState::initBlackPieces() {
	mBlackPieces.push_back(shared_ptr<ChessPiece>(new King(BoardPosition(EIGHT, E), ImageType::BLACK_KING)));
	mBlackPieces.push_back(shared_ptr<ChessPiece>(new Queen(BoardPosition(EIGHT, D), ImageType::BLACK_QUEEN)));
	mBlackPieces.push_back(shared_ptr<ChessPiece>(new Knight(BoardPosition(EIGHT, B), ImageType::BLACK_KNIGHT)));
	mBlackPieces.push_back(shared_ptr<ChessPiece>(new Knight(BoardPosition(EIGHT, G), ImageType::BLACK_KNIGHT)));
	mBlackPieces.push_back(shared_ptr<ChessPiece>(new Rook(BoardPosition(EIGHT, A), ImageType::BLACK_ROOK)));
	mBlackPieces.push_back(shared_ptr<ChessPiece>(new Rook(BoardPosition(EIGHT, H), ImageType::BLACK_ROOK)));
	mBlackPieces.push_back(shared_ptr<ChessPiece>(new Bishop(BoardPosition(EIGHT, C), ImageType::BLACK_BISHOP)));
	mBlackPieces.push_back(shared_ptr<ChessPiece>(new Bishop(BoardPosition(EIGHT, F), ImageType::BLACK_BISHOP)));
	for(int i=0; i<8; ++i)
		mBlackPieces.push_back(shared_ptr<ChessPiece>(new Pawn(BoardPosition(SEVEN, BoardColumn(i)), ImageType::BLACK_PAWN)));
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
	assert(!mWhitePieces.empty());
	assert(!mBlackPieces.empty());
}

} /* namespace sch */
