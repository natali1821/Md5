#pragma once
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cassert>

std::string hash_str(std::string str) {
	auto hash_start = str.find('"', 0);
	auto hash_end = str.find('"', hash_start + 1);
	std::string hash = str.substr(hash_start + 1, hash_end - hash_start - 1);
	return hash;
}

std::string firstHash(std::string fileName) {
	std::ifstream file(fileName);
	std::string firstHash;
	if (file.is_open()) {
		std::string str;
		std::getline(file, str);
		firstHash = hash_str(str);
	}
	else {
		throw std::invalid_argument("Unable to open file");
	}
	return firstHash;
}

std::string lastHash(std::string fileName) {
	std::ifstream file(fileName);
	std::string lastHash;
	// to read the last string of the file
	if (file.is_open()) {
		file.seekg(-1, std::ios_base::end);
		bool flag = true;
		while (flag) {
			char s;
			file.get(s);
			if (s == '\n' || s == '\r') {
				flag = false;
				break;
			}
			else {
				file.seekg(-2, std::ios_base::cur); // move to the front of the symbol, then to the front of the symbol before it
			}
		}
		std::getline(file, lastHash);
	}
	else {
		throw std::invalid_argument("Unable to open file");
	}
	return hash_str(lastHash);
}