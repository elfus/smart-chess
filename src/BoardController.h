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

#include "BoardState.h"

namespace Gtk {
	class Statusbar;
	class Grid;
}

namespace sch {

class BoardController {
public:
	BoardController();
	virtual ~BoardController();

	void chessBoardClicked(BoardSquare);

	bool gameInProgress() { return mState.operator bool();}
	std::shared_ptr<BoardState> getState() const {return mState; }

	void setBoardView(std::shared_ptr<BoardView> v) { mView = v; }
	void setStatusbar(Gtk::Statusbar *s) { mStatus = s; }
	void setOptionsGrid(Gtk::Grid *g) { mOptionsGrid = g; }

	void startGame();
	void endGame();
	void resetGame();
private:
	std::shared_ptr<BoardState> mState;
	std::shared_ptr<BoardView> mView;
	std::shared_ptr<ChessPiece> mSelectedPiece;
	PlayerColor mCurrentPlayer;
	std::map<PlayerType, PlayerColor> mPlayers;
	Gtk::Statusbar *mStatus;
	Gtk::Grid *mOptionsGrid;

	bool validGameOptions() const;
};

} /* namespace sch */

#endif /* BOARDCONTROLLER_H_ */
