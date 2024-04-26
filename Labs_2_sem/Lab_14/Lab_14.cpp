#include <iostream>
#include <string>
#include <vector>
#include <cmath>

unsigned long long calculateHash(const std::string& str, int start, int end, int prime) {
    unsigned long long hashValue = 0;
    for (int i = start; i <= end; ++i) {
        hashValue = (hashValue * prime + (int)str[i]) % prime;
    }
    return hashValue;
}

void searchRabinKarp(const std::string& text, const std::string& pattern, int prime) {
    int n = text.length();
    int m = pattern.length();
    int p = prime;

    unsigned long long patternHash = calculateHash(pattern, 0, m - 1, p);
    unsigned long long textHash = calculateHash(text, 0, m, p);

    for (int i = 0; i <= n - m; ++i) {
        if (patternHash == textHash) {
            bool check = true;
            for (int j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j]) {
                    check = false;
                }
            }
            if (check) {
                std::cout << "Pattern found at index " << i << std::endl;
            }
        }
        if (i < n - m) {
            textHash = (textHash - (int)text[i] + p) % p;
            textHash = (textHash * prime + (int)text[i + m]) % p;
        }
    }
}

int main() {
    std::string text = " abcabca abacbab abcabcabc";
    std::string pattern = "abcabc";
    int prime = 111;

    searchRabinKarp(text, pattern, prime);

    return 0;
}