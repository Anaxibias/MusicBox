#include "database_connection.h"

DatabaseConnection::DatabaseConnection(const char* db_name, int is_new) {
	result_code = sqlite3_open(db_name, &db);

	if (result_code)
		std::cout << "Error opening database: " << sqlite3_errmsg(db) << std::endl;

	if (is_new == 1)
		create_tables();
}

sqlite3* DatabaseConnection::get() {
	return(db);
}

void DatabaseConnection::create_tables() {
	for(int i = 0; i < sql_instructions::create_init_tables.size(); ++i){
		result_code = sqlite3_exec(db, sql_instructions::create_init_tables.at(i), null_callback, NULL, NULL);
		++i;
	}
}