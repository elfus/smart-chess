#include <gtkmm.h>
#include <iostream>
#include <exception>

using namespace std;

int main(int argc, char * argv[])
{
	try {
		Glib::RefPtr<Gtk::Application> app =
				Gtk::Application::create(argc, argv);

		// @todo Improve how we retrieve the resource files, we don't want
		// harcoded stuff.
		Glib::RefPtr<Gtk::Builder> builder =
				Gtk::Builder::create_from_file("data/chess-gui.glade");

		Gtk::Window* main_window = nullptr;
		builder->get_widget("MainWindow", main_window);

		unique_ptr<Gtk::Window> uptr_window(main_window);

		app->run(*main_window);

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
