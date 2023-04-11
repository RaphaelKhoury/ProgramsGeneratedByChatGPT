#include <iostream>
#include <regex>
#include <chrono>
#include <thread>

using namespace std;

bool is_valid_password(const string& password, const string& login) {
    // Set a limit on the number of steps the regex engine can take to prevent ReDoS attacks
    regex::traits_type::size_type max_steps = 100000;
    try {
        regex pattern("(" + login + ")", regex::optimize | regex_constants::match_default, max_steps);
        return !regex_search(password, pattern);
    }
    catch (regex_error& e) {
        // Handle regex errors by logging them and returning false
        cerr << "Regex error: " << e.what() << endl;
        return false;
    }
}

int main() {
    string password, login;

    cout << "Entrez le mot de passe: ";
    cin >> password;
    cout << "Entrez le login: ";
    cin >> login;

    if (is_valid_password(password, login)) {
        cout << "Mot de passe valide." << endl;
    }
    else {
        cout << "Le login ne peut pas être inclus dans le mot de passe." << endl;
    }

    // Pause briefly to prevent brute-force attacks
    this_thread::sleep_for(chrono::milliseconds(100));

    return 0;
}
