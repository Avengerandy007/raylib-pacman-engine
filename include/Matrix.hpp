#pragma once
#include <memory>
#include <vector>

template<typename T>
struct Matrix2{
	std::vector<std::vector<T>> matrix;
	
	Matrix2(int coll, int row){
		matrix.resize(coll, std::vector<T>(row));
		Fill();
	}

private:
	void Fill(){
		for(auto coll : matrix){
			for(auto it : coll){
				it = new T();
			}
		}
	}
};
