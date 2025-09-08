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

	Matrix2<Tile, 20> CreateTileSet(const std::string fileContent){
		Matrix2<Tile, 20> matrix;
		
		uint32_t currentChar = 0;
		Coin::coinCount = 0;
		std::string coinCountChars = "";
		while(currentChar <= 400){
			if (fileContent[currentChar] == ',') break;
			coinCountChars += fileContent[currentChar];
			currentChar++;
		}

		Coin::coinCount = coinCountChars != "" ? std::stoi(coinCountChars) : 0;
		currentChar++;

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
		return CreateTileSet(FileContent(file));
	}
}
