#ifndef DATABASE_SEARCH_H
#define DATABASE_SEARCH_H

#include <iostream>
#include <string>
#include <stdbool.h>
#include <utility>
#include "sqlite3.h"
#include "sql_generator.h"
#include "getter.h"

class Inquirer {
public:
	Inquirer();
	Inquirer(sqlite3* db);
	/*std::string search_artist(std::string artist);
	std::string search_song(std::string song);
	std::string search_track(std::string track);*/
	int artist_in_db(std::pair<std::string, std::string> artist_name);
	int song_in_db(std::string song);
	std::vector<int> track_search(int id1, int id2);


private:
	//void preparer();
	sqlite3* db{ nullptr };
	int result_code{};
	sqlite3_stmt* stmt{};
	std::string sql{};


};
#endif // !DATABASE_SEARCH_H */
