/*
 * BoardController.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: aortegag
 */

#include "BoardController.h"
#include "ChessPiece.h"
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
: mState(nullptr),
  mView(nullptr),
  mSelectedPiece(nullptr),
  mCurrentPlayer(PlayerColor::WHITE_PLAYER),
  mPlayers(),
  mStatus(nullptr),
  mOptionsGrid(nullptr),
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
 * @note Enable this callback when there is a human player.
 */
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
			mAlgorithmConnection = Glib::signal_idle().connect(sigc::mem_fun(*this, &BoardController::AlgorithmLogic));
			mHumanConnection.disconnect();
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
			mAlgorithmConnection = Glib::signal_idle().connect(sigc::mem_fun(*this, &BoardController::AlgorithmLogic));
			mHumanConnection.disconnect();
		} else
			cout << "Empty square1" << endl;
		mSelectedPiece->setSelected(false);
		mSelectedPiece.reset();
	} else if(!s.hasPiece() && !mSelectedPiece) {
		cout << "Empty square2" << endl;
	}

	mState->setCurrentPlayer(mCurrentPlayer);
	Glib::ustring msg((mCurrentPlayer==PlayerColor::WHITE_PLAYER)? "White player's turn." : "Black player's turn.");
	mStatus->pop();
	mStatus->push(msg);
	mView->force_redraw();
	cout.flush();
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

	if(mPlayers[0]->getColor() == mCurrentPlayer)
		player = mPlayers[0].get();
	else if(mPlayers[1]->getColor() == mCurrentPlayer)
		player = mPlayers[1].get();

	if(typeid(*player) == typeid(Human)) {
		cerr << "This method should not be called for a human!" << endl;
	} else {
		Move move = player->makeMove(*mState);
		if(!isValidMove(*mState, move)) {
			cerr << "Invalid move: " << move << endl;
			return true;
		} else {
			// check if the algorithm is capturing a piece first
			if(mState->hasPieceAt(move.final_pos))
				mState->capture(move.piece, mState->getPieceAt(move.final_pos));
			else
				mState->move(move.piece, move.final_pos);
		}
	}

	mCurrentPlayer = (mCurrentPlayer==PlayerColor::WHITE_PLAYER) ? PlayerColor::BLACK_PLAYER : PlayerColor::WHITE_PLAYER;
	mState->setCurrentPlayer(mCurrentPlayer);
	Glib::ustring msg((mCurrentPlayer==PlayerColor::WHITE_PLAYER)? "White player's turn." : "Black player's turn.");
	mStatus->pop();
	mStatus->push(msg);
	mView->force_redraw();
	cout.flush();

	// Let the human play
	if(mPlayingAgainstHuman) {
		mHumanConnection = mView->getSignalClickedReleased().connect(
						sigc::mem_fun(*this,&BoardController::chessBoardClicked));
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

void BoardController::createChessPlayerObjects() {
	mPlayers.clear();
	vector<Gtk::Widget*> children = mOptionsGrid->get_children();
	Gtk::ComboBoxText *cbt1 {nullptr};
	Gtk::ComboBoxText *cbt2 {nullptr};
	Gtk::ComboBoxText *color1 {nullptr};
	Gtk::ComboBoxText *color2 {nullptr};
	for(Gtk::Widget*& ptr : children) {
		if(ptr->get_name() == "PlayerComboBox1")
			cbt1 = dynamic_cast<Gtk::ComboBoxText*>(ptr);
		if(ptr->get_name() == "PlayerComboBox2")
			cbt2 = dynamic_cast<Gtk::ComboBoxText*>(ptr);
		if(ptr->get_name() == "ColorComboBox1")
			color1 = dynamic_cast<Gtk::ComboBoxText*>(ptr);
		if(ptr->get_name() == "ColorComboBox2")
			color2 = dynamic_cast<Gtk::ComboBoxText*>(ptr);
	}
	if(cbt1->get_active_text() == "Human") {
		mPlayingAgainstHuman = true;
		mPlayers.push_back(unique_ptr<Human>(new Human()));
		mHumanConnection = mView->getSignalClickedReleased().connect(
				sigc::mem_fun(*this,&BoardController::chessBoardClicked));
	}
	else if(cbt1->get_active_text() == "Algorithm") {
		mPlayers.push_back(unique_ptr<Algorithm>(new Algorithm()));
		// If player 1 one is the computer connect the callback method
		mAlgorithmConnection = Glib::signal_idle().connect(sigc::mem_fun(*this, &BoardController::AlgorithmLogic));
	}

	if(color1->get_active_text() == "White")
		mPlayers.back()->setColor(PlayerColor::WHITE_PLAYER);
	else if(color1->get_active_text() == "Black")
		mPlayers.back()->setColor(PlayerColor::BLACK_PLAYER);

	if(cbt2->get_active_text() == "Human") {
		mPlayingAgainstHuman = true;
		mPlayers.push_back(unique_ptr<Human>(new Human()));
	}
	else if(cbt2->get_active_text() == "Algorithm")
		mPlayers.push_back(unique_ptr<Algorithm>(new Algorithm()));

	if(color2->get_active_text() == "White")
		mPlayers.back()->setColor(PlayerColor::WHITE_PLAYER);
	else if(color2->get_active_text() == "Black")
		mPlayers.back()->setColor(PlayerColor::BLACK_PLAYER);

	assert(mPlayers.size() == 2);
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
		createChessPlayerObjects();
	} else {
		Gtk::MessageDialog msg("Invalid Game Options");
		msg.run();
	}
}

void BoardController::endGame() {
	cout << "BoardController::endGame" << endl;
	// process current game state, then delete;
	mPlayingAgainstHuman = false;
	mState.reset();
	mOptionsGrid->set_sensitive(true);
	mStatus->remove_all_messages();
	mHumanConnection.disconnect();
	mAlgorithmConnection.disconnect();
	mPlayers.clear();
	mView->force_redraw();
}

void BoardController::resetGame() {
	cout << "BoardController::resetGame" << endl;
	endGame();
	startGame();
}



} /* namespace sch */
