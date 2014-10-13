// report.cpp

#include <iostream>
using namespace std;

int main(){
	string my_name = "Jason Hatfield"; //edited
	string my_text_editor = "VIM"; //edited
	string my_home_os = "Windows"; //edited
	bool i_worked = true;

	cout << "My name is " << my_name << endl;

	if(i_worked){
		cout << "I was able to install and test g++ and "
		     << "the text editor " << my_text_editor << '\n'
		     << "in my home computer/laptop, which runs "
		     << my_home_os << endl;
	} else {
		cout << "I wasn't able to install and test g++ and/or a text "
		     << "editor because ... " //give a lame reason here
		     << endl;
	}
	return 0;
}

