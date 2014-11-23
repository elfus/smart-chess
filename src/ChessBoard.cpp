/*
 * ChessBoard.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: aortegag
 */

#include "ChessBoard.h"
#include <iostream>

using namespace std;

namespace sch {

ChessBoard::ChessBoard() : Gtk::DrawingArea(){
	set_vexpand();
}

ChessBoard::~ChessBoard() {
	// TODO Auto-generated destructor stub
}

void ChessBoard::draw_squares(const Cairo::RefPtr<Cairo::Context>& ctx,
		int board_width, int board_height)
{
	const int square_w = board_width / SQUARE_NUM;
	const int square_h = board_height / SQUARE_NUM;
	int x = 0, y = 0;
	ctx->set_source_rgb(1.0, 1.0, 1.0);
	bool is_white = true;
	for(int i=0; i < SQUARE_NUM; ++i) {
		x = i * square_w;
		for(int j=0; j < SQUARE_NUM; ++j) {
			if(is_white) {
				ctx->set_source_rgb(1.0, 1.0, 1.0);
				is_white = false;
			}
			else {
				ctx->set_source_rgb(0, 0, 0);
				is_white = true;
			}
			y = j * square_h;
			ctx->rectangle(x,y, square_w, square_h);
			ctx->fill();
		}
		if(is_white) {
			ctx->set_source_rgb(1.0, 1.0, 1.0);
			is_white = false;
		}
		else {
			ctx->set_source_rgb(0, 0, 0);
			is_white = true;
		}
	}
}

bool ChessBoard::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	draw_squares(ctx, width, height);

	// coordinates for the center of the window
	static float i = 0;
	int xc, yc;
	xc = width / 2;
	yc = height / 2;
	if( i == width)
		i = 0;

	ctx->set_line_join(Cairo::LineJoin::LINE_JOIN_ROUND);
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
