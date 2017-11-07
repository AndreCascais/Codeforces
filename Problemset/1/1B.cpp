#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>

std::string reverseFormat(std::string code);
int getType(std::string code);

std::string reverseFormat(std::string code) {
    
    int t = getType(code);
    
    long long row = 0, col = 0;
    if (t == 1) { // CCCDDD
        int i = 0;
        while(isalpha(code[i])) {
            col = col * 26 + code[i++] - 'A' + 1;
        }
        for(; i < code.length(); i++) {
            row = row * 10 + code[i] - '0';
        }
        return std::string("R") + std::to_string(row) + std::string("C") + std::to_string(col);
    }
    else { // RXCY
        int res, i = 1;
        std::string result = "";
        while(code[i] != 'C') {
            row = row * 10 + code[i++] - '0';
        }
        for(i = i + 1; i < code.length(); i++) {
            col = col * 10 + code[i] - '0';
        }
        while(col > 0) {
            res = col % 26;
            // -1 % a is not a - 1
            result.append(std::string(1, ((res - 1) + 26) % 26 + 'A'));
            // special case
            if (res == 0) {
                col = col / 26 - 1;
            }
            else {
                col = col / 26;
            }   
        }
        std::reverse(result.begin(), result.end());
        return result + std::to_string(row);
    }
}
 // 0 for RXCY 1 otherwise
int getType(std::string code) {
    if (code[0] == 'R') {
        if (isalpha(code[1])) {
            return 1;
        }
        for (int i = 2; i < code.length(); i++) {
            if (code[i] == 'C') {
                return 0;
            }
        }
        return 1;
    }
    return 1;
}

int main() {
    long long i, n;
    std::string code, reverseCode;
    int format;
    std::cin >> n;
    std::cin.get();
    for (i = 0; i < n; i++) {
        std::getline(std::cin, code);
        reverseCode = reverseFormat(code);
        std::cout << reverseCode << std::endl;
    }
    return 0;
}