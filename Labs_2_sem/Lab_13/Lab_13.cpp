#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

std::map<char, int> displaced(const std::string& pattern) {
    std::set<char> uniqueChars;
    std::map<char, int> displaceMap;
    int p_size = pattern.size() - 1;
    for (int i = p_size - 1; i >= 0; i--) {
        if (uniqueChars.find(pattern[i]) == uniqueChars.end()) {
            uniqueChars.insert(pattern[i]);
            displaceMap.insert(std::make_pair(pattern[i], p_size - i));
        }
    }

    if (uniqueChars.find(pattern[p_size]) == uniqueChars.end())
        displaceMap.insert(std::make_pair(pattern[p_size], p_size + 1));

    displaceMap.insert(std::make_pair('*', p_size + 1));
    return displaceMap;
}

void algorithmBMH(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::map<char, int> p = displaced(pattern);

    int i = m - 1, check = 0;
    while (i < n) {
        int k = 0;
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i - k]) {
            j--;
            k++;
        }
        if (j == -1) {
            check = 1;
            std::cout << "Pattern found at index " << i - m + 1 << std::endl;
        }
        if (p.find(text[i]) == p.end()) {
            i += p['*'];
        }
        else {
            i += p[text[i]];
        }
    }
    if (!check)
        std::cout << "There is no pattern in the text " << std::endl;
}

int main() {
    std::string text = " abcabca abacbab abcabcabc";
    std::string pattern = "abcabc";
    algorithmBMH(text, pattern);
    return 0;
}