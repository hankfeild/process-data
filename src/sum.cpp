// File:    sum.cpp
// Author:  Hank Feild
// Usage:   sum <file> <column>
//
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <vector>
using namespace std;

float getColumnValueAsFloat(string line, int column);
float sum(string line, int column, float currentSum);
vector<string>* getCSVCols(string line);    

int main(int argc, char** argv){
    if(argc < 3){
        cerr << "Error: too few arguments." << endl;
        cerr << "Usage: sum <file> <column>" << endl;
        return 1;
    }
    
    // Read in data filename and column to sum.
    char* filename = argv[1];
    int column = atoi(argv[2]);
    
    if(column < 1){
        cerr << "The column must be 1 or greater." << endl;
        return 1;
    }
    
    // Read through data file, summing values in given column.
    float runningSum = 0;
    string line;
    ifstream fin(filename);
    while(fin.good()){
        getline(fin, line);
        runningSum = sum(line, column, runningSum);
    }
    fin.close();
    
    // Print out the sum.
    cout << runningSum << endl;
    
    return 0;
}

float getColumnValueAsFloat(string line, int column){
    vector<string> *columns = getCSVCols(line);
    if(column > columns->size()){
        cerr << "Column out of bounds! The current line has too few columns:"
             << endl << line << endl;
        return 0;
    }
    return atof((*columns)[column-1].c_str());
}

float sum(string line, int column, float currentSum){
	return getColumnValueAsFloat(line, column) + currentSum;
}

vector<string>* getCSVCols(string line){
    vector<string> *columns = new vector<string>();
    
    string delimiter = ",";
    size_t current;
    size_t next = -1;
    do {
      current = next + 1;
      next = line.find_first_of(delimiter, current);
      columns->push_back(line.substr(current, next - current));
    } while (next != string::npos);
    
    return columns;
}

