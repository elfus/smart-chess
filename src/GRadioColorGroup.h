//
// Created by aortegag on 7/5/15.
//

#ifndef SMARTCHESS_GRADIOCOLORGROUP_H
#define SMARTCHESS_GRADIOCOLORGROUP_H

#include <gtkmm/grid.h>

namespace Gtk {
    class RadioButton;
}

namespace sch {

    class GRadioColorGroup : public Gtk::Grid {
    public:
        GRadioColorGroup();

        sigc::signal<void> signalClickedWhite();
        sigc::signal<void> signalClickedBlack();

        std::string getColor() const;
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
