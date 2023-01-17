#include "Console_GUI.h"

Console_GUI::Console_GUI(Cinema& cinema, const locale loc) : cinema(cinema), loc(loc) {};

void Console_GUI::clear()
{
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif
}

void Console_GUI::save()
{
	wofstream file(L"cinema.txt");
	if (file.good())
	{
		wcout << L"Вивантаження...\n";
		file.imbue(loc);
		file << cinema;
		wcout << L"Успішно.\n";
	}
	else
		wcout << L"Файл пошкоджений.\n";
	file.close();
}

void Console_GUI::wrong_task() { wcout << L"Некоретний запит. Спробуйте ще раз.\n"; }

wstring Console_GUI::input_movie(int row_num)
{
	wostringstream wout;

	wstring movie_tmp;
	wcout << L"Назва фільму: ";
	getline(wcin, movie_tmp);
	wout << movie_tmp << L"?";

	wcout << L"Мінімальний вік: ";
	getline(wcin, movie_tmp);
	wout << atoi(_bstr_t(movie_tmp.c_str())) << L"?";

	wcout << L"Категорія: ";
	getline(wcin, movie_tmp);
	wout << atoi(_bstr_t(movie_tmp.c_str())) << L"?";

	wcout << L"Рейтинг: ";
	getline(wcin, movie_tmp);
	wout << atof(_bstr_t(movie_tmp.c_str())) << L"?";

	wcout << L"Ціна за квиток: ";
	getline(wcin, movie_tmp);
	wout << atof(_bstr_t(movie_tmp.c_str()));

	wcout << L"Скільки сеансів: ";
	getline(wcin, movie_tmp);
	for (size_t i = 1; i <= atoi(_bstr_t(movie_tmp.c_str())); i++)
	{
		wstring session_tmp;

		wcout << L"Рік: ";
		getline(wcin, session_tmp);
		wout << L"(" << atoi(_bstr_t(session_tmp.c_str())) << L":";

		wcout << L"Місяць: ";
		getline(wcin, session_tmp);
		wout << atoi(_bstr_t(session_tmp.c_str())) << L":";

		wcout << L"День: ";
		getline(wcin, session_tmp);
		wout << atoi(_bstr_t(session_tmp.c_str())) << L":";

		wcout << L"Година: ";
		getline(wcin, session_tmp);
		wout << atoi(_bstr_t(session_tmp.c_str())) << L":";

		wcout << L"Хвилина: ";
		getline(wcin, session_tmp);
		wout << atoi(_bstr_t(session_tmp.c_str())) << L")";

		wcout << L"Заброньовані місця (через кому)\n";
		for (size_t i = 1; i <= row_num; i++)
		{
			wstring booked_tmp;

			wcout << i << L": ";
			getline(wcin, booked_tmp);
			wout << i << L"@" << booked_tmp;
			if (i != row_num) wout << L"|";
		}
	}

	return wout.str();
}
wstring Console_GUI::input_hall()
{
	wstring tmp;
	wostringstream wout;

	wcout << L"Назва: ";
	getline(wcin, tmp);
	wout << tmp << L"(";

	wcout << L"Скільки рядів: ";
	getline(wcin, tmp);
	size_t row_num = atoi(_bstr_t(tmp.c_str()));
	for (size_t i = 1; i <= row_num; i++)
	{
		wstring rows_tmp;
		wcout << L"Ряд №" << i << L": ";
		getline(wcin, rows_tmp);
		wout << i << L":" << atoi(_bstr_t(rows_tmp.c_str()));

		i != atoi(_bstr_t(tmp.c_str())) ? wout << L"*" : wout << L")";
	}

	wcout << L"Скільки фільмів: ";
	getline(wcin, tmp);
	for (size_t i = 1; i <= atoi(_bstr_t(tmp.c_str())); i++)
	{
		wcout << L"ФІЛЬМ " << i << endl;
		wout << input_movie(row_num);
	}

	return wout.str();
}

void Console_GUI::start()
{
	SetConsoleTitle(L"Кінотеатр. Курсова");

	wstring tmp;
	bool is_begin = true;
	while (is_begin)
	{
		wcout << L"Що ви бажаєте?\n";
		wcout << L"1.\tЗаповнити з текстового файлу\n2.\tЗаповнити вручну\n0.\tВийти з програми\n";

		getline(wcin, tmp);
		switch (atoi(_bstr_t(tmp.c_str())))
		{
		case 1:
		{
			SetConsoleTitle(L"Заповнюється...");
			wcout << L"Ви вибрали: Заповнити з текстового файлу\n";

			wifstream fin_text("cinema.txt");
			fin_text.imbue(loc);
			if (fin_text.eof())
			{
				wcout << L"Цей файл пустий. Спробуйте знову.\n";
				continue;
			}
			else
			{
				fin_text >> cinema;
				wcout << L"Заповнено.\n";
				fin_text.close();
			}
			is_begin = false;
			break;
		}
		case 2:
		{
			SetConsoleTitle(L"Введення інформації — Кінотеатр. Курсова");
			wostringstream wout;

			wstring tmp;
			wcout << L"Назва кінотеатру: ";
			getline(wcin, tmp);
			wout << tmp << L"\n";

			wcout << L"\nСкільки кінозалів у кінотеатрі: ";
			getline(wcin, tmp);
			for (size_t i = 1; i <= atoi(_bstr_t(tmp.c_str())); i++)
			{
				wcout << L"КІНОЗАЛ " << i << endl;
				wout << input_hall();
				if (i != atoi(_bstr_t(tmp.c_str()))) wout << L"\n";
			}

			wistringstream w_in(wout.str());
			w_in >> cinema;

			save();

			is_begin = false;
			break;
		}
		case 0:
			exit(0);
		default:
		{
			wrong_task();
			continue;
		}
		}
	}

	main_screen();
}

int Console_GUI::main_screen()
{
	clear();

	wcout << L"Дані завантажено.\n\n";
	wcout << L"=================================================\n\n";

	wstring tmp;
	bool isnotexit = true;
	while (isnotexit)
	{
		SetConsoleTitle(L"Головна — Кінотеатр");

		wcout << L"Оберіть дію:\n";
		wcout << L"1)\tПереглянути фільми\n" << L"0)\tВийти з програми\n";
		wcout << L"ВВЕДІТЬ КОМАНДУ: \n";

		getline(wcin, tmp);
		size_t command = atoi(_bstr_t(tmp.c_str()));

		switch (command)
		{
		case 1:
			clear();
			movies_actions();
			break;
		case 0:
			save();
			exit(0);
		default:
			wrong_task();
			continue;
		}
	}
}

void Console_GUI::movies_actions()
{
	wstring tmp;
	bool isnotbreak = true;
	while (isnotbreak)
	{
		SetConsoleTitle(L"Переглянути фільми — Кінотеатр");

		for (auto hall : cinema.get_halls())
		{
			wcout << L"Кінозал " << hall.get_name() << L":\n";
			for (auto movie : hall.get_movies())
				wcout << movie.get_name() << L": " << movie.get_price() << L" грн" << endl;
			wcout << endl;
		}

		wcout << L"Оберіть дію:\n";
		wcout << L"1)\tПереглянути фільм та дії до нього\n" << L"2)\tДодати фільм\n" << L"3)\tДодати кінозал\n" << L"4)\tВидалити кінозал\n" << L"0)\tВийти на головне меню\n";

		getline(wcin, tmp);
		size_t command = atoi(_bstr_t(tmp.c_str()));

		switch (command)
		{
		case 1:
		{
			SetConsoleTitle(L"Переглянути фільм та дії до нього — Кінотеатр");

			wcout << L"Введіть повну назву фільму: ";
			bool isOK = true;
			while (isOK)
			{
				SetConsoleTitle(L"Переглянути фільм та дії до нього — Кінотеатр");

				wstring name_tmp;
				getline(wcin, name_tmp);
				Movie* mov = cinema.find_movie_by_name(name_tmp);
				if (mov != nullptr)
				{
					clear();
					switch (movie_actions(mov))
					{
					case 0:
						clear();
						isOK = false;
						break;
					case 1:
						clear();
						isnotbreak = false;
						isOK = false;
						break;
					default:
						break;
					}
				}
				else
				{
					wcout << L"Фільм не знайдено. Спробуйте ще раз...\n";
					isOK = false;
				}
			}
		}
		break;
		case 2:
		{
			SetConsoleTitle(L"Додати фільм — Кінотеатр");

			bool isOK = true;
			while (isOK)
			{
				wcout << L"Введіть назву кінозалу: ";

				wstring tmp;
				getline(wcin, tmp);
				Cinema_Hall* hall = cinema.find_hall(tmp);
				if (hall != nullptr)
				{
					auto seats = hall->get_seats_number();
					Movie tmp_movie = Movie(seats);
					wistringstream w_in(input_movie(seats.size()));
					w_in >> tmp_movie;

					hall->add_movie(tmp_movie);

					isOK = false;
					clear();
					save();
				}
				else
				{
					wcout << L"Кінозал не знайдено. Спробуйте ще раз...\n";
					isOK = false;
				}
			}
		}
		break;
		case 3:
		{
			wistringstream w_in(input_hall());
			Cinema_Hall tmp = Cinema_Hall(cinema.get_halls()[0].get_seats_number());
			w_in >> tmp;

			cinema.add_hall(tmp);

			save();
			clear();
		}
		break;
		case 4:
		{
			wcout << L"Введіть назву кінозалу: ";
			wstring tmp;
			getline(wcin, tmp);
			if (cinema.remove_hall(tmp) == 0)
				save();
			else
				wcout << L"Неправильна назва залу.\n";

			clear();
		}
		break;
		case 0:
			clear();
			return;
		default:
			wrong_task();
			continue;
		}
	}
}

int Console_GUI::movie_actions(Movie* mov)
{
	SetConsoleTitle(mov->get_name().c_str());
	wstring tmp;
	while (true)
	{
		clear();

		wcout << L"Фільм \"" << mov->get_name() << "\":\n";
		wcout << L"Мінімальний вік для перегляду: " << mov->get_min_age() << endl;
		wcout << L"Категорія: " << mov->listNameGetre[mov->get_category()] << endl;
		wcout << L"Рейтинг: " << mov->get_rating() << endl;
		wcout << L"Ціна за квиток: " << mov->get_price() << endl << endl;

		wcout << L"Оберіть дію:\n";
		wcout << L"1)\tПридбати квиток\n" << L"========\n2)\tЗмінити дані фільму\n" << L"3)\tВидалити фільм\n" << L"========\n9)\tПовернутися назад\n" << L"0)\tВийти до головного меню\n";

		getline(wcin, tmp);
		size_t command = atoi(_bstr_t(tmp.c_str()));

		switch (command)
		{
		case 1:
		{
			auto sessions = mov->get_sessions();

			time_t now = time(0);
			struct tm date_now;
			localtime_s(&date_now, &now);
			date_now.tm_sec = 0;

			auto it = find_if(sessions.begin(), sessions.end(),
				[date_now](pair<tm, Movie_Session> elem)
				{
					tm date = elem.first;
					return (date.tm_year + (date.tm_mon + 1) / 12 + date.tm_mday / (31 * 12) + date.tm_hour / (31 * 12 * 24) + date.tm_min / (31 * 12 * 24 * 60))
						>= (date_now.tm_year + (date_now.tm_mon + 1) / 12 + date_now.tm_mday / (31 * 12) + date_now.tm_hour / (31 * 12 * 24) + date_now.tm_min / (31 * 12 * 24 * 60));
				}
			);

			if (it != sessions.end())
			{
				vector<Movie_Session> sessions_tmp;

				for (size_t i = 1; it != sessions.end(); ++it, ++i)
				{
					auto date = it->first;
					wcout << L"Сеанс " << i << L": " << date.tm_year + 1900 << L"-" << date.tm_mon + 1 << L"-" << date.tm_mday << L" " << date.tm_hour << ":" << date.tm_min << endl;

					sessions_tmp.push_back(it->second);
				}

				wcout << L"Введіть сеанс, в якому купується місце:\n";
				wstring tmp;
				getline(wcin, tmp);
				size_t num = atoi(_bstr_t(tmp.c_str())) - 1;
				Movie_Session session = sessions_tmp[num];

				wcout << L"Всього рядів: " << session.get_seats().size() << endl;
				wcout << L"Заброньовані:\n";

				auto booked = session.get_booked();
				auto it = booked.begin(); ++it;
				for (; it != booked.end(); ++it)
				{
					wcout << it->first << L":\t";
					for (size_t i : it->second)
					{
						wcout << i;
						i != *--it->second.end() ? wcout << L", " : wcout << endl;
					}
				}

				wcout << L"Введіть ряд: ";
				getline(wcin, tmp);
				size_t row = atoi(_bstr_t(tmp.c_str()));

				wcout << L"Введіть місце: ";
				getline(wcin, tmp);
				size_t seat = atoi(_bstr_t(tmp.c_str()));

				Movie_Session& sess = mov->get_session(session);
				sess.set_booked_seat(row, seat);

				save();
			}
			else
			{
				wcout << L"Доступних сеансів немає. Спробуйте інший фільм.\n";
				break;
			}
		}
		break;
		break;
		case 2:
		{
			bool isnotbreak = true;
			while (isnotbreak)
			{
				wcout << L"Що ви хочете змінити?\n";
				wcout << L"1)\tНазву\n" << L"2)\tМінімальний вік\n" << L"3)\tКатегорію\n" << L"4)\tРейтинг\n" << L"5)\tЦіну за 1 квиток\n";

				wstring tmp;
				getline(wcin, tmp);
				size_t command = atoi(_bstr_t(tmp.c_str()));

				switch (command)
				{
				case 1:
				{
					wcout << L"Введіть назву: ";
					getline(wcin, tmp);
					mov->set_name(tmp);
					isnotbreak = false;
				}
				break;
				case 2:
				{
					while (true)
					{
						wcout << L"Введіть мінімальний вік (від 0 до 21): ";
						getline(wcin, tmp);
						size_t age = atoi(_bstr_t(tmp.c_str()));
						if (age >= 0 && age <= 21)
						{
							mov->set_min_age(age);
							break;
						}
						else
						{
							wcout << L"Неправильний вік. Введіть ще раз.\n";
							continue;
						}
					}
					isnotbreak = false;
				}
				break;
				case 3:
				{
					wcout << L"Доступні категорії:\n";
					for (size_t i = 0; i < (int)NUMBER_GENRE - 1; i++)
						wcout << i + 1 << ": " << mov->listNameGetre[i] << endl;

					while (true)
					{
						wcout << L"Введіть номер категорії, на яку ви хочете змінити фільм: ";
						getline(wcin, tmp);
						size_t cat = atoi(_bstr_t(tmp.c_str()));
						if (cat >= 0 && cat <= (int)NUMBER_GENRE - 1)
						{
							mov->set_category((Categories)cat);
							break;
						}
						else
						{
							wcout << L"Неправильна категорія. Введіть ще раз.\n";
							continue;
						}
					}
					isnotbreak = false;
				}
				break;
				case 4:
					while (true)
					{
						wcout << L"Введіть рейтинг (від 0 до 10): ";
						getline(wcin, tmp);
						float rating = atof(_bstr_t(tmp.c_str()));
						if (rating >= 0. && rating <= 10.)
						{
							mov->set_rating(rating);
							break;
						}
						else
						{
							wcout << L"Неправильний рейтинг. Введіть ще раз.\n";
							continue;
						}
					}
					isnotbreak = false;
					break;
				case 5:
					while (true)
					{
						wcout << L"Введіть ціну за квиток (більше 0 грн): ";
						getline(wcin, tmp);
						float price = atof(_bstr_t(tmp.c_str()));
						if (price >= 0.)
						{
							mov->set_price(price);
							break;
						}
						else
						{
							wcout << L"Неправильний рейтинг. Введіть ще раз.\n";
							continue;
						}
					}
					isnotbreak = false;
					break;
				default:
					wrong_task();
					break;
				}
			}
		}
		break;
		case 3:
		{
			cinema.delete_movie(mov->get_name());
			clear();
			save();
		}
		return 0;
		case 9:
			save();
			return 0;
		case 0:
			save();
			return 1;
		default:
			wrong_task();
			break;
		}
	}
}