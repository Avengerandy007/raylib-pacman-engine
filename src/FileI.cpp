#include "../include/FileI.hpp"
#include <cstdint>
#include <fstream>
#include <ios>
#include <memory>
#include <inttypes.h>
#include <utility>

namespace FileI{
	std::ifstream FindFile(){
		std::cout << "Input the name of the file you want to edit.\n";
		std::string fileName;
		std::cin >> fileName;
		std::ifstream file(fileName);
		if (file.good()) return file;
		else {
			std::cout << "File does not exist. Creating new one.\n";
			return file;
		}
	}



	Matrix2<Tile, 20> MakeMatrix(std::ifstream file){
		Matrix2<Tile, 20> matrix;
		if (!file.is_open()) return matrix;
		std::string data;
		std::getline(file, data, '\0');
		std::cout << data << "\n";

		uint32_t currentChar = 0;
		
		for (uint32_t i = 0; i < 20; i++){
			for (uint32_t k = 0; k < 20; k++){
				switch (data[currentChar]) {
					case '0':
						break;

					case '1':
						matrix.matrix[i][k].m_containedEntity = std::make_unique<Wall>();
						break;

					case '2':
						matrix.matrix[i][k].m_containedEntity = std::make_unique<Player>(i, k);
						break;

					default:
						std::cout << "Unrecognized char " << data[currentChar] << "\n";
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

}
