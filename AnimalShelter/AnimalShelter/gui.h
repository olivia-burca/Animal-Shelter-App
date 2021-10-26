#pragma once
#include <QtWidgets/QMainWindow>
#include "ui.h"
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qbuttongroup.h>

#include <vector>
#include <algorithm>


class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI( QWidget* parent = 0);
	~GUI();
private:
	Repo* repo;
	MemRepo* list;
	// lists
	QListWidget* repoWidget;
	QListWidget* listWidget;

	// form		
	QLineEdit* nameInput;
	QLineEdit* breedInput;
	QLineEdit* ageInput;
	QLineEdit* photoInput;
	

	// buttons
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* moveOneButton;
	QPushButton* updateAgeButton;
	QPushButton* updatePhotoButton;
	

	

	std::vector<Dog> dogVector;
	void init();
	void populate();
	int getSelectedDogIndex();
	void populateList();

	void connectSignalsAndSlots();
	

private slots:
	void addDog();
	void adoptDog();
	void deleteDog();
};