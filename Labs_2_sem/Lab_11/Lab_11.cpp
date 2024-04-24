#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefFunc(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> func(m + 1, 0);
    func[0] = -1;
    int k = -1;
    for (int q = 1; q <= m; ++q) {
        while (k >= 0 && pattern[k] != pattern[q - 1])
            k = func[k];
        func[q] = ++k;
    }
    return func;
}

void searchPattern(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> func = prefFunc(pattern);
    int q = 0;
    for (int i = 0; i < n; ++i) {
        while (q >= 0 && pattern[q] != text[i])
            q = func[q];
        if (++q == m) {
            std::cout << "Pattern found at index " << i - m + 1 << std::endl;
            q = func[q];
        }
    }
}

int main() {
    std::string text = "ababcababcabca";
    std::string pattern = "ababc";
    searchPattern(text, pattern);
    return 0;
}