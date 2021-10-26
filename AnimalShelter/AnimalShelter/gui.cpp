#include "gui.h"
#include <sstream>
#include "dog_validator.h"
#include <iostream>
#include "repo_exception.h"
#include "file_repo.h"
using namespace std;

GUI::GUI( QWidget* parent) :  QWidget{ parent }
{
	this->init();
	this->repo =  new FileRepo("file3.txt");;
	this->list = new CSVList;
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
	this->moveOneButton = new QPushButton{ "adopt" };
	
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

	// buttons
	//	- see dog button
	//  - next button
	QWidget* watchlistButtonsWidget = new QWidget{};
	QHBoxLayout* watchlistButtonsLayout = new QHBoxLayout{ watchlistButtonsWidget };
	watchlistButtonsLayout->addWidget(new QPushButton{ "See dog" });
	watchlistButtonsLayout->addWidget(new QPushButton{ "Next" });

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

int GUI::getSelectedDogIndex()
{
	if (repoWidget->count() == 0)
		return -1;
	QModelIndexList indexList = this->repoWidget->selectionModel()->selectedIndexes();
	if (indexList.size() == 0)
	{
		nameInput->clear();
		breedInput->clear();
		ageInput->clear();
		photoInput->clear();
		
		return -1;
	}
	int index = indexList.at(0).row();
	return index;
}

void GUI::populateList()
{
	// empty the list
	if (listWidget->count() == 0)
		 listWidget->clear();

	for (auto t : this->list->getDA())
	{
		QString itemInList = QString::fromStdString(t.getName() + " - " + t.getBreed() + " - " + t.getAge() + " - " + t.getPhoto());
		this->listWidget->addItem(itemInList);
	}
}

void GUI::addDog()
{
	std::string name = nameInput->text().toStdString();
	std::string breed = breedInput->text().toStdString();
	std::string age = ageInput->text().toStdString();
	
	std::string photo = photoInput->text().toStdString();
	std::string tutorialString = name + ',' + breed + ',' + age + ',' + photo ;

	std::stringstream stream{ tutorialString };
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

}



void GUI::adoptDog()
{
}

// connects all the components to their callbacks
void GUI::connectSignalsAndSlots() {
	// connect repository widget and add a callback that modifies the selection of the dogs
	QObject::connect(repoWidget, SIGNAL(itemSelectionChanged()), this, SLOT(listItemChanged()));

	// add button
	// connect the addButton to the callback that is called when the clicked() event happened
	QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(addDog()));

}