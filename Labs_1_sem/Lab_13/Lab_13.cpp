#include <iostream>
#include <string>
#include <fstream>
#include <list>

class  Hash_Table {
	std::list< std::string> *Table;
	size_t Size_table;

	int hash_function(const std::string& _name) {
		int sum = 0;
		for (char a : _name)
			sum += (int)a;

		return (sum %= Size_table);
	}

	void define_Table(std::string _path) {
		std::ifstream file(_path);

		if (!file.is_open()) {
			std::cerr << "Error: Could not open the file." << std::endl;
			return;
		}

		std::string name;
		while (file >> name) {
			Size_table++;
		}

		file.close();

		file.open(_path);

		Table = new std::list<std::string>[Size_table];
		while (file >> name) {
			insert(name);
		}
		file.close();
	}

public:
	Hash_Table(std::string _path){
		define_Table(_path);
	};

	void insert(std::string _name) {
		int index = hash_function(_name);
		if(Table[index].empty())
			Table[index].push_back(_name);
		else {
			int free_pos = 0;
			while (!Table[free_pos].empty()) {
				free_pos++;
			}
			Table[free_pos].push_back(_name);
		}
	}
	void print_to_file(std::string _path) {
		std::ofstream outputFile(_path);
		if (!outputFile.is_open()) {
			std::cerr << "Error: Could not open the file for writing." << std::endl;
		}
		for (int i = 0; i < Size_table; i++){
			if (!Table[i].empty()) {
				outputFile << '[';
				for (const auto& item : Table[i])
					outputFile << item;
				outputFile << "]\n";
			}
			else
				outputFile << "[ ]\n";
		}
		outputFile.close();
	}

	~Hash_Table() {
		delete[] Table;
		Table = nullptr;
	}
};

int main() {
	Hash_Table Table("Data/Name.txt");
	Table.print_to_file("Table/output.txt");
}