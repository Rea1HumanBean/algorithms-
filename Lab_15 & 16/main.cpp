#include <iostream>
#include <fstream>
#include <string>
#include <stack>

struct TreeNode
{
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int _value) : value(_value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void insertIntoTree(TreeNode*& root, int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
        }
        else {
            if (value < root->value) {
                insertIntoTree(root->left, value);
            }
            else {
                insertIntoTree(root->right, value);
            }
        }
    }

    void buildTreeFromString(TreeNode*& root, const std::string& str, size_t& index) {
        while (index < str.size() && (str[index] == ' ' || str[index] == ',')) {
            index++;
        }
        if (index == str.size() || str[index] == ')') {
            return;
        }
        int value = 0;
        while (index < str.size() && std::isdigit(str[index])) {
            value = value * 10 + (str[index] - '0');
            index++;
        }
        insertIntoTree(root, value);
        if (index < str.size() && str[index] == '(') {
            index++;
            buildTreeFromString(root->left, str, index);
        }

        if (index < str.size() && str[index] == ',') {
            index++;
            buildTreeFromString(root->right, str, index);
        }
        index++; // Увеличение index на ')' после обработки поддерева
    }

public:
    BinaryTree(std::string _path) : root(nullptr) {
        std::string treeString = readTree(_path);
        std::cout << treeString << '\n';
        size_t index = 0;

        buildTreeFromString(root, treeString, index);
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
};

int main() {
    BinaryTree tree("Data/Tree.txt");
    tree.rightRecursive();
    tree.centerRecursive();
    tree.endedRecursive();

    return 0;
}