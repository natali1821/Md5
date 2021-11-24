#include "Additional.hpp"
#include <vector>

const int number = 12; // number of tables

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Invalid arguments" << std::endl;
		return 1;
	}
	std::string hash = argv[1];

	std::vector<std::string> hashFirst; // to save first hash of each file
	for (int i = 0; i < number; ++i) {
		std::string str = firstHash("md5_rainbow_table_part_" + std::to_string(i + 1) + ".csv");
		hashFirst.push_back(str);
	}
	
	// binary search 
	bool flag = false;
	int left = 0;
	int right = number - 1;
	int middle = 0;
	int result = -1;
	if (hash >= hashFirst[0] && hash <= lastHash("md5_rainbow_table_part_12.csv")) {
		while ((left <= right) && (flag != true)) {
			middle = (left + right) / 2; 
			if (hashFirst[middle] <= hash && hash <= lastHash("md5_rainbow_table_part_" + std::to_string(middle + 1) + ".csv")) {
				result = middle + 1;
				flag = true; 
				break;
			}
			if (hashFirst[middle] > hash) {
				right = middle - 1; 
			}
			else {
				left = middle + 1;
			}
		}
	}
	else {
		std::cout << "Hash doesn't exist";
	}

	std::cout << "The number of the file - " << result << std::endl;

	// to find original in searchable file
	std::ifstream file("md5_rainbow_table_part_" + std::to_string(result) + ".csv");
	std::string str;
	while (std::getline(file, str)) {
		auto hash_start = str.find('"', 0);
		auto hash_end = str.find('"', hash_start + 1);
		std::string strHash = str.substr(hash_start + 1, hash_end - hash_start - 1);

		auto original_start = str.find('"', hash_end + 1);
		auto original_end = str.find('"', original_start + 1);
		std::string original = str.substr(original_start + 1, original_end - original_start - 1);

		if (hash == strHash) {
			std::cout << original << std::endl;
			break;
		}
	}

	file.close();
}
