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

    bool search(TreeNode* root, int _value) {
        if (root == nullptr)
            return false;

        if (root->value == _value)
            return true;

        return search(root->left, _value) || search(root->right, _value);
    }

    void insert(TreeNode*& root, int key) {
        if (root == nullptr) {
            TreeNode* leaf = new TreeNode(key);
            root = leaf;
        }

        if (key < root->value) {
            insert(root->left, key);
        }
        else if (key > root->value) {
            insert(root->right, key);
        }
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void remove(TreeNode*& root, int key) {
        if (root == nullptr) {
            return;
        }

        if (key == root->value) {
            if (root->left == nullptr) {
                root = root->right;
            }
            else if (root->right == nullptr) {
                root = root->left;
            }
            else {
                rebuild(root);
            }
        }
        else {
            remove(root->left, key);
            remove(root->right, key);
        }
    }

    void rebuild(TreeNode*& root) {
        if (root->right == nullptr && root->left == nullptr) {
            root = nullptr;
        }
        else if (root->left == nullptr) {
            root = root->right;
        }
        else if (root->right == nullptr) {
            root = root->left;
        }
        else {
            root->value = (root->left->value > root->right->value) ? root->right->value : root->left->value;
            if (root->left->value > root->right->value)
                rebuild(root->right);
            else rebuild(root->left);
        }
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

    bool search(int key) {
        return search(root, key);
    }

    void insert(int key) {
        insert(root, key);
    }

    void remove(int key) {
        remove(root, key);
    }
};

class Menu {
    BinaryTree* tree;
public:
    Menu(const std::string _path) {
        tree = new BinaryTree(_path);
    }

    void DoList() {
        int doSomething = 0;
        int a;
        while (doSomething != 5) {
            std::cout << "Enter number command" << '\n';
            std::cout << "Search - 1" << '\n' << "Insert - 2" << '\n' << "Delete - 3" << '\n' << "Print - 4" << '\n' << "Exit - 5" << '\n';
            std::cin >> doSomething;
            switch (doSomething) {
            case 1:
                std::cout << "Enter the number you want to search" << '\n';
                std::cin >> a;
                if (tree->search(a) == false)
                    std::cout << "Present" << '\n';
                else std::cout << "Absent" << '\n';
                break;
            case 2:
                std::cout << "Enter the number you want to insert" << '\n';
                std::cin >> a;
                tree->insert(a);
                break;
            case 3:
                std::cout << "Enter the number you want to delete" << '\n';
                std::cin >> a;
                tree->remove(a);
                break;
            case 4:
                tree->preOrderRecursive();
                break;
            case 5:
                return;
            }
        }
    }
};
int main() {
    Menu Tree("Data/Tree.txt");
    Tree.DoList();
    return 0;
}