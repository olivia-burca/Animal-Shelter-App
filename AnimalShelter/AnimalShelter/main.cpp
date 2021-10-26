#include <iostream>
#include "domain.h"
#include "repo.h"
#include "file_repo.h"
#include "ui.h"
#include "tests.h"
#include "GUI.h"
#include <string.h>
#include <assert.h>
#include <QtWidgets/QApplication>

using namespace std;
/*
int main()
{
	UI ui;
	ui.startMe();
	//Tests tests;
	//tests.runTests();

	return 0;
}*/


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	
	GUI w; 
	w.show();
	return a.exec();
} 
