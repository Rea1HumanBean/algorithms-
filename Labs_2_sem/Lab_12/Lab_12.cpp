#include <iostream>
#include <string>
#include <vector>

std::vector<int> KMP(const std::string& pattern) {
    std::vector<int> arr(pattern.size(), 0);
    int i = 1, j = 0;
    while (i < pattern.size()) {
        if (pattern[j] == pattern[i]) {
            arr[i] = j + 1;
            i++; j++;
        }
        else
            if (j == 0) {
                arr[i] = 0;
                i++;
            }
            else j = arr[j - 1];
    }
    return arr;
}

void searchPattern(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> p = KMP(pattern);
    int i = 0, j = 0, check = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
            if (j == m) {
                check = 1;
                std::cout << "Pattern found at index " << i - m << std::endl;
            }
        }
        else {
            if (j > 0)
                j = p[j - 1];
            else i++;
        }
        if (i == n && !check)
            std::cout << "There is no pattern in the text " << std::endl;
    }

}

int main() {
    std::string text = " abcabca abacbab abcabcabc";
    std::string pattern = "abcabc";
    searchPattern(text, pattern);
    return 0;
}