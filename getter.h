#ifndef GETTER_H
#define GETTER_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>

namespace getter {
	// namespace getter contains utility functions for querying the user for input

	std::pair<std::string, std::string> get_string_pair(std::string i, std::string j); // get_string_pair queries the user for two strings and returns a pair object of type string
	std::string get_string_element(std::string i); // get_string_element queries the user for a string
	int get_int(std::string i); // get_quantity queries the user for an integer value and returns an int
	

};
#endif // !GETTER_H
