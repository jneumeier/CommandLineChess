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
#include <string>
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

	// Create and hold ascii-drawn chess pieces in the Board object, so they only have to be created once
	// and destroyed once.
	string* m_pstrAscii_Pawn_Clear = GetAscii_Pawn_Clear();
	string* m_pstrAscii_Pawn_Filled = GetAscii_Pawn_Filled();
	string* m_pstrAscii_Rook_Clear = GetAscii_Rook_Clear();
	string* m_pstrAscii_Rook_Filled = GetAscii_Rook_Filled();
	string* m_pstrAscii_Knight_Clear = GetAscii_Knight_Clear();
	string* m_pstrAscii_Knight_Filled = GetAscii_Knight_Filled();
	string* m_pstrAscii_Bishop_Clear = GetAscii_Bishop_Clear();
	string* m_pstrAscii_Bishop_Filled = GetAscii_Bishop_Filled();
	string* m_pstrAscii_Queen_Clear = GetAscii_Queen_Clear();
	string* m_pstrAscii_Queen_Filled = GetAscii_Queen_Filled();
	string* m_pstrAscii_King_Clear = GetAscii_King_Clear();
	string* m_pstrAscii_King_Filled = GetAscii_King_Filled();
	string* m_pstrAscii_Empty_Square = GetAscii_Empty_Square();

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
	string* GetAscii_Pawn_Clear();
	string* GetAscii_Pawn_Filled();
	string* GetAscii_Rook_Clear();
	string* GetAscii_Rook_Filled();
	string* GetAscii_Knight_Clear();
	string* GetAscii_Knight_Filled();
	string* GetAscii_Bishop_Clear();
	string* GetAscii_Bishop_Filled();
	string* GetAscii_Queen_Clear();
	string* GetAscii_Queen_Filled();
	string* GetAscii_King_Clear();
	string* GetAscii_King_Filled();
	string* GetAscii_Empty_Square();

	void DisplayBoard_Simple(bool blnWhiteOrBlackTurn);
	void DisplayBoard_Ascii(bool blnWhiteOrBlackTurn);
	void PrintAsciiLetterLine(int intIndex, int intLineNumber);
	void SwapSquares(int intPiece1, int intPiece2);
	void CapturePiece(int intPiece1, int intPiece2);
	int GetPositionIndex(int intColumn, int intRow);
	int GetPieceIndex(int intPieceAsciiValue, int intPieceFile, int intPieceRow, int intDesiredPosition, bool blnWhiteOrBlackTurn);
	char GetNotationName(int intSquareIndex);
	bool GetPieceColor(int intSquareIndex);
	bool CheckMovePath(int intPieceStartIndex, int intDestinationIndex);
	bool IsKingInCheck(bool blnWhiteOrBlackTurn, int intPosition);
	bool CheckKnightPatternArray(int aintDirections[], int intArraySize, bool blnWhiteOrBlackTurn);
	int GetKingIndex(bool blnWhiteOrBlackTurn);

protected:

private:


};