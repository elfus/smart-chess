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
  mPlayers(),
  mPlayingAgainstHuman(false){

}

BoardController::~BoardController() {
	// TODO Auto-generated destructor stub
}

/**
 * Member function callback whenever there is a human player against A.I.
 *
 * This method controls the logic of the game.
 *
 */
void BoardController::chessBoardClicked(BoardPosition pos)
{
	cout << "POSITION: " << pos.row << " " << pos.column << endl;

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
				cout << "The " << mState.getCurrentPlayer() << "player is trying to move a "
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
	auto moves = m.piece->getPossibleMoves(s);
	for(auto& pos : moves) {
		if(pos == m.final_pos) {
			valid = true;
			break;
		}
	}
	return valid;
}

void BoardController::startGame(PlayerColor player1, PlayerColor player2) {
	cout << "BoardController::startGame" << endl;

	mPlayingAgainstHuman = false;
	mState.reset();
    mState.setCurrentPlayer(player1);
    mState.setGameInProgress();

    mBoardStateUpdated(mState);
}

void BoardController::endGame() {
	cout << "BoardController::endGame" << endl;
	// process current game state, then delete;
	mPlayingAgainstHuman = false;
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
    startGame(PlayerColor::WHITE_PLAYER, PlayerColor::BLACK_PLAYER);
}


    sigc::signal<void, const BoardState&> BoardController::signalBoardStateUpdated() {
        return mBoardStateUpdated;
    }
} /* namespace sch */
