#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <chrono>

using namespace std;

/*
Program to write code that randomly generates edges for the graph into a text file. 

Input file format:
• Each of the following lines has two numbers that are indices of two nodes of an edge.
For example:
3 2
1 2
2 3


18 modules in the problem. So 18 nodes. 
List randomly generated edges between 80 and 300.


Vertices are also called nodes.
Connected by edges.

So in the above example, there are 3 nodes and 2 edges.



*/

void graph(){

  // Generate random number between 80 and 300
  srand(time(NULL));
  int randomNum = 80 + rand() % 221;

  // num of nodes
  int numNodes = 18;

  // Need to have two nodes per line in file.
  int outputFileNodes = randomNum * 2;

  // Create vector to store the edges and indices.

  vector<int> vec1;

  for (int i = 0; i < outputFileNodes; i++)
  {
    vec1.push_back(1 + rand() % 18);
  }
  /*
  Debugging code to print out the vector
  cout << "Output of Vector is: " << endl;

  for (int i = 0; i < randomNum; i++){
      cout << "Index " << i << ": " << vec1[i] << endl;
  }

  cout << "Size of the vector is: " << vec1.size() << endl;
  */

  // Create file to store the edges and indices.

  ofstream MyFile;
  MyFile.open("Hunter.Britton.Input");

  // Write nodes to file

  if (MyFile.is_open())
  {
    cout << "File is open" << endl;
  }

  for (int i = 0; i < outputFileNodes; i = i + 2)
  {
    MyFile << vec1[i] << " " << vec1[i + 1] << endl;
  }

  MyFile.close();

  cout << "File is closed" << endl;

  // Two Way Partion Problem Initial Solution
  vector<int> partition1TWPP;
  vector<int> partition2TWPP;

  for (int i = 1; i <= 18; i++)
  {
    if (i % 2 == 0)
    {
      partition1TWPP.push_back(i);
    }
    else
    {
      partition2TWPP.push_back(i);
    }
  }

  cout << "Partition 1: " << endl;
  for (int i = 0; i < partition1TWPP.size(); i++)
  {
    cout << partition1TWPP[i] << endl;
  }

  cout << "Partition 2: " << endl;
  for (int i = 0; i < partition2TWPP.size(); i++)
  {
    cout << partition2TWPP[i] << endl;
  }

  // List number of cuts for initial solution.

  // Open file
  ifstream inputFile;

  inputFile.open("Hunter.Britton.Input");

  // Error checking

  if (inputFile.fail())
  {
    cout << "Error opening file. " << endl;
    exit(1);
  }
  else
  {
    cout << "File opened successfully. " << endl;
  }

  // read each line of the file

  string line;
  istringstream iss(line);
  int num1 = 0;
  int num2 = 0;
  int numCutsTWPP = 0;
  bool partition1TWPPCheckNum1 = false;
  bool partition1TWPPCheckNum2 = false;

  while (getline(inputFile, line))
  {

    istringstream iss(line);
    iss >> num1 >> num2;
    // cout << "Num1: " << num1 << endl;
    // cout << "Num2: " << num2 << endl;

    for (int i = 0; i < partition1TWPP.size(); i++)
    {
      if (partition1TWPP[i] == num1)
      {
        // cout << "Num1 is in partition 1" << endl;
        partition1TWPPCheckNum1 = true;
      }
      if (partition1TWPP[i] == num2)
      {
        // cout << "Num2 is in partition 1" << endl;
        partition1TWPPCheckNum2 = true;
      }
    }
    if (partition1TWPPCheckNum1 == partition1TWPPCheckNum2)
    {
      // cout << "No cut" << endl;
    }
    else
    {
      // cout << "Cut" << endl;
      numCutsTWPP++;
    }
    partition1TWPPCheckNum1 = false;
    partition1TWPPCheckNum2 = false;
  }

  // Close File

  inputFile.close();

  cout << "Number of cuts for Two Way Partition Problem: " << numCutsTWPP << endl;

  // Three Way Partition Problem Initial Solution

  vector<int> partition13WPP;
  vector<int> partition23WPP;
  vector<int> partition33WPP;
  num1 = 0;
  num2 = 0;
  int numCuts3WPP = 0;

  for (int i = 1; i <= 18; i++)
  {
    if (i % 3 == 0)
    {
      partition13WPP.push_back(i);
    }
    else if (i % 3 == 1)
    {
      partition23WPP.push_back(i);
    }
    else
    {
      partition33WPP.push_back(i);
    }
  }

  cout << "Partition 1: " << endl;
  for (int i = 0; i < partition13WPP.size(); i++)
  {
    cout << partition13WPP[i] << endl;
  }

  cout << "Partition 2: " << endl;
  for (int i = 0; i < partition23WPP.size(); i++)
  {
    cout << partition23WPP[i] << endl;
  }

  cout << "Partition 3: " << endl;
  for (int i = 0; i < partition33WPP.size(); i++)
  {
    cout << partition33WPP[i] << endl;
  }

  // List number of cuts for initial solution.

  // Open file

  inputFile.open("Hunter.Britton.Input");

  // Error checking

  if (inputFile.fail())
  {
    cout << "Error opening file. " << endl;
    exit(1);
  }
  else
  {
    cout << "File opened successfully. " << endl;
  }

  // read each line of the file
  string line1;
  bool partition13WPPCheckNum1 = false;
  bool partition13WPPCheckNum2 = false;
  bool partition23WPPCheckNum1 = false;
  bool partition23WPPCheckNum2 = false;
  bool partition33WPPCheckNum1 = false;
  bool partition33WPPCheckNum2 = false;

  while (getline(inputFile, line1))
  {
    istringstream iss(line1);
    iss >> num1 >> num2;

    for (int i = 0; i < partition13WPP.size(); i++)
    {
      if (partition13WPP[i] == num1)
      {
        // cout << "Num1 is in partition 1" << endl;
        partition13WPPCheckNum1 = true;
      }
      if (partition13WPP[i] == num2)
      {
        // cout << "Num2 is in partition 1" << endl;
        partition13WPPCheckNum2 = true;
      }

      if (partition23WPP[i] == num1)
      {
        // cout << "Num1 is in partition 2" << endl;
        partition23WPPCheckNum1 = true;
      }
      if (partition23WPP[i] == num2)
      {
        // cout << "Num2 is in partition 2" << endl;
        partition23WPPCheckNum2 = true;
      }

      if (partition33WPP[i] == num1)
      {
        // cout << "Num1 is in partition 3" << endl;
        partition33WPPCheckNum1 = true;
      }

      if (partition33WPP[i] == num2)
      {
        // cout << "Num2 is in partition 3" << endl;
        partition33WPPCheckNum2 = true;
      }

    }



    if (partition13WPPCheckNum1 != partition13WPPCheckNum2)
    {
      numCuts3WPP++;
    }
    else if (partition23WPPCheckNum1 != partition23WPPCheckNum2)
    {
      numCuts3WPP++;
    }
    else if (partition33WPPCheckNum1 != partition33WPPCheckNum2)
    {
      numCuts3WPP++;
    }
    else
    {
      // cout << "No cut" << endl;
    }

    partition13WPPCheckNum1 = false;
    partition13WPPCheckNum2 = false;
    partition23WPPCheckNum1 = false;
    partition23WPPCheckNum2 = false;
    partition33WPPCheckNum1 = false;
    partition33WPPCheckNum2 = false;


  }

  // Close File

  inputFile.close();

  cout << "Number of cuts for Three Way Partition Problem: " << numCuts3WPP << endl;

}

int main()
{
    auto start = chrono::high_resolution_clock::now();
 
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
 
    graph();
 
    auto end = chrono::high_resolution_clock::now();
 
    // Calculating total time taken by the program.
    double time_taken =
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
 
    time_taken *= 1e-9;
 
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9);
    cout << " sec" << endl;
    return 0;
}