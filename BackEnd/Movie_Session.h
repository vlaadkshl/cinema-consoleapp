#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <comdef.h>

using namespace std;

class Movie_Session
{
	map<size_t, set<size_t>> booked_seats;
	map<size_t, size_t> seats_number;

public:
	Movie_Session(map<size_t, size_t> seats_number);
	Movie_Session(map<size_t, size_t> seats_number, map<size_t, set<size_t>> booked);

	map<size_t, set<size_t>> get_booked() const;
	map<size_t, size_t> get_seats() const;

	void set_seats_number(const map<size_t, size_t> seats_number);
	int set_booked_seat(const size_t row, const size_t booked_seat);
	void set_booked_seats(map<size_t, set<size_t>>);

	bool remove_booked_seat(const size_t row, const size_t booked_seat);

	bool operator==(Movie_Session& a);
};

wostream& operator<<(wostream& out, Movie_Session& session);
wistream& operator>>(wistream& in, Movie_Session& session);