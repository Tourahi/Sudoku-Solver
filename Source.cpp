#include <iostream>
#include <string>
#include <windows.h>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<fstream>


#define toDigit(c) (c-'0')

class matrice
{
private:
	mutable int size;
	mutable int **matr;
public:
	
	matrice(int s  = 3)
		: size(s)
	{	
		matr = new int *[size];
		for (int i = 0; i < size; i++)
		{
			matr[i] = new int[size];
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matr[i][j] = 0;
			}
		}
	}

	void init(int Size)
	{
		matr = new int *[Size];
		for (int i = 0; i < Size; i++)
		{
			matr[i] = new int[Size];
		}
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				matr[i][j] = 0;
			}
		}
	}

	void DefaultMatr()  //Debug function.
	{
		int sudoku[9][9] = {
			{8, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 3, 6, 0, 0, 0, 0, 0},
			{0, 7, 0, 0, 9, 0, 2, 0, 0},
			{0, 5, 0, 0, 0, 7, 0, 0, 0},
			{0, 0, 0, 0, 4, 5, 7, 0, 0},
			{0, 0, 0, 1, 0, 0, 0, 3, 0},
			{0, 0, 1, 0, 0, 0, 0, 6, 8},
			{0, 0, 8, 5, 0, 0, 0, 1, 0},
			{0, 9, 0, 0, 0, 0, 4, 0, 0}
		};

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matr[i][j] = sudoku[i][j];
			}
		}
		
	}

	void initFromFile()
	{
		std::ifstream in;
		in.open("Sudoku.txt");
		if (in.fail())
		{
			std::cout << "Failed to open the file.\n";
		}
		else {
			char tmp;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					in >> tmp;
					matr[i][j] = toDigit(tmp);
				}
			}
		}
	}


	int Random() {  // [0-9]  Unused Function. 

		return rand() % 10;
	}

	void showBlock(bool Multi_M_grid = false)
	{
		int R, C;
		R = 0;
		C = 0;
		if (!Multi_M_grid)
		{
			bool first = true;
			for (int i = 0; i < size; i++)
			{
				if(i == 0) std::cout << "[ ";
				
				if (R % 3 == size % 3) {
					
					if (!first) { std::cout << "-------------------------- \n"; std::cout << "[ "; }
					R = 0;
				}
				else std::cout << "[ ";
			
				for (int j = 0; j < size; j++)
				{
					if (C % 3 == size % 3 && C != 0) {
						std::cout << "| ";
						C = 0;
					}
					std::cout << matr[i][j] << " ";
				
					if (j == 2) first = false;
					C++;
				}

				std::cout << "]";
				C = 0;
				std::cout << "" << std::endl;
				R++;
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				std::cout << "[ ";
				for (int j = 0; j < size; j++)
				{
					std::cout << matr[i][j] << " ";
				}
				std::cout << "]";
				if(i != size-1)
				std::cout << "" << std::endl;
			}
		}
	}


	bool isFull()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (matr[i][j] == 0) return false;
			}
		}
		return true;
	}

	int* possibleValues(int i, int j)
	{
		int* possibilities = new int[10];
		for (int i = 1; i < 10; i++)
		{
			possibilities[i] = 0;
		}

		//Check horizontal column
		
		for (int y = 0; y < size; y++)
		{
			if (matr[i][y] != 0)
			{
				possibilities[matr[i][y]] = 1;
			}
		}


		//Check Vertical column

		for (int x = 0; x < size;x++)
		{
			if (matr[x][j] != 0)
			{
				possibilities[matr[x][j]] = 1;
			}
		}

		//check Squeers of three x three

		int k = (i / 3) * 3;
	    int l = (j / 3) * 3;

		for (int x = k; x < k + 3; x++)
		{
			for (int y = l; y < l + 3; y++)
			{
				if (matr[x][y] != 0)
				{
					possibilities[matr[x][y]] = 1;
				}
			}
		}

		for (int i = 1; i < 10; i++)
		{
			if (possibilities[i] == 0) possibilities[i] = i;
			else possibilities[i] = 0;
		}

		return possibilities;

	}

	bool Solver()
	{
		int i = 0;
		int j = 0;

		int* possibilities;
		
		//si plein on peut plus rien faire.
		if (isFull())
		{
			std::cout << "Sudoku Solved Successfully!" << std::endl;
			showBlock();
			return true;
		}
		else
		{
			//trouve 0s
			for (int x = 0; x < size; x++)
			{
				for (int y = 0; y < size; y++)
				{
					if (matr[x][y] == 0)
					{
						i = x;
						j = y;
						break;
					}
				}
			}

			//get all the possibilities for (i, j)
			
			possibilities = possibleValues(i,j);
			
			  //go through all the possibilities and call the the function
		     //again and again --> recursive calls 

			for (int x = 1; x < 10; x++)
			{
				if (possibilities[x] != 0)
				{
					matr[i][j] = possibilities[x];
					//Debug_(i,j, x, possibilities);
					Solver();
				}
			}
			//Backtraking
			matr[i][j] = 0;
		}
	}

	void Debug_(int i,int j,int x,int *possibilities)
	{
		std::cout << "(i,j) : " << i << " " << j <<"\nLes possib : "<< std::endl;
		std::cout << "" << std::endl;
		for (int l = 0; l < 10; l++)
		{
			if(l != 0)
			std::cout << possibilities[l] <<" ";
		}
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Possibility : " << possibilities[x] << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Etat actuelle : " << std::endl;
		std::cout << "" << std::endl;
		showBlock();
		std::cout << "" << std::endl;
		system("pause");
		std::cout << "" << std::endl;
	}

	int GetPos(int x, int y)
	{
		return matr[x][y];
	}

	void Update_Pos(int x, int y,int num)
	{
		matr[x][y] = num;
	}

	virtual ~matrice()
	{
		for (int i = 0; i < size; i++)
		{
			delete matr[i];
		}
		delete matr;
	}
};


class Grid
{

private:
	int size; // size of one Block
	int Gsize;
	matrice *grid;


public:
	// size of a block, Multi matrice
	Grid(int s = 3 ,bool Multi = false)
		: size(s)
	{
		//if (Multi) {               //Pour n matrices
		//	grid = new matrice[size];
		//	for (int i = 0; i < size; i++) {
		//		matrice M(s);
		//		grid[i] = M;
		//	}
		//	//init the grid
		//	for (int i = 0; i < size; i++)
		//	{
		//		grid[i].init(size);
		//	}
		//}
			grid = new matrice(size*size);
			Gsize = size*size;
	}

	void showMultiMatrxGrid() //Not used
	{
		int GridP = 0;
		for (int i = 0; i < size; i++) { //Here we treat the 3n columns Of the i(n) matrice in  the Grid as one column.
			GridP = 0;
			for (int j = 0; j < size; j++) {
				if (GridP < size) {
					std::cout << grid[GridP].GetPos(i, j);
					if (j == size - 1) {
						j = -1; 
						GridP++;
						std::cout << " | ";
					}
				}
				/*else if (GridP == 1) {
					std::cout << grid[GridP].showPos(i, j);
					if (j == size - 1) {
						j = -1;
						GridP++;
						std::cout << " | ";
					}
				}
				else if (GridP == 2) {
					std::cout << grid[GridP].showPos(i, j);
				}*/
			}std::cout << "" << std::endl;			
		}
		//grid[i].showBlock(true);

	}

	void ShowGrid() {
		grid->showBlock();
	}

	void SolveGrid() {
		grid->Solver();
	}

	void Manual_initGrid() {
		int num;
		int skip = 0;
		for (int i = 0; i < size*size; i++) {
			for (int j = 0; j < size*size; j++) {
				if (skip == 0) {
					std::cout << "Pos : ( " << i << ", " << j << " )" << std::endl;
					std::cin >> num;
					grid->Update_Pos(i, j, num);
					std::cout << "Skip " << std::endl;
					std::cin >> skip;
					system("cls");
				}
				skip--;
			}
	   }
	}

	void DefaultGrid(bool file = false)
	{
		if (!file)
		{
		  grid->DefaultMatr();
		}else
		grid->initFromFile();
	}


};



int main()
{
	//srand(time(NULL));
	Grid TM(3);
	TM.DefaultGrid(false);
	//TM.Manual_initGrid();
	std::cout << "The Start Sudoku :\n";
	TM.ShowGrid();
	std::cout << "" << std::endl;
	TM.SolveGrid();
	std::cin.get();
	return 0;
}