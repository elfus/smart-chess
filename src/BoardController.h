/*
 * BoardController.h
 *
 *  Created on: Nov 29, 2014
 *      Author: aortegag
 */

#ifndef BOARDCONTROLLER_H_
#define BOARDCONTROLLER_H_

#include "BoardState.h"

namespace sch {

class BoardController {
public:

	BoardController(std::shared_ptr<BoardState> state);
	virtual ~BoardController();

	void chessBoardClicked(BoardSquare);

	void startGame();
	void endGame();
	void resetGame();
private:
	std::shared_ptr<BoardState> mState;
};

} /* namespace sch */

#endif /* BOARDCONTROLLER_H_ */
