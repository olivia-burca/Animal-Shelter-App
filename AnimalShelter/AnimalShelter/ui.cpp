#include "memory_repo.h"
#include "ui.h"
#include "file_repo.h"
#include "repo_exception.h"
#include "dog_validator.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "ui.h"

UI::UI()
{
   
    //this->list = new MemRepo;
    //this->list = new CSVList;
}

UI::~UI()
{
  
}

void UI::printMenu1()
{
    printf("\n|-----------------------------------------------------------------------------------------------------------------| \n");
    printf("| 1.Administrator mode                                                                                            |\n");
    printf("| 2.User mode                                                                                                     |\n");                                                                           
    printf("|-----------------------------------------------------------------------------------------------------------------| \n");

}

void UI::printMenu2()
{
    printf("\n|-----------------------------------------------------------------------------------------------------------------| \n");
    printf("| 1.Add a dog.                                                                                                    |\n");
    printf("| 2.Remove a dog.                                                                                                 |\n");
    printf("| 3.Update the age of a dog.                                                                                      |\n");
    printf("| 4.Update the photo of a dog.                                                                                    |\n");
    printf("| 5.List all dogs.                                                                                                |\n");
    printf("| 0.Exit                                                                                                          |\n");
    printf("|-----------------------------------------------------------------------------------------------------------------| \n");

}

void UI::printMenu3()
{
    printf("\n|-----------------------------------------------------------------------------------------------------------------| \n");
    printf("| 1.See the dogs and adopt.                                                                                       |\n");
    printf("| 2.See all the dogs of a given breed, having an age less than a given number                                     |\n");
    printf("| 3.Display the adoption list.                                                                                    |\n");
    printf("| 4.See the adoption list in the corresponding application.                                                       |\n");
    printf("| 0.Exit                                                                                                          |\n");
    printf("|-----------------------------------------------------------------------------------------------------------------| \n");
}

void UI::addDogUi()
{
    string name, breed, photo, age;
    int age_;
    cout << "Enter the name of the dog you want to add: ";
    cin >> name;
    cout << "Enter the breed of the dog: ";
    cin >> breed;
    cout << "Enter the age of the dog: ";
    cin >> age;
    cout << "Enter the link of the photo of the dog: ";
    cin >> photo;
    try {
        
        Dog d{ name,breed,age,photo };
        int x = this->getRepo()->addDog(d);
        if (x == -1)
            cout << "A dog with this name already exists!";
    }
    catch (DogException& e) {
        for (auto i : e.getErrors())
            cout << i;
    }
    catch (RepoException& e)
    {
        cout << e.what();
    }

}

void UI::removeDogUi()
{ /*
    string name;
    cout << "Enter the name of the dog you want to remove: ";
    cin >> name;
    int x = this->getRepo()->removeDog(name);
    if (x == -1)
        cout << "A dog with the given name does not exist!";

        */
}

void UI::updateAgeUi()
{
    string name, age;
    cout << "Enter the name of the dog: ";
    cin >> name;
    cout << "Enter the new age: ";
    cin >> age;
    int x = this->getRepo()->updateAge(name, age);
    if (x == -1)
        cout << "A dog with the given name does not exist!";
}

void UI::updatePhotoUi()
{
    string name, photo;
    cout << "Enter the name of the dog: ";
    cin >> name;
    cout << "Enter the link og the new photo : ";
    cin >> photo;
    int x = this->getRepo()->updatePhoto(name, photo);
    if (x == -1)
        cout << "A dog with the given name does not exist!";
}

void UI::listAll()
{
    int pos = 0;
    for (auto i : this->getRepo()->getDA())
    {
        cout << pos + 1;
        pos++;
        cout << '.';
        cout << i.toString();
    }
        
}

void UI::seeAdoptUi()
{ /*
    cout <<'\n'<< this->getRepo()->getDA()[0].toString();
    char command[50];
    int i = 0;
    cout << "\nDo you want to adopt this dog?\n";
    cout << "\nadopt                   next\n";
    cout << "\nEnter your command: ";
    cin >> command;
    
    while (strcmp(command, "adopt") != 0 && strcmp(command, "next") != 0)
    {
        cout << "Bad command!\n";
        cout << "\nEnter your command: ";
        cin >> command;
    }
    while (strcmp(command, "stop") != 0)
    {
        if (strcmp(command, "adopt") == 0)
        {
            this->list->adoptDog(this->getRepo()->getDA()[i]);
            this->getRepo()->removeDog(this->getRepo()->getDA()[i].getName());
        }
        else
        {
            if (i == this->getRepo()->getDA().size() - 1)
                i = 0;
            else i++;
        }
        cout << '\n' << this->getRepo()->getDA()[i].toString();
        cout << "\nDo you want to adopt this dog?\n";
        cout << "\nadopt                   next                  stop\n";
        cout << "\nEnter your command: ";
        cin >> command;
        while (strcmp(command, "adopt") != 0 && strcmp(command, "next") != 0 && strcmp(command,"stop") != 0)
        {
            cout << "Bad command!\n";
            cout << "\nEnter your command: ";
            cin >> command;
        }
    }
    */
}

void UI::filterBreedAgeUi()
{
    int age_;

    string breed, age;
    cout << "Enter the breed: ";
    std::getline(std::cin, breed);
    cout << "Enter the age: ";
    cin >> age;

    try {
        age_ = stoul(age);
        vector<Dog> v = this->r->filterAgeBreed(breed, age_);
        if (v.size() == 0)
            cout << "There are no dogs of this breed, with the age smaller tha your input!\n";
        else 
            
        {
            cout << '\n' << v[0].toString();
            char command[50];
            int i = 0;
            cout << "\nDo you want to adopt this dog?\n";
            cout << "\nadopt                   next\n";
            cout << "\nEnter your command: ";
            cin >> command;

            while (strcmp(command, "adopt") != 0 && strcmp(command, "next") != 0)
            {
                cout << "Bad command!\n";
                cout << "\nEnter your command: ";
                cin >> command;
            }
            while (strcmp(command, "stop") != 0 && v.size() > 0)
            {
                if (strcmp(command, "adopt") == 0)
                {
                    this->getList()->addDog(v[i]);
                   // this->getRepo()->removeDog(v[i].getName());
                    v.erase(v.begin() + i);
                    
                }
                else
                {
                    if (i == v.size() - 1)
                        i = 0;
                    else i++;
                }
                if (v.size() > 0)
                {
                    cout << '\n' << v[i].toString();
                    cout << "\nDo you want to adopt this dog?\n";
                    cout << "\nadopt                   next                  stop\n";
                    cout << "\nEnter your command: ";
                    cin >> command;
                    while (strcmp(command, "adopt") != 0 && strcmp(command, "next") != 0 && strcmp(command, "stop") != 0)
                    {
                        cout << "Bad command!\n";
                        cout << "\nEnter your command: ";
                        cin >> command;
                    }
                }
                
            }
        }

       
    }
    catch (invalid_argument) {
        cout << "Age should be an integer number!\n";
    }
}

void UI::seeList()
{
    int pos = 0;
    for (auto i : this->getList()->getDA())
    {
        cout << pos + 1;
        pos++;
        cout << '.';
        cout << i.toString();
    }
}

void UI::seeListApp()
{
    this->list->openInApp();
} 

void UI::startAdministratorMode()
{
    bool done = false;
    string command;
    //this->r->initialize();
    this->r = new FileRepo("file.txt");
    while (!done)
    {
        printMenu2();
        cout << "Enter your command: ";
        cin >> command;
        if (command == "1") 
            addDogUi();
        else if (command == "2") 
            removeDogUi();
        else if (command == "3") 
            updateAgeUi();
        else if (command == "4") 
            updatePhotoUi();
        else if (command == "5") 
            listAll();
        else if (command == "0") 
            done = true;
        else cout << "Bad command!";
    }
    this->r->save();
}

void UI::startUserMode()
{
    bool done = false;
    string command;
    this->r = new FileRepo("file.txt");
    
    cout << "Do you want to use \n 1.A CSV file \n 2.A HTML file \n Enter your command: ";
    cin >> command;
    while (command != "1" && command != "2")
    {
        cout << "Bad command! Enter 1 or 2:";
        cin >> command;
    }
    if (command == "1")
        this->list = new CSVList;
    else if (command == "2")
        this->list = new HTMLList;
        
    while (!done)
    {
        printMenu3();
        cout << "Enter your command: ";
        cin >> command;
        getchar();
        if (command == "1")
            seeAdoptUi();
        else if (command == "2")
            filterBreedAgeUi();
        else if (command == "3")
            seeList();
        else if (command == "4")
            seeListApp();
        else if (command == "0") 
            done = true;
        else cout << "Bad command!";
        this->list->save();
    }
    this->r->save();
}

void UI::startMe()
{
    //this->r->save();
    string command;
    printMenu1();
    cout << "Enter a command: ";
    cin >> command;
    while (command != "1" && command != "2") 
    {
        cout << "Bad command!\n";
        cout << "Enter a command: ";
        cin >> command;
    }
    if (command == "1")
        startAdministratorMode();
    else startUserMode();
   
}


