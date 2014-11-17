/*
 * ChessBoard.h
 *
 *  Created on: Nov 16, 2014
 *      Author: aortegag
 */

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <gtkmm/drawingarea.h>

namespace sch {

class ChessBoard: public Gtk::DrawingArea {
public:
	ChessBoard();
	virtual ~ChessBoard();

	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
};

} /* namespace sch */

#endif /* CHESSBOARD_H_ */
