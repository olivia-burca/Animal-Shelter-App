#include "GUI.h"
#include <sstream>
#include "dog_validator.h"
#include <iostream>
#include "repo_exception.h"
#include "file_repo.h"
#include "qdebug.h"
#include <typeinfo>

using namespace std;

GUI::GUI(QWidget* parent) : QWidget{ parent }
{
	this->init();
	this->repo = new FileRepo("file3.txt");;
	this->list = new MemRepo;
	this->dogVector = this->repo->getDA();
	this->populate();
}

GUI::~GUI()
{
	delete repoWidget;
	delete listWidget;
}

void GUI::init()
{
	this->setWindowTitle("Animal Shelter");
	this->setWindowIcon(QIcon("./puppy.ico"));
	this->setStyleSheet("background-color: burlywood;");
	//General layout of the window
	QHBoxLayout* layout = new QHBoxLayout{ this };


	QWidget* leftW = new QWidget{};
	QVBoxLayout* leftSide = new QVBoxLayout{ leftW };

	// List
	this->repoWidget = new QListWidget{};
	// Set the selection model
	this->repoWidget->setSelectionMode(QAbstractItemView::SingleSelection);

	// Dog form
	QWidget* tutorialDataWidget = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ tutorialDataWidget };
	this->nameInput = new QLineEdit{};
	this->breedInput = new QLineEdit{};
	this->ageInput = new QLineEdit{};
	this->photoInput = new QLineEdit{};

	formLayout->addRow("&Name:", nameInput);
	formLayout->addRow("&Breed:", breedInput);
	formLayout->addRow("&Age:", ageInput);
	formLayout->addRow("&Photo:", photoInput);


	// buttons
	QWidget* buttonsWidget = new QWidget{};
	QGridLayout* gridLayout = new QGridLayout{ buttonsWidget };
	this->addButton = new QPushButton("Add a dog");
	this->deleteButton = new QPushButton("Remove a dog");
	this->updateAgeButton = new QPushButton("Update the age of a dog");
	this->updatePhotoButton = new QPushButton("Update the photo of a dog");

	gridLayout->addWidget(addButton, 0, 0);
	gridLayout->addWidget(deleteButton, 0, 1);
	gridLayout->addWidget(updateAgeButton, 1, 0);
	gridLayout->addWidget(updatePhotoButton, 1, 1);

	// add everything to the left layout
	leftSide->addWidget(new QLabel{ "Dogs" });
	leftSide->addWidget(repoWidget);
	leftSide->addWidget(tutorialDataWidget);
	leftSide->addWidget(buttonsWidget);

	// middle side widget:
	// - move one dog to adoption list 
	QWidget* middleW = new QWidget{};
	QVBoxLayout* vLayoutMiddle = new QVBoxLayout{ middleW };
	this->moveOneButton = new QPushButton{ "Adopt dog" };

	QWidget* upperPart = new QWidget{};
	QWidget* lowerPart = new QWidget{};
	QVBoxLayout* vLayoutUpperPart = new QVBoxLayout{ upperPart };
	vLayoutUpperPart->addWidget(moveOneButton);

	vLayoutMiddle->addWidget(upperPart);
	vLayoutMiddle->addWidget(lowerPart);

	// right sidw widget - the watchlist
	QWidget* rightW = new QWidget{};
	QVBoxLayout* rightSide = new QVBoxLayout{ rightW };


	listWidget = new QListWidget{};

	
	QWidget* watchlistButtonsWidget = new QWidget{};
	QHBoxLayout* watchlistButtonsLayout = new QHBoxLayout{ watchlistButtonsWidget };
	
	this->seeListButton = new QPushButton{ "See adoption list in corresponding format" };
	this->CSVButton = new QRadioButton{ "CSV" };
	this->HTMLButton = new QRadioButton{ "HTML" };
	watchlistButtonsLayout->addWidget( this->seeListButton);
	watchlistButtonsLayout->addWidget(this->CSVButton);
	watchlistButtonsLayout->addWidget(this->HTMLButton);
	

	// create the right widget
	rightSide->addWidget(new QLabel{ "Adoption list" });
	rightSide->addWidget(listWidget);
	rightSide->addWidget(watchlistButtonsWidget);

	// compose the main layout with the three created widgets
	layout->addWidget(leftW);
	layout->addWidget(middleW);
	layout->addWidget(rightW);

	// connect the signals and slots
	this->connectSignalsAndSlots();
}

void GUI::populate()
{

	if (repoWidget->count() != 0)
		repoWidget->clear();


	for (auto t : dogVector) {
		QString listItem = QString::fromStdString(t.toString());
		QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
		this->repoWidget->addItem(listItemWidget);
	}

	// set the first element to be selected
	if (dogVector.size() > 0)
		repoWidget->setCurrentRow(0);
}

void GUI::populateList()
{

	if (listWidget->count() != 0)
		listWidget->clear();


	for (auto t : listVector) {
		QString listItem = QString::fromStdString(t.toString());
		QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
		this->listWidget->addItem(listItemWidget);
	}

	// set the first element to be selected
	if (listVector.size() > 0)
		repoWidget->setCurrentRow(0);
}


void GUI::addDog()
{
	std::string name = nameInput->text().toStdString();
	std::string breed = breedInput->text().toStdString();
	std::string age = ageInput->text().toStdString();

	std::string photo = photoInput->text().toStdString();
	std::string dogString = name + ',' + breed + ',' + age + ',' + photo;

	std::stringstream stream{ dogString };
	try
	{
		Dog t;
		stream >> t;
		this->repo->addDog(t);
		// refresh the list
		dogVector = this->repo->getDA();
		this->populate();
	}
	catch (DogException& e)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
	}
	catch (RepoException& e)
	{
		std::cout << e.what();
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Cannot add element! Dog already existing");
	}
}

void GUI::deleteDog()
{
	QItemSelectionModel* select = this->repoWidget->selectionModel();
	QModelIndexList s = select->selectedRows();
	if (s.isEmpty()) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", QString::fromStdString("Null is undeletable!"));
		return;
	}
	auto index = s.at(0);
	//auto index = 
	if (index.isValid()) {
		QString cellText = index.data().toString();
		qDebug() << cellText;
		int row = index.row();
		auto v = this->repo->removeDog(row);
		dogVector = this->repo->getDA();
		this->populate();
	}
}


void GUI::updateAge()
{
	std::string name = nameInput->text().toStdString();
	
	std::string age = ageInput->text().toStdString();

	
	if (this->repo->searchByName(name) == -1)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", QString::fromStdString("A dog with this name doesn't exist!"));
	}
	else
	{
		int pos = this->repo->searchByName(name);
		if (age == this->repo->getDA()[pos].getAge())
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Error", QString::fromStdString("Cannot update with the same age!"));
		}
		else
		{
			try {
				int age_ = stoul(age);
				this->repo->updateAge(name, age);
			}
			catch (invalid_argument) {
				QMessageBox messageBox;
				messageBox.critical(0, "Error", QString::fromStdString("Invalid data! Age must be an integer."));
			}
		}
		// refresh the list
		dogVector = this->repo->getDA();
		this->populate();
	}
	

	

}

void GUI::adoptDog()
{
	if (!this->CSVButton->isChecked() && !this->HTMLButton->isChecked())
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", QString::fromStdString("Before adopting a dog, choose a format for the list: CSV or HTML!"));
	}
	else
	{
		//if (this->list->getDA().size() == 0)
		//{
			if (this->CSVButton->isChecked())
			{
				vector<Dog> v = this->list->getDA();
				delete this->list;
				this->list = new CSVList;
				for (int i = 0; i < v.size(); i++)
					this->list->adoptDog(v[i]);
			}
			else if (this->HTMLButton->isChecked())
			{
				vector<Dog> v = this->list->getDA();
				delete this->list;
				this->list = new HTMLList;
				for (int i = 0; i < v.size(); i++)
					this->list->adoptDog(v[i]);
			}
		//}

			
		QItemSelectionModel* select = this->repoWidget->selectionModel();
		QModelIndexList s = select->selectedRows();
		if (s.isEmpty()) {
			QMessageBox messageBox;
			messageBox.critical(0, "Error", QString::fromStdString("Cannot adopt NULL!"));
			return;
		}
		auto index = s.at(0);
		//auto index = 
		if (index.isValid()) {
			QString cellText = index.data().toString();
			qDebug() << cellText;
			int row = index.row();
			Dog d = this->repo->getDA()[row];
			this->list->adoptDog(d);
			auto v = this->repo->removeDog(row);
			dogVector = this->repo->getDA();
			listVector = this->list->getDA();
			this->populate();
			this->populateList();
		}
		this->list->save();
	}

	
}

void GUI::updatePhoto()
{
	std::string name = nameInput->text().toStdString();

	std::string photo = photoInput->text().toStdString();


	if (this->repo->searchByName(name) == -1)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", QString::fromStdString("A dog with this name doesn't exist!"));
	}
	else
	{
		int pos = this->repo->searchByName(name);
		if (photo == this->repo->getDA()[pos].getPhoto())
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Error", QString::fromStdString("Cannot update with the same photo!"));
		}
		else
		{
			int i1 = photo.find("www");
			int i2 = photo.find("http");
			if (i1 != 0 && i2 != 0)
			{
				QMessageBox messageBox;
				messageBox.critical(0, "Error", QString::fromStdString("The link of the photo must start with 'www' or 'http' !"));
			}
			else
			{
				this->repo->updatePhoto(name, photo);
				// refresh the list
				dogVector = this->repo->getDA();
				this->populate();
			}
				
		}
	
	}
}

void GUI::seeAdoptionList()
{
	if (this->CSVButton->isChecked())
	{
		vector<Dog> v = this->list->getDA();
		delete this->list;
		this->list = new CSVList;
		for (int i = 0; i < v.size(); i++)
			this->list->adoptDog(v[i]);
	}
	else if (this->HTMLButton->isChecked())
	{
		vector<Dog> v = this->list->getDA();
		delete this->list;
		this->list = new HTMLList;
		for (int i = 0; i < v.size(); i++)
			this->list->adoptDog(v[i]);
	}
	this->list->save();

	this->list->openInApp();
}

// connects all the components to their callbacks
void GUI::connectSignalsAndSlots() {
	// connect repository widget and add a callback that modifies the selection of the dogs
	QObject::connect(repoWidget, SIGNAL(itemSelectionChanged()), this, SLOT(listItemChanged()));

	// add button
	// connect the addButton to the callback that is called when the clicked() event happened
	QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(addDog()));

	QObject::connect(this->deleteButton, SIGNAL(clicked()), this, SLOT(deleteDog()));

	QObject::connect(this->updateAgeButton, SIGNAL(clicked()), this, SLOT(updateAge()));

	QObject::connect(this->updatePhotoButton, SIGNAL(clicked()), this, SLOT(updatePhoto()));

	QObject::connect(this->moveOneButton, SIGNAL(clicked()), this, SLOT(adoptDog()));

	QObject::connect(this->seeListButton, SIGNAL(clicked()), this, SLOT(seeAdoptionList()));

}