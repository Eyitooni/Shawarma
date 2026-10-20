#include <iostream>
#include <vector>
// Made Split function for string because C++ doesnt have it like you said it does ;-; only .contains, 
// Update, Mine definitely does not have .split nor .contains maybe it is my decade old c++ 17 compiler in vscode
std::vector<std::string> split(std::string s,char split) {
    std::vector<std::string> updated;
    int index = 0;
    for (int string = 0; string < s.size(); string++) {
        if (s[string] == split) {
            std::string newstring;
            for (int i = index; i < string; i++) {
                newstring += s[i];
            }
            index = string + 1;
            updated.push_back(newstring);
        }
    }
    
    if (index != s.size() - 1) {
        std::string remainder;
        for (int i = index; i < s.size() - 1; i++) {
            remainder += s[i];
        }
        updated.push_back(remainder);
    }

    return updated;
}

