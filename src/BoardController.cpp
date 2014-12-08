/*
 * BoardController.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: aortegag
 */

#include "BoardController.h"
#include "ChessPiece.h"
#include <iostream>

using namespace std;

namespace sch {

BoardController::BoardController()
: mState(nullptr){


}

BoardController::~BoardController() {
	// TODO Auto-generated destructor stub
}

void BoardController::chessBoardClicked(BoardSquare s)
{
	cout << "POSITION: " << s.mPosition.row << " " << s.mPosition.column << ", ";
	cout << "PIECE: ";
	if(s.hasPiece())
		cout << s.getPiece()->getPieceType() << endl;
	else
		cout << "NO PIECE" << endl;

}

void BoardController::startGame() {
	cout << "BoardController::startGame" << endl;
	mState = make_shared<BoardState>();

	mView->force_redraw();
}

void BoardController::endGame() {
	cout << "BoardController::endGame" << endl;
	// process current game state, then delete;
	mState.reset();

	mView->force_redraw();
}

void BoardController::resetGame() {
	cout << "BoardController::resetGame" << endl;
	endGame();
	startGame();
}

} /* namespace sch */
