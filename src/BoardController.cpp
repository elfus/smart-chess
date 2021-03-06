/*
 * BoardController.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: aortegag
 */

#include "BoardController.h"
#include "ChessPlayer.h"
#include <iostream>
#include <gtkmm/statusbar.h>
#include <gtkmm/grid.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/comboboxtext.h>
#include <glibmm.h>

using namespace std;

namespace sch {

BoardController::BoardController()
: mState(),
  mSelectedPiece(nullptr),
  mPlayers(){

}

BoardController::~BoardController() {

}

/**
 * Member function callback whenever there is a human player against A.I.
 *
 * This method controls the logic of the game.
 *
 */
void BoardController::chessBoardClicked(BoardPosition pos)
{
	if(mState.isValidPosition(pos)) {
		// 1st check if we clicked on a possible movement
		if(auto selected_piece = mState.getSelectedPiece()) {
			auto moves = selected_piece->getPossibleMoves(mState);
			for(auto& move : moves) {
				if(pos == move) {
					cout << "Clicked on a possible move" << endl;
					mState.moveTo(pos);

					mState.switchPlayer();
					mBoardStateUpdated(mState);

					if(!mPlayer1->isHuman() || !mPlayer2->isHuman()) {
						Glib::signal_idle().connect(sigc::mem_fun(this, &BoardController::mainGameLogic));
					}
					return;
				}
			}
			mState.unselectPiece();
		}

		auto selected_square = mState.getSquareAt(pos);
		if(selected_square.hasPiece() && selected_square.getPiece()->getColor() == mState.getCurrentPlayer()) {
			cout << "The selected square has a piece at " << endl;
			if(mState.selectPieceAt(pos)) {
				cout << "Piece selected" << endl;
			}
		} else {
			if(selected_square.hasPiece() && selected_square.getPiece()->getColor() != mState.getCurrentPlayer())
				cout << "The " << mState.getCurrentPlayer() << " is trying to move a "
				<< selected_square.getPiece()->getColor() << " piece"<< endl;
			else
				cout << "Empty square" << endl;
		}

		mBoardStateUpdated(mState);
	}
}

bool BoardController::isValidMove(const BoardState& s, const Move& m) const
{
	bool valid = false;
	if(m.piece.get() != nullptr) {
		auto moves = m.piece->getPossibleMoves(s);
		for(auto& pos : moves) {
			if(pos == m.final_pos) {
				valid = true;
				break;
			}
		}
	}
	return valid;
}

void BoardController::startGame(ChessPlayer* player1, ChessPlayer* player2) {
	cout << "BoardController::startGame" << endl;

	mPlayer1 = unique_ptr<ChessPlayer>(player1);
	mPlayer2 = unique_ptr<ChessPlayer>(player2);

	mState.reset();
    mState.setCurrentPlayer(mPlayer1->getColor());
    mState.setGameInProgress();

    mBoardStateUpdated(mState);
}

void BoardController::endGame() {
	cout << "BoardController::endGame" << endl;

	mState.reset();
	mHumanConnection.disconnect();
	mAlgorithmConnection.disconnect();
	mPlayers.clear();

	mBoardStateUpdated(mState);
}

void BoardController::resetGame() {
	cout << "BoardController::resetGame" << endl;
	endGame();
    /// @todo Save the initial player colors and also if they are human or not
    startGame(mPlayer1.get(), mPlayer2.get());
}

	bool BoardController::mainGameLogic() {
		Move move;

		if(mPlayer1 && mPlayer1->getColor() == mState.getCurrentPlayer())
			move = mPlayer1->makeMove(mState);

		if(mPlayer2  && mPlayer2->getColor() == mState.getCurrentPlayer())
			move = mPlayer2->makeMove(mState);

		if(isValidMove(mState, move)) {
			auto target_square = mState.getSquareAt(move.piece->getBoardPosition());
			if(mState.selectPieceAt(target_square)) {
				auto moves = mState.getSelectedPiece()->getPossibleMoves(mState);
				for(auto& possible_pos : moves) {
					if(move.final_pos == possible_pos) {
						cout << "Clicked on a possible move" << endl;
						mState.moveTo(move.final_pos);

						mState.switchPlayer();
						mBoardStateUpdated(mState);
						break;
					}
				}
				mState.unselectPiece();
			}
		}

		mBoardStateUpdated(mState);

		// when playing only A.I. we should not disconnect this method
		bool both_ai = (typeid(*mPlayer1.get()) != typeid(Human)) && (typeid(*mPlayer2.get()) != typeid(Human));
		return both_ai;// when returning false means this method will be disconnected from the glib idle functions
	}


    sigc::signal<void, const BoardState&> BoardController::signalBoardStateUpdated() {
        return mBoardStateUpdated;
    }
} /* namespace sch */
