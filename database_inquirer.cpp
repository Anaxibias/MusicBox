#include "database_inquirer.h"

Inquirer::Inquirer() = default;

Inquirer::Inquirer(sqlite3 * db) {
	this->db = db;
}

int Inquirer::artist_in_db(std::pair<std::string, std::string> artist_name) {
	sql = Generator::artist_in_db(artist_name);

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

int Inquirer::song_in_db(std::string song) {
	sql = Generator::song_in_db(song);

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

std::vector<int> Inquirer::track_search(int song_id, int artist_id) {
	if (song_id >= 0 && artist_id < 0) {
		sql = Generator::track_search_by_title(song_id);
	}
	else if (song_id < 0 && artist_id >= 0) {
		sql = Generator::track_search_by_artist(artist_id);
	}
	else{
		sql = Generator::track_search_by_song_artist(song_id, artist_id);
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

/*void Inquirer::preparer() {
	result_code = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

	if (result_code != SQLITE_OK) {
		std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
	}
}*/