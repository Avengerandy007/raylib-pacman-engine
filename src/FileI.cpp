#include "../include/FileI.hpp"
#include <cstdint>
#include <fstream>
#include <inttypes.h>
#include <string>

namespace FileI{
	std::ifstream FindFile(){
		std::cout << "Input the name of the file you want to edit.\n";
		std::string fileName;
		std::cin >> fileName;
		std::ifstream file("./levels/" + fileName);
		if (file.good()) return file;
		else {
			std::cout << "File does not exist. Creating new one.\n";
			return file;
		}
	}

	std::string FileContent(std::ifstream &file){
		if (!file.is_open()) return "";
		std::string data;
		std::getline(file, data, '\0');
		return data;
	}


	uint16_t GetCoinCount(const std::string& fileContent, uint16_t& currentChar){

		Coin::coinCount = 0;
		std::string coinCountChars = "";
		while(fileContent[currentChar] != ','){
			coinCountChars += fileContent[currentChar];
			currentChar++;
		}		
		currentChar++;
		return coinCountChars != "" ? std::stoi(coinCountChars) : 0;
	}

	

	Matrix2<Tile, 20> MakeMatrix(std::ifstream& file){
		uint16_t current = 0;
		std::string fileContent = FileContent(file);
		Coin::coinCount = GetCoinCount(fileContent, current);
		return CreateTileSet<20>(fileContent, current);
	}
}
