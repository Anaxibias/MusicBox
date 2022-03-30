#ifndef DATABASE_EDITOR_H
#define DATABASE_EDITOR_H
#include <vector>
#include <string>
#include <utility>
#include "sqlite3.h"
#include "sql_generator.h"
#include "sql_instructions.h"
#include "callback_functions.h"
#include "getter.h"
#include "database_inquirer.h"
//#include "user_interface.h"

class Editor{
public:
	Editor();
	Editor(sqlite3* db, Inquirer* inq_ptr);
	void add_track();
	void add_artist(std::pair<std::string, std::string> artist_name);
	void add_song(std::string title);
	void add_genre();
	//void edit_track_info(track_data track);

private:
	struct track_data {
		std::vector<int> artists{};
		int genre_id{};
		int song_id{};
		std::string notes{};
		std::string release_title{};
		std::string release_year{};
	};
	
	
	sqlite3* db{ nullptr };
	Inquirer* inquirer_ptr{ nullptr };
	int result_code{ 0 };
	int return_val{};
	std::string my_string;
	std::pair<std::string, std::string> my_pair;

	track_data get_track_data();
	std::vector<int> check_duplicates(track_data);
};
#endif // !DATABASE_EDITOR_H