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
#include "ChessPlayer.h"

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
	 * Moves the current selected piece to the BoardPosition pos.
	 *
	 * If there is an opponent's piece it will be captured.
	 */
	void moveTo(BoardPosition pos);


	/**
	 * Selects the piece at the give BoardSquare.
	 *
	 * @return True if a piece was selected, false when there was no piece to select.
	 */
	bool selectPieceAt(const BoardSquare& s);

	void unselectPiece();

	std::shared_ptr<ChessPiece> getPieceAt(BoardSquare pos) const;
	const BoardSquare& getSquareAt(BoardPosition pos) const;

	bool hasPieceAt(const BoardSquare& pos) const;
	bool isValidPosition(const BoardSquare& pos) const;

	ChessPlayer::Color getCurrentPlayer() const { return mCurrentPlayer; }

    bool isGameInProgress();

    std::shared_ptr<ChessPiece> getSelectedPiece();

    ChessPlayer::Color getCurrentPlayer() { return mCurrentPlayer; }
private:
	/// The active white pieces
	std::vector<std::shared_ptr<ChessPiece>> mWhitePieces;

	/// The active black pieces
	std::vector<std::shared_ptr<ChessPiece>> mBlackPieces;

	/// White pieces captured by black player
	std::vector<std::shared_ptr<ChessPiece>> mWhiteHostages;

	/// Black pieces captured by white player
	std::vector<std::shared_ptr<ChessPiece>> mBlackHostages;

	/// The current selected ChessPiece
	std::shared_ptr<ChessPiece> mSelectedPiece;

	/// The 64 squares in a board plus one extra square used to mark the end of it.
	std::vector<BoardSquare> mSquares;

	ChessPlayer::Color mCurrentPlayer;
    bool mGameInProgress;

    /**
	 * The ChessPiece pointed to by hostage is removed from the vector of
	 * currently active pieces and added to the captured vector
	 *
	 * @param[in] hostage The ChessPiece that is being captured.
	 *
	 * @note This method does not check any chess rule or pre-condition for the
	 * move to done. It assumes the move can be done. The game logic is managed
	 * by the BoardController class.
	 */
	void capture(std::shared_ptr<ChessPiece>& hostage); // method accessed by BoardController because it's a friend

	void switchPlayer(); // method accessed by BoardController because it's a friend

	void setGameInProgress(bool in_progress=true) {mGameInProgress=in_progress;} // method accessed by BoardController because it's a friend

	void initWhitePieces();
	void initBlackPieces();
	void initSquares();

	/// Every square in the board can point to a ChessPiece.
	void bindPiecesToSquares();
	void reset();

	void setCurrentPlayer(ChessPlayer::Color c) { mCurrentPlayer = c; }

	void copy(const BoardState& rhs);
	std::shared_ptr<ChessPiece>  copyPiece(std::shared_ptr<ChessPiece> piece);

	BoardSquare& getSquareAt(BoardPosition pos);
};

} /* namespace sch */

#endif /* CHESSGAME_H_ */
