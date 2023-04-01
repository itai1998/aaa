#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

int total_bit = 0;
using namespace std;

// A Tree node
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}


// Builds Huffman Tree and decode given input text
void buildHuffmanTree(map<char, int> freq, string orderString)
{

	// count frequency of appearance of each character
	// and store it in a map
	//unordered_map<char, int> freq;
	//for (char ch : text) {
	//	freq[ch]++;
	//}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	Node* root = pq.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	int count_bit;
	for (auto pair : huffmanCode) {
		count_bit = 0;
		cout << pair.second << " " << pair.first << endl;
		count_bit = pair.second.size() * freq[pair.first];
		total_bit += count_bit;

	}

	//cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string

	string str = "";
	int count;
	for (char ch : orderString) {
		count = 0;
		str += huffmanCode[ch];
	}



	//string str = "";
	//
	//for (auto i : freq) {
	//	cout << i.first << endl;
	//	str += i.second;
	//}

	// try to use map to display the int 
	cout << "the following string is for testing" << endl;
	//for (int i = 0; i < orderString.size(); i++) {
	//	cout << orderString[i];
	//}
	//cout << " " << endl;

	cout << "encodeing is: " << str << endl;

}

// Huffman coding algorithm
int main(int argc, char** argv)
{

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

	string text = "Was it a rat I saw? \n ";
	map<char, int> frequencies;

	string input_word = "";
	char key[1];				   // Create a char array that accepts only one char
	while (ifs.read(key, 1)) {     // Read one char from the file and save it into key
		char value = key[0];
		frequencies[value]++;      // Add the key into the map and +1 into its value
		input_word += value;
	}
	ifs.close();


	//for (auto c : frequencies) {
	//	// print the key and its value out
	//	cout << "Key: " << c.first << ", value: " << c.second << endl;
	//}

	string input;

	buildHuffmanTree(frequencies, input_word);
	cout << "*****" << endl;
	cout << total_bit << endl;


	return 0;
}