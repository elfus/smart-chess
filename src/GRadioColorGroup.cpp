//
// Created by aortegag on 7/5/15.
//

#include <gtkmm/radiobutton.h>
#include <gtkmm/label.h>
#include "GRadioColorGroup.h"
#include "Util.h"

namespace sch {

    GRadioColorGroup::GRadioColorGroup() {
        for (auto i : IntRange(2)) {
            insert_column(i);
            insert_row(i);
        }

        mWhiteRadioButton = Gtk::manage(new Gtk::RadioButton());
        mWhiteRadioButton->signal_released().connect(
                sigc::mem_fun(*this, &GRadioColorGroup::clickedWhiteRadioButton));
        attach(*mWhiteRadioButton, 0, 0, 1, 1);
        Gtk::Label* white = Gtk::manage(new Gtk::Label("White"));
        attach(*white, 1, 0, 1, 1);

        auto group = mWhiteRadioButton->get_group();
        mBlackRadioButton = Gtk::manage(new Gtk::RadioButton(group));
        mBlackRadioButton->signal_released().connect(
                sigc::mem_fun(*this, &GRadioColorGroup::clickedBlackRadioButton));
        attach(*mBlackRadioButton, 0, 1, 1, 1);
        Gtk::Label* black = Gtk::manage(new Gtk::Label("Black"));
        attach(*black, 1, 1, 1, 1);


    }

    sigc::signal<void> GRadioColorGroup::signalClickedWhite() {
        return mClickedWhite;
    }

    sigc::signal<void> GRadioColorGroup::signalClickedBlack() {
        return mClickedBlack;
    }

    void GRadioColorGroup::clickedWhiteRadioButton() {
        mClickedWhite();
    }

    void GRadioColorGroup::clickedBlackRadioButton() {
        mClickedBlack();
    }

    void GRadioColorGroup::setWhite() {
        mWhiteRadioButton->set_active();
    }

    void GRadioColorGroup::setBlack() {
        mBlackRadioButton->set_active();
    }

    PlayerColor GRadioColorGroup::getColor() const {
        if(mWhiteRadioButton->get_active())
            return PlayerColor::WHITE_PLAYER ;
        if(mBlackRadioButton->get_active())
            return PlayerColor::BLACK_PLAYER;
    }
}