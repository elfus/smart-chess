//===-- smart-chess/ChessPiece.cpp ------------------------------*- C++ -*-===//
//
// This file is part of smart-chess, a chess game meant to provide an easy
// interface to experiment, learn and implement Artificial Intelligence
// algorithms.
//
// Copyright (c) 2014 Adrián Ortega García <adrianog(dot)sw(at)gmail(dot)com>
// All rights reserved.
//
// smart-chess is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// smart-chess is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with smart-chess (See file COPYING for details).
// If not, see <http://www.gnu.org/licenses/>.
//
//===----------------------------------------------------------------------===//
///
/// \file ChessPiece.cpp
/// \brief The class in charge of representing chess pieces.
///
//===----------------------------------------------------------------------===//

#include "ChessPiece.h"

namespace sch {

std::map<PieceType, Glib::RefPtr<Gdk::Pixbuf>> ChessPiece::images;

std::ostream& operator << (std::ostream& os, PieceType t)
{
	switch(t) {
	case PieceType::WHITE_KING : os << "WHITE_KING"; break;
	case PieceType::WHITE_QUEEN : os << "WHITE_QUEEN"; break;
	case PieceType::WHITE_BISHOP : os << "WHITE_BISHOP"; break;
	case PieceType::WHITE_ROOK : os << "WHITE_ROOK"; break;
	case PieceType::WHITE_KNIGHT : os << "WHITE_KNIGHT"; break;
	case PieceType::WHITE_PAWN : os << "WHITE_PAWN"; break;

	case PieceType::BLACK_KING : os << "WHITE_KING"; break;
	case PieceType::BLACK_QUEEN : os << "WHITE_QUEEN"; break;
	case PieceType::BLACK_BISHOP : os << "WHITE_BISHOP"; break;
	case PieceType::BLACK_ROOK : os << "WHITE_ROOK"; break;
	case PieceType::BLACK_KNIGHT : os << "WHITE_KNIGHT"; break;
	case PieceType::BLACK_PAWN : os << "WHITE_PAWN"; break;
	case PieceType::UNDEFINED: os << "UNDEFINED"; break;
	}
	return os;
}

ChessPiece::~ChessPiece() {
	// TODO Auto-generated destructor stub
}

/// @note This method MUST be called at the beginning of the program.
void ChessPiece::loadImages()
{
	images[PieceType::WHITE_KING] = Gdk::Pixbuf::create_from_file("data/kingw.gif");
	images[PieceType::WHITE_QUEEN] = Gdk::Pixbuf::create_from_file("data/queenw.gif");
	images[PieceType::WHITE_ROOK] = Gdk::Pixbuf::create_from_file("data/rookw.gif");
	images[PieceType::WHITE_BISHOP] = Gdk::Pixbuf::create_from_file("data/bishopw.gif");
	images[PieceType::WHITE_KNIGHT] = Gdk::Pixbuf::create_from_file("data/knightw.gif");
	images[PieceType::WHITE_PAWN] = Gdk::Pixbuf::create_from_file("data/pawnw.gif");

	images[PieceType::BLACK_KING] = Gdk::Pixbuf::create_from_file("data/kingb.gif");
	images[PieceType::BLACK_QUEEN] = Gdk::Pixbuf::create_from_file("data/queenb.gif");
	images[PieceType::BLACK_ROOK] = Gdk::Pixbuf::create_from_file("data/rookb.gif");
	images[PieceType::BLACK_BISHOP] = Gdk::Pixbuf::create_from_file("data/bishopb.gif");
	images[PieceType::BLACK_KNIGHT] = Gdk::Pixbuf::create_from_file("data/knightb.gif");
	images[PieceType::BLACK_PAWN] = Gdk::Pixbuf::create_from_file("data/pawnb.gif");
}

bool ChessPiece::isWhite() {
	switch(mPieceType) {
	case PieceType::WHITE_KING:
	case PieceType::WHITE_QUEEN:
	case PieceType::WHITE_BISHOP:
	case PieceType::WHITE_KNIGHT:
	case PieceType::WHITE_ROOK:
	case PieceType::WHITE_PAWN:
		return true;
	default:
		return false;
	}
}

bool ChessPiece::isBlack() {
	return !isWhite();
}

} /* namespace sch */
