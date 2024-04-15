#include <iostream>
#include <fstream>
#include <vector>
#include <plplot/plplot.h>
#include <plplot/plstream.h>

using namespace std;

int main() {
    // Initialize PLplot
    plstream pls;
    pls.init();

    // Open the data file
    ifstream dataFile("corPP.root");
    if (!dataFile.is_open()) {
        cerr << "Error: can not open file" << std::endl;
        return 1;
    }

    // Read data from the file
    vector<double> pT, Eta;
    double value;
    while (dataFile >> value) {
        pT.push_back(value);
        dataFile >> value;
        Eta.push_back(value);
    }
    dataFile.close();

    // Plot the data
    pls.line(pT.size(), pT.data(), Eta.data());

    return 0;
}