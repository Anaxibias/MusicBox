#include <iostream>
#include <string>
#include "sqlite3.h"
#include "sql_instructions.h"
#include "callback_functions.h"

class Database {
public:
	Database(const char* db_name, int is_new);
	sqlite3* get();

private:
	sqlite3* db;
	int result_code;
	void create_tables();
};