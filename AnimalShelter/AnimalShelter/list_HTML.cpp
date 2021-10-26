#include "list_HTML.h"
#include <Windows.h>
#include <shellapi.h>
#include <fstream>

HTMLList::HTMLList()
{
}


HTMLList::~HTMLList()
{
}

void HTMLList::save()
{
	std::ofstream f("list2.html");

	f << "<!DOCTYPE html>" << "\n";
	f << "<html>" << "\n";

	f << "<head>" << "\n";
	f << "<title>Adoption List</title>" << "\n";
	f << "</head>" << "\n";

	f << "<body>" << "\n";

	f << "<table border=\"1\">" << "\n";

	f << "<tr>" << "\n";
	f << "<td>Dog's name</td>" << "\n";
	f << "<td>Breed</td>" << "\n";
	f << "<td>Age</td>" << "\n";
	f << "<td>Photo</td>" << "\n";
	f << "</tr>" << "\n";

	for (auto i : this->getDA())
	{
		f << "<tr>" << "\n";

		f << "<td>" << i.getName() << "</td>" << "\n";
		f << "<td>" << i.getBreed() << "</td>" << "\n";
		f << "<td>" << i.getAge() << "</td>" << "\n";
		f << "<td><a href =" << i.getPhoto() << ">Link</a></td>";

		f << "</tr>" << "\n";
	}

	f << "</table>" << "\n";

	f << "</body>" << "\n";

	f << "</html>" << "\n";
	f.close();

}

void HTMLList::openInApp()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", "file:///D:/a89-912-burca-olivia/AnimalShelter_/AnimalShelter_/list2.html", NULL, SW_SHOWMAXIMIZED);
	system("PAUSE");
}