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
#include <iostream>

using namespace std;

namespace sch {

BoardState::BoardState()
: mWhitePieces(), mBlackPieces(), mWhiteHostages(), mBlackHostages(),
  mSquares(), mCurrentPlayer(ChessPlayer::Color::WHITE), mGameInProgress(false),
  mSelectedPiece(nullptr) {
	reset();
	cout << "BoardState Constructor" << endl;
}

BoardState::BoardState(const BoardState& rhs)
: mCurrentPlayer(rhs.mCurrentPlayer)
{
	copy(rhs);
	clog << "BoardState COPY Constructor" << endl;
}

BoardState::BoardState(BoardState&& rhs)
        : mCurrentPlayer{rhs.mCurrentPlayer}, mGameInProgress(rhs.mGameInProgress)
{
	mWhitePieces.swap(rhs.mWhitePieces);

	mBlackPieces.swap(rhs.mBlackPieces);

	mWhiteHostages.swap(rhs.mWhiteHostages);

	mBlackHostages.swap(rhs.mBlackHostages);

	mSquares.swap(rhs.mSquares);

	assert(mWhitePieces.size() == 16);
	assert(mBlackPieces.size() == 16);
	clog << "BoardState MOVE Constructor" << endl;
}

BoardState& BoardState::operator = (const BoardState& rhs)
{
	copy(rhs);
	clog << "BoardState ASSIGNMENT OPERATOR" << endl;
	return *this;
}

std::shared_ptr<ChessPiece>  BoardState::copyPiece(std::shared_ptr<ChessPiece> piece) {
	std::shared_ptr<ChessPiece> ptr {nullptr};
	switch(piece->getPieceType()) {
	case PieceType::WHITE_KING:
	case PieceType::BLACK_KING:
		ptr = make_shared<King>(BoardPosition(ONE, E), PieceType::WHITE_KING);
		break;
	case PieceType::WHITE_QUEEN:
	case PieceType::BLACK_QUEEN:
		ptr = make_shared<Queen>(BoardPosition(ONE, E), PieceType::WHITE_KING);
		break;
	case PieceType::WHITE_KNIGHT:
	case PieceType::BLACK_KNIGHT:
		ptr = make_shared<Knight>(BoardPosition(ONE, E), PieceType::WHITE_KING);
		break;
	case PieceType::WHITE_ROOK:
	case PieceType::BLACK_ROOK:
		ptr = make_shared<Rook>(BoardPosition(ONE, E), PieceType::WHITE_KING);
		break;
	case PieceType::WHITE_BISHOP:
	case PieceType::BLACK_BISHOP:
		ptr = make_shared<Bishop>(BoardPosition(ONE, E), PieceType::WHITE_KING);
		break;
	case PieceType::WHITE_PAWN:
	case PieceType::BLACK_PAWN:
		ptr = make_shared<Pawn>(BoardPosition(ONE, E), PieceType::WHITE_KING);
		break;
	}
	*ptr = *piece;
	return ptr;
}

void BoardState::copy(const BoardState& rhs) {
	mCurrentPlayer = rhs.mCurrentPlayer;
    mGameInProgress = rhs.mGameInProgress;

	mWhitePieces.clear();
	for(auto piece : rhs.mWhitePieces)
		mWhitePieces.push_back(copyPiece(piece));

	mBlackPieces.clear();
	for(auto piece : rhs.mBlackPieces)
		mBlackPieces.push_back(copyPiece(piece));

	mWhiteHostages.clear();
	for(auto piece : rhs.mWhiteHostages)
		mWhiteHostages.push_back(copyPiece(piece));

	mBlackHostages.clear();
	for(auto piece : rhs.mBlackHostages)
		mBlackHostages.push_back(copyPiece(piece));

	mSquares.clear();
	for(auto sq : rhs.mSquares)
		mSquares.push_back(BoardSquare(sq));
}

BoardState::~BoardState() {
	clog << "BoardState Destructor" << endl;
}

void BoardState::initWhitePieces() {
	mWhitePieces.push_back(make_shared<King>(BoardPosition(ONE, E), PieceType::WHITE_KING));
	mWhitePieces.push_back(make_shared<Queen>(BoardPosition(ONE, D), PieceType::WHITE_QUEEN));
	mWhitePieces.push_back(make_shared<Knight>(BoardPosition(ONE, B), PieceType::WHITE_KNIGHT));
	mWhitePieces.push_back(make_shared<Knight>(BoardPosition(ONE, G), PieceType::WHITE_KNIGHT));
	mWhitePieces.push_back(make_shared<Rook>(BoardPosition(ONE, A), PieceType::WHITE_ROOK));
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
	// Used for special cases
	mSquares.push_back(BoardSquare(BoardPosition(Row::MAX_ROW, Column::MAX_COL)));
}


void BoardState::bindPiecesToSquares()
{
	for(auto p : mWhitePieces) {
		for(auto& s : mSquares) {
			if(s.getBoardPosition() == p->getBoardPosition())
				s.setPiece(p);
		}
	}

	for(auto p : mBlackPieces) {
		for(auto& s : mSquares) {
			if(s.getBoardPosition() == p->getBoardPosition())
				s.setPiece(p);
		}
	}
}

void BoardState::reset() {
	mGameInProgress = false;
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

/**
 * Checks whether the BoardSqare @b sq is valid.
 *
 * This is done by comparing @b sq with all the BoardSqaures in the current
 * BoardState.
 *
 * @param[in] sq The BoardSquare we want to check.
 *
 * @return True when the BoardSquare is valid and inside the valid BoardSquares
 * in a chess board.
 */
bool BoardState::isValidPosition(const BoardSquare& sq) const {
	sch::BoardPosition board_position = sq.getBoardPosition();
	for(auto& s : mSquares) {
		if (s.getBoardPosition() == board_position)
			return true;
	}
	return false;
}

bool BoardState::selectPieceAt(const BoardSquare& s) {
	if(mSelectedPiece) mSelectedPiece->setSelected(false);

	if(hasPieceAt(s)) {

		mSelectedPiece = getPieceAt(s);
		mSelectedPiece->setSelected();
		return true;
	}
	return false;
}

void BoardState::unselectPiece() {
	if(mSelectedPiece) {
		mSelectedPiece->setSelected(false);
		mSelectedPiece.reset();
	}
}

shared_ptr<ChessPiece> BoardState::getPieceAt(BoardSquare sq) const
{
	shared_ptr<ChessPiece> piece(nullptr);
	try {
		piece = getSquareAt(sq.getBoardPosition()).getPiece();
	} catch (const BoardPositionException& e) {
		cerr << "WARNING[BoardState::getPieceAt]: " << e.what() << endl;
	}
	return piece;
}

bool BoardState::hasPieceAt(const BoardSquare& s) const {
	try {
		return getSquareAt(s.getBoardPosition()).hasPiece();
	} catch(const BoardPositionException& e) {
		cerr << "WARNING: " << e.what() << endl;
	}
	return false;
}

const BoardSquare& BoardState::getSquareAt(BoardPosition pos) const
{
	for(auto& s : mSquares) {
		if(s.getBoardPosition() == pos)
			return s;
	}

	throw BoardPositionException(pos);
}

BoardSquare& BoardState::getSquareAt(BoardPosition pos)
{
	for(auto& s : mSquares) {
		if(s.getBoardPosition() == pos)
			return s;
	}

	throw BoardPositionException(pos);
}

bool BoardState::isCheckmate() const
{
	assert(false && "Implement this method.");
	return false;
}


bool BoardState::isStalemate() const
{
	assert(false && "Implement this method.");
	return false;
}

std::vector<std::shared_ptr<ChessPiece>> BoardState::getPiecesThatCanBeMoved() const
{
	std::vector<std::shared_ptr<ChessPiece>> moves;

	if(getCurrentPlayer() == ChessPlayer::Color::WHITE) {
		for(auto p : mWhitePieces)
			if(p->canMove(*this))
				moves.push_back(p);
	} else {
		for(auto p : mBlackPieces)
			if(p->canMove(*this))
				moves.push_back(p);
	}

	return moves;
}

	void BoardState::capture(shared_ptr<ChessPiece>& hostage)
	{
		if(hostage->isWhite()) {
			auto it =find_if(mWhitePieces.begin(), mWhitePieces.end(), [&](const shared_ptr<ChessPiece>& p) {
					return p->getBoardPosition() == hostage->getBoardPosition();
					});
			mWhitePieces.erase(it);
			mWhiteHostages.push_back(hostage);
		}
		else {
			auto it = find_if(mBlackPieces.begin(), mBlackPieces.end(), [&](const shared_ptr<ChessPiece>& p) {
							return p->getBoardPosition() == hostage->getBoardPosition();
							});
			mBlackPieces.erase(it);
			mBlackHostages.push_back(hostage);
		}
	}

	void BoardState::moveTo(BoardPosition pos) {
		if(mSelectedPiece) {
			BoardSquare& old = getSquareAt(mSelectedPiece->getBoardPosition());
			auto old_piece = old.removePiece();

			assert(old_piece->getBoardPosition() == mSelectedPiece->getBoardPosition());

			mSelectedPiece->setPosition(pos);
			mSelectedPiece->setSelected(false);

			BoardSquare& sq = getSquareAt(pos);
			// Check if we are capturing an enemy piece
			if(sq.hasPiece() && sq.getPiece()->getColor() != mSelectedPiece->getColor()) {
				auto captured_piece = sq.removePiece();
				capture(captured_piece);
			}
			sq.setPiece(mSelectedPiece);

			mSelectedPiece.reset();
		}
	}

    void BoardState::switchPlayer() {
        if(mCurrentPlayer == ChessPlayer::Color::WHITE)
            mCurrentPlayer = ChessPlayer::Color::BLACK;
        else if(mCurrentPlayer == ChessPlayer::Color::BLACK)
            mCurrentPlayer = ChessPlayer::Color::WHITE;

    }

    bool BoardState::isGameInProgress() {
        return mGameInProgress;
    }

    std::shared_ptr<ChessPiece> BoardState::getSelectedPiece() {
    	return mSelectedPiece;
    }
} /* namespace sch */
