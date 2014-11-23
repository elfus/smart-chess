/*
 * ChessBoard.h
 *
 *  Created on: Nov 16, 2014
 *      Author: aortegag
 */

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <gtkmm/drawingarea.h>
#include <tuple>

namespace sch {

class ChessBoard: public Gtk::DrawingArea {
public:
	enum Row {
		ONE = 7,
		TWO = 6,
		THREE = 5,
		FOUR = 4,
		FIVE = 3,
		SIX = 2,
		SEVEN = 1,
		EIGHT = 0
	};

	enum Column {
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H
	};

	ChessBoard();
	virtual ~ChessBoard();

	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);

private:
	static const int SQUARE_NUM = 8;
	static const int MIN_BOARD_W = 400;
	static const int MIN_BOARD_H = MIN_BOARD_W;

	int mBoardWidth;
	int mBoardHeight;
	int mSquareWidth;
	int mSquareHeight;

	void draw_squares(const Cairo::RefPtr<Cairo::Context>& ctx,
			int board_width, int board_height);

	bool click_released(GdkEventButton* event);

	std::tuple<Row,Column> calculateSquare(double x, double y);
};

std::ostream& operator <<(std::ostream& os, ChessBoard::Row r);
std::ostream& operator <<(std::ostream& os, ChessBoard::Column c);


} /* namespace sch */

#endif /* CHESSBOARD_H_ */
