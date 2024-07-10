#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
	string file = argv[1];
	string h;
	map<string, int> pool;
	std::ifstream inFile(file);
	while (inFile >> h) {
		++pool[h];
	}
	int mode = 0;
	map<string, int>::const_iterator itr;
	for (itr = pool.begin(); itr != pool.end(); ++itr) {
		if (itr->second > mode) {
			mode = itr->second;
		}
	}
	vector<string> modeVal;
	for (itr = pool.begin(); itr != pool.end(); ++itr) {
		if (itr->second == mode) {
			modeVal.push_back(itr->first);
		}
	}
	cout << "Modes: ";
	for (int n = 0; n<modeVal.size(); n++) {
		cout << modeVal[n] << " ";
	}
	cout<<endl;
}