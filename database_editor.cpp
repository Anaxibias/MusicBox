#include "database_editor.h"

Editor::Editor() = default;

Editor::Editor(sqlite3* db, Inquirer* inq_ptr) {
	this->db = db;
	inquirer_ptr = inq_ptr;
}

void Editor::add_artist(std::pair<std::string, std::string> artist_name) {
	//std::string artist_string{ Generator::add_artist(getter::get_string_pair("Artist first name: ", "Artist last name: ")) };
	
	return_val = inquirer_ptr->artist_in_db(artist_name);

	if (return_val == -1) {
		std::string string{ Generator::add_artist(artist_name) + sql_instructions::new_artist };
		result_code = sqlite3_exec(db, string.c_str(), null_callback, NULL, NULL);
	}
	else
		std::cout << "Error: Artist already exists in database" << std::endl;
	//check_error(result_code);
}

void Editor::add_song(std::string title) {

	return_val = inquirer_ptr->song_in_db(title);

	if (return_val == -1)
		result_code = sqlite3_exec(db, Generator::add_song(title).c_str(), null_callback, NULL, NULL);
	else
		std::cout << "Error: Song already exists in database" << std::endl;
	//check_error(result_code);
}

void Editor::add_genre() {
	result_code = sqlite3_exec(db, Generator::add_genre(getter::get_string_element("Enter genre: ")).c_str(), null_callback, NULL, NULL);
	//check_error(result_code);
}

void Editor::add_track() {
	Editor::track_data track = get_track_data();
	std::vector<std::string> track_strings{ Generator::add_track(track.song_id, track.release_year, track.release_title, track.genre_id, track.notes, track.artists) };
	for(std::size_t i = 0, ilen = track_strings.size(); i < ilen; ++i)
		result_code = sqlite3_exec(db, track_strings.at(i).c_str(), null_callback, NULL, NULL);
	//check_error(result_code);
}

Editor::track_data Editor::get_track_data() {
	using getter::get_string_element;
	using getter::get_int;
	using getter::get_string_pair;

	Editor::track_data track;

	int temp{};
	int num_artists = get_int("Enter number of artists on track: ");
	for (int i = 0; i < num_artists; ++i) {
		std::pair<std::string, std::string> temp_name = get_string_pair("Enter artist first name: ", "Enter artist last name: ");
		temp = inquirer_ptr->artist_in_db(temp_name);

		if (temp == -1) {
			add_artist(temp_name);
			temp = inquirer_ptr->artist_in_db(temp_name);
		}
		track.artists.push_back(temp);
	}
	track.genre_id = 0;//inquirer_ptr->genre_in_db(get_string_element("Enter genre: "));
	track.notes = get_string_element("Enter notes: ");
	track.release_title = get_string_element("Enter album title: ");
	track.release_year = get_string_element("Enter release year: ");
	
	std::string temp_song = get_string_element("Enter song title: ");
	track.song_id = inquirer_ptr->song_in_db(temp_song);
	if (track.song_id == -1) {
		add_song(temp_song);
		track.song_id = inquirer_ptr->song_in_db(temp_song);
	}

	return track;
}

std::vector<int> Editor::check_duplicates(Editor::track_data track) {
	std::vector<int> search_return{};
	std::vector<int> temp_vect{};
	for (int i = 0; i < track.artists.size(); ++i) {
		temp_vect = inquirer_ptr->track_search(track.artists.at(i), track.song_id);
		search_return.insert(search_return.end(), temp_vect.begin(), temp_vect.end());
		temp_vect.clear();
	}

	return search_return;
}