#include "sql_generator.h"

namespace Generator {
	std::string add_artist(std::pair<std::string, std::string> artist) {
		std::string add_artist_string;
		add_artist_string = "INSERT INTO Artists(first_name, last_name) VALUES ('" + case_correction(artist.first) + "', '" + case_correction(artist.second) + "');";
		return add_artist_string;
	}

	std::string add_song(std::string song_title) {
		std::string add_song_string;
		add_song_string = "INSERT INTO Songs(song_title) VALUES ('" + case_correction(song_title) + "');";
		return add_song_string;
	}

	std::string add_genre(std::string genre) {
		std::string add_genre_string;
		add_genre_string = "INSERT INTO Genres(genre) VALUES ('" + genre + "');";
		return add_genre_string;
	}

	std::vector<std::string> add_track(int song_id, std::string release_year, std::string release_title, int genre_id, std::string track_notes, std::vector<int> artists) {
		std::vector<std::string> add_track_strings{};
		add_track_strings.push_back("INSERT INTO Tracks(track_song, track_release_year, track_release, track_genre, track_notes) VALUES ('" + std::to_string(song_id) +
			"', '" + release_year + "', '" + release_title + "', '" + std::to_string(genre_id) +
			"', '" + track_notes + "');");
		
		for (std::size_t i = 0, ilen = artists.size(); i < ilen; ++i) {
			add_track_strings.push_back(
				"INSERT INTO TrackArtist(track, artist) VALUES ('" + std::to_string(song_id) + "', '" + std::to_string(artists.at(i)) + "');");
		}
		return add_track_strings;
	}

	std::string artist_in_db(std::pair<std::string, std::string> artist) {
		std::string artist_in_db{};
		artist_in_db = "SELECT * FROM Artists\nWHERE upper(first_name) = '" + to_upper(artist.first) + "' AND upper(last_name) = '" + to_upper(artist.second) + "';";
		return artist_in_db;
	}

	std::string song_in_db(std::string title) {
		std::string song_in_db{};
		song_in_db = "SELECT * FROM Songs\nWHERE upper(song_title) = '" + to_upper(title) + "';";
		return song_in_db;
	}

	std::string track_search_by_title(int song_id) {
		std::string track_search{};
		track_search = "SELECT * FROM TrackArtist WHERE song = " + std::to_string(song_id) + ";";
		return track_search;
	}
	std::string track_search_by_artist(int artist_id) {
		std::string track_search{};
		track_search = "SELECT * FROM TrackArtist WHERE artist = " + std::to_string(artist_id) + ";";
		return track_search;
	}
	std::string track_search_by_song_artist(int song_id, int artist_id) {
		std::string track_search{};
		track_search = "SELECT Track_Id FROM TrackArtist WHERE song = " + std::to_string(song_id) + " AND artist = " + std::to_string(artist_id) + ";";
		return track_search;
	}

	std::string to_upper(std::string str) {
		for (unsigned int i = 0; i < str.size(); ++i)
			str.at(i) = toupper(str.at(i));

		return str;
	}

	std::string case_correction(std::string str) {
		str.at(0) = toupper(unsigned(str.at(0)));
		for (std::size_t i = 1, ilen = str.size(); i < ilen; ++i) {
			if (str.at(i - 1) == ' ')
				str.at(i) = toupper(unsigned(str.at(i)));
		}

		return str;
	}
};