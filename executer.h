#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <iostream>
#include <string>
#include "sqlite3.h"
#include "database_connection.h"
#include "database_editor.h"
#include "database_inquirer.h"
#include "getter.h"

class Executor {
public:
	Executor(); // Default constructor
	int run(); // run function calls main_menu, and close_db on exit

private:
	int user_choice; // stores integer input from users
	std::string user_text; // stores string input from users
	sqlite3* db{ nullptr }; // a pointer to a sqlite3 object, initialized as null
	int id{};
	std::string my_string{};
	std::pair<std::string, std::string> my_pair{};
	std::vector<int> track_search_results{};

	Inquirer inquirer_obj = Inquirer::Inquirer(); // a pointer to an Inquirer object, intialized as null
	Editor editor_obj = Editor::Editor(); // a pointer to an Editor object, initialized as null
	
	int main_menu(); // main_menu function determines whether user wants to query or edit the database
	std::vector<int> track_search();
	void close_db(); // closes the database
};
#endif // !EXECUTOR_H