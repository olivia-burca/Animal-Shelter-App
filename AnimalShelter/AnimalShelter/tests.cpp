#include "tests.h"
#include "memory_repo.h"
#include "file_repo.h"
#include <string>
#include <assert.h>
#include <iostream>


void Tests::runTests()
{
	MemRepo* r = new FileRepo("list.txt");
	
	r->initialize();
	assert(r->getDA().size() == 10);

	int x = r->searchByName("Milo");
	assert(x == 1);
	
	x = r->searchByName("shjkhs");
	assert(x == -1);

	Dog d{ "Milo","Husky","2", "photo" };
	x = r->addDog(d);
	assert(x == -1);
	Dog d2{ "Jackie","Husky","2", "photo" };
	x = r->addDog(d2);
	assert(x == 1);
	assert(r->getDA().size() == 11);
	assert(r->getDA()[10].getName()=="Jackie");
	assert(r->getDA()[10].getBreed()== "Husky") ;
	assert(r->getDA()[10].getAge()== "2");
	assert(r->getDA()[10].getPhoto()== "photo") ;

	/*
	x = r->removeDog("Abc");
	assert(x == -1);
	x = r->removeDog("Max");
	assert(x == 1);
	assert(r->getDA().size() == 10);
	x = r->searchByName("Max");
	assert(x == -1);
	*/
	x = r->updateAge("sjdh", "2");
	assert(x == -1);
	x = r->updateAge("Milo", "2");
	assert(r->getDA()[0].getAge()== "2");

	
	x = r->updatePhoto("sjds", "photo");
	assert(x == -1);
	x = r->updatePhoto("Milo", "photo");
	assert(r->getDA()[0].getPhoto()=="photo") ;
	
	
	int age_ = 4;
	vector<Dog> v = r->filterAgeBreed( "Corgi", age_);
	assert(v.size() == 2);
	assert(v[0].getName() == "Milo");
	assert(v[1].getName() == "Lucky");
	
	int list2[100], n2 = 0;
	
	v = r->filterAgeBreed( "", 2);
	assert(v[0].getName() == "Milo");
	
	assert(d2.toString().size() == 55);
	Dog d3;
	r->adoptDog(d3);
	assert(r->getDA().size() == 11);
	

	
}