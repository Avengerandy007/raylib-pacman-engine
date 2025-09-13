#include "../include/FileI.hpp"
#include <cstdint>
#include <fstream>
#include <ios>
#include <memory>
#include <inttypes.h>
#include <string>
#include <utility>

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

	Matrix2<Tile, 20> CreateTileSet(const std::string fileContent, const uint16_t startChar){
		Matrix2<Tile, 20> matrix;
		
		uint16_t currentChar = startChar;

		for (uint32_t i = 0; i < 20; i++){
			for (uint32_t k = 0; k < 20; k++){
				switch (fileContent[currentChar]) {
					case '0':
						break;

					case '1':
						matrix.matrix[i][k].m_containedEntity = std::make_unique<Wall>();
						break;

					case '2':
						matrix.matrix[i][k].m_containedEntity = std::make_unique<Player>(i, k);
						break;

					case '3':
						matrix.matrix[i][k].m_coinContainer= std::make_unique<Coin>();
						break;
					case '4':
						matrix.matrix[i][k].m_containedEntity = std::make_unique<Ghost>(i, k);
						break;

					default:
						std::cout << "Unrecognized char " << fileContent[currentChar] << "\n";
						i--;
						k--;
						break;

				}
				currentChar++;
			}
		}
		std::cout << "Finished creating matrix\n";
		return matrix;
	}

	Matrix2<Tile, 20> MakeMatrix(std::ifstream& file){
		uint16_t current = 0;
		const std::string fileContent = FileContent(file);
		Coin::coinCount = GetCoinCount(fileContent, current);
		return CreateTileSet(fileContent, current);
	}
}
