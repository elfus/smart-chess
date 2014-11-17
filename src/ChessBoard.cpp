/*
 * ChessBoard.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: aortegag
 */

#include "ChessBoard.h"

namespace sch {

ChessBoard::ChessBoard() {
	// TODO Auto-generated constructor stub

}

ChessBoard::~ChessBoard() {
	// TODO Auto-generated destructor stub
}

bool ChessBoard::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	// coordinates for the center of the window
	static float i = 0;
	int xc, yc;
	xc = width / 2;
	yc = height / 2;
	if( i == width)
		i = 0;

	ctx->set_line_width(5.0);

	// draw red lines out from the center of the window
	ctx->set_source_rgb(0.8, 0.0, 0.0);
	ctx->move_to(i++, 0);
	ctx->line_to(xc, yc);
	ctx->line_to(0, height);
	ctx->move_to(xc, yc);
	ctx->line_to(width, yc);
	ctx->stroke();

	return true;
}

} /* namespace sch */
