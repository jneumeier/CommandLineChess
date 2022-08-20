// --------------------------------------------------------------------------------
// Name: Piece
// Abstract: This class holds properties and methods for the representation of a 
//			 chess piece.
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
using namespace std;



class Piece
{
	// --------------------------------------------------------------------------------
	// Properties
	// --------------------------------------------------------------------------------
public:			// Never make public properties.  
				// Make protected or private with public get/set methods

protected:

	char m_chrNotationName = 0; // char property for algebraic notation name (ex. K, B, or N)
	string m_strFullName = ""; // Property holding the name of the piece (ex. King, Bishop, or Knight)
	int m_intPosition = 0; // Represents the 0-63 index upon which the piece is sitting. Updated at the same time the Board Positions array is updated.
	bool m_blnWhiteOrBlack; // True is White piece, False is Black piece.
	int m_intMoveCount = 0; // Number of times the piece has moved. Used primarily for validating castling and en-passant moves.

private:


	// --------------------------------------------------------------------------------
	// Methods
	// --------------------------------------------------------------------------------

public:
	Piece();
	Piece(char chrNotationName, string strFullName, int intPosition, bool blnWhiteOrBlack); // constructor

	char ReturnNotationName();
	bool ReturnPieceColor();
	int ReturnMoveCount();
	void IncrementMoveCount();
	void UpdatePosition(int intTargetPosition);
	bool Move(int intTargetPosition);
	bool CheckIfValidMove(int intCurrentPosition, int intDesiredPosition, bool blnWhiteOrBlackMove);
	bool CheckMovement_Knight(int intCurrentPosition, int intDesiredPosition, bool blnWhiteOrBlackMove);
	bool CheckMovement_Bishop(int intCurrentPosition, int intDesiredPosition);
	bool CheckMovement_Rook(int intCurrentPosition, int intDesiredPosition);
	bool CheckMovement_King(int intCurrentPosition, int intDesiredPosition);
	bool CheckMovement_Pawn(int intCurrentPosition, int intDesiredPosition, bool blnWhiteOrBlackMove);

protected:

private:							// Delete the list


};