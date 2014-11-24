//===-- smart-chess/ChessPiece.h --------------------------------*- C++ -*-===//
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
/// \file ChessPiece.h
/// \brief The class in charge of representing chess pieces.
///
//===----------------------------------------------------------------------===//

#ifndef CHESSPIECE_H_
#define CHESSPIECE_H_

namespace sch {

class ChessPiece {
public:
	ChessPiece();
	virtual ~ChessPiece();
protected:

};

class King : public ChessPiece{

};

class Queen : public ChessPiece {

};

class Rook : public ChessPiece {

};

class Bishop : public ChessPiece {

};

class Knight : public ChessPiece {

};

class Pawn : public ChessPiece {

};

} /* namespace sch */

#endif /* CHESSPIECE_H_ */
