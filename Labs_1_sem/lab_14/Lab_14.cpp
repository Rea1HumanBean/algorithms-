#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Table_element {
	std::string Name;
public:
	bool be_deleted;
	Table_element(std::string _Name) : Name(_Name), be_deleted(false) {};
};

class  Hash_Table {
	std::vector<std::vector<Table_element>> Table;
	size_t Size_table;
	size_t Quantity_Elements = 0;

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
		while (file >> name)
			Size_table++;

		if (Size_table < 5)
			Size_table = 5;

		file.close();
		file.open(_path);

		Table.resize(Size_table);
		while (file >> name) {
			insert(name);
			Quantity_Elements++;
		}
		file.close();
	}

	void expand(int _size) {
		std::vector<std::vector<Table_element>> New_Table;
		New_Table.resize(_size * 1.5);

		for (const auto& vectorItem : Table) {
			for (const auto& elementItem : vectorItem) {
				if (elementItem.be_deleted == false)
					New_Table[hash_function(elementItem.Name)].push_back(elementItem);
			}
		}
		Table = New_Table;
	}

public:
	Hash_Table(std::string _path) {
		define_Table(_path);
	};
	void insert(std::string _name) {
		Table_element _element(_name);
		int index = hash_function(_name);
		if (Quantity_Elements > 2 * Size_table)
			expand(Quantity_Elements);

		if (Table[index].empty())
			Table[index].push_back(_element);

		else {
			int free_pos = 0;
			while (!Table[free_pos].empty())
				free_pos++;
			Table[index].push_back(_element);
		}
		Quantity_Elements++;
	}

	void deleted_elements(std::string _name) {
		int index = hash_function(_name);
		for (auto& elementItem : Table[index]) {
			if (_name == elementItem.Name) {
				elementItem.be_deleted = true;
				Quantity_Elements--;
				return;
			}
		}
		std::cerr << "Error: Element not found." << std::endl;
	};

	bool search(std::string _name) {
		int index = hash_function(_name);
		for (auto& elementItem : Table[index]) {
			if (_name == elementItem.Name) {
				return true;
				break;
			}
		}
		return 0;
	};

	void print_to_file(std::string _path) {
		std::ofstream outputFile(_path);
		if (!outputFile.is_open()) {
			std::cerr << "Error: Could't open the file for writing." << std::endl;
		}
		int i = 0;
		for (const auto& vectorItem : Table) {
			outputFile << i++ << ". ";
			for (const auto& elementItem : vectorItem) {
				if (elementItem.be_deleted != true)
					outputFile << '[' << elementItem.Name << "] ";
			}
			outputFile << '\n';
		}
	}

};

int main() {
	Hash_Table Table("Data/Name.txt");

	std::vector<std::string> randomNames = { "Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Henry", "Ivy", "Jack" };
	for (const auto& name : randomNames) {
		Table.insert(name);
	}
	Table.print_to_file("Table/output.txt");
	for (const auto& name : randomNames) {
		Table.deleted_elements(name);
	}

	Table.print_to_file("Table/output_1.txt");
}