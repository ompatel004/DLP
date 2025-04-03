#include <iostream>
#include <cctype>
using namespace std;

bool isValidPassword(const string &password) {
    if (password.length() < 9 || password.length() > 15) 
        return false;

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    
    string specialChars = "*;,#$@";

    for (char ch : password) {
        if (islower(ch)) hasLower = true;
        else if (isupper(ch)) hasUpper = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (specialChars.find(ch) != string::npos) hasSpecial = true;
    }

    return hasLower && hasUpper && hasDigit && hasSpecial;
}

int main() {
    string password;
    cout << "Enter password: ";
    cin >> password;  
    
    if (isValidPassword(password))
        cout << "Valid password" << endl;
    else
        cout << "Invalid password" << endl;

    return 0;
}
