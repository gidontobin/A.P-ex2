#include "timeseries.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::istringstream;

string readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

int main()
{
    string filename("trainFile1.csv");
    string file_contents = readFileIntoString(filename);
    istringstream sstream(file_contents);
    string line;
    std::vector<std::string> seglist;
    while (std::getline(sstream, line)) {
        while (std::getline(sstream, line,',')) {

        }
        seglist.push_back(line);
    }
    for (string i: seglist)
        std::cout << i << endl;
}