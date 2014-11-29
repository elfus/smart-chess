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

std::map<ImageType, Glib::RefPtr<Gdk::Pixbuf>> ChessPiece::images;

ChessPiece::~ChessPiece() {
	// TODO Auto-generated destructor stub
}

/// @note This method MUST be called at the beginning of the program.
void ChessPiece::loadImages()
{
	images[ImageType::WHITE_KING] = Gdk::Pixbuf::create_from_file("data/kingw.gif");
	images[ImageType::WHITE_QUEEN] = Gdk::Pixbuf::create_from_file("data/queenw.gif");
	images[ImageType::WHITE_ROOK] = Gdk::Pixbuf::create_from_file("data/rookw.gif");
	images[ImageType::WHITE_BISHOP] = Gdk::Pixbuf::create_from_file("data/bishopw.gif");
	images[ImageType::WHITE_KNIGHT] = Gdk::Pixbuf::create_from_file("data/knightw.gif");
	images[ImageType::WHITE_PAWN] = Gdk::Pixbuf::create_from_file("data/pawnw.gif");

	images[ImageType::BLACK_KING] = Gdk::Pixbuf::create_from_file("data/kingb.gif");
	images[ImageType::BLACK_QUEEN] = Gdk::Pixbuf::create_from_file("data/queenb.gif");
	images[ImageType::BLACK_ROOK] = Gdk::Pixbuf::create_from_file("data/rookb.gif");
	images[ImageType::BLACK_BISHOP] = Gdk::Pixbuf::create_from_file("data/bishopb.gif");
	images[ImageType::BLACK_KNIGHT] = Gdk::Pixbuf::create_from_file("data/knightb.gif");
	images[ImageType::BLACK_PAWN] = Gdk::Pixbuf::create_from_file("data/pawnb.gif");
}

} /* namespace sch */
