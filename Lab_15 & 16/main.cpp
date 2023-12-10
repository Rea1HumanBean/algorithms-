#include <iostream>
#include <fstream>
#include <string>
#include <stack>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int _value, TreeNode* _left = nullptr, TreeNode* _right = nullptr) : value(_value), left(_left), right(_right) {}
};

class BinaryTree {
private:
    TreeNode* root;

    size_t searchBranch(const std::string& str, size_t index) {
        int RightValue = -1;

        if (str[index] == ',' || str[index] == ')')
            return 0;

        index++;
        while (RightValue != 0 || index < str.size()) {
            if (RightValue == -1 && str[index] == ',')
                return index;

            if (str[index] == '(')
                RightValue--;

            if (str[index] == ')')
                RightValue++;

            index++;
        }

        return index;
    }

    void parseAndBuild(TreeNode*& root, const std::string& str, size_t& index, size_t& end_index) {
        int _value = 0;
        size_t Branch_end = 0;

        while (index < end_index) {
            while (index < str.size() && isdigit(str[index])) {
                _value = _value * 10 + (str[index] - '0');
                index++;
            }

            if (_value != 0) {
                if (root == nullptr)
                    root = new TreeNode(_value);

                Branch_end = searchBranch(str, index);

                if (Branch_end == 0)
                    return;

                parseAndBuild(root->left, str, index, Branch_end);
                parseAndBuild(root->right, str, index, end_index);
            }
            _value = 0;
            index++;
        }
    }

    void preOrderRecursive(TreeNode* node) {
        if (node == nullptr)
            return;
        std::cout << node->value << " ";
        preOrderRecursive(node->left);
        preOrderRecursive(node->right);
    }

    void centerRecursive(TreeNode* node) {
        if (node == nullptr)
            return;
        centerRecursive(node->left);
        std::cout << node->value << " ";
        centerRecursive(node->right);
    }

    void endedRecursive(TreeNode* node) {
        if (node == nullptr)
            return;

        endedRecursive(node->left);
        endedRecursive(node->right);
        std::cout << node->value << " ";
    }

    void preOrderNonRecursive(TreeNode* node) {
        if (node == nullptr)
            return;

        std::stack<TreeNode*> stack;
        stack.push(node);

        while (!stack.empty()) {
            TreeNode* current = stack.top();
            stack.pop();

            std::cout << current->value << " ";

            if (current->right)
                stack.push(current->right);

            if (current->left)
                stack.push(current->left);
        }
    }

    std::string readTree(const std::string& _path) {
        std::ifstream file(_path);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file." << std::endl;
            return "";
        }

        std::string _tree;
        std::getline(file, _tree);
        file.close();
        _tree.erase(std::remove(_tree.begin(), _tree.end(), ' '), _tree.end());
        if (!_tree.empty() && isWithoutMistake(_tree))
            return _tree;
        else {
            std::cerr << "Error: : Invalid tree structure in the file." << std::endl;
            return "";
        }
    }

    bool isWithoutMistake(const std::string& _tree) {
        int count = 0;
        for (char a : _tree) {
            if (a == '(')
                count++;
            else if (a == ')') {
                count--;
                if (count < 0) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    BinaryTree(std::string _path) : root(nullptr) {
        std::string treeString = readTree(_path);
        size_t index = 0;
        size_t end_index = treeString.size();
        std::cout << treeString << '\n';

        parseAndBuild(root, treeString, index, end_index);
    }

    void preOrderRecursive() {
        std::cout << "Started Recursive Traversal: ";
        preOrderRecursive(root);
        std::cout << '\n';
    }

    void centerRecursive() {
        std::cout << "Center Recursive Traversal: ";
        centerRecursive(root);
        std::cout << '\n';
    }

    void endedRecursive() {
        std::cout << "Ended Recursive Traversal: ";
        endedRecursive(root);
        std::cout << '\n';
    }

    void NotRecursiveOrder() {
        std::cout << "Not Recursive: ";
        preOrderNonRecursive(root);
        std::cout << '\n';
    }

};

int main() {
    BinaryTree tree("Data/Tree.txt");

    tree.preOrderRecursive();
    tree.centerRecursive();
    tree.endedRecursive();

    tree.NotRecursiveOrder();

    return 0;
}