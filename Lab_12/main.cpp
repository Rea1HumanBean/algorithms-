#include <algorithm>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>

class multiphase {
    std::vector<std::fstream> fileArray;
    std::string filename = "Auxiliary files/";
    size_t quantityAuxArray = 0;

    void quickSort(std::vector<int>& arr, int start, int end) {
        if (start < end) {
            int current = start;
            for (size_t i = start + 1; i <= end; i++) {
                if (arr[i] < arr[start]) {
                    current++;
                    std::swap(arr[current], arr[i]);
                }
            }
            std::swap(arr[start], arr[current]);

            quickSort(arr, start, current - 1);
            quickSort(arr, current + 1, end);
        }
    }

    void sortedFileArray(std::vector<std::fstream>& Array) {
        for (size_t i = 0; i < Array.size(); i++)
            sortedInFile(Array[i]);

        sortedFiles(Array);
    }

    void sortedInFile(std::fstream& _file) {
        std::vector<int> integers;
        std::string line;
        while (std::getline(_file, line))
            integers.emplace_back(std::stoi(line));

        quickSort(integers, 0, integers.size() - 1);

        _file.clear();
        _file.seekp(0);
        for (const auto& sortedLine : integers)
            _file << sortedLine << '\n';
    }

    void sortedFiles(std::vector<std::fstream>& Array) {
        std::string line, other_line;
        std::fstream _buble("Data/SortArray.txt", std::ios::out | std::ios::trunc);

        for (size_t i = 1; i < Array.size(); i++) {
            Array[i].seekp(0);

            while (std::getline(Array[i], line)) {
                int value;
                std::istringstream(line) >> value;

                bool add = true;

                Array[0].clear();
                Array[0].seekg(0);
                Array[0].seekp(0);

                while (std::getline(Array[0], other_line)) {
                    int other_value;

                    std::istringstream(other_line) >> other_value;

                    if (value < other_value && add) {
                        add = false;
                        _buble << line << '\n';
                    }
                    _buble << other_line << '\n';
                }
                if (add)
                    _buble << line << '\n';

                Array[0].seekp(0);
                _buble.seekg(0);
                Array[0].close();

                std::ifstream bubleReader("Data/SortArray.txt");
                Array[0].open(filename + "0.txt");

                while (std::getline(bubleReader, line))
                    Array[0] << line << '\n';

                bubleReader.close();

                std::ofstream clearBuble("Data/SortArray.txt", std::ios::trunc);
                clearBuble.close();
            }
        }

        std::ofstream sortedArray("Data/SortArray.txt");
        Array[0].open(filename + "0.txt");
        Array[0].clear();
        Array[0].seekg(0);
        Array[0].seekp(0);;

        while (std::getline(Array[0], line)) {
            sortedArray << line << '\n';
        }
        sortedArray.close();
    }

public:
    multiphase(std::string _path) {
        std::fstream Main_array(_path);
        size_t step = 0;
        std::string filenameAuxArray = filename + std::to_string(quantityAuxArray) + ".txt";
        std::ofstream Auxiliary_array(filenameAuxArray);

        std::string line;
        while (std::getline(Main_array, line)) {
            if (step == 4) {
                Auxiliary_array.close();
                fileArray.emplace_back(filenameAuxArray);

                quantityAuxArray++;
                filenameAuxArray = filename + std::to_string(quantityAuxArray) + ".txt";
                Auxiliary_array.open(filenameAuxArray);

                step = 0;
            }
            Auxiliary_array << line << '\n';
            step++;
        }
        if (step != 0) {
            Auxiliary_array.close();
            fileArray.emplace_back(filenameAuxArray);
        }
        sortedFileArray(fileArray);
    }

    ~multiphase() {
        int i = 0;
        std::string name;
        for (auto& file : fileArray) {
            file.close();
            name = filename + std::to_string(i) + ".txt";
            std::remove(name.c_str());
            i++;
        }
    }
};

int main() {
    multiphase array("Data/Array.data");
    return 0;
}