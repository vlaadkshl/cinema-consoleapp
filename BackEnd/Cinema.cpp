#include "Cinema.h"

Cinema::Cinema() : name(L"Cinema Example") { halls.push_back(Cinema_Hall({ {1,3},{2,10},{3,10},{4,3} })); }
Cinema::Cinema(wstring name, vector<Cinema_Hall> halls) : name(name) { this->halls = halls; }

wstring Cinema::get_name() const { return this->name; }
vector<Cinema_Hall> Cinema::get_halls() const { return this->halls; }

//	Пошук зали за назвою фільму
Cinema_Hall* Cinema::find_hall(wstring name, int)
{
	for (Cinema_Hall& hall : halls)
		for (Movie mov : hall.get_movies())
			if (mov.get_name() == name)
				return &hall;

	return nullptr;
}

//	Пошук зали за назвою зали
Cinema_Hall* Cinema::find_hall(wstring name)
{
	for (Cinema_Hall& hall : halls)
		if (hall.get_name() == name)
			return &hall;

	return nullptr;
}

//	Пошук фільму за назвою
Movie* Cinema::find_movie_by_name(wstring name)
{
	for (Cinema_Hall& hall : halls)
		for (auto& movie : hall.get_movies_addr())
			if (movie.get_name() == name)
				return &movie;

	return nullptr;
}

//	Видалити фільм за назвою
void Cinema::delete_movie(wstring name)
{
	Cinema_Hall* hall = find_hall(name, 0);
	hall->delete_movie(name);
}

void Cinema::set_name(wstring name) { this->name = name; }
void Cinema::set_halls(vector<Cinema_Hall> vect) { halls = vect; }

void Cinema::add_hall(Cinema_Hall hall) { this->halls.push_back(hall); }
int Cinema::remove_hall(wstring name)
{
	auto it = find_if(halls.begin(), halls.end(), [name](Cinema_Hall& hall) {return hall.get_name() == name; });
	if (it != halls.end())
	{
		halls.erase(it);
		return 0;
	}
	return 1;
}
void Cinema::erase_halls() { halls.erase(halls.begin(), halls.end()); }

wistream& operator>>(wistream& in, Cinema& cinema)
{
	cinema.erase_halls();

	wstring w_tmp;
	getline(in, w_tmp, L'\n');
	cinema.set_name(w_tmp);

	vector<Cinema_Hall> tmp_vect;
	copy(istream_iterator<Cinema_Hall, wchar_t>(in), istream_iterator<Cinema_Hall, wchar_t>(), back_inserter(tmp_vect));
	cinema.set_halls(tmp_vect);

	return in;
}
wostream& operator<<(wostream& out, const Cinema& cinema)
{
	out << cinema.get_name() << L"\n";
	auto halls = cinema.get_halls();
	for (auto it = halls.begin(); it != halls.end(); ++it)
	{
		out << *it;
		if (it != --halls.end())
			out << L"\n";
	}

	return out;
}