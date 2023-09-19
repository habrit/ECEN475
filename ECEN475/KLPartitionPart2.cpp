#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <algorithm>

using namespace std;

// https://www.youtube.com/watch?v=GsMZYDBFJv4

struct Node
{
    int id;
    vector<int> neighbors;
};

struct TWPPartition
{
    vector<int> partition1;
    vector<int> partition2;
};

vector<Node> readGraphfromFile(const string &filePath)
{
    ifstream file(filePath);
    vector<Node> nodes;
    int node1, node2;
    while (file >> node1 >> node2)
    {
        if (node1 >= nodes.size())
        {
            nodes.resize(node1 + 1);
        }
        if (node2 >= nodes.size())
        {
            nodes.resize(node2 + 1);
        }
        nodes[node1].id = node1;
        nodes[node2].id = node2;
        nodes[node1].neighbors.push_back(node2);
        nodes[node2].neighbors.push_back(node1);
    }

    // cout << "Number of nodes: " << nodes.size() << endl;
    // cout << "Node 1 has " << nodes[1].neighbors.size() << " neighbors." << endl;
    return nodes;
};

// generate a random Two Way Partition given 18 nodes with both partitions being equal size

pair<vector<int>, vector<int>> createTwoWayPartition(int numNodes, int seed, bool print = false)
{
    if (seed == 0)
    {
        seed = time(NULL);
    }
    srand(seed);

    vector<int> partition1;
    vector<int> partition2;
    // Equal sized partitions.
    int partitionSize = numNodes / 2;
    // Create partitions
    for (int i = 1; i <= 18; i++)
    {
        if (i <= partitionSize)
        {
            partition1.push_back(i);
        }
        else
        {
            partition2.push_back(i);
        }
    }

    // print out the two partitions
    if (print == true)
    {
        cout << "Partition 1: ";
        for (int i = 0; i < partition1.size(); i++)
        {
            cout << partition1[i] << " ";
        }

        cout << endl;

        cout << "Partition 2: ";
        for (int i = 0; i < partition2.size(); i++)
        {
            cout << partition2[i] << " ";
        }

        cout << endl;
    }
    return make_pair(partition1, partition2);
}

// Create Three Way Partition

vector<vector<int>> createThreeWayPartition(int numNodes, int seed, bool print = false)
{
    // bool print is set to false by default, but if want to see if the partitions are correct, set to true

    if (seed == 0)
    {
        seed = time(NULL);
    }
    srand(seed);

    vector<vector<int>> partitions(3);

    int partitionSize = numNodes / 3;

    for (int i = 1; i <= numNodes; ++i)
    {
        if (i <= partitionSize)
        {
            partitions[0].push_back(i);
        }
        else if (i <= 2 * partitionSize)
        {
            partitions[1].push_back(i);
        }
        else
        {
            partitions[2].push_back(i);
        }
    }

    // print out the three partitions

    if (print == true)
    {
        cout << "Partition 1: ";
        for (int i = 0; i < partitions[0].size(); i++)
        {
            cout << partitions[0][i] << " ";
        }

        cout << endl;

        cout << "Partition 2: ";

        for (int i = 0; i < partitions[1].size(); i++)
        {
            cout << partitions[1][i] << " ";
        }

        cout << endl;

        cout << "Partition 3: ";

        for (int i = 0; i < partitions[2].size(); i++)
        {
            cout << partitions[2][i] << " ";
        }

        cout << endl;
    }

    return partitions;
}

// Calculate the cut size of the two partitions

int calculateCutSizeTWPP(vector<int> partition1, vector<int> partition2, vector<Node> nodes)
{
    int cutSize = 0;

    for (int i = 0; i < partition1.size(); i++)
    {
        for (int j = 0; j < nodes[partition1[i]].neighbors.size(); j++)
        {
            if (find(partition2.begin(), partition2.end(), nodes[partition1[i]].neighbors[j]) != partition2.end())
            {
                cutSize++;
            }
        }
    }

    return cutSize;
}

// Calculate Cut Size for 3WPP

int calculateCutSize3WPP(vector<int> partition1, vector<int> partition2, vector<int> partition3, vector<Node> nodes)
{
    int cutSize = 0;

    // Calculate cut size for edges crossing partition 1 and partition 2/3
    for (int nodeId : partition1)
    {
        for (int neighbor : nodes[nodeId].neighbors)
        {
            if (find(partition2.begin(), partition2.end(), neighbor) != partition2.end() ||
                find(partition3.begin(), partition3.end(), neighbor) != partition3.end())
            {
                cutSize++;
            }
        }
    }

    // Calculate cut size for edges crossing partition 2 and partition 3
    for (int nodeId : partition2)
    {
        for (int neighbor : nodes[nodeId].neighbors)
        {
            if (find(partition3.begin(), partition3.end(), neighbor) != partition3.end())
            {
                cutSize++;
            }
        }
    }

    return cutSize;
}

// Function to calculate D-values for the Kernighan-Lin algorithm
vector<vector<int>> calculateDValues(const vector<Node> &nodes, const vector<int> &partition1, const vector<int> &partition2)
{
    int numNodes = nodes.size();
    vector<vector<int>> dValues(numNodes, vector<int>(numNodes, 0));

    // Calculate D-values for all node pairs (i, j)
    for (int i = 0; i < numNodes; ++i)
    {
        if (find(partition1.begin(), partition1.end(), i) != partition1.end())
        {
            // Node i is in partition 1
            for (int j = 0; j < numNodes; ++j)
            {
                if (find(partition2.begin(), partition2.end(), j) != partition2.end())
                {
                    // Node j is in partition 2
                    for (int neighbor : nodes[i].neighbors)
                    {
                        if (find(partition1.begin(), partition1.end(), neighbor) != partition1.end())
                        {
                            // Neighbor of i is in partition 1
                            dValues[i][j]--;
                        }
                        else if (find(partition2.begin(), partition2.end(), neighbor) != partition2.end())
                        {
                            // Neighbor of i is in partition 2
                            dValues[i][j]++;
                        }
                    }
                }
            }
        }
    }

    return dValues;
}

// function to calculate D-Values for 3WPP

vector<vector<int>> calculateDValues3WPP(const vector<Node> &nodes, const vector<int> &partition1, const vector<int> &partition2, const vector<int> &partition3)
{
    int numNodes = nodes.size();
    vector<vector<int>> dValues(numNodes, vector<int>(numNodes, 0));

    // Calculate D-values for all node pairs (i, j)
    for (int i = 0; i < numNodes; ++i)
    {
        if (find(partition1.begin(), partition1.end(), i) != partition1.end())
        {
            // Node i is in partition 1
            for (int j = 0; j < numNodes; ++j)
            {
                if (find(partition2.begin(), partition2.end(), j) != partition2.end() || find(partition3.begin(), partition3.end(), j) != partition3.end())
                {
                    // Node j is in partition 2 or 3
                    for (int neighbor : nodes[i].neighbors)
                    {
                        if (find(partition1.begin(), partition1.end(), neighbor) != partition1.end())
                        {
                            // Neighbor of i is in partition 1
                            dValues[i][j]--;
                        }
                        else if (find(partition2.begin(), partition2.end(), neighbor) != partition2.end() || find(partition3.begin(), partition3.end(), neighbor) != partition3.end())
                        {
                            // Neighbor of i is in partition 2 or 3
                            dValues[i][j]++;
                        }
                    }
                }
            }
        }
    }

    return dValues;
}

// Kernighan-Lin Algorithm
void kernighanLinTWPP(vector<int> &partiton1, vector<int> &partition2, vector<Node> &nodes, int numIterations, bool print = false)
{
    // bool print is set to false by default, but if want to see if the partitions are correct, set to true

    vector<bool> swapped(nodes.size(), false);

    // Calculate D-values for all node pairs (i, j)
    vector<vector<int>> dValues = calculateDValues(nodes, partiton1, partition2);

    // Calculate the initial cut size
    int cutSize = calculateCutSizeTWPP(partiton1, partition2, nodes);

    // select the node swap with the highest gain
    int maxGain = 0;
    int maxGainNode1 = 0;
    int maxGainNode2 = 0;

    // Iterate through the nodes in partition 1
    for (int i = 0; i < partiton1.size(); i++)
    {
        // Iterate through the nodes in partition 2
        for (int j = 0; j < partition2.size(); j++)
        {
            // Check if both nodes are not swapped
            if (!swapped[partiton1[i]] && !swapped[partition2[j]])
            {
                // Calculate the gain for swapping nodes i and j
                int gain = dValues[partiton1[i]][partition2[j]] - dValues[partition2[j]][partiton1[i]];

                // Check if this is the highest gain so far
                if (gain > maxGain)
                {
                    maxGain = gain;
                    maxGainNode1 = partiton1[i];
                    maxGainNode2 = partition2[j];
                }
            }
        }
    }

    // swap the nodes with the highest gain

    // Remove the nodes from their current partitions
    partiton1.erase(remove(partiton1.begin(), partiton1.end(), maxGainNode1), partiton1.end());
    partition2.erase(remove(partition2.begin(), partition2.end(), maxGainNode2), partition2.end());

    // Add the nodes to their new partitions
    partiton1.push_back(maxGainNode2);
    partition2.push_back(maxGainNode1);

    // Calculate the new cut size

    int newCutSize = calculateCutSizeTWPP(partiton1, partition2, nodes);

    // Check if the cut size has improved

    if (newCutSize < cutSize)
    {
        cutSize = newCutSize;
    }
    else
    {
        // If the cut size has not improved, swap the nodes back
        partiton1.erase(remove(partiton1.begin(), partiton1.end(), maxGainNode2), partiton1.end());
        partition2.erase(remove(partition2.begin(), partition2.end(), maxGainNode1), partition2.end());

        partiton1.push_back(maxGainNode1);
        partition2.push_back(maxGainNode2);
    }

    swapped[maxGainNode1] = true;
    swapped[maxGainNode2] = true;

    if (numIterations != 0)
    {
        kernighanLinTWPP(partiton1, partition2, nodes, numIterations - 1, print);
    }
}

// Kernighan Lin Algorithm for 3WPP

// Kernighan-Lin Algorithm for Three-Way Partition Problem
void kernighanLin3WPP(vector<int> &partition1, vector<int> &partition2, vector<int> &partition3, vector<Node> &nodes, int numIterations, bool print = false)
{
    vector<bool> swapped(nodes.size(), false);

    // Calculate D-values for all node pairs (i, j)
    vector<vector<int>> dValues = calculateDValues3WPP(nodes, partition1, partition2, partition3);

    // Calculate the initial cut size
    int cutSize = calculateCutSize3WPP(partition1, partition2, partition3, nodes);

    // Iterate through the nodes in partition 1
    for (int i = 0; i < partition1.size(); ++i)
    {
        // Iterate through the nodes in partition 2
        for (int j = 0; j < partition2.size(); ++j)
        {
            // Iterate through the nodes in partition 3
            for (int k = 0; k < partition3.size(); ++k)
            {
                // Check if all nodes are not swapped
                if (!swapped[partition1[i]] && !swapped[partition2[j]] && !swapped[partition3[k]])
                {
                    // Calculate the gain for swapping nodes i, j, and k
                    int gain = dValues[partition1[i]][partition2[j]] + dValues[partition2[j]][partition3[k]] + dValues[partition3[k]][partition1[i]];

                    // Check if this is the highest gain so far
                    if (gain > 0)
                    {
                        // Swap the nodes with positive gain
                        swap(partition1[i], partition2[j]);
                        swap(partition2[j], partition3[k]);

                        // Mark the nodes as swapped
                        swapped[partition1[i]] = true;
                        swapped[partition2[j]] = true;
                        swapped[partition3[k]] = true;

                        // Calculate the new cut size
                        int newCutSize = calculateCutSize3WPP(partition1, partition2, partition3, nodes);

                        // Check if the cut size has improved
                        if (newCutSize < cutSize)
                        {
                            cutSize = newCutSize;
                        }
                        else
                        {
                            // If the cut size has not improved, swap the nodes back
                            swap(partition1[i], partition2[j]);
                            swap(partition2[j], partition3[k]);

                            // Mark the nodes as unswapped
                            swapped[partition1[i]] = false;
                            swapped[partition2[j]] = false;
                            swapped[partition3[k]] = false;
                        }
                    }
                }
            }
        }
    }

    if (numIterations > 1)
    {
        kernighanLin3WPP(partition1, partition2, partition3, nodes, numIterations - 1, print);
    }

    if (print)
    {
        cout << "Final Partition 1: ";
        for (int node : partition1)
        {
            cout << node << " ";
        }
        cout << endl;

        cout << "Final Partition 2: ";
        for (int node : partition2)
        {
            cout << node << " ";
        }
        cout << endl;

        cout << "Final Partition 3: ";
        for (int node : partition3)
        {
            cout << node << " ";
        }
        cout << endl;
    }
}

int main()
{

    string fileName;
    // Ask user for input file name with edges
    cout << "Please type in the name of the input file. " << endl;

    cin >> fileName;
    // Sample File name
    // fileName = "Hunter.Britton.Input";
    //  Open file
    ifstream inputFile;

    inputFile.open(fileName);

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

    // string line;

    // while (getline(inputFile, line)){
    //     cout << line << endl;
    // }

    // Close file
    inputFile.close();

    // Call function to read graph from file
    vector<Node> nodes = readGraphfromFile(fileName);

    /*
    //List the Neighbors of each node


    for (int i = 0; i < nodes.size(); i++){
        cout << "Node " << nodes[i].id << " has " << nodes[i].neighbors.size() << " neighbors." << endl;
        for (int j = 0; j < nodes[i].neighbors.size(); j++){
            cout << nodes[i].neighbors[j] << " ";
        }
        cout << endl;
    }

    */

    // Check the TWPP

    // Create a random Two Way Partition

    pair<vector<int>, vector<int>> partitions = createTwoWayPartition(18, 0);

    /*
    cout << "Partition 1: ";
    for (int i = 0; i < partitions.first.size(); i++){
        cout << partitions.first[i] << " ";
    }

    cout << endl;
    */

    int numNodes = 18;

    vector<vector<int>> partitions3WPP = createThreeWayPartition(numNodes, 0);

    /*
    // Access the partitions as partitions[0], partitions[1], and partitions[2]
    cout << "Partition 1: ";
    for (int nodeId : partitions[0]) {
        cout << nodeId << " ";
    }
    cout << endl;

    cout << "Partition 2: ";
    for (int nodeId : partitions[1]) {
        cout << nodeId << " ";
    }
    cout << endl;

    cout << "Partition 3: ";
    for (int nodeId : partitions[2]) {
        cout << nodeId << " ";
    }
    cout << endl;
    */

    // Calculate the cut size of the two partitions

    int cutSize = calculateCutSizeTWPP(partitions.first, partitions.second, nodes);

    cout << "Cut Size: " << cutSize << endl;

    int cutSize3WPP = calculateCutSize3WPP(partitions3WPP[0], partitions3WPP[1], partitions3WPP[2], nodes);
    //    cout << "Cut Size for 3WPP: " << cutSize3WPP << endl;

    // Kernighan-Lin Algorithm

    int numItertions = 5;
    kernighanLinTWPP(partitions.first, partitions.second, nodes, numItertions, true);

    int fiveCutSizeTWPP = calculateCutSizeTWPP(partitions.first, partitions.second, nodes);
    cout << "Cut size after 5 iterations: " << fiveCutSizeTWPP << endl;

    // Print out the final partitions

    cout << "Partition 1 (after five iterations): ";
    for (int i = 0; i < partitions.first.size(); i++)
    {
        cout << partitions.first[i] << " ";
    }
    cout << endl;

    cout << "Partition 2 (after five iterations): ";
    for (int i = 0; i < partitions.second.size(); i++)
    {
        cout << partitions.second[i] << " ";
    }
    cout << endl;

    numItertions = 50;
    kernighanLinTWPP(partitions.first, partitions.second, nodes, numItertions, true);

    int finalCutSizeTWPP = calculateCutSizeTWPP(partitions.first, partitions.second, nodes);
    cout << "Cut size after 50 iterations: " << finalCutSizeTWPP << endl;

    // Print out the final partitions

    cout << "Partition 1 (after fifty iterations): ";
    for (int i = 0; i < partitions.first.size(); i++)
    {
        cout << partitions.first[i] << " ";
    }
    cout << endl;

    cout << "Partition 2 (after fifty iterations): ";
    for (int i = 0; i < partitions.second.size(); i++)
    {
        cout << partitions.second[i] << " ";
    }
    cout << endl;

    kernighanLin3WPP(partitions3WPP[0], partitions3WPP[1], partitions3WPP[2], nodes, 1);

    // Three Way Partition Problem outputs

    // Initial Cut size
    cout << "Initial Cut Size for 3WPP: " << cutSize3WPP << endl;

    // Five Iterations KL 3WPP

    kernighanLin3WPP(partitions3WPP[0], partitions3WPP[1], partitions3WPP[2], nodes, 5);

    // Cut size after 5 iterations
    int cutSize3WPP1 = calculateCutSize3WPP(partitions3WPP[0], partitions3WPP[1], partitions3WPP[2], nodes);
    cout << "Cut size after 5 iterations: " << cutSize3WPP1 << endl;


    // Print out after five iterations partitions

    cout << "Partition 1 (after five iterations): ";
    for (int node : partitions3WPP[0])
    {
        cout << node << " ";
    }

    cout << endl;

    cout << "Partition 2 (after five iterations): ";

    for (int node : partitions3WPP[1])
    {
        cout << node << " ";
    }

    cout << endl;

    cout << "Partition 3 (after five iterations): ";

    for (int node : partitions3WPP[2])
    {
        cout << node << " ";
    }

    cout << endl;

    // Fifty Iterations KL 3WPP

    kernighanLin3WPP(partitions3WPP[0], partitions3WPP[1], partitions3WPP[2], nodes, 50);

    // Cut size after 50 iterations

    int cutSize3WPP2 = calculateCutSize3WPP(partitions3WPP[0], partitions3WPP[1], partitions3WPP[2], nodes);

    cout << "Cut size after 50 iterations: " << cutSize3WPP2 << endl;

    // Final Partition

    cout << "Final Partition 1: ";
    for (int node : partitions3WPP[0])
    {
        cout << node << " ";
    }
    cout << endl;

    cout << "Final Partition 2: ";
    for (int node : partitions3WPP[1])
    {
        cout << node << " ";
    }

    cout << endl;

    cout << "Final Partition 3: ";

    for (int node : partitions3WPP[2])
    {
        cout << node << " ";
    }

    cout << endl;

    return 0;
}