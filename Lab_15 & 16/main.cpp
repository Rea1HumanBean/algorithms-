#include <iostream>
#include <fstream>
#include <string>
#include <stack>

int rank(int number) {
    int count = 0;
    while (number > 0) {
        number /= 10;
        count++;
    }

    return count;
}

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int _value, TreeNode* _left = nullptr, TreeNode* _right = nullptr) : value(_value), left(_left), right(_right) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void parseAndBuild(TreeNode*& _root, const std::string& str, size_t& index) {
        static int _value = 0;

        while (index < str.size()) {
            while (index < str.size() && isdigit(str[index])) {
                _value = _value * 10 + (str[index] - '0');
                index++;
            }

            if (_value != 0) {
                TreeNode* newNode = new TreeNode(_value);
                if (_root == nullptr) {
                    _root = newNode;
                }

                if (index < str.size() && str[index] == '(') {
                    _value = 0;
                    index++;
                    parseAndBuild(newNode->left, str, index);
                }

                if (index < str.size() && str[index] == ',') {
                    _value = 0;
                    index++;
                    parseAndBuild(newNode->right, str, index);
                }
            }

            if (index < str.size() && str[index] == ')') {
                index++;
                return;
            }

            index++;
        }
    }

public:
    BinaryTree(std::string _path) : root(nullptr) {
        std::string treeString = readTree(_path);
        size_t index = 0;
        std::cout << treeString << '\n';
        parseAndBuild(root, treeString, index);
    }

    void rightRecursive() {
        std::cout << "Right Recursive Traversal: ";
        rightRecursive(root);
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

    void NotRecursive() {
        std::cout << "NotRecursive Traversal: ";
        NotRecursive(root);
        std::cout << '\n';
    }

private:
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

    void rightRecursive(TreeNode* node) {
        if (node == nullptr)
            return;

        std::cout << node->value << " ";
        rightRecursive(node->left);
        rightRecursive(node->right);
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

    void NotRecursive(TreeNode* node) {
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
};

int main() {
    BinaryTree tree("Data/Tree.txt");
    tree.rightRecursive();
    tree.centerRecursive();
    tree.endedRecursive();
    tree.NotRecursive();

    return 0;
}