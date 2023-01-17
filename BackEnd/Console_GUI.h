#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>

#include <Windows.h>
#include <comutil.h>

#include "Cinema.h"

class Console_GUI
{
	Cinema& cinema;
	const locale loc;

	void wrong_task();

	void clear();
	void save();
	int main_screen();

	void movies_actions();
	int movie_actions(Movie* mov);

	wstring input_movie(int row_num);
	wstring input_hall();

public:
	Console_GUI(Cinema& cinema, const locale loc);

	void start();
};