/*
 * BoardController.h
 *
 *  Created on: Nov 29, 2014
 *      Author: aortegag
 */

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
