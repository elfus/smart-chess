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
}

namespace sch {

class BoardController {
public:
enum class Player {
	WHITE_PLAYER,
	BLACK_PLAYER
};
	BoardController();
	virtual ~BoardController();

	void chessBoardClicked(BoardSquare);

	bool gameInProgress() { return mState.operator bool();}
	std::shared_ptr<BoardState> getState() const {return mState; }

	void setBoardView(std::shared_ptr<BoardView> v) { mView = v; }
	void setStatusbar(Gtk::Statusbar *s) { mStatus = s; }

	void startGame();
	void endGame();
	void resetGame();
private:
	std::shared_ptr<BoardState> mState;
	std::shared_ptr<BoardView> mView;
	std::shared_ptr<ChessPiece> mSelectedPiece;
	Player mCurrentPlayer;
	Gtk::Statusbar *mStatus;
};

} /* namespace sch */

#endif /* BOARDCONTROLLER_H_ */
