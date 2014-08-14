// Solve an unblockme puzzle
#include <vector>
#include <iostream>

using namespace std;

class Piece
{
public:
	long id;
	long size;
	long row;
	long col;
	bool isVertical;
	bool isRed;

public:
	Piece(long idIn, long rowIn, long colIn, long sizeIn, bool isVerticalIn, bool isRedIn)
	{
		id = idIn;
		row = rowIn;
		col = colIn;
		size = sizeIn;
		isVertical = isVerticalIn;
		isRed = isRedIn;
	}
};

class Board
{
	vector<Piece*> pieces;
	vector<Piece> oldPositions;
	long width;
	long height;
	Piece *redPiece;

public:
	// Basic Constructor
	Board(long w = 4, long h = 5)
	{
		width = w;
		height = h;
		redPiece = NULL;
	}

	// Example setup
	void ExampleSetup()
	{
		// | - | - | - | - |
		// | - | - | - | x |
		// | x | x | - | x 
		// | - | - | - | x |
		// | - | - | - | - |
		printf("Creating the example setup....\n");
		width = 4;
		height = 5;
		pieces.clear();
		pieces.insert(pieces.end(), new Piece(0, 2, 0, 2, false, true));
		pieces.insert(pieces.end(), new Piece(1, 1, 3, 2, true, false));
		redPiece = pieces[0];
	}

	// Check if a square is empty
	bool CheckSquareOccupied(long row, long col)
	{
		bool occupied = false;

		for (long i = 0; i < pieces.size(); i++)
		{
			Piece *piece = pieces[i];
			// if piece if vertical check that p->col == col and p->row <= row <= p->row+size
			if (piece->isVertical)
			{
				if (piece->col == col && 
					  piece->row <= row && 
						row < (piece->row + piece->size))
				{
					occupied = true;
					break;
				}
			}
			// if piece is horiz check that p->row = row and p->col <= col <= p->col+size
			else
			{
				if (piece->row == row && 
					  piece->col <= col && 
						col < (piece->col + piece->size))
				{
					occupied = true;
					break;
				}
			}
		}
		return occupied;
	}

	// Output text version of 
	void PrintBoard()
	{
		for (long row = 0; row < height; row++)
		{
			printf("|");
			for (long col = 0; col < width; col++)
			{
				if (CheckSquareOccupied(row,col))
				{
					printf(" + |");
				}
				else
				{
					printf("   |");
				}
			}
			if (redPiece != NULL && row == redPiece->row)
			{
				printf(" =>");
			}
			printf("\n");
		}
	}

	// Check to see if the Red piece has clear path to exit
	bool CheckSolved()
	{
		bool solved = true;

		if (redPiece == NULL)
		{
			printf("You forgot to set the Red Piece\n");
			exit(1);
		}
		else
		{
			for (long col = redPiece->col + redPiece->size; col <= width; col++)
			{
				if (CheckSquareOccupied(redPiece->row, col))
				{
					solved = false;
					break;
				}
			}
		}
		return solved;
	}

	// Recurse through all the moves till puzzle is solved
	//
	// After each move check to see if Red piece has clear path to exit
	bool SolveBoard()
	{
		// Keep track of each move on a stack to emulate recursion, and pop off if we get to dead end
		long currentPieceIndex = 0;
		long solved = false;

		while (!solved)
		{
			// 1. Pick next piece in list
			Piece* moving = pieces[currentPieceIndex];

			// 2. Move the piece in a direction
			long newRow = moving->row;
			long newCol = moving->col;
			if (!moving->isVertical)
			{
				newRow = moving->row + 1;
			}
			else
			{
				newCol = moving->col + 1;
			}
			// 		a. Can the piece move in the direction?
			if (!CheckSquareOccupied(newRow, newCol))
			{
				oldPositions.insert(oldPositions.end(), *moving);
				moving->row = newRow;
				moving->col = newCol;
				printf("-------------------------------------");
				PrintBoard();
				printf("-------------------------------------");
				if (CheckSolved())
				{
					printf("Solved!!!\n");
					solved = true;
				}
			}
		}
		return solved;
	}
};

int main()
{
	printf("Starting the game.....\n");
	// Create a new Board
	Board board;

	board.ExampleSetup();
	board.PrintBoard();
	board.SolveBoard();

	printf("Done with game!\n");
	return 1;
}
