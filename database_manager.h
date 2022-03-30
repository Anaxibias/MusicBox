#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "sqlite3.h"

#include "callback_functions.h"
#include "sql_instructions.h"
#include "sql_generator.h"

class DatabaseManager {
public:
	DatabaseManager(sqlite3_object);
	void close();

protected:
	void check_error(int result_code);
	sqlite3* db;
	int result_code;
	int is_open;

private:
	void initiate_new();
	int open_new;
};
#endif // !DATABASE_H