#ifndef SQL_INSTRUCTIONS_H
#define SQL_INSTRUCTIONS_H
#include <vector>
#include <string>

//CODE TO CREATE TABLES
namespace sql_instructions {
	inline const std::vector<const char*> create_init_tables = { 
		"PRAGMA foreign_keys = ON;\n\n\
		CREATE TABLE Artists(\n\
		\tartist_id	INTEGER PRIMARY KEY,\n\
		\tfirst_name TEXT NOT NULL,\n\
		\tlast_name	TEXT NOT NULL,\n\
		\tnum_tracks	INTEGER,\n\
		\ttimes_played INTEGER);",

		"CREATE INDEX ucasename ON Artists(upper(first_name), upper(last_name));"
		,
		"CREATE TABLE Songs(\n\
		\tsong_id	INTEGER PRIMARY KEY,\n\
		\tsong_title TEXT NOT NULL);",

		"CREATE INDEX ucasetitle ON Songs(upper(song_title));",

		"CREATE TABLE Genres(\n\
		\tgenre_id INTEGER PRIMARY KEY,\n\
		\tgenre TEXT NOT NULL);",
	
		"CREATE TABLE Tracks(\n\
		\ttrack_id INTEGER PRIMARY KEY,\n\
		\ttrack_song INTEGER NOT NULL,\n\
		\ttrack_release_year INTEGER,\n\
		\ttrack_release TEXT NOT NULL,\n\
		\ttrack_genre INTEGER,\n\
		\ttrack_notes TEXT,\n\
		\tFOREIGN KEY(track_song) REFERENCES songs(song_id),\n\
		\tFOREIGN KEY(track_genre) REFERENCES genres(genre_id));",

		"CREATE TABLE TrackArtist(\n\
		\ttrack INTEGER NOT NULL,\n\
		\tartist INTEGER NOT NULL,\n\
		\tsong INTEGER NOT NULL,\n\
		\tPRIMARY KEY(track, artist),\n\
		\tFORIEGN KEY(track) REFERENCES Tracks(track_id),\n\
		\tFORIEGN KEY(artist) REFERENCES Artists(artist_id),\n\
		\tFORIEGN KEY(song) REFERENCES Tracks(track_song));",

		"CREATE TABLE Playlists(\n\
		\tplaylist_id INTEGER PRIMARY KEY,\n\
		\tplaylist_year	INTEGER NOT NULL,\n\
		\tplaylist_month INTEGER NOT NULL,\n\
		\tplaylist_day INTEGER NOT NULL,\n\
		\tFORIEGN KEY(playlist_year) REFERENCES Years(year),\n\
		\tFORIEGN KEY(playlist_month) REFERENCES Months(month_id),\n\
		\tFORIEGN KEY(playlist_day) REFERENCES Days(day));",

		"CREATE TABLE PlaylistTracks(\n\
		\tplaylist INTEGER NOT NULL,\n\
		\ttrack INTEGER NOT NULL,\n\
		\tsong INTEGER NOT NULL,\n\
		\tPRIMARY KEY(playlist, track),\n\
		\tFORIEGN KEY(playlist) REFERENCES Playlists(playlist_id),\n\
		\tFORIEGN KEY(track) REFERENCES Tracks(track_id),\n\
		\tFORIEGN KEY(song) REFERENCES Tracks(track_song));",

		"CREATE TABLE Years(\n\
		\tyear INTEGER PRIMARY KEY);",

		"CREATE TABLE Months(\n\
		\tmonth_id INTEGER PRIMARY KEY,\n\
		\tmonth_name TEXT NOT NULL);",

		"CREATE TABLE Days(\n\
		\tday INTEGER PRIMARY KEY);"
	};

	inline const std::string new_artist{ "INSERT INTO Artists(num_tracks, times_played) VALUES (0, 0);" };
	inline const std::string new_track{ "INSERT INTO Tracks(track_release) VALUES (_NULL_VALUE_);" };
}

#endif // !SQL_H
