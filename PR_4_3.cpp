#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

int main() {
    ifstream file("input.txt"); 
    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    int char_count = 0, word_count = 0, line_count = 0;
    int space_count = 0, tab_count = 0, newline_count = 0;
    
    string line;
    while (getline(file, line)) { 
        line_count++; 
        char_count += line.length(); 

        bool inWord = false;
        for (char ch : line) {
            if (isspace(ch)) {
                if (ch == ' ') space_count++;  
                if (ch == '\t') tab_count++;  

                if (inWord) {
                    word_count++;
                    inWord = false;
                }
            } else {
                inWord = true;
            }
        }
        if (inWord) word_count++; 
    }
    
    newline_count = line_count;  
    char_count += newline_count; 

    file.close(); 

    cout << "Total Characters : " << char_count << endl;
    cout << "Total Words : " << word_count << endl;
    cout << "Total Lines : " << line_count << endl;
    cout << "Spaces : " << space_count << endl;
    cout << "Tabs : " << tab_count << endl;
    cout << "Newlines : " << newline_count << endl;

    return 0;
}
