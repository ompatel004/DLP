#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <vector>
using namespace std;

struct Token {
    string type;
    string value;
};

const unordered_set<string> keywords = {
    "int", "char", "float", "double", "return", "if", "else", "for", "while", "do", "switch", "case", "break", "continue", "void", "static", "struct", "typedef", "const"
};


const unordered_set<char> punctuation = {'(', ')', '{', '}', '[', ']', ',', ';'};
const unordered_set<string> operators = {"=", "+", "-", "*", "/", "%", "==", "!=", "<", "<=", ">", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>"};

void removeCommentsInFile(const string &filename, string &processedSource) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    bool multiLineComment = false;

    while (getline(inputFile, line)) {
        if (multiLineComment) {
            size_t endPos = line.find("*/");
            if (endPos != string::npos) {
                multiLineComment = false;
                line = line.substr(endPos + 2);
            } else {
                continue;
            }
        }

        size_t singleLinePos = line.find("//");
        if (singleLinePos != string::npos) {
            line = line.substr(0, singleLinePos);
        }

        size_t multiLineStart = line.find("/*");
        if (multiLineStart != string::npos) {
            multiLineComment = true;
            line = line.substr(0, multiLineStart);
        }

        if (!line.empty()) {
            processedSource += line + "\n";
        }
    }

    inputFile.close();
}

vector<Token> tokenize(const string &sourceCode, unordered_set<string> &symbolTable, vector<string> &lexicalErrors) {
    vector<Token> tokens;
    regex tokenRegex(R"((\d+[a-zA-Z_][a-zA-Z0-9_]*|[a-zA-Z_][a-zA-Z0-9_]*|\d+|'[^']*'|"[^"]*"|==|!=|<=|>=|&&|\|\||[{}()\[\],;]|[-+*/%=&|^!<>~]))");
    smatch match;
    string::const_iterator searchStart(sourceCode.cbegin());

    while (regex_search(searchStart, sourceCode.cend(), match, tokenRegex)) {
        string token = match[0];

        // Check for keywords
        if (keywords.count(token)) {
            tokens.push_back({"Keyword", token});
        }
        // Check for punctuation
        else if (punctuation.count(token[0])) {
            tokens.push_back({"Punctuation", token});
        }
        // Check for operators
        else if (operators.count(token)) {
            tokens.push_back({"Operator", token});
        }
        // Check for numeric constants
        else if (regex_match(token, regex(R"(\d+)"))) {
            tokens.push_back({"Constant", token});
        }
        // Check for strings or characters
        else if (regex_match(token, regex(R"('[^']*')"))) {
            tokens.push_back({"String", token});
        }
        // Check for valid identifiers
        else if (regex_match(token, regex(R"([a-zA-Z_][a-zA-Z0-9_]*)"))) {
            tokens.push_back({"Identifier", token});
            if (token != "main") {
                symbolTable.insert(token);
            }
        }
        // If the token starts with a digit but contains letters (e.g., 7H)
        else if (regex_match(token, regex(R"(\d+[a-zA-Z_][a-zA-Z0-9_]*)"))) {
            lexicalErrors.push_back(token);
        }
        // All other cases
        else {
            lexicalErrors.push_back(token);
        }

        searchStart = match.suffix().first;
    }

    return tokens;
}


void writeOutput(const string &filename, const vector<Token> &tokens, const unordered_set<string> &symbolTable, const vector<string> &lexicalErrors, const string &processedSource) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }

    outputFile << "TOKENS:\n";
    for (const auto &token : tokens) {
        outputFile << token.type << ": " << token.value << "\n";
    }

    outputFile << "\nSYMBOL TABLE ENTRIES:\n";
    for (const auto &symbol : symbolTable) {
        outputFile << symbol << "\n";
    }

    outputFile << "\nLEXICAL ERRORS:\n";
    for (const auto &error : lexicalErrors) {
        outputFile << error << "\n";
    }

    outputFile << "\nMODIFIED SOURCE CODE:\n" << processedSource;
    outputFile.close();
}

int main() {
    string filename = "sample.txt";
    string processedSource = "";

    // Step 1: Remove comments
    removeCommentsInFile(filename, processedSource);

    unordered_set<string> symbolTable;
    vector<string> lexicalErrors;
    vector<Token> tokens = tokenize(processedSource, symbolTable, lexicalErrors);

    string outputFilename = "output.txt";
    writeOutput(outputFilename, tokens, symbolTable, lexicalErrors, processedSource);

    cout << "Lexical analysis complete. Results saved to " << outputFilename << endl;

    return 0;
}
