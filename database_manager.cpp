#include "database_manager.h"

//default constructor, opens database if there is no database open
DatabaseManager::DatabaseManager(std::string filename, int open_new) {
	if (!is_open) {
		this->open_new = open_new;

		result_code = sqlite3_open(filename.c_str(), &db);

		if (result_code)
			std::cout << "Error opening database " << sqlite3_errmsg(db) << std::endl;

		if (this->open_new)
			initiate_new();

		is_open = 1;
	}
}

//runs SQL code to set up necessary tables in new databases
void DatabaseManager::initiate_new() {

	for (unsigned int i = 0; i < create_tables.size(); ++i) {


		result_code = sqlite3_exec(db, create_tables.at(i), null_callback, NULL, NULL);

		if (result_code) {
			std::cout << sqlite3_errmsg(db) << std::endl;
			break;
		}
	}
}

void DatabaseManager::check_error(int result_code) {
	if (result_code) {
		std::cout << sqlite3_errmsg(db) << std::endl;
	}
}

void DatabaseManager::close() {
	sqlite3_close(db);
}
