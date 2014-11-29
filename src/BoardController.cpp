/*
 * BoardController.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: aortegag
 */

#include "BoardController.h"
#include <iostream>

using namespace std;

namespace sch {

BoardController::BoardController(std::shared_ptr<BoardState> state)
: mState(state){


}

BoardController::~BoardController() {
	// TODO Auto-generated destructor stub
}

void BoardController::chessBoardClicked(BoardSquare s)
{
	cout << "clicked: " << s.row << " " << s.column << endl;
}

} /* namespace sch */
