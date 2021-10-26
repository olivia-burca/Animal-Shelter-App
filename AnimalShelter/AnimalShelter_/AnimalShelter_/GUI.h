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
#include <QtWidgets/qradiobutton.h>

#include <vector>
#include <algorithm>
#include "iterator.h"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(QWidget* parent = 0);
	~GUI();
private:
	Repo* repo;
	MemRepo* list;
	//Iterator it;
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
	QPushButton* seeListButton;
	QRadioButton* CSVButton;
	QRadioButton* HTMLButton;



	std::vector<Dog> dogVector;
	std::vector<Dog> listVector;
	void init();
	void populate();
	void populateList();
	//int getSelectedDogIndex();
	//void populateList();

	void connectSignalsAndSlots();


private slots:
	void addDog();
	void adoptDog();
	void deleteDog();
	void updateAge();
	void updatePhoto();
	void seeAdoptionList();
	//void configIterator();
};