#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <iostream>
#include <string>
#include <stdbool.h>
#include <utility>
#include "sqlite3.h"
#include "database_connection.h"
#include "database_editor.h"
#include "database_inquirer.h"
#include "sql_generator.h"
#include "sql_instructions.h"
#include "callback_functions.h"
#include "getter.h"

class DbManager {
public:
	DbManager(); // Default constructor
	int run(); // run function calls main_menu, and close_db on exit
	/*std::string search_artist(std::string artist);
	std::string search_song(std::string song);
	std::string search_track(std::string track);*/
	int find_artist(std::pair<std::string, std::string> artist_name);
	int find_song(std::string song);
	std::vector<int> track_search(int id1, int id2);
	void add_track();
	void add_artist(std::pair<std::string, std::string> artist_name);
	void add_song(std::string title);
	void add_genre();

private:
	int user_choice; // stores integer input from users
	std::string user_text; // stores string input from users
	sqlite3* db{ nullptr }; // a pointer to a sqlite3 object, initialized as null
	int id{};
	std::string my_string{};
	std::pair<std::string, std::string> my_pair{};
	std::vector<int> track_search_results{};
	int result_code{};
	int result_code{};
	std::string my_string;
	std::pair<std::string, std::string> my_pair;
	sqlite3_stmt* stmt{};
	std::string sql{};

	struct track_data {
		std::vector<int> artists{};
		int genre_id{};
		int song_id{};
		std::string notes{};
		std::string release_title{};
		std::string release_year{};
	};
	
	//void preparer();
	track_data get_track_data();
	std::vector<int> check_duplicates(track_data);
	std::vector<int> search_track();
	void close_db(); // closes the database
};
#endif // !DBMANAGER_H