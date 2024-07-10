#include <iostream>
#include <string>

int lengthOfLongestSubstring(std::string s) {
	if (s.size() <= 1) {
		return s.size();
	}
	int res = 0;
	std::string cur;
	int idx = 0;
	while (idx != s.size()) {
		for (int n = idx; n < s.size(); n++) {
			if (cur.find(s[n])==std::string::npos) {
				cur.push_back(s[n]);
			}
			else if (cur.find(s[n])!=std::string::npos) {
				if (cur.size()>res) {
					res = cur.size();
				}
				std::cout << cur << std::endl;
				cur.clear();
				idx++;
			}
		}
	}
	return res;

}

int main() {
	std::cout << lengthOfLongestSubstring()

}