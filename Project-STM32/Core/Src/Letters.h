#pragma once
#include <vector>
#include <utility>
#include <array>
#include <string>
#include <bitset>

//CHARS LIB FOR MatrixDisplay's writeString Method
class Letters
{
public:
		std::vector<std::pair<int, int>> A = {
			std::make_pair(2, 0),
			std::make_pair(2, 1),
			std::make_pair(2, 2),
			std::make_pair(2, 3),
			std::make_pair(2, 4),
			std::make_pair(2, 5),
			
			std::make_pair(3, 6),
			std::make_pair(4, 6),
	
			std::make_pair(5, 0),
			std::make_pair(5, 1),
			std::make_pair(5, 2),
			std::make_pair(5, 3),
			std::make_pair(5, 4),
			std::make_pair(5, 5),
			
			std::make_pair(3, 2),
			std::make_pair(4, 2),
			std::make_pair(5, 2),
		};
	
		std::vector<std::pair<int, int>> B = {
			std::make_pair(2, 0),
			std::make_pair(2, 1),
			std::make_pair(2, 2),
			std::make_pair(2, 3),
			std::make_pair(2, 4),
			std::make_pair(2, 5),
			std::make_pair(2, 6),
		
		
			std::make_pair(3, 0),
			std::make_pair(4, 1),
			std::make_pair(4, 2),
			std::make_pair(3, 3),
		
			std::make_pair(4, 4),
			std::make_pair(4, 5),
			std::make_pair(3, 6),
		};
	
		std::vector<std::pair<int, int>> DASH = {
			std::make_pair(0, 0),
			std::make_pair(1, 0),
			std::make_pair(2, 0),
			std::make_pair(3, 0),
			std::make_pair(4, 0),
			std::make_pair(5, 0),
			std::make_pair(6, 0),
			std::make_pair(7, 0),
			std::make_pair(0, 1),
			std::make_pair(1, 1),
			std::make_pair(2, 1),
			std::make_pair(3, 1),
			std::make_pair(4, 1),
			std::make_pair(5, 1),
			std::make_pair(6, 1),
			std::make_pair(7, 1),
		};
		std::vector<std::pair<int, int>> C = {
			std::make_pair(2, 1),
			std::make_pair(2, 2),
			std::make_pair(2, 3),
			std::make_pair(2, 4),
			std::make_pair(2, 5),
			
			std::make_pair(3, 0),
			std::make_pair(3, 6),
			std::make_pair(4, 0),
			std::make_pair(4, 6),
			std::make_pair(5, 1),
			std::make_pair(5, 5),
			
		};
		std::vector<std::pair<int, int>> D = {
			std::make_pair(2, 0),
			std::make_pair(2, 1),
			std::make_pair(2, 2),
			std::make_pair(2, 3),
			std::make_pair(2, 4),
			std::make_pair(2, 5),
			std::make_pair(2, 6),
		
		
			std::make_pair(3, 0),
			std::make_pair(4, 0),
			std::make_pair(5, 1),
			std::make_pair(5, 2),
			std::make_pair(5, 3),
			std::make_pair(5, 4),
			std::make_pair(5, 5),
			
			std::make_pair(3, 6),
			std::make_pair(4, 6),
			
		
		};
		std::vector<std::pair<int, int>> E = {
			std::make_pair(2, 0),
			std::make_pair(2, 1),
			std::make_pair(2, 2),
			std::make_pair(2, 3),
			std::make_pair(2, 4),
			std::make_pair(2, 5),
			std::make_pair(2, 6),
		
		
			std::make_pair(3, 0),
			std::make_pair(4, 0),
			std::make_pair(5, 0),
			
			std::make_pair(3, 3),
			std::make_pair(4, 3),
			std::make_pair(5, 3),
			
			std::make_pair(3, 6),
			std::make_pair(4, 6),
			std::make_pair(4, 6),
			std::make_pair(5, 6),
			
		
	};
	std::vector<std::pair<int, int>> F = {
		std::make_pair(2, 0),
		std::make_pair(2, 1),
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		std::make_pair(2, 6),
			
		std::make_pair(3, 3),
		std::make_pair(4, 3),
		std::make_pair(5, 3),
			
		std::make_pair(3, 6),
		std::make_pair(4, 6),
		std::make_pair(4, 6),
		std::make_pair(5, 6),
			
		
	};
	
	std::vector<std::pair<int, int>> G = {
		std::make_pair(2, 0),
		std::make_pair(2, 1),
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		std::make_pair(2, 6),
		
		std::make_pair(3, 0),
		std::make_pair(4, 0),
		std::make_pair(5, 0),
		std::make_pair(5, 1),
		std::make_pair(5, 2),
		
		std::make_pair(3, 6),
		std::make_pair(4, 6),
		std::make_pair(5, 6),
		
		std::make_pair(4, 2),
		
	};
	
	std::vector<std::pair<int, int>> H = {
		std::make_pair(2, 0),
		std::make_pair(2, 1),
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		std::make_pair(2, 6),
		
		std::make_pair(5, 0),
		std::make_pair(5, 1),
		std::make_pair(5, 2),
		std::make_pair(5, 3),
		std::make_pair(5, 4),
		std::make_pair(5, 5),
		std::make_pair(5, 6),
		
		std::make_pair(3, 3),
		std::make_pair(4, 3),
			
		
	};
	
	std::vector<std::pair<int, int>> I = {
		std::make_pair(3, 0),
		std::make_pair(4, 0),
		std::make_pair(3, 1),
		std::make_pair(4, 1),
		std::make_pair(3, 2),
		std::make_pair(4, 2),
        std::make_pair(3, 3),
		std::make_pair(4, 3),
		std::make_pair(3, 4),
		std::make_pair(4, 4),
		std::make_pair(3, 5),
		std::make_pair(4, 5),
		std::make_pair(3, 6),
		std::make_pair(4, 6),

	};
	
	std::vector<std::pair<int, int>> J = {
		std::make_pair(5, 6),
		std::make_pair(5, 5),
		std::make_pair(5, 4),
		std::make_pair(5, 3),
		std::make_pair(5, 2),
		std::make_pair(5, 1),
		std::make_pair(4, 0),
		std::make_pair(3, 0),
		std::make_pair(2, 1),		
	};
	
	std::vector<std::pair<int, int>> K = {
		std::make_pair(2, 0),
		std::make_pair(2, 1),
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		std::make_pair(2, 6),
		
		std::make_pair(3, 4),
		std::make_pair(4, 5),
		std::make_pair(5, 6),
		std::make_pair(4, 3),
		std::make_pair(5, 2),
		std::make_pair(5, 1),
		std::make_pair(5, 0),		
		
	};
	
	std::vector<std::pair<int, int>> L = {
		std::make_pair(2, 0),
		std::make_pair(2, 1),
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		std::make_pair(2, 6),
		
		std::make_pair(3, 0),
		std::make_pair(4, 0),
		std::make_pair(5, 0),
		
	};
	std::vector<std::pair<int, int>> M = {
		std::make_pair(1, 0),
		std::make_pair(1, 1),
		std::make_pair(1, 2),
		std::make_pair(1, 3),
		std::make_pair(1, 4),
		std::make_pair(1, 5),
		std::make_pair(1, 6),
		
		std::make_pair(2, 5),
		std::make_pair(3, 4),
		std::make_pair(4, 5),
		std::make_pair(5, 6),
		
		std::make_pair(5, 0),
		std::make_pair(5, 1),
		std::make_pair(5, 2),
		std::make_pair(5, 3),
		std::make_pair(5, 4),
		std::make_pair(5, 5),	
		
	};
	std::vector<std::pair<int, int>> N = {
		std::make_pair(1, 0),
		std::make_pair(1, 1),
		std::make_pair(1, 2),
		std::make_pair(1, 3),
		std::make_pair(1, 4),
		std::make_pair(1, 5),
		
		std::make_pair(2,4),
		std::make_pair(3, 3),
		std::make_pair(4, 2),
		std::make_pair(5, 1),
		
		std::make_pair(6, 0),
		std::make_pair(6, 1),
		std::make_pair(6, 2),	
		std::make_pair(6, 3),
		std::make_pair(6, 4),
		std::make_pair(6, 5),
		
	};
	std::vector<std::pair<int, int>> O = {
		std::make_pair(3, 6),
		std::make_pair(4, 6),
		
		std::make_pair(2, 5),
		std::make_pair(5, 5),
		
		std::make_pair(1, 2),
		std::make_pair(1, 3),
		std::make_pair(1, 4),
		std::make_pair(6, 2),
		std::make_pair(6, 3),
		std::make_pair(6, 4),
		
		std::make_pair(2, 1),
		std::make_pair(5, 1),
		
		std::make_pair(3, 0),	
		std::make_pair(4, 0),
		
	};
	std::vector<std::pair<int, int>> P = {
		std::make_pair(2, 0),
		std::make_pair(2, 1),
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		std::make_pair(2, 6),
		
		std::make_pair(3, 6),
		std::make_pair(4, 6),
		
		std::make_pair(5, 4),
		std::make_pair(5, 5),
		
		std::make_pair(3, 3),
		std::make_pair(4, 3),
		
	};
	std::vector<std::pair<int, int>> R = {
		std::make_pair(2, 0),
		std::make_pair(2, 1),
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		std::make_pair(2, 6),
		
		std::make_pair(3, 6),
		std::make_pair(4, 6),
		
		std::make_pair(5, 4),
		std::make_pair(5, 5),
		
		std::make_pair(3, 3),
		std::make_pair(4, 3),
		
		std::make_pair(3,2),
		std::make_pair(4,1),
		std::make_pair(5,0),
		
		
	};
	std::vector<std::pair<int, int>> S = {
		std::make_pair(3, 6),
		std::make_pair(4, 6),
		std::make_pair(5, 6),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		
		std::make_pair(3, 3),
		std::make_pair(4, 3),
		
		std::make_pair(5, 1),
		std::make_pair(5, 2),
		
		std::make_pair(2, 0),
		std::make_pair(3, 0),
		std::make_pair(4, 0),
		
	};

	std::vector<std::pair<int, int>> T = {
		std::make_pair(1, 6),
		std::make_pair(2, 6),
		std::make_pair(3, 6),
		std::make_pair(4, 6),
		std::make_pair(5, 6),
		
		std::make_pair(3, 0),
		std::make_pair(3, 1),
		std::make_pair(3, 2),
		std::make_pair(3, 3),
		std::make_pair(3, 4),
		std::make_pair(3, 5),
		
	};
	std::vector<std::pair<int, int>> U = {
		std::make_pair(2, 1),
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(2, 5),
		std::make_pair(2, 6),
		
		std::make_pair(5, 1),
		std::make_pair(5, 2),
		std::make_pair(5, 3),
		std::make_pair(5, 4),
		std::make_pair(5, 5),
		std::make_pair(5, 6),
		
		std::make_pair(3, 0),
		std::make_pair(4, 0),
		
	};
	std::vector<std::pair<int, int>> W = {
		std::make_pair(1, 0),
		std::make_pair(1, 1),
		std::make_pair(1, 2),
		std::make_pair(1, 3),
		std::make_pair(1, 4),
		std::make_pair(1, 5),
		std::make_pair(1, 6),
		
		std::make_pair(5, 0),
		std::make_pair(5, 1),
		std::make_pair(5, 2),
		std::make_pair(5, 3),
		std::make_pair(5, 4),
		std::make_pair(5, 5),
		std::make_pair(5, 6),
		
		std::make_pair(2, 1),
		std::make_pair(3, 2),
		std::make_pair(4, 1),
		
	};
	std::vector<std::pair<int, int>> X = {
		std::make_pair(1, 0),
		std::make_pair(2, 1),
		std::make_pair(3, 2),
		std::make_pair(4, 3),
		std::make_pair(5, 4),
		std::make_pair(6, 5),
		std::make_pair(7, 6),
		
		std::make_pair(1, 6),
		std::make_pair(2, 5),
		std::make_pair(3, 4),
		std::make_pair(5, 2),
		std::make_pair(6, 1),
		std::make_pair(7, 0),

		
	};
	std::vector<std::pair<int, int>> Y = {
		std::make_pair(3, 0),
		std::make_pair(3, 1),
		std::make_pair(3, 2),
		std::make_pair(3, 3),
		std::make_pair(3, 4),
		
		std::make_pair(2, 5),
		std::make_pair(4, 5),
		
		std::make_pair(1, 6),
		std::make_pair(5, 6),
		
		std::make_pair(3, 0),
		
	};
	std::vector<std::pair<int, int>> Z = {
		std::make_pair(1, 6),
		std::make_pair(2, 6),
		std::make_pair(3, 6),
		std::make_pair(4, 6),
		std::make_pair(5, 6),
		
		std::make_pair(5, 5),
		std::make_pair(4, 4),
		std::make_pair(3,3),
		std::make_pair(2, 2),
		std::make_pair(1, 1),
		
		std::make_pair(1, 0),
		std::make_pair(2, 0),
		std::make_pair(3, 0),
		std::make_pair(4, 0),
		std::make_pair(5, 0),	
	};
	std::vector<std::pair<int, int>> V = {
		std::make_pair(1, 2),
		std::make_pair(1, 3),
		std::make_pair(1, 4),
		std::make_pair(1, 5),
		std::make_pair(1, 6),
		
		std::make_pair(5, 2),
		std::make_pair(5, 3),
		std::make_pair(5, 4),
		std::make_pair(5, 5),
		std::make_pair(5, 6),
		
		std::make_pair(2, 1),
		std::make_pair(4, 1),
		std::make_pair(3, 0),
	};
	std::vector<std::pair<int, int>> PLUS = {
		std::make_pair(1, 3),
		std::make_pair(2, 3),
		std::make_pair(3, 3),
		std::make_pair(4, 3),
		std::make_pair(5, 3),
		
		std::make_pair(3, 1),
		std::make_pair(3, 2),
		std::make_pair(3, 3),
		std::make_pair(3, 4),
		std::make_pair(3, 5),
	};
	
	std::vector<std::pair<int, int>> SLASH = {
		std::make_pair(1, 0),
		std::make_pair(2, 1),
		std::make_pair(3, 2),
		std::make_pair(4, 3),
		std::make_pair(5, 4),
		std::make_pair(6, 5),
		std::make_pair(7, 6),
	};
	
};