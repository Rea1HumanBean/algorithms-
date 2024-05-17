#include <iostream>
#include <vector>
#include <string>

std::vector<int> computeTransitionTable(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> transition(m + 1, 0);
    transition[0] = -1;
    int k = -1;
    for (int q = 1; q <= m; ++q) {
        while (k >= 0 && pattern[k] != pattern[q - 1]) {
            k = transition[k];
        }
        k++;
        transition[q] = k;
    }
    return transition;
}

void searchPattern(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> transition = computeTransitionTable(pattern);
    int q = 0;
    for (int i = 0; i < n; ++i) {
        while (q >= 0 && pattern[q] != text[i]) {
            q = transition[q];
        }
        q++;
        if (q == m) {
            std::cout << "Pattern found at index " << i - m + 1 << std::endl;
            q = transition[q];
        }
    }
}

int main() {
    std::string text = "ababcababcabcabc";
    std::string pattern = "abcabc";

    searchPattern(text, pattern);
    return 0;
}