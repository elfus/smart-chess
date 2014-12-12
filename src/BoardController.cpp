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
: mState(nullptr),
  mView(nullptr),
  mSelectedPiece(nullptr){


}

BoardController::~BoardController() {
	// TODO Auto-generated destructor stub
}

void BoardController::chessBoardClicked(BoardSquare s)
{
	cout << "POSITION: " << s.mPosition.row << " " << s.mPosition.column << ", ";
	cout << "PIECE: ";
	if(s.hasPiece()) {
		if(mSelectedPiece)
			mSelectedPiece->setSelected(false);
		mSelectedPiece = s.getPiece();
		mSelectedPiece->setSelected();
		cout << s.getPiece()->getPieceType() << endl;
	}
	else {
		cout << "NO PIECE" << endl;
		if(mSelectedPiece) {
			auto moves = mSelectedPiece->getPossibleMoves(*mState);
			auto it = find(moves.begin(), moves.end(), s.mPosition);
			if(it != moves.end()) {
				mState->move(mSelectedPiece, *it);
			}
			mSelectedPiece->setSelected(false);
			mSelectedPiece.reset();
		}
	}

	mView->force_redraw();
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
