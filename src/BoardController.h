//===-- smart-chess/BoardController.h ---------------------------*- C++ -*-===//
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
/// \file BoardController.h
/// \brief The class wich controls a BoardState
///
//===----------------------------------------------------------------------===//

#ifndef BOARDCONTROLLER_H_
#define BOARDCONTROLLER_H_

#include "ChessPlayer.h"
#include "BoardState.h"

namespace Gtk {
	class Statusbar;
	class Grid;
}

namespace sch {

class ChessPlayer;

class BoardController {
public:
	BoardController();
	virtual ~BoardController();

	void chessBoardClicked(BoardPosition);

	bool gameInProgress() { return mState.isGameInProgress();}

	void startGame(ChessPlayer* player1, ChessPlayer* player2);
	void endGame();
	void resetGame();

	bool mainGameLogic();

    sigc::signal<void,const BoardState&> signalBoardStateUpdated();
private:
	BoardState 	mState;
	std::unique_ptr<ChessPlayer>	mPlayer1;
	std::unique_ptr<ChessPlayer>	mPlayer2;
	std::shared_ptr<ChessPiece> mSelectedPiece;
	std::vector<std::unique_ptr<ChessPlayer>> mPlayers;
	sigc::connection mAlgorithmConnection; // Connection to the algorithm logic.
	sigc::connection mHumanConnection; // Connection to the game logic.
    sigc::signal<void, const BoardState&> mBoardStateUpdated;

	bool isValidMove(const BoardState& s, const Move& m) const;
};

} /* namespace sch */

#endif /* BOARDCONTROLLER_H_ */
