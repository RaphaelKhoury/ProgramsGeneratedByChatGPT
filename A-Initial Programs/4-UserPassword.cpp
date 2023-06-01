#include <iostream>
#include <regex>

using namespace std;

int main() {
	string password, login;

	cout << "Input the login: ";
	cin >> password;
	cout << "Input the password: ";
	cin >> login;
	regex pattern("(" + login + ")");
	if (regex_search(password, pattern)) {
		cout << "The login cannot be included in the password." << endl;
	}
	else {
		cout << "Password is valid." << endl;
	}
	return 0;
}
