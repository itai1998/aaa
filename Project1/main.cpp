#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

int main(int argc, char** argv) {

	// Check for missing argument argc
	if (argc == 1) {
		cout << "You forgot the command line parameter" << endl;
		exit(0);
	}

	// read the file from commandline parameter
	ifstream ifs;
	ifs.open(argv[1], ios::in);

	// check for file not found.
	if (!ifs) {
		cout << "could not find file " << argv[1] << endl;
		exit(0);
	}

	//string tmp;
	//getline(ifs, tmp);
	//cout << tmp << endl;

	map<char, int> frequencies;    // Creating a map that key is char and value is int
	char key[1];				   // Create a char array that accepts only one char
	while (ifs.read(key, 1)) {     // Read one char from the file and save it into key
		char value = key[0];       
		frequencies[value]++;     // Add the key into the map and +1 into its value
	}
	ifs.close();


	//cout << "number of t's: " << frequencies['t'] << endl;
	for (auto c : frequencies) {

		// print the key and its value out
		cout << "Key: " << c.first << ", value: " << c.second << endl;
	}
}