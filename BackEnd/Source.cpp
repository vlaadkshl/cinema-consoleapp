#include "Cinema.h"
#include "Console_GUI.h"

using namespace std;

int main()
{
	const std::locale utf8_locale = locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Cinema cinema = Cinema();
	Console_GUI cons = Console_GUI(cinema, utf8_locale);

	cons.start();

	wcin.get();
	return 0;
}