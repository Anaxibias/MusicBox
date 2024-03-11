#include "menu.h"

Menu::Menu()

int Menu::main_menu() {

	/*
	* Allows user to choose whether to search for a track or add a new track
	* Loops until user chooses to exit
	*/

	do {
		user_choice = getter::get_int("Query or Edit:\n0. Search Tracks\n1. Add New Track\n2. Exit");

		if (user_choice == 0) {
			track_search_results = search_track();
			if (track_search_results.back() == -11) {}
			else if (track_search_results.back() == -12) {}
			else if (track_search_results.back() == -13) {};
		}
		else if (user_choice == 1) {
			editor_obj.add_track();
		}
		else
			std::cout << "Error: Invalid Entry" << std::endl;

	} while (user_choice != 2);

	return 0;
}