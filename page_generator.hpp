//This function generates the index.html file on localhost
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int pageGenerator(string data) {

	string s1 = "<HTML>\n<HEAD>\n</HEAD>\n<BODY>\n<H1>\n" ;
	string s11 = "Temperaturen i rummet er ";
	string s2 = " grader.\n</BODY>\n</HTML>";
	data.erase(4);
	ofstream webPage;
	webPage.open("/var/www/html/index.html");
	if(!webPage)
	{
		cout << "Failed to open HTML file" << endl;
	}
	webPage << s1 << s11 << data << s2;
	webPage.close();

	return 0;
}
