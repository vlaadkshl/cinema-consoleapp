#include "Movie_Session.h"

Movie_Session::Movie_Session(map<size_t, size_t> seats_number) : seats_number(seats_number)
{ for (auto seat : seats_number) booked_seats[seat.first].insert({}); }
Movie_Session::Movie_Session(map<size_t, size_t> seats_number, map<size_t, set<size_t>> booked) : seats_number(seats_number), booked_seats(booked) {}

map<size_t, set<size_t>> Movie_Session::get_booked() const { return this->booked_seats; }
map<size_t, size_t> Movie_Session::get_seats() const { return this->seats_number; }

void Movie_Session::set_seats_number(const map<size_t, size_t> seats_number) { this->seats_number = seats_number; }
int Movie_Session::set_booked_seat(const size_t row, size_t booked_seat)
{
	size_t row_number = (--seats_number.end())->first;
	if (booked_seat <= seats_number[row])
	{
		if (row <= row_number)
		{
			if (booked_seats[row].insert(booked_seat).second)
				return 0;
			else
				return 1;
		}
		else
		{
			auto end = booked_seats.end();
			--end;
			if (end->second.insert(booked_seat).second)
				return 0;
			else
				return 2;
		}
	}
	else return 3;
}
void Movie_Session::set_booked_seats(map<size_t, set<size_t>> seats) { this->booked_seats = seats; }

bool Movie_Session::remove_booked_seat(const size_t row, const size_t booked_seat) { return this->booked_seats[row].erase(booked_seat); }

bool Movie_Session::operator==(Movie_Session& a) { return booked_seats == a.booked_seats && seats_number == a.seats_number; }

wistream& operator>>(wistream& in, Movie_Session& session)
{
	//	Ряд@Бронь,Бронь|Ряд@Бронь,Бронь,Бронь|Ряд@Бронь

	map<size_t, set<size_t>> booked_tmp;
	wstring tmp;

	while (!in.eof())
	{
		getline(in, tmp, L'|');
		wistringstream row(tmp);

		while (!row.eof())
		{
			wstring row_string;

			getline(row, row_string, L'@');
			size_t row_tmp = atoi(_bstr_t(row_string.c_str()));

			getline(row, row_string);
			wistringstream reserved_stream(row_string);
			set<size_t> booked_seats_tmp;
			while (!reserved_stream.eof())
			{
				wstring reserved_string;
				getline(reserved_stream, reserved_string, L',');
				booked_seats_tmp.emplace(atoi(_bstr_t(reserved_string.c_str())));
			}

			booked_tmp.emplace(make_pair(row_tmp, booked_seats_tmp));
		}
	}
	session.set_booked_seats(booked_tmp);

	return in;
}
wostream& operator<<(wostream& out, Movie_Session& session)
{
	//	Ряд@Бронь,Бронь|Ряд@Бронь,Бронь,Бронь|Ряд@Бронь

	int i = 1;
	for (auto row : session.get_booked())
	{
		out << row.first << L"@";
		for (auto it = row.second.begin(); it != row.second.end(); it++)
		{
			out << *it;
			auto limit = row.second.end();
			--limit;
			if (it != limit)
				out << L",";
		}

		if (i < session.get_booked().size())
			out << L"|";
		i++;
	}
	return out;
}