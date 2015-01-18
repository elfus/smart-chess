/*
 * BoardController.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: aortegag
 */

#include "BoardController.h"
#include "ChessPiece.h"
#include <iostream>
#include <gtkmm/statusbar.h>
#include <gtkmm/grid.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/comboboxtext.h>

using namespace std;

namespace sch {

BoardController::BoardController()
: mState(nullptr),
  mView(nullptr),
  mSelectedPiece(nullptr),
  mCurrentPlayer(PlayerColor::WHITE_PLAYER),
  mPlayers(),
  mStatus(nullptr),
  mOptionsGrid(nullptr){
	mPlayers[PlayerType::HUMAN_PLAYER] = PlayerColor::WHITE_PLAYER;
	mPlayers[PlayerType::ALGORITHM_PLAYER] = PlayerColor::BLACK_PLAYER;
}

BoardController::~BoardController() {
	// TODO Auto-generated destructor stub
}

void BoardController::chessBoardClicked(BoardSquare s)
{
	cout << "POSITION: " << s.mPosition.row << " " << s.mPosition.column << ", ";

	if(s.hasPiece() && mSelectedPiece) {
		if(s.getPiece()->isWhite() == mSelectedPiece->isWhite()) {
			mSelectedPiece->setSelected(false);
			mSelectedPiece = s.getPiece();
			mSelectedPiece->setSelected();
			cout << "Selected2: " << s.getPiece()->getPieceType() << endl;
		}
		// check if the user is capturing a piece
		auto moves = mSelectedPiece->getPossibleMoves(*mState);
		auto it = find(moves.begin(), moves.end(), s.getPiece()->getPosition());
		if(it != moves.end()) {
			mState->capture(mSelectedPiece, s.getPiece());
			mCurrentPlayer = (mCurrentPlayer==PlayerColor::WHITE_PLAYER) ? PlayerColor::BLACK_PLAYER : PlayerColor::WHITE_PLAYER;
			mSelectedPiece->setSelected(false);
			mSelectedPiece = nullptr;
		}
	} else if(s.hasPiece() && !mSelectedPiece) {
		if((mCurrentPlayer == PlayerColor::WHITE_PLAYER && s.getPiece()->isWhite()) ||
			(mCurrentPlayer == PlayerColor::BLACK_PLAYER && s.getPiece()->isBlack())) {
			mSelectedPiece = s.getPiece();
			mSelectedPiece->setSelected();
			cout << "Selected1: " << s.getPiece()->getPieceType() << endl;
		}
	}
	else if(!s.hasPiece() && mSelectedPiece){
		// check if the user just wants to move
		auto moves = mSelectedPiece->getPossibleMoves(*mState);
		auto it = find(moves.begin(), moves.end(), s.mPosition);
		if(it != moves.end()) {
			mState->move(mSelectedPiece, *it);
			mCurrentPlayer = (mCurrentPlayer==PlayerColor::WHITE_PLAYER) ? PlayerColor::BLACK_PLAYER : PlayerColor::WHITE_PLAYER;
		} else
			cout << "Empty square1" << endl;
		mSelectedPiece->setSelected(false);
		mSelectedPiece.reset();
	} else if(!s.hasPiece() && !mSelectedPiece) {
		cout << "Empty square2" << endl;
	}

	Glib::ustring msg((mCurrentPlayer==PlayerColor::WHITE_PLAYER)? "White player's turn." : "Black player's turn.");
	mStatus->pop();
	mStatus->push(msg);
	mView->force_redraw();
	cout.flush();
}

bool BoardController::validGameOptions() const
{
	vector<Gtk::Widget*> children = mOptionsGrid->get_children();
	Gtk::ComboBoxText *cbt1 {nullptr};
	Gtk::ComboBoxText *cbt2 {nullptr};
	for(Gtk::Widget*& ptr : children) {
		if(ptr->get_name() == "ColorComboBox1")
			cbt1 = dynamic_cast<Gtk::ComboBoxText*>(ptr);
		if(ptr->get_name() == "ColorComboBox2")
			cbt2 = dynamic_cast<Gtk::ComboBoxText*>(ptr);
	}

	// Check player colors
	if(!cbt1 || !cbt2)
		return false;

	if(cbt1->get_active_text() == "" || cbt2->get_active_text() == "")
		return false;

	if(cbt1->get_active_text() == "Black" && cbt2->get_active_text() == "Black")
		return false;

	if(cbt1->get_active_text() == "White" && cbt2->get_active_text() == "White")
		return false;

	return true;
}

void BoardController::startGame() {
	cout << "BoardController::startGame" << endl;
	if(validGameOptions()) {
		mState = make_shared<BoardState>();
		mOptionsGrid->set_sensitive(false);
		mCurrentPlayer = PlayerColor::WHITE_PLAYER;
		mState->setCurrentPlayer(mCurrentPlayer);
		mStatus->push("White player's turn.");
		mView->force_redraw();
	} else {
		Gtk::MessageDialog msg("Invalid Game Options");
		msg.run();
	}
}

void BoardController::endGame() {
	cout << "BoardController::endGame" << endl;
	// process current game state, then delete;
	mState.reset();
	mOptionsGrid->set_sensitive(true);
	mStatus->remove_all_messages();
	mView->force_redraw();
}

void BoardController::resetGame() {
	cout << "BoardController::resetGame" << endl;
	endGame();
	startGame();
}

} /* namespace sch */
