//===-- smart-chess/main.cpp ------------------------------------*- C++ -*-===//
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
/// \file main.cpp
/// \brief Main entry point for smart-chess
///
//===----------------------------------------------------------------------===//
#include "ChessPiece.h"
#include "SmartChessWindow.h"
#include "SmartChessConfig.h"
#include <gtkmm/builder.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	try {
		Glib::RefPtr<Gtk::Application> app =
				Gtk::Application::create(argc, argv);

		string data_dir = SMARTCHESS_DATA_DIR;
		sch::ChessPiece::loadImages(data_dir);

		Glib::RefPtr<Gtk::Builder> builder =
				Gtk::Builder::create_from_file(data_dir + "/chess-gui.glade");

		sch::SmartChessWindow main_window;

		app->run(main_window);
	} catch (const std::exception& e) {
		cerr << e.what() << endl;
	}
	catch (const Glib::Exception& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Unknown exception thrown!" << endl;
	}

	return EXIT_SUCCESS;
}
