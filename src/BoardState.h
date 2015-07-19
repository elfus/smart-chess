//===-- smart-chess/BoardState.h --------------------------------*- C++ -*-===//
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
/// \file BoardState.h
/// \brief The class representing a single game or match.
///
//===----------------------------------------------------------------------===//

#ifndef CHESSGAME_H_
#define CHESSGAME_H_

#include <vector>
#include <memory>
#include <assert.h>
#include "ChessPiece.h"

namespace sch {

class BoardState {
	friend class BoardController;
public:
	BoardState();
	BoardState(const BoardState& rhs);
	BoardState(BoardState&& rhs);
	BoardState& operator = (const BoardState& rhs);

	~BoardState();

	auto getWhitePieces() const -> std::vector<std::shared_ptr<ChessPiece>> {
		return mWhitePieces;
	}

	auto getBlackPieces() const -> std::vector<std::shared_ptr<ChessPiece>>  {
		return mBlackPieces;
	}

	/// Returns true if the current state is a checkmate
	bool isCheckmate() const;

	/// Returns true if the current state is a stalemate
	bool isStalemate() const;

	/**
	 * This method checks the current state of the game and returns a vector
	 * with only the ChessPieces that can be moved right now.
	 *
	 * @note Use the public methods in ChessPiece class to find out more
	 * about the possible moves for each ChessPiece.
	 */
	std::vector<std::shared_ptr<ChessPiece>> getPiecesThatCanBeMoved() const;

	/**
	 * Moves the ChessPiece pointed to by ptr to the given BoardPosition pointed
	 * to by pos.
	 *
	 * @param[in] ptr The ChessPiece to move.
	 * @param[in] pos The BoardPosition where we are moving the piece.
	 *
	 * @note This method does not check any chess rule or pre-condition for the
	 * move to done. It assumes the move can be done. The game logic is managed
	 * by the BoardController class.
	 */
	BoardState move(std::shared_ptr<ChessPiece> ptr, BoardPosition pos);

	/**
	 * The ChessPiece pointed to by capturer captures the ChessPiece pointed
	 * to by hostage.
	 *
	 * @param[in] capturer The ChessPiece that is capturing.
	 * @param[in] hostage The ChessPiece that is being captured.
	 *
	 * @note This method does not check any chess rule or pre-condition for the
	 * move to done. It assumes the move can be done. The game logic is managed
	 * by the BoardController class.
	 */
	BoardState capture(std::shared_ptr<ChessPiece> capturer, std::shared_ptr<ChessPiece> hostage);

	std::shared_ptr<ChessPiece> getPieceAt(BoardPosition pos) const;
	const BoardSquare& getSquareAt(BoardPosition pos) const;

	bool hasPieceAt(const BoardPosition& pos) const;
	bool isValidPosition(BoardPosition pos) const;

	PlayerColor getCurrentPlayer() const { return mCurrentPlayer; }
    void switchPlayer();

    void setGameInProgress(bool in_progress=true) {mGameInProgress=in_progress;}
    bool isGameInProgress();

private:
	/// The active white pieces
	std::vector<std::shared_ptr<ChessPiece>> mWhitePieces;

	/// The active black pieces
	std::vector<std::shared_ptr<ChessPiece>> mBlackPieces;

	/// White pieces captured by black player
	std::vector<std::shared_ptr<ChessPiece>> mWhiteHostages;

	/// Black pieces captured by white player
	std::vector<std::shared_ptr<ChessPiece>> mBlackHostages;

	/// The 64 squares in a board plus one extra square used to mark the end of it.
	std::vector<BoardSquare> mSquares;

	PlayerColor mCurrentPlayer;
    bool mGameInProgress;

	void initWhitePieces();
	void initBlackPieces();
	void initSquares();

	/// Every square in the board can point to a ChessPiece.
	void bindPiecesToSquares();
	void reset();

	void setCurrentPlayer(PlayerColor c) { mCurrentPlayer = c; }

	void copy(const BoardState& rhs);
	std::shared_ptr<ChessPiece>  copyPiece(std::shared_ptr<ChessPiece> piece);
};

} /* namespace sch */

#endif /* CHESSGAME_H_ */
