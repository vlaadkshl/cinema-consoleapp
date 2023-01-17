#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <functional>

#include "Cinema_Hall.h"

using namespace std;

class Cinema
{
	wstring name;
	vector<Cinema_Hall> halls;

public:
	Cinema();
	Cinema(wstring name, vector<Cinema_Hall> halls);

	wstring get_name() const;
	vector<Cinema_Hall> get_halls() const;

	//	Пошук зали за назвою зали
	Cinema_Hall* find_hall(wstring name);

	//	Пошук зали за назвою фільму
	Cinema_Hall* find_hall(wstring name, int);

	//	Пошук фільму за назвою
	Movie* find_movie_by_name(wstring name);

	//	Видалити фільм за назвою
	void delete_movie(wstring name);

	void erase_halls();
	void set_name(wstring name);
	void add_hall(Cinema_Hall hall);
	int remove_hall(wstring name);

	void set_halls(vector<Cinema_Hall> vect);
};

wistream& operator>>(wistream& in, Cinema& cinema);
wostream& operator<<(wostream& out, const Cinema& cinema);