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

	map<char, int> frequencies;
	char jared[1];
	while (ifs.read(jared, 1)) {
		char parker = jared[0];
		//int count = frequencies[parker];
		//count++;
		//frequencies[parker] = count;
		frequencies[parker]++;
	}
	ifs.close();
	//cout << "number of t's: " << frequencies['t'] << endl;
	for (auto c : frequencies) {
		cout << "Key: " << c.first << ", value: " << c.second << endl;
	}

	cout << "this is test" << endl;
	cout << "thie is the second line" << endl;
}