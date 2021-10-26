#pragma once 
#include "domain.h"
#include "repo.h"
#include "dog_validator.h"
#include <string>
#include <vector>
//typedef Dog TElement;

class MemRepo :
	public Repo
{
private:
	//DynamicArray<Dog>* da;
	vector<Dog> da;
	DogValidator dog_validator;

public:
	/// <summary>
	/// Default constructor for a repository, with a dynamic array with a capacity of 1 element.
	/// </summary>
	MemRepo();

	/// <summary>
	/// The destructor of the repository.
	/// </summary>
	~MemRepo();

	/// <summary>
	/// Searches a dog by name, if it exists, it returns the position in the repo, if not, it returns -1.
	/// </summary>
	/// <param name="name">the name of the dog</param>
	/// <returns></returns>
	int searchByName(string name);

	/// <summary>
	/// Adds a dog to the repo. If a dog with the given name already exists, it returns -1. If not, it adds it and returns 1.
	/// </summary>
	/// <param name="t">the dog</param>
	/// <returns></returns>
	int addDog(Dog t);

	void adoptDog(Dog t);

	/// <summary>
	/// Removes a dog from the repo. If a dog with the given name does not exist, it returns -1. Else, it returns 1 and it removes it.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	int removeDog(int pos);

	//Dog findDog(int pos);

	/// <summary>
	/// It updates the age of a dog. If a dog with the given name does not exist, it returns -1. Else, it returns 1 and updates the age.
	/// </summary>
	/// <param name="name">the name of the dog</param>
	/// <param name="age">the new age</param>
	/// <returns></returns>
	int updateAge(string name, string age);

	/// <summary>
	/// It updates the link of the photo of a dog. If a dog with the given name does not exist, it returns -1. Else, it returns 1 and updates the link.
	/// </summary>
	/// <param name="name">the name of the dog</param>
	/// <param name="photo">the new link</param>
	/// <returns></returns>
	int updatePhoto(string name, string photo);

	/// <summary>
	/// Searches dogs of a given breed (if string is empty, all dogs are considered), younger than a guven age. Returns a vector<Dog>
	/// </summary>
	/// <param name="breed">the breed</param>
	/// <param name="age">the age</param>
	vector<Dog> filterAgeBreed(string breed, int age);

	/// <summary>
	/// It initializes the repo with 10 dogs.
	/// </summary>
	void initialize();

	vector<Dog> & getDA() { return this->da; }
	MemRepo& operator=(const MemRepo& other);

	//virtual void openInApp() = 0;
	void openInApp();
	void save();
};
