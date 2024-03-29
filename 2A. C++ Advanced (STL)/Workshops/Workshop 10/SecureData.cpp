/*
OOP345
Workshop 10
Title    : Multi-Threading
Date     : 04/03/17
Author   : Alejandro Mesa
Student# : 038515151
Email    : amesasuarez@myseneca.ca
*/

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "SecureData.h"

namespace w10 {

	void converter(char* t, char key, int n, const Cryptor& c) {
		for (int i = 0; i < n; i++)
			t[i] = c(t[i], key);
	}

	SecureData::SecureData(const char* file, char key) {
		// open text file
		std::fstream input(file, std::ios::in);
		if (!input)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// copy from file into memory
		nbytes = 0;
		input >> std::noskipws;
		while (input.good()) {
			char c;
			input >> c;
			nbytes++;
		}
		nbytes--;
		input.clear();
		input.seekg(0, std::ios::beg);
		text = new char[nbytes + 1];

		int i = 0;
		while (input.good())
			input >> text[i++];
		text[--i] = '\0';
		std::cout << "\n" << nbytes << " bytes copied from text "
			<< file << " into memory (null byte added)\n";
		encoded = false;

		// encode using key
		code(key);
		std::cout << "Data encrypted in memory\n";
	}

	SecureData::~SecureData() {
		delete[] text;
	}

	void SecureData::display(std::ostream& os) const {
		if (text && !encoded)
			os << text << std::endl;
		else if (encoded)
			throw std::string("\n***Data is encoded***\n");
		else
			throw std::string("\n***No data stored***\n");
	}

	void SecureData::code(char key) {

		const int THREADS = 3;
		int portion = nbytes / THREADS;
		std::thread threadz[THREADS];
		Cryptor cryptors[THREADS];

		for (int x = 0; x < THREADS; x++) {
			threadz[x] = std::thread(std::bind(converter, text + x * portion, key, x + 1 < THREADS ? portion : (nbytes - x * portion), cryptors[x]));
		}

		for (int x = 0; x < THREADS; x++) {
			threadz[x].join();
		}

		encoded = !encoded;
	}

	void SecureData::backup(const char* file) {
		if (!text)
			throw std::string("\n***No data stored***\n");
		else if (!encoded)
			throw std::string("\n***Data is not encoded***\n");
		else {
			// open binary file
			std::ofstream ofs(file);
			ofs << text;
			ofs.close();
            /*
			//CODE
			// write binary file here
			if (!ins.is_open()){
				throw std::string("\n***Failed to open file ") +
					std::string(file) + std::string(" ***\n");
			}
			ins << text;
			ins.close();
			//END CODE
			*/
		}
	}

	void SecureData::restore(const char* file, char key) {
		// open binary file
		// CODE
		std::ifstream ifs(file, std::ios::in);
        // END CODE
        // CODE
		// allocate memory here
		nbytes = 0;
		ifs >> std::noskipws;
		while (ifs.good()) {
			char c;
			ifs >> c;
			nbytes++;
		}
		nbytes--;
		ifs.clear();
		ifs.seekg(0, std::ios::beg);
		text = new char[nbytes + 1];

        // END CODE

        // CODE
		// read binary file here
		// read binary file
		int i = 0;
		while (ifs.good())
			ifs >> text[i++];
		text[--i] = '\0';
        // END CODE

		std::cout << "\n" << nbytes + 1 << " bytes copied from binary file "
			<< file << " into memory (null byte included)\n";
		encoded = true;

		// decode using key
		code(key);
		std::cout << "Data decrypted in memory\n\n";
	}

	std::ostream& operator<<(std::ostream& os, const SecureData& sd) {
		sd.display(os);
		return os;
	}

}
