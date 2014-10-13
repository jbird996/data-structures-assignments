// Jason Hatfield  29163434
// Email: jrh7@buffalo.edu
// Assignment 1, txtparser.cpp  

#include <iostream>
#include <fstream>

using namespace std;

void startPrompt(), prompt(), readFile(), extractStrings(), reset();
string input, function, filename, line;
ifstream stream;
int rows = 0;
int cols = 0;
int colsTemp = 0;
bool validFile = false;

int main(){
	
	startPrompt();

	while(getline(cin,input)){

		while(true){

			if(input == "exit" || input == "Exit"){
				return 0;
			}	
		
			extractStrings();
		
			if(function == "numcols"){

				readFile();
				if(validFile) {cout << cols << endl;}

			} else if(function == "numrows"){

				readFile();	
				if(validFile) {cout << rows << endl;}
			
			} else{

				cout << endl <<"*** INPUT NOT RECOGNIZED --> " << '"' << input << '"' 
				     << " <-- PLEASE TRY AGAIN (numrows <file>, numcols <file>) or " 
				     << "type 'exit' to quit ***" << endl;

			}
			
			reset();
			prompt();			
			break;	
		}

	}	

	return 0;

}

void startPrompt(){

	cout << endl << "*** Please enter a function name followed "
	     << "by the name of a text file in the current directory ***"
	     << endl << "*** Valid functions: numrows <file>, numcols <file>, or exit ***" << endl
	     << "> ";


}	

void prompt(){

	cout << "> ";

}

void readFile(){

	stream.open(filename.c_str());

	if(stream.fail()){

		cerr << endl << "*** ERROR--Failed to open file --> " << '"' << filename 
		     << '"' << " <-- try another function and file:" << endl;
		stream.clear();

	} else {

		while(getline(stream,line)){
			
			validFile = true;	

			rows++;	
			
			if(isalpha(line[0])){
				colsTemp++;
			}

			for(int i = 1; i < line.length(); i++){
				if(isalpha(line[i]) && !isalpha(line[i-1])){
					colsTemp++;
				}

			}

			if(colsTemp > cols){
				cols = colsTemp;
			}

			colsTemp = 0;

		}

		stream.close();
	}

}

void extractStrings(){

	for(int i = 0; i <= input.length();i++){
		if(input[i] == ' '){

			function = input.substr(0,i);
			filename = input.substr(i+1,input.length()-1);				

		}	
				
	}

}

void reset(){

	function = "";
	filename = "";
	rows = 0;
	cols = 0;
	validFile = false;

}
