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

//https://www.youtube.com/watch?v=GsMZYDBFJv4


struct Node {
    int id;
    vector<int> neighbors;
};

vector<Node> readGraphfromFile(const string& filePath){
    ifstream file(filePath);
    vector<Node> nodes;
    int node1, node2;
    while (file >> node1 >> node2){
        if (node1 >= nodes.size()){
            nodes.resize(node1 + 1);
        }
        if (node2 >= nodes.size()){
            nodes.resize(node2 + 1);
        }
        nodes[node1].id = node1;
        nodes[node2].id = node2;
        nodes[node1].neighbors.push_back(node2);
        nodes[node2].neighbors.push_back(node1);
    }

    //cout << "Number of nodes: " << nodes.size() << endl;
    //cout << "Node 1 has " << nodes[1].neighbors.size() << " neighbors." << endl;
    return nodes;
};


//void kernighanLinAlgorithm(const vector<Node> &nodes, const vector<edge> &edges){

//}



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

//string line;

//while (getline(inputFile, line)){
//    cout << line << endl;
//}



//Close file
inputFile.close();

//Call function to read graph from file
vector<Node> nodes = readGraphfromFile(fileName);

//List the Neighbors of each node


for (int i = 0; i < nodes.size(); i++){
    cout << "Node " << nodes[i].id << " has " << nodes[i].neighbors.size() << " neighbors." << endl;
    for (int j = 0; j < nodes[i].neighbors.size(); j++){
        cout << nodes[i].neighbors[j] << " ";
    }
    cout << endl;
}

return 0;
}
