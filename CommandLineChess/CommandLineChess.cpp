// --------------------------------------------------------------------------------
// John Neumeier
// 03/xx/22
// Command Line Chess
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "Board.h"
#include "Piece.h"
using namespace std;



// --------------------------------------------------------------------------------
// Initializers
// --------------------------------------------------------------------------------
void Menus(string* strView, bool* blnGameRunning, Board* clsBoard, Board* clsNewBoard, bool* blnWhiteOrBlackTurn, string* strBoardStyle);
void DisplayMenu(bool blnGameRunning);
void DisplayOptions(string* strBoardStyle);
void DisplayInfo();
string GetCommand();
void TurnDisplay(Board* clsBoard, bool blnWhiteOrBlackTurn, string* strErrorMessageToUser, string* strMessageToUser, string strBoardStyle);
string GetMove();
bool ValidateEntry(string strMove);
bool MakeMove(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strMessageToUser);
bool HandleCheckmate(Board* clsBoard, Board* clsNewBoard, bool* blnWhiteOrBlackTurn, string* strView, bool* blnGameRunning);
bool HandleCheckStatus(Board* clsBoard, Board* clsBoardCopy, bool blnWhiteOrBlackTurn, string* strErrorMessageToUser, string* strMessageToUser, bool blnMoveSuccessful, string strMove);
bool CheckForPieceAscii(int intPieceAscii);
bool CheckForSquareAscii(int intColumn, int intRow);
bool MovePiece_Pawn(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser);
bool MovePiece(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser);
bool MovePiece_Capture(char chrPieceMoving, char chrSquareLetter_Dest, char chrSquareNumber_Dest, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser);
bool MovePiece_Castle(bool blnKingside, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser);



// --------------------------------------------------------------------------------
// Name: main
// Abstract: The hub of our chess application!!!
// --------------------------------------------------------------------------------
int main()
{
	// define variables
	bool blnWhiteOrBlackTurn = true; // true is White, false is Black
	bool blnMoveSuccessful = false;
	bool blnGameRunning = false;
	bool blnCurrentPlayerCheckStatus = false;
	string strMove = "";
	string strErrorMessageToUser = "";
	string strMessageToUser = "";
	string strView = "menu";
	string strBoardStyle = "small";

	// initialize the chess board (and some handy copies of it)
	Board clsNewBoard;
	Board clsBoard;
	Board clsBoardCopy;

	// start game loop. Exits loop when break is called
	while (1)
	{
		// always check if strView is telling us to be in a different "view", or menu.
		Menus(&strView, &blnGameRunning, &clsBoard, &clsNewBoard, &blnWhiteOrBlackTurn, &strBoardStyle);

		// Game Area
		if (strView == "new" || strView == "continue")
		{
			blnGameRunning = true;
			clsBoardCopy = clsBoard; // copy board so reversion is possible within current move (used for HandleCheckStatus)
			TurnDisplay(&clsBoard, blnWhiteOrBlackTurn, &strErrorMessageToUser, &strMessageToUser, strBoardStyle); // run the current turn's display

			// assess for checkmate, and ask for input if so:
			if (blnWhiteOrBlackTurn) { blnCurrentPlayerCheckStatus = clsBoard.m_blnWhiteInCheck; }
			else { blnCurrentPlayerCheckStatus = clsBoard.m_blnBlackInCheck; }

			if (blnCurrentPlayerCheckStatus == true)
			{
				// if current player is in checkmate, strView is set to either "new" or "menu", and we skip the rest of the While loops current iteration
				if(HandleCheckmate(&clsBoard, &clsNewBoard, &blnWhiteOrBlackTurn, &strView, &blnGameRunning)) { continue; }
			}

			strMove = "";
			strMove = GetMove(); // get the move from the user

			if (strMove == "exit") { cout << "Exiting...Bye!" << endl; break; } // exit the game
			if (strMove == "menu") { strView = "menu"; continue; }

			blnMoveSuccessful = MakeMove(strMove, blnWhiteOrBlackTurn, &clsBoard, &strErrorMessageToUser); // try to make the entered move
			blnMoveSuccessful = HandleCheckStatus(&clsBoard, &clsBoardCopy, blnWhiteOrBlackTurn, &strErrorMessageToUser, &strMessageToUser, blnMoveSuccessful, strMove);
			

			// Change turns if the move was successful, and, change message back to ""
			if (blnMoveSuccessful == true)
			{
				blnWhiteOrBlackTurn = !blnWhiteOrBlackTurn;
				strErrorMessageToUser = "";
			}
		}
		else if (strView == "exit") { cout << "Exiting...Bye!" << endl; break; }
	}
}



// --------------------------------------------------------------------------------
// Name: Menus()
// Abstract: Checks the state of strView and calls its corresponding menu to be
//			 displayed. User input is received via GetCommand(), evaluated,
//			 and game states are altered if necessary.
// --------------------------------------------------------------------------------
void Menus(string *strView, bool *blnGameRunning, Board *clsBoard, Board *clsNewBoard, bool *blnWhiteOrBlackTurn, string *strBoardStyle)
{
	string strCommand = "";

	cout << endl;

	if (*strView == "menu")
	{
		DisplayMenu(*blnGameRunning);
		strCommand = GetCommand();

		if (strCommand == "exit") { *strView = strCommand; } // exit the game
		else if (strCommand == "new")
		{
			*strView = strCommand;
			*clsBoard = *clsNewBoard; // reset the game board
			*blnWhiteOrBlackTurn = true; // set to white's move
		}
		else if (strCommand == "continue") { *strView = strCommand; }
		else if (strCommand == "options") { *strView = strCommand; }
		else if (strCommand == "info") { *strView = strCommand; }
		else { *strView = "menu"; }
	}
	else if (*strView == "options")
	{
		DisplayOptions(strBoardStyle);
		strCommand = GetCommand();

		if (strCommand == "exit") { *strView = strCommand; } // exit the game
		else if (strCommand == "back") { *strView = "menu"; }
		else if (strCommand == "small" || strCommand == "large") { *strBoardStyle = strCommand; }
		else { *strView = "options"; }
	}
	else if (*strView == "info")
	{
		DisplayInfo();
		strCommand = GetCommand();

		if (strCommand == "exit") { *strView = strCommand; } // exit the game
		else if (strCommand == "back") { *strView = "menu"; }
		else { *strView = "info"; }
	}
}



// --------------------------------------------------------------------------------
// Name: DisplayMenu()
// Abstract: Displays the main menu
// --------------------------------------------------------------------------------
void DisplayMenu(bool blnGameRunning)
{
	cout << "*************************************************************************" << endl << endl;
	if (!blnGameRunning) {
	cout << "                       Welcome to Command Line Chess!                    " << endl << endl;}
	cout << "                                 Main Menu                               " << endl << endl;
	cout << "                                 New Game                                " << endl;
	if(blnGameRunning) {
	cout << "                                 Continue                                " << endl; }
	cout << "                                 Options                                 " << endl;
	cout << "                                 Info                                    " << endl;
	cout << "                                 Exit                                    " << endl << endl << endl;
	cout << "*************************************************************************" << endl << endl;
}



// --------------------------------------------------------------------------------
// Name: DisplayOptions()
// Abstract: Displays the options menu
// --------------------------------------------------------------------------------
void DisplayOptions(string* strBoardStyle)
{
	cout << "*************************************************************************" << endl << endl;
	cout << "                                 Options                                 " << endl << endl;
	cout << "                            ----Board Size----                           " << endl;
	if (*strBoardStyle == "small") {
	cout << "                           > small     large                             " << endl << endl;}
	else if (*strBoardStyle == "large") {
	cout << "                             small   > large                             " << endl << endl;}
	cout << "                                  Back                                   " << endl << endl << endl;
	cout << "*************************************************************************" << endl << endl;
}



// --------------------------------------------------------------------------------
// Name: DisplayInfo()
// Abstract: Displays the info menu
// --------------------------------------------------------------------------------
void DisplayInfo()
{
	cout << "*************************************************************************" << endl << endl;
	cout << "                                  Info                                   " << endl << endl;
	cout << "                      Copyright 2022 by John Neumeier                    " << endl << endl;
	cout << "                                  Back                                   " << endl << endl << endl;
	cout << "*************************************************************************" << endl << endl;
}



// --------------------------------------------------------------------------------
// Name: GetCommand
// Abstract: Gets the program command from the user
// --------------------------------------------------------------------------------
string GetCommand()
{
	string strCommand = "";
	string strReturnCommand = "";
	bool blnValidMove = false;
	bool blnValidEntry = false;
	int intIndex = 0;
	int intStringLength = 0;

	do
	{
		// prompt the user for input
		cout << ">> Enter a selection: " << endl;

		// get user input
		cin >> strCommand;

		// make sure all letters are lowercase before evaluating
		intStringLength = strCommand.length();
		string strCommandLowerCase = strCommand; // initialize before we change the letters all to lower case
		for (intIndex = 0; intIndex < intStringLength; intIndex++)
		{
			if (strCommand[intIndex] >= 65 && strCommand[intIndex] <= 90) { strCommandLowerCase[intIndex] = strCommand[intIndex] + 32; }
			else { strCommandLowerCase[intIndex] = strCommand[intIndex]; }
		}

		// check for special commands first
		if (strCommandLowerCase == "new" || strCommandLowerCase == "continue" || strCommandLowerCase == "options" || strCommandLowerCase == "exit"
			|| strCommandLowerCase == "small" || strCommandLowerCase == "large" || strCommandLowerCase == "back" || strCommandLowerCase == "info")
		{
			strReturnCommand = strCommandLowerCase;
		}
	} while (strReturnCommand == "");

	return strReturnCommand;
}



// --------------------------------------------------------------------------------
// Name: TurnDisplay
// Abstract: Shows all display needed for the current player's turn--the board
//			 and all messages that need to be shown
// --------------------------------------------------------------------------------
void TurnDisplay(Board* clsBoard, bool blnWhiteOrBlackTurn, string* strErrorMessageToUser, string* strMessageToUser, string strBoardStyle)
{
	// print the board
	if (strBoardStyle == "small") { (*clsBoard).DisplayBoard_Simple(blnWhiteOrBlackTurn); }
	else if (strBoardStyle == "large") { (*clsBoard).DisplayBoard_Ascii(blnWhiteOrBlackTurn); }
	

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
		cout << ">> Enter a move. (Type \"menu\" for Main Menu): " << endl;

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
		strMove == "(=)" || strMove == "exit" || strMove == "undo" || strMove == "u" ||
		strMove == "menu" || strMove == "Menu")
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

	// Entry format ex. e4, make the move. (this is for pawns only)
	if (strMove.length() == 2 && CheckForSquareAscii(strMove[0], strMove[1]) == true)
	{
		blnMoveSuccessful = MovePiece_Pawn(strMove, blnWhiteOrBlackTurn, clsBoard, strErrorMessageToUser);
	}

	// Entry format--> ex. Bxe5, or w/ pawn (exd5)---then make the move.
	else if (strMove.length() == 4 && (CheckForPieceAscii(strMove[0]) == true || ((strMove[0]) >= 97 && (strMove[0]) <= 104)) && CheckForSquareAscii(strMove[2], strMove[3]) == true && strMove[1] == 'x')
	{
		blnMoveSuccessful = MovePiece_Capture(strMove[0], strMove[2], strMove[3], blnWhiteOrBlackTurn, clsBoard, strErrorMessageToUser);
	}

	
	

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
	else { blnMoveSuccessful = MovePiece(strMove, blnWhiteOrBlackTurn, clsBoard, strErrorMessageToUser); }

	return blnMoveSuccessful;
}



// --------------------------------------------------------------------------------
// Name: HandleCheckmate
// Abstract: Assesses if the given player's king is in checkmate, and if so, resets
//			 the appropriate variables in order to begin a new game.
// --------------------------------------------------------------------------------
bool HandleCheckmate(Board* clsBoard, Board* clsNewBoard, bool* blnWhiteOrBlackTurn, string* strView, bool* blnGameRunning)
{
	bool IsInCheckmate = false;
	int intKingIndex;
	int intKingsReach[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
	vector <int> vecPossibleKingMoves;
	int intIndex = 0;
	int intLandingSquare = 0;
	char chrLandingSquarePiece;
	bool blnLandingSquareColor;
	string strCurrentPlayer = "White";
	string strInput = "";

	if (!*blnWhiteOrBlackTurn) { strCurrentPlayer = "Black"; }

	// Get given player's king position
	intKingIndex = (*clsBoard).GetKingIndex(*blnWhiteOrBlackTurn);

	// Find what squares in reach of the king are empty.
	// Use IsKingInCheck for as many times as there are empty squares immediately around the king, using it's king-index parameter as each of those squares.
	for (intIndex = 0; intIndex < 8; intIndex++)
	{
		intLandingSquare = intKingIndex + intKingsReach[intIndex];

		// if the move is possible only in terms of the king's pure ability to move (all other-piece situational restraints aside)
		if (clsBoard->m_vecPositions[intKingIndex].CheckMovement_King(intKingIndex, intLandingSquare))
		{
			chrLandingSquarePiece = clsBoard->m_vecPositions[intLandingSquare].ReturnNotationName();
			blnLandingSquareColor = clsBoard->m_vecPositions[intLandingSquare].ReturnPieceColor();

			if (chrLandingSquarePiece == '-' || (chrLandingSquarePiece != '-' && chrLandingSquarePiece != 'K' && blnLandingSquareColor == !*blnWhiteOrBlackTurn))
			{
				// now that we know that this potential square for the king is a possible move, we check it to see if Check would result from moving there
				if (clsBoard->IsKingInCheck(*blnWhiteOrBlackTurn, intKingsReach[intIndex])) { IsInCheckmate = true; }
				else { IsInCheckmate = false; break; } // break when first king's target to-move-to square comes back as not resulting in check
			}
		}
	}

	if (IsInCheckmate)
	{
		cout << strCurrentPlayer << " is in checkmate." << endl;

		do
		{
			cout << "New game? (Y/N): ";
			cin >> strInput;
		} while (strInput != "Y" && strInput != "y" && strInput != "N" && strInput != "n");
		
		if (strInput == "Y" || strInput == "y")
		{
			*strView = "new";
			*clsBoard = *clsNewBoard; // reset the game board
			*blnWhiteOrBlackTurn = true; // set to white's move
		}
		else
		{
			*strView = "menu";
		}
	}

	return IsInCheckmate;
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
			// *pblnCurrentPlayerCheckStatus = true;
			*clsBoard = *clsBoardCopy; // Now that we know check has resulted from current turn's move, board goes back to its state before current turn's move was made.
			if (strMove[0] == 'K' && *pblnCurrentPlayerCheckStatus == true) { *strErrorMessageToUser = "Invalid move. Your king cannot escape check there."; }
			else if (strMove[0] == 'K' && *pblnCurrentPlayerCheckStatus == false) { *strErrorMessageToUser = "Invalid move. Your king would enter check there."; }
			else if (*pblnCurrentPlayerCheckStatus == true) { *strErrorMessageToUser = "Invalid move. That does not help your king escape check."; }
			else { *strErrorMessageToUser = "Invalid move. That would put your king in check."; }
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

	// find the index for the piece to move to
	intDestinationIndex = (*clsBoard).GetPositionIndex(strMove[0], strMove[1]);

	// if landing position already has a piece on it, don't allow the move
	if ((*clsBoard).GetNotationName(intDestinationIndex) != '-') { intPieceStartIndex = -1; }

	// search for a pawn one or two squares behind the desired move
	// if white
	else if (blnWhiteOrBlackTurn == true)
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
	else if (blnWhiteOrBlackTurn == false)
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
// Name: MovePiece
// Abstract: Moves a piece on the board
// --------------------------------------------------------------------------------
bool MovePiece(string strMove, bool blnWhiteOrBlackTurn, Board* clsBoard, string* strErrorMessageToUser)
{
	bool blnMoveSuccessful = false;
	int intDestinationIndex = 0;
	int intPieceStartIndex = 0;


	// If given move is in format--> example: Ke4, then, make the move.
	if (strMove.length() == 3 && CheckForPieceAscii(strMove[0]) == true && CheckForSquareAscii(strMove[1], strMove[2]) == true)
	{
		// find the index for the square to move to
		intDestinationIndex = (*clsBoard).GetPositionIndex(strMove[1], strMove[2]);

		// find the index for the square of the given piece. Will equal -1 if nonexistent.
		// -2 if more than one of same type piece can get to the square. This also validates if the piece can make the move.
		intPieceStartIndex = (*clsBoard).GetPieceIndex(strMove[0], 0, 0, intDestinationIndex, blnWhiteOrBlackTurn);
	}

	// If given move is in format--> example: Bae5, then, make the move.
	else if (strMove.length() == 4 && CheckForPieceAscii(strMove[0]) && CheckForSquareAscii(strMove[2], strMove[3])
		&& strMove[1] >= 97 && strMove[1] <= 104)
	{
		// find the index for the square to move to
		intDestinationIndex = (*clsBoard).GetPositionIndex(strMove[2], strMove[3]);

		// find the index for the square of the given piece. Will equal -1 if nonexistent.
		// -2 if more than one of same type piece can get to the square. This also validates if the piece can make the move.
		intPieceStartIndex = (*clsBoard).GetPieceIndex(strMove[0], strMove[1], 0, intDestinationIndex, blnWhiteOrBlackTurn);
	}

	// If given move is in format--> example: B1e5, then, make the move.
	else if (strMove.length() == 4 && CheckForPieceAscii(strMove[0]) && CheckForSquareAscii(strMove[2], strMove[3])
		&& strMove[1] >= 1 && strMove[1] <= 8)
	{
		// find the index for the square to move to
		intDestinationIndex = (*clsBoard).GetPositionIndex(strMove[2], strMove[3]);

		// find the index for the square of the given piece. Will equal -1 if nonexistent.
		// -2 if more than one of same type piece can get to the square. This also validates if the piece can make the move.
		intPieceStartIndex = (*clsBoard).GetPieceIndex(strMove[0], 0, strMove[1], intDestinationIndex, blnWhiteOrBlackTurn);
	}

	// If given move is in format--> example: Qa4e5, then, make the move.
	else if (strMove.length() == 5 && CheckForPieceAscii(strMove[0]) && CheckForSquareAscii(strMove[3], strMove[4])
		&& CheckForSquareAscii(strMove[1], strMove[2]))
	{
		// find the index for the square to move to
		intDestinationIndex = (*clsBoard).GetPositionIndex(strMove[3], strMove[4]);

		// find the index for the square of the given piece. Will equal -1 if nonexistent.
		// -2 if more than one of same type piece can get to the square. This also validates if the piece can make the move.
		intPieceStartIndex = (*clsBoard).GetPieceIndex(strMove[0], strMove[1], strMove[2], intDestinationIndex, blnWhiteOrBlackTurn);
	}



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
	intPieceStartIndex = (*clsBoard).GetPieceIndex(chrPieceMoving, 0, 0, intDestinationIndex, blnWhiteOrBlackTurn);

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
		if ((*clsBoard).m_vecPositions[intKingIndex].ReturnMoveCount() == 0)
		{
			if ((*clsBoard).m_vecPositions[intRookIndex].ReturnMoveCount() == 0)
			{
				// set king-pathway direction for checking
				if (blnKingside) { intIncrement = 1; }
				else { intIncrement = -1; } // first, see which direction to check in

				// see if there are any pieces in the immediate pathway between king and rook
				if ((*clsBoard).m_vecPositions[intKingIndex + intIncrement].ReturnNotationName() == '-' && (*clsBoard).m_vecPositions[intKingIndex + (intIncrement * 2)].ReturnNotationName() == '-')
				{
					// see if king is in check in current, passing, and final square before moving
					if ((*clsBoard).IsKingInCheck(blnWhiteOrBlackTurn, intKingIndex) == false)
					{
						if ((*clsBoard).IsKingInCheck(blnWhiteOrBlackTurn, intKingIndex + intIncrement) == false)
						{
							if ((*clsBoard).IsKingInCheck(blnWhiteOrBlackTurn, intKingIndex + (intIncrement * 2)) == false)
							{
								// castling is now seen as legal, now we can make the move
								(*clsBoard).SwapSquares(intKingIndex, intKingIndex + (intIncrement * 2));
								(*clsBoard).SwapSquares(intRookIndex, intKingIndex + intIncrement);
								blnMoveSuccessful = true;
							}
							else { *strErrorMessageToUser = "Castling failed. Your king would be landing on check."; }
						}
						else { *strErrorMessageToUser = "Castling failed. You cannot castle through check."; }
					}
					else { *strErrorMessageToUser = "You cannot castle while your king is in check."; }
				}
				else { *strErrorMessageToUser = "Castling attempt failed. There are pieces in the way."; }
			}
			else if (blnKingside) { *strErrorMessageToUser = "Castling kingside is not possible. That side's rook has already moved at least once.";}
			else { *strErrorMessageToUser = "Castling queenside is not possible. That side's rook has already moved at least once.";}
		}
		else { *strErrorMessageToUser = "Castling is not possible. Your king has already moved at least once."; }
	}
	else if (blnKingside) { *strErrorMessageToUser = "Castling kingside is not possible. Your pieces are not on the appropriate squares."; }
	else { *strErrorMessageToUser = "Castling queenside is not possible. Your pieces are not on the appropriate squares."; }

	return blnMoveSuccessful;
}