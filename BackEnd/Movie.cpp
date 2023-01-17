#include "Movie.h"

Movie::Movie(map<size_t, size_t> seats_number) :
	movie_name(L"Movie Example"),
	min_age(6),
	category(Categories::COMEDY),
	rating(10.),
	price(50.),
	seats_num(seats_number)
{
	for (int day = 1; day <= 10; day++)
	{
		time_t now = time(0);
		struct tm now_date;
		localtime_s(&now_date, &now);

		now_date.tm_mon--;
		now_date.tm_mday = day;
		movie_sessions.insert(make_pair(now_date, Movie_Session(seats_number)));
	}

}
Movie::Movie(map<size_t, size_t> seats_number, wstring name, int min_age, Categories category, float rating, float price, map<tm, Movie_Session> sessions) :
	movie_name(name),
	min_age(min_age),
	category(category),
	rating(rating),
	price(price),
	movie_sessions(sessions)
{
	for (auto& session : movie_sessions)
		session.second.set_seats_number(seats_number);
}

wstring Movie::get_name() const { return this->movie_name; }
int Movie::get_min_age() const { return this->min_age; }
Categories Movie::get_category() const { return this->category; }
float Movie::get_rating() const { return this->rating; }
float Movie::get_price() const { return this->price; }

map<tm, Movie_Session> Movie::get_sessions() const { return movie_sessions; }
map<size_t, size_t> Movie::get_seats_num() const { return this->seats_num; }
Movie_Session& Movie::get_session(Movie_Session sess)
{
	for (auto& elem : movie_sessions)
	{
		Movie_Session& session = elem.second;
		if (elem.second == sess)
			return elem.second;
	}
}

void Movie::set_name(wstring name) { this->movie_name = name; }
void Movie::set_min_age(int age) { this->min_age = age; }
void Movie::set_category(Categories cat) { this->category = cat; }
void Movie::set_rating(float rating) { this->rating = rating; }
void Movie::set_price(float price) { this->price = price; }
void Movie::set_sessions(map <tm, Movie_Session> sessions) { this->movie_sessions = sessions; }
void Movie::set_seats_number(map<size_t, size_t> seats_number)
{
	for (auto& session : movie_sessions)
		session.second.set_seats_number(seats_number);
}

void Movie::erase_sessions() { movie_sessions.clear(); }

bool Movie::operator==(const Movie& second)
{
	if (
		min_age == second.get_min_age() &&
		category == second.get_category() &&
		rating == second.get_rating() &&
		price == second.get_price() &&
		movie_name == second.get_name()
		)
		return true;
	else return false;
}
bool Movie::operator==(Movie second)
{
	if (
		min_age == second.get_min_age() &&
		category == second.get_category() &&
		rating == second.get_rating() &&
		price == second.get_price() &&
		movie_name == second.get_name()
		)
		return true;
	else return false;
}
bool Movie::operator<(const Movie& second) { return this->movie_name < second.get_name(); }

wistream& operator>>(wistream& in, Movie& movie)
{
	//	Назва?Вік?Категорія?Рейтинг?Ціна(Рік:Місяць:День:Година:Хвилина)Сеанс(Рік:Місяць:День:Година:Місяць)Сеанс
	wstring tmp;
	getline(in, tmp, L'?');
	movie.set_name(tmp);

	getline(in, tmp, L'?');
	movie.set_min_age(atoi(_bstr_t(tmp.c_str())));

	getline(in, tmp, L'?');
	int cat_number = atoi(_bstr_t(tmp.c_str()));
	Categories cat = (cat_number >= 0 && cat_number <= NUMBER_GENRE) ? (Categories)cat_number : ACTION;
	movie.set_category(cat);

	getline(in, tmp, L'?');
	movie.set_rating(atof(_bstr_t(tmp.c_str())));

	getline(in, tmp, L'(');
	movie.set_price(atof(_bstr_t(tmp.c_str())));

	getline(in, tmp);
	wistringstream sessions_stream(tmp);
	movie.erase_sessions();
	map<tm, Movie_Session> sessions_tmp;
	vector<Movie_Session> test;
	wstring tmp_session;
	while (!sessions_stream.eof())
	{
		time_t now = time(0);
		struct tm date_tmp;
		localtime_s(&date_tmp, &now);
		date_tmp.tm_sec = 0;

		getline(sessions_stream, tmp_session, L':');
		date_tmp.tm_year = atoi(_bstr_t(tmp_session.c_str())) - 1900;

		getline(sessions_stream, tmp_session, L':');
		date_tmp.tm_mon = atoi(_bstr_t(tmp_session.c_str())) - 1;

		getline(sessions_stream, tmp_session, L':');
		date_tmp.tm_mday = atoi(_bstr_t(tmp_session.c_str()));

		getline(sessions_stream, tmp_session, L':');
		date_tmp.tm_hour = atoi(_bstr_t(tmp_session.c_str()));

		getline(sessions_stream, tmp_session, L')');
		date_tmp.tm_min = atoi(_bstr_t(tmp_session.c_str()));

		getline(sessions_stream, tmp_session, L'(');
		Movie_Session tmp_sess = Movie_Session(movie.get_seats_num());
		wistringstream session_stream(tmp_session);
		session_stream >> tmp_sess;

		sessions_tmp.insert(make_pair(date_tmp, tmp_sess));
		test.push_back(tmp_sess);
	}
	movie.set_sessions(sessions_tmp);

	return in;
}
wostream& operator<<(wostream& out, Movie& movie)
{
	//	Назва?Вік?Категорія?Рейтинг?Ціна(Рік:Місяць:День:Година:Хвилина)Сеанс(Рік:Місяць:День:Година:Місяць)Сеанс

	out << movie.get_name() << L"?";
	out << movie.get_min_age() << L"?";
	out << (int)movie.get_category() << L"?";
	out << movie.get_rating() << L"?";
	out << movie.get_price();

	for (auto& session : movie.get_sessions())
	{
		out << L"(";

		tm time = session.first;
		out << time.tm_year + 1900 << L":";
		out << time.tm_mon + 1 << L":";
		out << time.tm_mday << L":";
		out << time.tm_hour << L":";
		out << time.tm_min << L")";

		out << session.second;
	}
	return out;
}

bool operator<(const tm& a, const tm& b)
{
	if (a.tm_year < b.tm_year) return true;
	else if (a.tm_year == b.tm_year)
		if (a.tm_mon < b.tm_mon) return true;
		else if (a.tm_mon == b.tm_mon)
			if (a.tm_mday < b.tm_mday) return true;
			else if (a.tm_mday == b.tm_mday)
				if (a.tm_hour < b.tm_hour) return true;
				else if (a.tm_hour == b.tm_hour)
					if (a.tm_min < b.tm_min) return true;
					else return false;
				else return false;
			else return false;
		else return false;
	else return false;
}