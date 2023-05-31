#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include <vector>
using namespace std;

struct pos
{
	int row;
	int column;
};


class sudoku
{
private:
	char l_data[9][9]; // Data of unprocessed soduku
	vector <pos> fixedPos;
public:

	// Display the outputs
	void display()
	{
		int row, column;
		
		for (int row = 0; row < 9; row++)
		{
			if( !( row % 3 ) ) cout << " -------- -------- -------- " << endl;
			cout << "| ";
			for (int column = 0; column < 9; column++)
			{
				if( !( column % 3 ) && (column) ) cout << " | ";
				cout << (isdigit(l_data[row][column]) ? l_data[row][column] : '_') << " ";
			}
			cout << " |" << endl;
		}
		cout << " -------- -------- -------- " << endl;
	}
	
	// Reads from file and stores element into 3x3 array
	void read(string inputFile)
	{
		ifstream fileStream;
		fileStream.open(inputFile, ios::in);
		
		int row, column; 
		
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				fileStream >> l_data[row][column];
			}
		}
	}
	
	// Scan for position of given values
	void scanFixedPos()
	{		
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				if(isdigit(l_data[row][column]))
				{
					fixedPos.push_back( {row,column} );
				}
			}
		}
	}
	
	// When comparing an integer to a double, the integer is promoted to a double and the comparison takes place as if they were both doubles. This can yield unexpected results (due to the way floating point is represented).
	void solve()
	{
		int row, column, count = 0;
		bool failureFlag = 0;
		
		// Scanned for position of given values
		scanFixedPos(); 
		
		// Backtracking Algorithm
		while( count < 81 )
		{
			// Iterate through all values of the array
			row = count / 9;
			column = count % 9;
			if(!isdigit(l_data[row][column]) ) l_data[row][column] = '1'; // If the current location is not assigned a value, assume that it is 1
			
			// Jumps into this block if a failure is detected, purpose is to increment the latest incrementable digit once
			if(failureFlag)
			{
				// If is a given value, then cannot change. Go back one spot.
				if(isFixed(row,column))
				{
					count--;
					continue;
				} 
				// If it is a changable value then increment it.
				else if ( (l_data[row][column] < '9') && (l_data[row][column] > '0') )
				{
					l_data[row][column]++;
					failureFlag = 0;
				}
				// If the position is 9, then it cannot be incremented further. Set it to '_' and go back a spot.
				else 
				{
					l_data[row][column] = '_';
					count--;
					continue;
				}
				
			}
			// If a constraint has been violated
			if( compareRow(row,column) || compareGrid(row,column) || compareColumn(row, column) ) 
			{
				// If the value is fixed then go back a spot
				if( isFixed(row,column) ) 
				{
					count--;
					failureFlag = 1;
				}
				
				// If it is a changeable value then increment it
				else if(l_data[row][column] < '9') 
					l_data[row][column] = l_data[row][column] + 1; 
				
				// If it is not a changeable value then reset the spot and go back
				else if(l_data[row][column] >= '9') 
				{
					l_data[row][column] = '_';
					count--; // If none of the values work
					failureFlag = 1;
				}
				continue;
			}
			count++;
		}
	}

	
	// Checks if a row consists of repeats
	bool compareRow (int r, int c) 
	{
		for(int i = 0; i < 9; i++ )
		{
			if (c == i) continue;
			if (l_data[r][c] == l_data[r][i]) return 1;
		}
		return 0;
	}
	
	// Checks if a grid consists of repeats
	bool compareGrid (int r, int c)
	{
		const int grid = 3;
		int gridCol, gridRow;
		
		// Transforms the column and row into a matrix representation 
		gridRow = r/3;
		gridCol = c/3;
		
		/*
		 -----------------------
		|	00	|	01	|	02	|
		 -----------------------
		|	10	|	11	|	12	|
		 -----------------------
		|	20	|	21	|	22	|
		 -----------------------
		*/
		
		// Iterating through the row and column of the grid its situated in
		for(int row = gridRow*3 ; row < (gridRow+1)*3 ; row++)
		{
			for(int column = gridCol*3 ; column < (gridCol+1)*3; column++)
			{
				//if( !isdigit( l_data[row][column] ) ) continue;
				if( (row == r) && (column == c) ) continue;
				if ( (l_data [r][c] == l_data[row][column]) ) return 1;
			}
		}
		return 0;
	}
	
	// Checks if a column consists of repeats
	bool compareColumn (int r, int c)
	{
		for(int i = 0; i < 9; i++ )
		{
			if(r == i) continue;
			if ( l_data [r][c] == l_data[i][c] ) return 1;
		}
		return 0;
	}
	
	// Checks if a value is a starting value
	bool isFixed (int r, int c)
	{
		for( int i = 0; i < fixedPos.size(); i++ )
		{
			if ( (fixedPos[i].row == r) && (fixedPos[i].column == c) )
			{
				return 1;
			}
		}
		return 0;

	}
	
};

int main ()
{
	sudoku board;
	board.read("P1_SUDOKU.txt");
	cout << "THE PUZZLE IS: " << endl;
	board.display();
	board.solve();
	cout << "THE SOLUTION IS: " << endl;
	board.display();
	return 0;
}

