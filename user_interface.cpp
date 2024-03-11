#include "user_interface.h"

namespace user_interface {

	std::pair<std::string, std::string> get_string_pair(std::string i, std::string j) {
		/*
		* queries the user for two strings, returns an object of class pair that contains two strings.
		* uses std::getline() in order to retrive multi-word strings
		*/

		std::cin.ignore();
		std::pair<std::string, std::string> string_pair;
		std::cout << i << std::endl;
		std::getline(std::cin, string_pair.first);
		std::cout << j << std::endl;
		std::getline(std::cin, string_pair.second);

		return string_pair;
	}

	std::string get_string_element(std::string i) {

		/*
		* queries the user for a single string, returns a string.
		* uses std::getline() in order to retrieve multi-word strings
		*/

		std::cin.ignore();
		std::string element;
		std::cout << i << std::endl;
		std::getline(std::cin, element);

		return element;
	}

	int get_int(std::string i) {

		/*
		* queries the user for an integer number
		*uses std::cin, then runs std::cin.clear and std::cin.sync to clear leftover newline characters
		*/

		int num;
		std::cout << i << std::endl;
		std::cin >> num;

		return num;
	}
}