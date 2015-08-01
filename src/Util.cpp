//
// Created by aortegag on 7/12/15.
//

#include "Util.h"

#include "SmartChessConfig.h"

namespace sch {

    ImageLoader &ImageLoader::instance() {
        static ImageLoader m_instance;
        return m_instance;
    }

    void ImageLoader::loadImages(std::string data_dir) {
        images[PieceType::WHITE_KING] = Gdk::Pixbuf::create_from_file(data_dir + "/kingw.gif");
        images[PieceType::WHITE_QUEEN] = Gdk::Pixbuf::create_from_file(data_dir + "/queenw.gif");
        images[PieceType::WHITE_ROOK] = Gdk::Pixbuf::create_from_file(data_dir + "/rookw.gif");
        images[PieceType::WHITE_BISHOP] = Gdk::Pixbuf::create_from_file(data_dir +"/bishopw.gif");
        images[PieceType::WHITE_KNIGHT] = Gdk::Pixbuf::create_from_file(data_dir + "/knightw.gif");
        images[PieceType::WHITE_PAWN] = Gdk::Pixbuf::create_from_file(data_dir + "/pawnw.gif");

        images[PieceType::BLACK_KING] = Gdk::Pixbuf::create_from_file(data_dir + "/kingb.gif");
        images[PieceType::BLACK_QUEEN] = Gdk::Pixbuf::create_from_file(data_dir + "/queenb.gif");
        images[PieceType::BLACK_ROOK] = Gdk::Pixbuf::create_from_file(data_dir + "/rookb.gif");
        images[PieceType::BLACK_BISHOP] = Gdk::Pixbuf::create_from_file(data_dir + "/bishopb.gif");
        images[PieceType::BLACK_KNIGHT] = Gdk::Pixbuf::create_from_file(data_dir + "/knightb.gif");
        images[PieceType::BLACK_PAWN] = Gdk::Pixbuf::create_from_file(data_dir + "/pawnb.gif");
    }

    ImageLoader::ImageLoader() {
        loadImages(SMARTCHESS_DATA_DIR);
    }

    Glib::RefPtr<Gdk::Pixbuf> ImageLoader::getImage(PieceType type) {
        return images[type];
    }

    std::ostream& operator << (std::ostream& os, PlayerColor c) {
    	switch(c) {
    	case PlayerColor::WHITE_PLAYER: os << "white player"; break;
    	case PlayerColor::BLACK_PLAYER: os << "black player"; break;
    	}
    	return os;
    }
}
