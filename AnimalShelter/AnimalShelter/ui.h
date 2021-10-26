#pragma once
#include "repo.h"
#include "list_CSV.h"
#include "list_HTML.h"

class UI {
private:
	Repo* r;
	//Repo* list;
	MemRepo* list;
public:
	/// <summary>
	/// Default constructor for UI.
	/// </summary>
	UI();

	/// <summary>
	/// The destructor of the UI.
	/// </summary>
	~UI();

	void printMenu1();

	void printMenu2();

	void printMenu3();

	void addDogUi();

	void removeDogUi();

	void updateAgeUi();

	void updatePhotoUi();

	void listAll();

	void seeAdoptUi();

	void filterBreedAgeUi();

	void seeList();

	void seeListApp();

	void startAdministratorMode();

	void startUserMode();

	void startMe();

	Repo* getRepo() { return this->r; }

	Repo* getList() { return this->list;  }
	







};