#include "executer.h"

Executor::Executor() {

	/*
	* Default contsructor for class Executer. 
	* Retrieves database name from user (Executer::user_text) and whether to create a new or find an existing database (Executer::user_choice)
	* Creates a DatabaseConnection object, uses DatabaseConnection::get to return the database connection.
	* Executor::db is a pointer to a sqlite object
	*/

	user_choice = getter::get_int("New or Existing Database:\n\n0. Existing\n1. New\n");
	user_text = getter::get_string_element("Enter database name: ");

	DatabaseConnection connection{ user_text.c_str(), user_choice };

	db = connection.get();

	Inquirer inquirer{db};
	inquirer_obj = inquirer;

	Editor editor{db, &inquirer_obj};
	editor_obj = editor;
	
	}

int Executor::main_menu() {

	/*
	* Allows user to choose whether to search for a track or add a new track
	* Loops until user chooses to exit
	*/

	do {
		user_choice = getter::get_int("Query or Edit:\n0. Search Tracks\n1. Add New Track\n2. Exit");

		if (user_choice == 0) {
			track_search_results = track_search();
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

std::vector<int> Executor::track_search() {
	using getter::get_int;
	using getter::get_string_element;
	using getter::get_string_pair;

	do {
		int id{};
		int id2{};
		int user_val = get_int("0. Go back\n1. Search by song\n2. search by artist\n3. Search by song & artist");
		switch (user_val) {
		case 0:
			break;
		case 1:
			id = inquirer_obj.song_in_db(get_string_element("Enter song title: "));
			if (id == -1) {
				std::cout << "There are no tracks with this title." << std::endl;
				break;
			}
			else {
				inquirer_obj.track_search(id, -1).push_back(-11);
				return inquirer_obj.track_search(id, -1);
			}
		case 2:
			id = inquirer_obj.artist_in_db(get_string_pair("Enter artist first name: ", "Enter artist last name"));
			if (id == -1) {
				std::cout << "Artist not in database." << std::endl;
				break;
			}
			else {
				inquirer_obj.track_search(-1, id).push_back(-12);
				return inquirer_obj.track_search(-1, id);
			}
		case 3:
			id = inquirer_obj.song_in_db(get_string_element("Enter song title: "));
			id2 = inquirer_obj.artist_in_db(get_string_pair("Enter artist first name: ", "Enter artist last name"));

			if (id == -1 || id2 == -1) {
				std::cout << "Track not in database.";
				break;
			}
			else {
				inquirer_obj.track_search(id, id2).push_back(-13);
				return inquirer_obj.track_search(id, id2);
			}
		default:
			std::cout << "Error: Invalid entry.\n\n" << std::endl;
			break;
		}
	} while (user_choice != 0);
	return {};
}

void Executor::close_db() {
	/*
	* Calls the sqlite3 member function to close the database
	*/

	sqlite3_close(db);
}

int Executor::run() {

	/*
	* Runs the Executor functions in order
	*/

	main_menu();
	close_db();

	return 0;
}