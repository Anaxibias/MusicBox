#ifndef SQL_GENERATOR_H
#define SQL_GENERATOR_H
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

namespace Generator {
	std::string add_artist(std::pair<std::string, std::string> artist_artist);
	std::string add_song(std::string song_title);
	std::string add_genre(std::string genre);
	std::vector<std::string> add_track(int song_id, std::string release_year, std::string release_title, int genre_id, std::string track_notes, std::vector<int> artists);

	//std::string search_artist(std::pair <std::string, std::string> artist);
	std::string artist_in_db(std::pair<std::string, std::string>);
	std::string song_in_db(std::string title);
	std::string track_search_by_title(int song_id);
	std::string track_search_by_artist(int artist_id);
	std::string track_search_by_song_artist(int song_id, int artist_id);

	std::string to_upper(std::string str);
	std::string case_correction(std::string str);
}

#endif //SQL_GENERATOR_H