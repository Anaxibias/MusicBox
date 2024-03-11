#include "db_manager.h"

DbManager::DbManager() {

	/*
	* Default contsructor for class Executer. 
	* Retrieves database name from user (Executer::user_text) and whether to create a new or find an existing database (Executer::user_choice)
	* Creates a DatabaseConnection object, uses DatabaseConnection::get to return the database connection.
	* DbManager::db is a pointer to a sqlite object
	*/

	user_choice = user_interface::get_int("New or Existing Database:\n\n0. Existing\n1. New\n");
	user_text = user_interface::get_string_element("Enter database name: ");

	DatabaseConnection connection{ user_text.c_str(), user_choice };

	db = connection.get();

	Inquirer inquirer{db};
	inquirer_obj = inquirer;

	Editor editor{db, &inquirer_obj};
	editor_obj = editor;
	
	}

std::vector<int> DbManager::search_track() {
	using user_interface::get_int;
	using user_interface::get_string_element;
	using user_interface::get_string_pair;

	do {
		int id{};
		int id2{};
		int user_val = get_int("0. Go back\n1. Search by song\n2. search by artist\n3. Search by song & artist");
		switch (user_val) {
		case 0:
			break;
		case 1:
			id = inquirer_obj.find_song(get_string_element("Enter song title: "));
			if (id == -1) {
				std::cout << "There are no tracks with this title." << std::endl;
				break;
			}
			else {
				inquirer_obj.find_track(id, -1).push_back(-11);
				return inquirer_obj.find_track(id, -1);
			}
		case 2:
			id = inquirer_obj.find_artist(get_string_pair("Enter artist first name: ", "Enter artist last name"));
			if (id == -1) {
				std::cout << "Artist not in database." << std::endl;
				break;
			}
			else {
				inquirer_obj.find_track(-1, id).push_back(-12);
				return inquirer_obj.find_track(-1, id);
			}
		case 3:
			id = inquirer_obj.find_song(get_string_element("Enter song title: "));
			id2 = inquirer_obj.find_artist(get_string_pair("Enter artist first name: ", "Enter artist last name"));

			if (id == -1 || id2 == -1) {
				std::cout << "Track not in database.";
				break;
			}
			else {
				inquirer_obj.find_track(id, id2).push_back(-13);
				return inquirer_obj.find_track(id, id2);
			}
		default:
			std::cout << "Error: Invalid entry.\n\n" << std::endl;
			break;
		}
	} while (user_choice != 0);
	return {};
}

int DbManager::find_artist(std::pair<std::string, std::string> artist_name) {
	sql = Generator::find_artist(artist_name);

	result_code = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

	if (result_code != SQLITE_OK) {
		std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
	}

	const unsigned char* first_name{};
	const unsigned char* last_name{};
	int index{};

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		first_name = last_name = NULL;
		first_name = sqlite3_column_text(stmt, 1);
		last_name = sqlite3_column_text(stmt, 2);
		index = sqlite3_column_int(stmt, 0);

		if (first_name != NULL && last_name != NULL)
			return index;
	}

	sqlite3_finalize(stmt);

	return -1;
}

int DbManager::find_song(std::string song) {
	sql = Generator::find_song(song);

	result_code = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

	if (result_code != SQLITE_OK) {
		std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
	}

	const unsigned char* song_title{};
	int index{};
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		song_title = NULL;
		song_title = sqlite3_column_text(stmt, 1);
		index = sqlite3_column_int(stmt, 0);

		if (song_title != NULL)
			return index;
	}

	sqlite3_finalize(stmt);

	return -1;
}

std::vector<int> DbManager::find_track(int song_id, int artist_id) {
	if (song_id >= 0 && artist_id < 0) {
		sql = Generator::find_track_by_title(song_id);
	}
	else if (song_id < 0 && artist_id >= 0) {
		sql = Generator::find_track_by_artist(artist_id);
	}
	else{
		sql = Generator::find_track_by_song_artist(song_id, artist_id);
	}

	result_code = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

	if (result_code != SQLITE_OK) {
		std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
	}

	std::vector<int> tracks{};

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		tracks.push_back(sqlite3_column_int(stmt, 0));
	}

	return tracks;
}

/*void DbManager::preparer() {
	result_code = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

	if (result_code != SQLITE_OK) {
		std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
	}
}*/

void DbManager::add_artist(std::pair<std::string, std::string> artist_name) {
	//std::string artist_string{ Generator::add_artist(getter::get_string_pair("Artist first name: ", "Artist last name: ")) };
	
	return_val = inquirer_ptr->find_artist(artist_name);

	if (return_val == -1) {
		std::string string{ Generator::add_artist(artist_name) + sql_instructions::new_artist };
		result_code = sqlite3_exec(db, string.c_str(), null_callback, NULL, NULL);
	}
	else
		std::cout << "Error: Artist already exists in database" << std::endl;
	//check_error(result_code);
}

void DbManager::add_song(std::string title) {

	return_val = inquirer_ptr->find_song(title);

	if (return_val == -1)
		result_code = sqlite3_exec(db, Generator::add_song(title).c_str(), null_callback, NULL, NULL);
	else
		std::cout << "Error: Song already exists in database" << std::endl;
	//check_error(result_code);
}

void DbManager::add_genre() {
	result_code = sqlite3_exec(db, Generator::add_genre(getter::get_string_element("Enter genre: ")).c_str(), null_callback, NULL, NULL);
	//check_error(result_code);
}

void DbManager::add_track() {
	DbManager::track_data track = get_track_data();
	std::vector<std::string> track_strings{ Generator::add_track(track.song_id, track.release_year, track.release_title, track.genre_id, track.notes, track.artists) };
	for(std::size_t i = 0, ilen = track_strings.size(); i < ilen; ++i)
		result_code = sqlite3_exec(db, track_strings.at(i).c_str(), null_callback, NULL, NULL);
	//check_error(result_code);
}

DbManager::track_data DbManager::get_track_data() {
	using getter::get_string_element;
	using getter::get_int;
	using getter::get_string_pair;

	DbManager::track_data track;

	int temp{};
	int num_artists = get_int("Enter number of artists on track: ");
	for (int i = 0; i < num_artists; ++i) {
		std::pair<std::string, std::string> temp_name = get_string_pair("Enter artist first name: ", "Enter artist last name: ");
		temp = inquirer_ptr->find_artist(temp_name);

		if (temp == -1) {
			add_artist(temp_name);
			temp = inquirer_ptr->find_artist(temp_name);
		}
		track.artists.push_back(temp);
	}
	track.genre_id = 0;//inquirer_ptr->genre_in_db(get_string_element("Enter genre: "));
	track.notes = get_string_element("Enter notes: ");
	track.release_title = get_string_element("Enter album title: ");
	track.release_year = get_string_element("Enter release year: ");
	
	std::string temp_song = get_string_element("Enter song title: ");
	track.song_id = inquirer_ptr->find_song(temp_song);
	if (track.song_id == -1) {
		add_song(temp_song);
		track.song_id = inquirer_ptr->find_song(temp_song);
	}

	return track;
}

std::vector<int> DbManager::check_duplicates(DbManager::track_data track) {
	std::vector<int> search_return{};
	std::vector<int> temp_vect{};
	for (int i = 0; i < track.artists.size(); ++i) {
		temp_vect = inquirer_ptr->track_search(track.artists.at(i), track.song_id);
		search_return.insert(search_return.end(), temp_vect.begin(), temp_vect.end());
		temp_vect.clear();
	}

	return search_return;
}

void DbManager::close_db() {
	/*
	* Calls the sqlite3 member function to close the database
	*/

	sqlite3_close(db);
}

int DbManager::run() {

	/*
	* Runs the DbManager functions in order
	*/

	main_menu();
	close_db();

	return 0;
}