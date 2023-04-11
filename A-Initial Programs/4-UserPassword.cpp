#include <iostream>
#include <regex>

using namespace std;

int main() {
	string password, login;

	cout << "Entrez le mot de passe: ";
	cin >> password;
	cout << "Entrez le login: ";
	cin >> login;
	regex pattern("(" + login + ")");
	if (regex_search(password, pattern)) {
		cout << "Le login ne peut pas être inclus dans le mot de passe." << endl;
	}
	else {
		cout << "Mot de passe valide." << endl;
	}
	return 0;
}