// --------------------------------------------------------------------------------
// Name: Board
// Abstract: This class holds properties and methods for the representation of a 
//			 chess board.
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
// Pre-compiler Directives
// --------------------------------------------------------------------------------
#pragma once		// Include this file only once even if referenced multiple times



// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------

#include <stdlib.h>
#include <iostream>

#include <vector>
#include "Piece.h"
using namespace std;




class Board
{
	// --------------------------------------------------------------------------------
	// Properties
	// --------------------------------------------------------------------------------
public:			// Never make public properties.  
				// Make protected or private with public get/set methods
	vector <Piece> m_vecPositions;
	bool m_blnWhiteInCheck = false;
	bool m_blnBlackInCheck = false;

protected:

	// char m_arrPositions[64]; // Array for all squares. Each value in array holds type char.

	// creating a vector (dynamic array) to store all the pieces and blank squares in the 
	// order that they are on the board. Class Piece is the superclass of all subclass pieces
	// vector <Piece> m_vecPositions;

private:


	// --------------------------------------------------------------------------------
	// Methods
	// --------------------------------------------------------------------------------

public:
	Board(); // constructor

	void SetStartingPosition();
	void DisplayBoard(bool blnWhiteOrBlackTurn);
	void SwapSquares(int intPiece1, int intPiece2);
	void CapturePiece(int intPiece1, int intPiece2);
	int GetPositionIndex(int intColumn, int intRow);
	int GetPieceIndex(int intPieceAsciiValue, int intDesiredPosition, bool blnWhiteOrBlackTurn);
	char GetNotationName(int intSquareIndex);
	bool GetPieceColor(int intSquareIndex);
	bool CheckMovePath(int intPieceStartIndex, int intDestinationIndex);
	bool IsKingInCheck(bool blnWhiteOrBlackTurn, int intPosition);
	bool CheckKnightPatternArray(int aintDirections[], int intArraySize, bool blnWhiteOrBlackTurn);
	int GetKingIndex(bool blnWhiteOrBlackTurn);

protected:

private:


};