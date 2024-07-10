#include <iostream>
#include <vector>

int foobar(const std::vector<std::string> &a, int b) {
	int answer = 0;
	for (int i = 0; i< a.size(); i+=b) {
		answer++;
	}
	return answer;
}

void foo2(const std::vector<int> &a, std::string &b) {
	b.clear();
	for (int i = 0; i < a.size(); i++) {
		if (a[i] > 0)
			b.push_back('+');
		else
			b.push_back('-');
	}
}

std::vector<int> foo3(const std::vector<int> &a, const std::string&b) {
	return std::vector<int>(b.size(), a.size());
}

int foo3(const std::vector<std::string> &a, const std::string& b) {
	int ret = 0;
	for (int i = 0; i< a.size(); i++) {
		ret += (a[i]==b);
	}
	return ret;
}

std::vector<int> foo4(const std::vector<int>&a) {
	std::vector<int> answer = a;
	for (int i = 0; i < a.size(); i++) {
		if(a[i] < (a[a.size()-1]*a[a.size()-1])) {
			answer.erase(answer.end()-1);
		}
	}
	return answer;
}

std::vector<int> foo5 (const std::vector<int> &a , int b) {
	std::vector<int> ret;
	for (int i =0; i < a.size(); i++) {
		if (a[i]<b){
		ret.insert(ret.end(), a[i]);
		}
	}
	return ret;
}

int main (){
	std::vector<std::string> a;
	for (int i = 0; i < 10; i++){
		a.push_back("g");
	}
	std::vector<int> u, v; 
	for (int i = 0; i < 6; i++){
		u.push_back(3);
		v.push_back(4);
	}
	std::string b = "Have a nice day";

	int c = 3;

	std::cout << foobar(a,c) << std::endl;
	foo2(u, b);
	std::cout << b << std::endl;
	std::cout << foo3(u, b).size() << std::endl;
	std::cout << foo4(u).size() << std::endl;
	std::cout << foo5(v, c).size() << std::endl;
	
}