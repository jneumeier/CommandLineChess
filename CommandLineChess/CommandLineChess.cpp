// --------------------------------------------------------------------------------
// John Neumeier
// 03/xx/22
// Command Line Chess
// --------------------------------------------------------------------------------


// To implement:
//
// piece obstructions when making moves


// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Board.h"
#include "Piece.h"
using namespace std;


// --------------------------------------------------------------------------------
// Initializers
// --------------------------------------------------------------------------------
void TurnDisplay(Board* clsBoard, bool blnWhiteOrBlackTurn, string* strErrorMessageToUser, string* strMessageToUser);
string GetMove();
bool ValidateEntry(string strMove);
bool MakeMove(string strMove, bool blnWhiteOrBlackTurn, Board *clsBoard, string *strMessageToUser);
bool HandleCheckStatus(Board* clsBoard, Board* clsBoardCopy, bool blnWhiteOrBlackTurn, string* strErrorMessageToUser, string* strMessageToUser, bool blnMoveSuccessful, string strMove);
bool CheckForPieceAscii(int intPieceAscii);
bool CheckForSquareAscii(int intColumn, int intRow);
bool MovePiece_Pawn(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser);
bool MovePiece_3Char(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser);
bool MovePiece_Capture(char chrPieceMoving, char chrSquareLetter_Dest, char chrSquareNumber_Dest, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser);
bool MovePiece_Castle(bool blnKingside, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser);


// --------------------------------------------------------------------------------
// Name: main
// Abstract: Demonstrates basic control over stacked and queued lists
// --------------------------------------------------------------------------------
int main()
{
	// define variables
	bool blnWhiteOrBlackTurn = true; // true is White, false is Black
	bool blnMoveSuccessful = false;
	string strMove = "";
	string strErrorMessageToUser = "";
	string strMessageToUser = "";

	Board clsBoard; // initialize the chess board. This also initializes all Pieces.
	Board clsBoardCopy;

	// start game loop. Exits loop when break is triggered
	while(1)
	{
		clsBoardCopy = clsBoard; // copy board so reversion is possible within current move (used for HandleCheckStatus)
		TurnDisplay(&clsBoard, blnWhiteOrBlackTurn, &strErrorMessageToUser, &strMessageToUser); // run the current turn's display
		strMove = GetMove(); // get the move from the user
		if (strMove == "exit") { cout << "Exiting...Bye!" << endl; break; } // exit the game
		blnMoveSuccessful = MakeMove(strMove, blnWhiteOrBlackTurn, &clsBoard, &strErrorMessageToUser); // try to make the entered move
		blnMoveSuccessful = HandleCheckStatus(&clsBoard, &clsBoardCopy, blnWhiteOrBlackTurn, &strErrorMessageToUser, &strMessageToUser, blnMoveSuccessful, strMove);

		// Change turns if the move was successful, and, change message back to ""
		if (blnMoveSuccessful == true)
		{ 
			blnWhiteOrBlackTurn = !blnWhiteOrBlackTurn;
			strErrorMessageToUser = "";
		}
	}
}


// --------------------------------------------------------------------------------
// Name: TurnDisplay
// Abstract: Shows all display needed for the current player's turn--the board
//			 and all messages that need to be shown
// --------------------------------------------------------------------------------
void TurnDisplay(Board* clsBoard, bool blnWhiteOrBlackTurn, string* strErrorMessageToUser, string* strMessageToUser)
{
	(*clsBoard).DisplayBoard(blnWhiteOrBlackTurn); // print the board

	if (*strErrorMessageToUser != "")
	{ 
		cout << *strErrorMessageToUser << endl; // print error message to user
		*strErrorMessageToUser = ""; // reset to prepare for another possible error message
	} 
	
	if (*strMessageToUser != "")
	{ 
		cout << *strMessageToUser << endl; // print informational message from last move
		*strMessageToUser = ""; // then reset it to prepare for another possible message
	} 
	
	// print king-in-check status
	int intKingIndex = (*clsBoard).GetKingIndex(blnWhiteOrBlackTurn);
	if ((*clsBoard).IsKingInCheck(blnWhiteOrBlackTurn, intKingIndex)) { cout << "You are in check." << endl << endl; }
}


// --------------------------------------------------------------------------------
// Name: GetMove
// Abstract: Gets the move from the user as algebraic notation, and validates it.
//			 If user entry is invalid the user gets 
//			 an error message and is prompted to enter proper Algebraic Notation.
//			 "exit" is allowed for exiting the program.
// --------------------------------------------------------------------------------
string GetMove()
{
	string strMove = "";
	bool blnValidMove = false;

	do
	{
		// prompt the user for input
		cout << ">> Enter a move: " << endl;

		// get user input
		cin >> strMove;

		blnValidMove = ValidateEntry(strMove);

		if (blnValidMove == false) { cout << "Entry is invalid." << endl; }

	} while (blnValidMove == false);

	return strMove;
}



// --------------------------------------------------------------------------------
// Name: ValidateEntry
// Abstract: Validates the entry only against max possible length and permitted chars
// --------------------------------------------------------------------------------
bool ValidateEntry(string strMove)
{
	bool blnValidEntry = false;
	int intIndex = 0;
	int intIndex2 = 0;
	char chrCurrentChar = '0';
	int aintValidAsciiChars[] = {49, 50, 51, 52, 53, 54, 55, 56, 97, 98, 99, 100, 101, 102, 103, 104,
								 75, 78, 120, 66, 82, 81};

	// check for special moves first
	if (strMove == "0-0-0" || strMove == "0-0" || strMove == "O-O-O" || strMove == "O-O" ||
		strMove == "(=)" || strMove == "exit")
	{
		blnValidEntry = true;
	}

	// no possible valid string representing a move that is above 6 chars
	else if (strMove.length() > 6) { blnValidEntry = false; }

	else
	{
		// check each character that the user gave
		for (intIndex = 0; intIndex < strMove.length(); intIndex += 1)
		{
			// check the character against all accepted characters
			for (intIndex2 = 0; intIndex2 < 22; intIndex2 += 1)
			{
				// if given character matches character in accepted character array
				if (strMove[intIndex] == aintValidAsciiChars[intIndex2])
				{
					blnValidEntry = true;
					break;
				}

				// if all accepted char array indicies have been iterated thru, and still false...
				else if(intIndex2 == 21 && blnValidEntry == false)
				{ 
					return blnValidEntry; 
				}
			}
		}
	}

	return blnValidEntry;
}



// --------------------------------------------------------------------------------
// Name: MakeMove
// Abstract: Analyzes user entry and calls correct type of move depending on format
// --------------------------------------------------------------------------------
bool MakeMove(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string *strErrorMessageToUser)
{
	bool blnMoveSuccessful = false;
	int intDestinationIndex = 0;
	int intPieceStartIndex = 0;

	// If given move is in format--> example: Ke4, then, make the move.
	if (strMove.length() == 3 && CheckForPieceAscii(strMove[0]) == true && CheckForSquareAscii(strMove[1], strMove[2]) == true)
	{
		blnMoveSuccessful = MovePiece_3Char(strMove, blnWhiteOrBlackTurn, clsBoard, strErrorMessageToUser);
	}

	// Entry format ex. e4, make the move. (this is for pawns only)
	else if (strMove.length() == 2 && CheckForSquareAscii(strMove[0], strMove[1]) == true)
	{
		blnMoveSuccessful = MovePiece_Pawn(strMove, blnWhiteOrBlackTurn, clsBoard, strErrorMessageToUser);
	}

	// Entry format--> ex. Bxe5, or w/ pawn (exd5)---then make the move.
	else if (strMove.length() == 4 && (CheckForPieceAscii(strMove[0]) == true || ((strMove[0]) >= 97 && (strMove[0]) <= 104)) && CheckForSquareAscii(strMove[2], strMove[3]) == true && strMove[1] == 'x')
	{
		blnMoveSuccessful = MovePiece_Capture(strMove[0], strMove[2], strMove[3], blnWhiteOrBlackTurn, clsBoard, strErrorMessageToUser);
	}

	// If given move is in format--> example: Bae5, then, make the move.
	// If given move is in format--> example: Qa4e5, then, make the move.
	// If given move is in format--> example: B1e5, then, make the move.
	// If given move is in format--> example: Bfxe5, then, make the move.
	// If given move is in format--> example: Bf4xe5, then, make the move.

	// If request to castle kingside
	else if (strMove == "0-0" || strMove == "O-O")
	{
		blnMoveSuccessful = MovePiece_Castle(true, blnWhiteOrBlackTurn, clsBoard, strErrorMessageToUser);
	}
	// If request to castle queenside
	else if (strMove == "0-0-0" || strMove == "O-O-O")
	{
		blnMoveSuccessful = MovePiece_Castle(false, blnWhiteOrBlackTurn, clsBoard, strErrorMessageToUser);
	}

	return blnMoveSuccessful;
}


// --------------------------------------------------------------------------------
// Name: HandleCheckStatus
// Abstract: Depending on board state this updates players' check statuses, and
//			 records the proper messages to be shown to the user.
// --------------------------------------------------------------------------------
bool HandleCheckStatus(Board* clsBoard, Board* clsBoardCopy, bool blnWhiteOrBlackTurn, string* strErrorMessageToUser, string* strMessageToUser, bool blnMoveSuccessful, string strMove)
{
	int intKingIndex;
	bool* pblnCurrentPlayerCheckStatus;
	bool* pblnOtherPlayerCheckStatus;

	// get address for current player's check status, so its value can be easily checked against
	if (blnWhiteOrBlackTurn)
	{
		pblnCurrentPlayerCheckStatus = &(*clsBoard).m_blnWhiteInCheck;
		pblnOtherPlayerCheckStatus = &(*clsBoard).m_blnBlackInCheck;
	}
	else
	{
		pblnCurrentPlayerCheckStatus = &(*clsBoard).m_blnBlackInCheck;
		pblnOtherPlayerCheckStatus = &(*clsBoard).m_blnWhiteInCheck;
	}

	if (blnMoveSuccessful)
	{
		// update other player's check status
		intKingIndex = (*clsBoard).GetKingIndex(!blnWhiteOrBlackTurn); // set king index to opposing player's
		if ((*clsBoard).IsKingInCheck(!blnWhiteOrBlackTurn, intKingIndex)) { *pblnOtherPlayerCheckStatus = true; }
		else { *pblnOtherPlayerCheckStatus = false; }

		// check for current player's king still being in check, else update current player's check status
		intKingIndex = (*clsBoard).GetKingIndex(blnWhiteOrBlackTurn); // set king index to current player's
		if ((*clsBoard).IsKingInCheck(blnWhiteOrBlackTurn, intKingIndex))
		{
			blnMoveSuccessful = false;
			*pblnCurrentPlayerCheckStatus = true;
			*clsBoard = *clsBoardCopy; // Now that we know check has resulted from current turn's move, board goes back to its state before current turn's move was made.
			if (strMove[0] == 'K' && *pblnCurrentPlayerCheckStatus == true) { *strErrorMessageToUser = "Invalid move. Your king cannot escape check there."; }
			else if (strMove[0] == 'K' && *pblnCurrentPlayerCheckStatus == false) { *strErrorMessageToUser = "Invalid move. Your king would enter check there."; }
			else { *strErrorMessageToUser = "Invalid move."; }
		}
		else { *pblnCurrentPlayerCheckStatus = false; }
	}

	return blnMoveSuccessful;
}


// --------------------------------------------------------------------------------
// Name: CheckForPieceAscii
// Abstract: Returns true if given int is ascii value for B, K, N, Q or R
// --------------------------------------------------------------------------------
bool CheckForPieceAscii(int intPieceAscii)
{
	bool blnValidLetter = false;
	int intIndex = 0;

	int aintValidAsciiLetters[] = { 66, 75, 78, 81, 82 }; // B, K, N, Q, R

	for (intIndex = 0; intIndex < 5; intIndex++)
	{
		if (intPieceAscii == aintValidAsciiLetters[intIndex]) { blnValidLetter = true; break; }
	}

	return blnValidLetter;
}

// --------------------------------------------------------------------------------
// Name: CheckForSquareAscii
// Abstract: Returns true if given int values are ascii values for a thru h and
// 1 thru 8
// --------------------------------------------------------------------------------
bool CheckForSquareAscii(int intColumn, int intRow)
{
	bool blnValidSquare = false;
	int intIndex = 0;
	// 97, 104

	if (intColumn >= 97 && intColumn <= 104) // a thru h
	{ 
		if (intRow >= 49 && intRow <= 56) { blnValidSquare = true; } // 1 thru 8 (ascii values)
	}
	
	return blnValidSquare;
}

// --------------------------------------------------------------------------------
// Name: MakeMove_Pawn
// Abstract: Moves a pawn on the board
// --------------------------------------------------------------------------------
bool MovePiece_Pawn(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser)
{
	bool blnMoveSuccessful = false;
	int intDestinationIndex = 0;
	int intPieceStartIndex = 0;

	// find the index for the square to move to
	intDestinationIndex = (*clsBoard).GetPositionIndex(strMove[0], strMove[1]);

	// search for a pawn one or two squares behind the desired move
	// if white
	if (blnWhiteOrBlackTurn == true)
	{
		// search for a pawn one square behind desired move
		if ((*clsBoard).m_vecPositions[intDestinationIndex + 8].ReturnNotationName() == 'P' &&
			(*clsBoard).m_vecPositions[intDestinationIndex + 8].ReturnPieceColor() == blnWhiteOrBlackTurn)
		{
			intPieceStartIndex = intDestinationIndex + 8;
		}

		// search for a pawn two squares behind desired move, AND only if the pawn is in its original row (hasn't moved yet)
		else if ((*clsBoard).m_vecPositions[intDestinationIndex + 16].ReturnNotationName() == 'P' &&
			(intDestinationIndex + 16) >= 48 && (intDestinationIndex + 16) <= 55 &&
			(*clsBoard).m_vecPositions[intDestinationIndex - 16].ReturnPieceColor() == blnWhiteOrBlackTurn)
		{
			intPieceStartIndex = intDestinationIndex + 16;
		}

		else { intPieceStartIndex = -1; }
	}

	// if black
	if (blnWhiteOrBlackTurn == false)
	{
		// search for a pawn one square behind desired move
		if ((*clsBoard).m_vecPositions[intDestinationIndex - 8].ReturnNotationName() == 'P' &&
			(*clsBoard).m_vecPositions[intDestinationIndex - 8].ReturnPieceColor() == blnWhiteOrBlackTurn)
		{
			intPieceStartIndex = intDestinationIndex - 8;
		}

		// search for a pawn two squares behind desired move, AND only if the pawn is in its original row (hasn't moved yet)
		else if ((*clsBoard).m_vecPositions[intDestinationIndex - 16].ReturnNotationName() == 'P' &&
			(intDestinationIndex - 16) >= 8 && (intDestinationIndex - 16) <= 15 &&
			(*clsBoard).m_vecPositions[intDestinationIndex - 16].ReturnPieceColor() == blnWhiteOrBlackTurn)
		{
			intPieceStartIndex = intDestinationIndex - 16;
		}

		else { intPieceStartIndex = -1; }
	}

	// if landing position already has a piece on it, don't allow the move
	if ((*clsBoard).GetNotationName(intDestinationIndex) != '-') { intPieceStartIndex = -1; }

	// Give error messages if move is invalid, else, make the move!
	if (intPieceStartIndex == -1) { *strErrorMessageToUser += "Attempted move is invalid. "; blnMoveSuccessful = false; }

	else
	{
		// make the move. Simple swap for now. Will elaborate later.
		(*clsBoard).SwapSquares(intPieceStartIndex, intDestinationIndex);

		blnMoveSuccessful = true;
	}

	return blnMoveSuccessful;
}

// --------------------------------------------------------------------------------
// Name: MovePiece_3Char
// Abstract: Moves a piece on the board
// --------------------------------------------------------------------------------
bool MovePiece_3Char(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser)
{
	bool blnMoveSuccessful = false;
	int intDestinationIndex = 0;
	int intPieceStartIndex = 0;

	// find the index for the square to move to
	intDestinationIndex = (*clsBoard).GetPositionIndex(strMove[1], strMove[2]);

	// find the index for the square of the given piece. Will equal -1 if nonexistent.
	// -2 if more than one of same type piece can get to the square.
	// This also validates if the piece can make the move.
	intPieceStartIndex = (*clsBoard).GetPieceIndex(strMove[0], intDestinationIndex, blnWhiteOrBlackTurn);

	// Check if there is any piece in the way during moving (Knight is excluded by rule)
	if (strMove[0] != 'N' && intPieceStartIndex != -1 && intPieceStartIndex != -2)
	{
		if ((*clsBoard).CheckMovePath(intPieceStartIndex, intDestinationIndex) == false)
		{
			intPieceStartIndex = -1;
			*strErrorMessageToUser += "There are pieces in the way of your desired path. ";
		}
	}

	// check if there is a piece already on target square
	if ((*clsBoard).m_vecPositions[intDestinationIndex].ReturnNotationName() != '-' && intPieceStartIndex != -1 && intPieceStartIndex != -2)
	{
		if ((*clsBoard).m_vecPositions[intDestinationIndex].ReturnPieceColor() == blnWhiteOrBlackTurn)
		{
			*strErrorMessageToUser += "Your own piece is on that destination square. ";
		}
		else { *strErrorMessageToUser += "You must notate this move as a capture. "; }

		intPieceStartIndex = -1;
	}

	// Give error messages if move is invalid, else, make the move!
	if (intPieceStartIndex == -1) { *strErrorMessageToUser += "Attempted move is invalid. "; blnMoveSuccessful = false; }
	else if (intPieceStartIndex == -2)
	{
		*strErrorMessageToUser += "More than one of that type of piece can make that move. Define the starting square in your notation. Ex. Rad4, R4d4, Ra4d4, Raxd4, etc. ";
		blnMoveSuccessful = false;
	}
	else
	{
		// make the move. Simple swap for now. Will elaborate later.
		(*clsBoard).SwapSquares(intPieceStartIndex, intDestinationIndex);

		blnMoveSuccessful = true;
	}

	return blnMoveSuccessful;
}

// --------------------------------------------------------------------------------
// Name: MovePiece_Capture
// Abstract: Caputures a piece on the board
// --------------------------------------------------------------------------------
bool MovePiece_Capture(char chrPieceMoving, char chrSquareLetter_Dest, char chrSquareNumber_Dest, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser)
{
	bool blnMoveSuccessful = false;
	int intDestinationIndex = 0;
	int intPieceStartIndex = 0;

	// find the index for the square to move to
	intDestinationIndex = (*clsBoard).GetPositionIndex(chrSquareLetter_Dest, chrSquareNumber_Dest);

	// find the index for the square of the given piece. Will equal -1 if nonexistent.
	// -2 if more than one of same type piece can get to the square.
	// This also validates if the piece can make the move.
	intPieceStartIndex = (*clsBoard).GetPieceIndex(chrPieceMoving, intDestinationIndex, blnWhiteOrBlackTurn);

	// check if there is nothing on target square
	if ((*clsBoard).GetNotationName(intDestinationIndex) == '-')
	{
		*strErrorMessageToUser += "The requested capture has no piece at destination. ";
		intPieceStartIndex = -1;
	}

	// check if a piece of the player's color is on the target square
	if ((*clsBoard).GetPieceColor(intDestinationIndex) == blnWhiteOrBlackTurn &&
		(*clsBoard).GetNotationName(intDestinationIndex) != '-')
	{
		*strErrorMessageToUser += "Your own piece is on that destination square. ";
		intPieceStartIndex = -1;
	}

	// Give error messages if move is invalid, else, make the move!
	if (intPieceStartIndex == -1) { *strErrorMessageToUser += "Attempted move is invalid. "; blnMoveSuccessful = false; }
	else if (intPieceStartIndex == -2)
	{
		*strErrorMessageToUser += "More than one of that type of piece can make that move. Define the starting square in your notation. Ex. Rad4, R4d4, Ra4d4, Raxd4, etc. ";
		blnMoveSuccessful = false;
	}
	else
	{
		// make the move. Simple swap for now. Will elaborate later.
		(*clsBoard).CapturePiece(intPieceStartIndex, intDestinationIndex);

		blnMoveSuccessful = true;
	}

	return blnMoveSuccessful;
}

// --------------------------------------------------------------------------------
// Name: MovePiece_Castle
// Abstract: Performs castling
// --------------------------------------------------------------------------------
bool MovePiece_Castle(bool blnKingside, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser)
{
	bool blnMoveSuccessful = false;

	// get the spots that the pieces must be in for castling to be a legal move
	int intKingIndex = 0;
	int intRookIndex = 0;
	int intIncrement = 0;

	// if white's move
	if (blnWhiteOrBlackTurn)
	{
		intKingIndex = 60;
		if (blnKingside) { intRookIndex = 63; }
		else { intRookIndex = 56; }
	}
	// if black's move
	else
	{
		intKingIndex = 4;
		if (blnKingside) { intRookIndex = 7; }
		else { intRookIndex = 0; }
	}

	// see if the king and rook are on their original squares
	if ((*clsBoard).GetNotationName(intKingIndex) == 'K' && (*clsBoard).GetNotationName(intRookIndex) == 'R')
	{
		// see if either piece has moved yet
		if ((*clsBoard).m_vecPositions[intKingIndex].ReturnMoveCount() == 0 &&
			(*clsBoard).m_vecPositions[intRookIndex].ReturnMoveCount() == 0)
		{
			// set king-pathway direction for checking
			if (blnKingside) { intIncrement = 1; } else { intIncrement = -1; } // first, see which direction to check in

			// see if there are any pieces in the immediate pathway between king and rook
			if ((*clsBoard).m_vecPositions[intKingIndex + intIncrement].ReturnNotationName() == '-' && (*clsBoard).m_vecPositions[intKingIndex + (intIncrement * 2)].ReturnNotationName() == '-')
			{
				// see if king is in check in current, passing, and final square before moving
				if ((*clsBoard).IsKingInCheck(blnWhiteOrBlackTurn, intKingIndex) && (*clsBoard).IsKingInCheck(blnWhiteOrBlackTurn, intKingIndex + intIncrement) &&
					(*clsBoard).IsKingInCheck(blnWhiteOrBlackTurn, intKingIndex + (intIncrement * 2)))
				{
					
				}
			}

			
			//// see if king is in check after moving
			//// see if king passes through check during move
		}
	}

	// make the move. Simple swap for now. Will elaborate later.
	//(*clsBoard).SwapSquares(intPieceStartIndex, intDestinationIndex);

	blnMoveSuccessful = true;

	return blnMoveSuccessful;
}