//
// Created by aortegag on 7/5/15.
//

#ifndef SMARTCHESS_GRADIOCOLORGROUP_H
#define SMARTCHESS_GRADIOCOLORGROUP_H

#include <gtkmm/grid.h>
#include "Util.h"
#include "ChessPlayer.h"

namespace Gtk {
    class RadioButton;
}

namespace sch {

    class GRadioColorGroup : public Gtk::Grid {
    public:
        GRadioColorGroup();

        sigc::signal<void> signalClickedWhite();
        sigc::signal<void> signalClickedBlack();

        ChessPlayer::Color getColor() const;
        void setWhite();
        void setBlack();
    private:
        Gtk::RadioButton*   mWhiteRadioButton;
        Gtk::RadioButton*   mBlackRadioButton;

        sigc::signal<void> mClickedWhite;
        sigc::signal<void> mClickedBlack;

        void clickedWhiteRadioButton();
        void clickedBlackRadioButton();
    };

}



#endif //SMARTCHESS_GRADIOCOLORGROUP_H
