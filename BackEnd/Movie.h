#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <vector>
#include <ctime>
#include <comdef.h>

#include "Movie_Session.h"

using namespace std;

enum Categories { ACTION, WESTERN, MYSTERY, DRAMA, COMEDY, ROMANCE, ADVENTURE, THRILLER, HISTORY, HORROR, FANTASY, NUMBER_GENRE };

class Movie
{
	wstring movie_name;
	int min_age;
	Categories category;
	float rating;
	float price;
	map<tm, Movie_Session> movie_sessions;
	map<size_t, size_t> seats_num;

public:
	const wchar_t* listNameGetre[NUMBER_GENRE] = { L"Бойовик", L"Вестерн", L"Містика", L"Драма", L"Комедія", L"Романс", L"Пригодницький", L"Триллер", L"Історичний", L"Жахи", L"Фентезі" };

	Movie(map<size_t, size_t> seats_number);
	Movie(map<size_t, size_t> seats_number, wstring name, int min_age, Categories category, float rating, float price, map<tm, Movie_Session> sessions);

	wstring get_name() const;
	int get_min_age() const;
	Categories get_category() const;
	float get_rating() const;
	float get_price() const;

	map<tm, Movie_Session> get_sessions() const;

	Movie_Session& get_session(Movie_Session sess);
	map<size_t, size_t> get_seats_num() const;

	void set_name(wstring name);
	void set_min_age(int age);
	void set_category(Categories cat);
	void set_rating(float rating);
	void set_price(float price);
	void set_sessions(map <tm, Movie_Session> sessions);
	void set_seats_number(map<size_t, size_t> seats_number);

	void erase_sessions();

	bool operator==(const Movie& second);
	bool operator==(Movie second);
	bool operator<(const Movie& second);
};

wistream& operator>>(wistream& in, Movie& movie);
wostream& operator<<(wostream& out, Movie& movie);