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
void BoardController::chessBoardClicked(BoardSquare s)
{
	cout << "POSITION: " << s.getBoardPosition().row << " " << s.getBoardPosition().column << endl;

	if(mState.isValidPosition(s)) {
		// 1st check if we clicked on a possible movement
		if(auto selected_piece = mState.getSelectedPiece()) {
			auto moves = selected_piece->getPossibleMoves(mState);
			cout << "A piece is already selected" << endl;
			for(auto& move : moves) {
				if(s.getBoardPosition() == move) {
					cout << "Clicked on a possible move" << endl;
					mState.moveTo(s.getBoardPosition());

					mState.switchPlayer();
					mBoardStateUpdated(mState);
					return;
				}
			}
		}

		if(mState.selectPieceAt(s)) {
			cout << "Piece selected" << endl;

		} else {
			cout << "Empty square" << endl;
		}

		mState.switchPlayer();
		mBoardStateUpdated(mState);
	}
}

/**
 * Callback method which gets called whenever the GUI is idle and calls the
 * AI algorithm and checks the of the current game.
 *
 * @see Programming with gtkmm, section 24 timeout and idle functions
 */
bool BoardController::AlgorithmLogic()
{
	// Check the player's turn
	// let the current player move
	// check if the move is valid
	// 		if move is valid then do the move
	// check any game post-conditions, i.e. checkmate
	ChessPlayer *player {nullptr};

	if(mPlayers[0]->getColor() == mState.getCurrentPlayer())
		player = mPlayers[0].get();
	else if(mPlayers[1]->getColor() == mState.getCurrentPlayer())
		player = mPlayers[1].get();

	if(typeid(*player) == typeid(Human)) {
		cerr << "This method should not be called for a human!" << endl;
	} else {
		Move move = player->makeMove(mState);
		if(!isValidMove(mState, move)) {
			cerr << "Invalid move: " << move << endl;
			return true;
		} else {
			// check if the algorithm is capturing a piece first
			if(mState.hasPieceAt(move.final_pos))
				mState = mState.capture(move.piece, mState.getPieceAt(move.final_pos));
			else
				mState = mState.move(move.piece, move.final_pos);
		}
	}

	mState.switchPlayer();
	cout.flush();

	// Let the human play
	if(mPlayingAgainstHuman) {
//		mHumanConnection = mView->signalClickedReleased().connect(
//						sigc::mem_fun(*this,&BoardController::chessBoardClicked));
		return false;
	} else {
		return true;
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
