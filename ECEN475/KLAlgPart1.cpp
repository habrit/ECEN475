#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <chrono>
#include <sstream>


using namespace std;


struct Node {
    int id;
    vector<int> neighbors;
};

vector<Node> readGraphfromFile(const string& filePath){
    ifstream file(filePath);
    vector<Node> nodes;

    int source, target;
    




}


void kernighanLinAlgorithm(const vector<node> &nodes, const vector<edge> &edges){

}



int main(){

string fileName;
//Ask user for input file name with edges
cout << "Please type in the name of the input file. " << endl;

cin >> fileName;

//Open file
ifstream inputFile;

inputFile.open(fileName);

//Error checking
if (inputFile.fail()){
    cout << "Error opening file. " << endl;
    exit(1);
} else {
    cout << "File opened successfully. " << endl;
}

//read each line of the file

string line;

while (getline(inputFile, line)){
    cout << line << endl;
}



//Close file
inputFile.close();




return 0;
}