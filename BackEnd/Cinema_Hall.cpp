#include "Cinema_Hall.h"

Cinema_Hall::Cinema_Hall() :
	hall_name(L"Default Example")
{
	this->seats_number = map<size_t, size_t>();
	for (size_t i = 1; i <= 10; i++)
		movies.push_back(Movie(seats_number));
}

Cinema_Hall::Cinema_Hall(map<size_t, size_t> seats_number) :
	seats_number(seats_number), hall_name(L"Hall Example")
{
	for (size_t i = 1; i <= 10; i++)
		movies.push_back(Movie(seats_number));
}

Cinema_Hall::Cinema_Hall(wstring name, vector<Movie> movies, map<size_t, size_t> seats_number) :
	hall_name(name), movies(movies), seats_number(seats_number)
{ for (Movie& movie : movies) movie.set_seats_number(seats_number); }

wstring Cinema_Hall::get_name() const { return this->hall_name; }
vector<Movie> Cinema_Hall::get_movies() const { return movies; }
vector<Movie>& Cinema_Hall::get_movies_addr() { return movies; }
map<size_t, size_t> Cinema_Hall::get_seats_number() const { return seats_number; }

void Cinema_Hall::add_movie(Movie mov) { movies.push_back(mov); }
void Cinema_Hall::delete_movie(wstring name) { movies.erase(find_if(movies.begin(), movies.end(), [name](Movie& mov) {return mov.get_name() == name; })); }
void Cinema_Hall::erase_movies() { movies.erase(movies.begin(), movies.end()); }

void Cinema_Hall::set_name(wstring name) { this->hall_name = name; }
void Cinema_Hall::set_movies(vector<Movie> movies) { this->movies = movies; }
void Cinema_Hall::set_seats(map<size_t, size_t> seats_number) { this->seats_number = seats_number; }

Cinema_Hall& Cinema_Hall::operator=(const Cinema_Hall& a)
{
	hall_name = a.hall_name;
	movies = a.movies;
	seats_number = a.seats_number;

	return *this;
}

wistream& operator>>(wistream& in, Cinema_Hall& hall)
{
	//	Íàçâà(Ðÿä:Ì³ñöÿ*Ðÿä:Ì³ñöÿ*Ðÿä:Ì³ñöÿ)Ê³íî\tÊ³íî\tÊ³íî\n

	wstring tmp;
	getline(in, tmp, L'(');
	hall.set_name(tmp);

	getline(in, tmp, L')');
	wistringstream rows(tmp);
	map<size_t, size_t> tmp_rows;
	wstring row;
	while (!rows.eof())
	{
		getline(rows, row, L'*');

		wistringstream one_row(row);
		while (!one_row.eof())
		{
			wstring tmp;
			getline(one_row, tmp, L':');
			size_t row_num = atoi(_bstr_t(tmp.c_str()));

			getline(one_row, tmp);
			size_t seats_num = atoi(_bstr_t(tmp.c_str()));

			tmp_rows.insert(make_pair(row_num, seats_num));
		}
	}
	hall.set_seats(tmp_rows);

	getline(in, tmp);
	wistringstream moviestream(tmp);
	hall.erase_movies();
	vector<Movie> tmp_movies;
	while (!moviestream.eof())
	{
		wstring tmp_mov;
		getline(moviestream, tmp_mov, L'\t');
		wistringstream one_movie_stream(tmp_mov);

		Movie tmp_movie = Movie(tmp_rows);
		one_movie_stream >> tmp_movie;
		tmp_movies.push_back(tmp_movie);
	}
	hall.set_movies(tmp_movies);

	return in;
}
wostream& operator<<(wostream& out, const Cinema_Hall& hall)
{
	//	Íàçâà(Ðÿä:Ì³ñöÿ*Ðÿä:Ì³ñöÿ*Ðÿä:Ì³ñöÿ)Ê³íî\tÊ³íî\tÊ³íî\n

	out << hall.get_name() << L"(";

	map<size_t, size_t> seats = hall.get_seats_number();
	for (auto i = seats.begin(); i != seats.end(); i++)
	{
		out << i->first << L":" << i->second;
		if (i != --seats.end()) out << L"*";
	}
	out << L")";

	vector<Movie> movies = hall.get_movies();
	for (auto i = movies.begin(); i != movies.end(); i++)
	{
		out << *i;
		auto limit = movies.end();
		limit--;
		if (i != limit)
			out << L"\t";
	}
	return out;
}

bool operator<(const Cinema_Hall& a, const Cinema_Hall& b) { return a.get_name() < b.get_name(); }