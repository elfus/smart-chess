//===-- smart-chess/ChessPlayer.h -------------------------------*- C++ -*-===//
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
/// \file ChessPlayer.h
/// \brief
///
//===----------------------------------------------------------------------===//

#ifndef CHESSPLAYER_H_
#define CHESSPLAYER_H_

#include "Util.h"

namespace sch {

class BoardState;

class ChessPlayer {
public:
	enum class Color {
		WHITE,
		BLACK
	};
	ChessPlayer(Color color);
	virtual ~ChessPlayer();

	virtual bool isHuman() { return false; }
	Color getColor() const { return mColor; }

	virtual Move makeMove(const BoardState& state) = 0;
private:
	Color mColor;
};

class Human : public ChessPlayer {
public:
	Human(Color color);
	virtual ~Human();

	bool isHuman() { return true; }
	Move makeMove(const BoardState& state);
};

class Algorithm : public ChessPlayer {
public:
	Algorithm(Color color);
	virtual ~Algorithm();

	Move makeMove(const BoardState& state);
};

std::ostream& operator << (std::ostream& os, ChessPlayer::Color c);

} /* namespace sch */

#endif /* CHESSPLAYER_H_ */
