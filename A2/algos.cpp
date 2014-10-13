// ============================================================================
// algos.cpp
// ~~~~~~~~~~~~~~~~
// author: Jason Hatfield 2916-3434
// Reads sets of edges from file in Stanford SNAP file format, removes
// duplicates, returns total number of pairs of edges
// - this is the ONLY file you can modify
// - feel free to include more headers if you need to
// ============================================================================

#include <stdexcept> // to throw exceptions if you need to
#include <iostream>
#include <fstream>   // to open & read from input file
#include <cstdlib>   // for atoi() if you want to use it
#include <string>
#include <set>       // for sba algorithm
#include <vector>    // for vba algorithm
#include <algorithm> // for vba algorithm
#include <cstdlib>
#include <sstream>
#include "Lexer.h"
#include "algos.h"

using namespace std; // BAD PRACTICE

void printVector(), remove(), reset();
ifstream stream;
string line, str1, str2;
int a, b, r;
pair<int,int> p;
vector<pair<int,int> > vec;
set<pair<int,int> > myset;


int vba(string filename)
{
    
    stream.open(filename.c_str());
    if(stream.fail()){
	cerr << endl << "*** ERROR--Failed to open file --> " << '"' << filename 
	     << '"' << " <-- try another function and file ***" << endl;
	stream.clear();
        return 0;
    } else {
	while(getline(stream,line)){
            if(line[0] != '#'){

                istringstream iss(line);
                iss >> str1 >> str2;
                a = atoi(str1.c_str());
                b = atoi(str2.c_str());
                if(a>b){ swap(a,b);}
                p = make_pair(a,b);
                vec.push_back(p);
                
            }
	}
	stream.close();
        sort(vec.begin(), vec.end());
        remove();
        r = vec.size();
        reset();
    }
    return r;
}

int sba(string filename)
{

    stream.open(filename.c_str());
    if(stream.fail()){
	cerr << endl << "*** ERROR--Failed to open file --> " << '"' << filename 
	     << '"' << " <-- try another function and file ***" << endl;
	stream.clear();
        return 0;
    } else {
	while(getline(stream,line)){
            if(line[0] != '#'){

                istringstream iss(line);
                iss >> str1 >> str2;
                a = atoi(str1.c_str());
                b = atoi(str2.c_str());
                if(a>b){ swap(a,b);}    //Standardize pairs to alleviate need to scan for duplicates
                p = make_pair(a,b);
                myset.insert(p);
            }
	}
	stream.close();
    }
    r = myset.size();
    reset();
    return r; 

}

void printVector(){     //Used to print contents of vector, used for debugging
    vector<pair<int,int> > :: iterator it;
    for(it = vec.begin();it!=vec.end();++it){
        cout << "(" << it->first << ", " << it->second << ")" << endl;
    }

}

void remove(){      //For vba, traverses vector, compares one pair to next, removes if duplicate
    vector<pair<int,int> > :: iterator i = vec.begin();
    while(i != vec.end()){
        vector<pair<int,int> > :: iterator j = i + 1;
        if(j != vec.end() && *j == *i){
            i = vec.erase(i);
        }
        i++;
        
    }
}

void reset(){   //Reset data structures for baseline performance next round
    vec.clear();
    myset.clear();
}
