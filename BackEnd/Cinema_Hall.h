#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <comdef.h>

#include "Movie.h"

using namespace std;

class Cinema_Hall
{
	wstring hall_name;
	vector<Movie> movies;
	map<size_t, size_t> seats_number;

public:
	Cinema_Hall();
	Cinema_Hall(map<size_t, size_t> seats_number);
	Cinema_Hall(wstring name, vector<Movie> movies, map<size_t, size_t> seats_number);

	wstring get_name() const;
	vector<Movie> get_movies() const;
	vector<Movie>& get_movies_addr();
	map<size_t, size_t> get_seats_number() const;

	void add_movie(Movie mov);
	void delete_movie(wstring name);
	void erase_movies();

	void set_name(wstring name);
	void set_movies(vector<Movie> movies);
	void set_seats(map<size_t, size_t> seats_number);

	Cinema_Hall& operator=(const Cinema_Hall& a);
};

wistream& operator>>(wistream& in, Cinema_Hall& hall);
wostream& operator<<(wostream& out, const Cinema_Hall& hall);

bool operator<(const Cinema_Hall& a, const Cinema_Hall& b);