// --------------------------------------------------------------------------------
// Name: Board
// Abstract: Class method definitions
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#include <vector>
#include <string>
#include "Board.h"



// --------------------------------------------------------------------------------
// Name: Board()
// Abstract: Class constructor
// --------------------------------------------------------------------------------
Board::Board()
{
	SetStartingPosition(); // set the board to begin
}



// --------------------------------------------------------------------------------
// Name: SetStartingPosition()
// Abstract: Sets the starting position by giving all indicies of the positions
//			 array values.
// --------------------------------------------------------------------------------
void Board::SetStartingPosition()
{
	// Create and define all pieces

	// Black pieces
	Piece BlackRook1('R', "Rook", 0, false);	 Piece BlackKnight1('N', "Knight", 1, false);	
	Piece BlackBishop1('B', "Bishop", 2, false); Piece BlackQueen('Q', "Queen", 3, false);	
	Piece BlackKing('K', "King", 4, false);		 Piece BlackBishop2('B', "Bishop", 5, false);	
	Piece BlackKnight2('N', "Knight", 6, false); Piece BlackRook2('R', "Rook", 7, false);	
	Piece BlackPawn1('P', "Pawn", 8, false);	 Piece BlackPawn2('P', "Pawn", 9, false);
	Piece BlackPawn3('P', "Pawn", 10, false);	 Piece BlackPawn4('P', "Pawn", 11, false);
	Piece BlackPawn5('P', "Pawn", 12, false);	 Piece BlackPawn6('P', "Pawn", 13, false);
	Piece BlackPawn7('P', "Pawn", 14, false);	 Piece BlackPawn8('P', "Pawn", 15, false);
	
	// White pieces
	Piece WhitePawn1('P', "Pawn", 48, true);	 Piece WhitePawn2('P', "Pawn", 49, true);
	Piece WhitePawn3('P', "Pawn", 50, true);	 Piece WhitePawn4('P', "Pawn", 51, true);
	Piece WhitePawn5('P', "Pawn", 52, true);	 Piece WhitePawn6('P', "Pawn", 53, true);
	Piece WhitePawn7('P', "Pawn", 54, true);	 Piece WhitePawn8('P', "Pawn", 55, true);
	Piece WhiteRook1('R', "Rook", 56, true);	 Piece WhiteKnight1('N', "Knight", 57, true);
	Piece WhiteBishop1('B', "Bishop", 58, true); Piece WhiteQueen('Q', "Queen", 59, true);
	Piece WhiteKing('K', "King", 60, true);		 Piece WhiteBishop2('B', "Bishop", 61, true);
	Piece WhiteKnight2('N', "Knight", 62, true); Piece WhiteRook2('R', "Rook", 63, true);

	Piece EmptySquare('-', "empty square", 16, true);

	// copying pieces to the board vector
	m_vecPositions.push_back(BlackRook1);	m_vecPositions.push_back(BlackKnight1);
	m_vecPositions.push_back(BlackBishop1); m_vecPositions.push_back(BlackQueen);
	m_vecPositions.push_back(BlackKing);	m_vecPositions.push_back(BlackBishop2);
	m_vecPositions.push_back(BlackKnight2); m_vecPositions.push_back(BlackRook2);
	m_vecPositions.push_back(BlackPawn1);	m_vecPositions.push_back(BlackPawn2);
	m_vecPositions.push_back(BlackPawn3);	m_vecPositions.push_back(BlackPawn4);
	m_vecPositions.push_back(BlackPawn5);	m_vecPositions.push_back(BlackPawn6);
	m_vecPositions.push_back(BlackPawn7);	m_vecPositions.push_back(BlackPawn8);

	// empty squares in the middle of the board
	m_vecPositions.push_back(EmptySquare);	m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare);
	m_vecPositions.push_back(EmptySquare);	m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare);
	m_vecPositions.push_back(EmptySquare);	m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare);
	m_vecPositions.push_back(EmptySquare);	m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare);
	m_vecPositions.push_back(EmptySquare);	m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare);
	m_vecPositions.push_back(EmptySquare);	m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare);
	m_vecPositions.push_back(EmptySquare);	m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare);
	m_vecPositions.push_back(EmptySquare);	m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare); m_vecPositions.push_back(EmptySquare);

	// white pieces
	m_vecPositions.push_back(WhitePawn1);	m_vecPositions.push_back(WhitePawn2);
	m_vecPositions.push_back(WhitePawn3);	m_vecPositions.push_back(WhitePawn4);
	m_vecPositions.push_back(WhitePawn5);	m_vecPositions.push_back(WhitePawn6);
	m_vecPositions.push_back(WhitePawn7);	m_vecPositions.push_back(WhitePawn8);
	m_vecPositions.push_back(WhiteRook1);	m_vecPositions.push_back(WhiteKnight1);
	m_vecPositions.push_back(WhiteBishop1); m_vecPositions.push_back(WhiteQueen);
	m_vecPositions.push_back(WhiteKing);	m_vecPositions.push_back(WhiteBishop2);
	m_vecPositions.push_back(WhiteKnight2); m_vecPositions.push_back(WhiteRook2);
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Pawn_Clear
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Pawn_Clear()
{
	string strLine1 = "       ";
	string strLine2 = "   _   ";
	string strLine3 = "  / \\  ";
	string strLine4 = "  \\ /  ";
	string strLine5 = "  | |  ";
	string strLine6 = " /___\\ ";

	static string astrPawn_Clear[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrPawn_Clear;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Pawn_Filled
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Pawn_Filled()
{
	string strLine1 = "       ";
	string strLine2 = "  ##   ";
	string strLine3 = " ####  ";
	string strLine4 = "  ##   ";
	string strLine5 = "  ##   ";
	string strLine6 = " ####  ";

	static string astrPawn_Filled[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrPawn_Filled;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Rook_Clear
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Rook_Clear()
{
	string strLine1 = " _ _ _ ";
	string strLine2 = "|_   _|";
	string strLine3 = " |   | ";
	string strLine4 = " |   | ";
	string strLine5 = " |   | ";
	string strLine6 = "/_____\\";

	static string astrRook_Clear[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrRook_Clear;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Rook_Filled
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Rook_Filled()
{
	string strLine1 = "# ## # ";
	string strLine2 = "###### ";
	string strLine3 = " ####  ";
	string strLine4 = " ####  ";
	string strLine5 = "###### ";
	string strLine6 = "###### ";

	static string astrRook_Filled[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrRook_Filled;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Knight_Clear
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Knight_Clear()
{
	string strLine1 = "  __   ";
	string strLine2 = " /  \\  ";
	string strLine3 = "/   _| ";
	string strLine4 = "\\   \\  ";
	string strLine5 = " |  |  ";
	string strLine6 = "/____\\ ";

	static string astrKnight_Clear[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrKnight_Clear;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Knight_Filled
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Knight_Filled()
{
	string strLine1 = "  ##   ";
	string strLine2 = " ####  ";
	string strLine3 = "###### ";
	string strLine4 = "###    ";
	string strLine5 = " ####  ";
	string strLine6 = "###### ";

	static string astrKnight_Filled[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrKnight_Filled;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Bishop_Clear
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Bishop_Clear()
{
	string strLine1 = "   _   ";
	string strLine2 = "  / \\  ";
	string strLine3 = " /  )\\ ";
	string strLine4 = " \\   / ";
	string strLine5 = "  | |  ";
	string strLine6 = " /___\\ ";

	static string astrBishop_Clear[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrBishop_Clear;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Bishop_Filled
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Bishop_Filled()
{
	string strLine1 = "  ##   ";
	string strLine2 = " ## #  ";
	string strLine3 = "### ## ";
	string strLine4 = " ####  ";
	string strLine5 = " ####  ";
	string strLine6 = "###### ";

	static string astrBishop_Filled[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrBishop_Filled;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Queen_Clear
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Queen_Clear()
{
	string strLine1 = " * * * ";
	string strLine2 = "\\_|_|_/";
	string strLine3 = " |   | ";
	string strLine4 = " \\   / ";
	string strLine5 = " /   \\ ";
	string strLine6 = "/_____\\";

	static string astrQueen_Clear[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrQueen_Clear;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Queen_Filled
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Queen_Filled()
{
	string strLine1 = " * * * ";
	string strLine2 = "## # ##";
	string strLine3 = " ##### ";
	string strLine4 = "  ###  ";
	string strLine5 = " ##### ";
	string strLine6 = "#######";

	static string astrQueen_Filled[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrQueen_Filled;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_King_Clear
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_King_Clear()
{
	string strLine1 = "   +   ";
	string strLine2 = "\\_____/";
	string strLine3 = " /   \\ ";
	string strLine4 = " \\   / ";
	string strLine5 = " |   | ";
	string strLine6 = "/_____\\";

	static string astrKing_Clear[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrKing_Clear;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_King_Filled
// Abstract: Returns pointer to array of strings representing each line of the piece.
// --------------------------------------------------------------------------------
string* Board::GetAscii_King_Filled()
{
	string strLine1 = "#  +  #";
	string strLine2 = "##   ##";
	string strLine3 = " ##### ";
	string strLine4 = " ##### ";
	string strLine5 = " ##### ";
	string strLine6 = "#######";

	static string astrKing_Filled[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrKing_Filled;
}



// --------------------------------------------------------------------------------
// Name: GetAscii_Empty_Square
// Abstract: Returns pointer to array of strings representing each line of the empty square.
// --------------------------------------------------------------------------------
string* Board::GetAscii_Empty_Square()
{
	string strLine1 = "       ";
	string strLine2 = "       ";
	string strLine3 = "       ";
	string strLine4 = "       ";
	string strLine5 = "       ";
	string strLine6 = "       ";

	static string astrKing_Filled[6] = { strLine1, strLine2, strLine3, strLine4, strLine5, strLine6 };

	return astrKing_Filled;
}



// --------------------------------------------------------------------------------
// Name: DisplayBoard_Simple()
// Abstract: Prints the current board to the user. Prints the array Positions, in 
// order, starting a new line after every 8 values printed. Uses each Piece's 
// NotationName to print. Empty squares print as hyphens.
// --------------------------------------------------------------------------------
void Board::DisplayBoard_Simple(bool blnWhiteOrBlackTurn)
{
	int intIndex = 0;
	string strCurrentColorTurn = "";
	int aintRowNames[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	char achrColumnNames[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	char chrPiece = 0;

	cout << endl << endl;

	// print the board
	for (intIndex = 0; intIndex < 64; intIndex++)
	{
		// print the row name
		if (intIndex == 0 || intIndex % 8 == 0)
		{
			cout << '[' << aintRowNames[intIndex / 8] << ']' << "   ";
		}

		// get the piece
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();

		// change to lower case if a black piece
		if (m_vecPositions[intIndex].ReturnPieceColor() == false) { chrPiece += 32; }
		
		// print the piece
		cout << chrPiece << "   ";

		if (intIndex == 7) { cout << endl << endl; } // new line after first row
		if (intIndex > 7) // handling newlines after the first newline
		{
			if ((intIndex - 7) % 8 == 0) { cout << endl << endl; }
		}	
	}
	
	// print the column names
	for (intIndex = 0; intIndex < 8; intIndex++)
	{
		if (intIndex == 0) { cout << "     "; }
		cout << '[' << achrColumnNames[intIndex] << ']' << " ";
	}
	cout << endl << endl;

	// display who's turn it is
	if (blnWhiteOrBlackTurn == true) { strCurrentColorTurn = "White"; }
	else { strCurrentColorTurn = "Black"; }
	cout << endl << strCurrentColorTurn << "'s turn to move." << endl;
}



// --------------------------------------------------------------------------------
// Name: DisplayBoard_Ascii()
// Abstract: Prints the current board to the user using ascii art for the pieces
// --------------------------------------------------------------------------------
void Board::DisplayBoard_Ascii(bool blnWhiteOrBlackTurn)
{
	int intIndex = 0;
	string strCurrentColorTurn = "";
	int aintRowNames[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	char achrColumnNames[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	char chrPiece = 0;
	int intLineNumber = 0;
	int intRow = 0;
	
	cout << "       ______________________________________________________________________________________________________________" << endl;

	for (intIndex; intIndex <= 63; intIndex++)
	{
		if (intIndex % 8 == 0 && intLineNumber == 3) { cout << aintRowNames[intRow] << "     "; intRow += 1; }
		else if ( intIndex % 8 == 0 ) { cout << "      "; }

		if (intIndex % 8 == 0) { cout << "|  "; }

		PrintAsciiLetterLine(intIndex, intLineNumber);
		if ((intIndex - 7) % 8 == 0 && intLineNumber != 6) { cout << endl; intIndex -= 8; intLineNumber++; }
		if ((intIndex - 7) % 8 == 0 && intLineNumber == 6) { intIndex += 8;  intLineNumber++; }
		if (intLineNumber == 7) { cout << "       ______________________________________________________________________________________________________________" << endl; intLineNumber = 0;
		}
	}

	cout << endl;

	for (intIndex = 0; intIndex < 8; intIndex++)
	{
		if (intIndex == 0) { cout << "            "; }
		cout << achrColumnNames[intIndex];
		cout << "             ";
	}

	cout << endl << endl;

	// display who's turn it is
	if (blnWhiteOrBlackTurn == true) { strCurrentColorTurn = "White"; }
	else { strCurrentColorTurn = "Black"; }
	cout << endl << strCurrentColorTurn << "'s turn to move." << endl;
}



// --------------------------------------------------------------------------------
// Name: PrintAsciiLetterLine()
// Abstract: Prints a single line of one of the ascii-drawn pieces. Each piece has
//			 exactly 6 lines tall, and each line is 7 chars wide. Line number is
//			 zero-based.
// --------------------------------------------------------------------------------
void Board::PrintAsciiLetterLine(int intIndex, int intLineNumber)
{
	char chrNotationName = m_vecPositions[intIndex].ReturnNotationName();
	bool blnColor = m_vecPositions[intIndex].ReturnPieceColor();

	switch (chrNotationName)
	{
		// Knight
		case 'N':
			if (blnColor) { cout << m_pstrAscii_Knight_Filled[intLineNumber]; }
			else { cout << m_pstrAscii_Knight_Clear[intLineNumber]; }
			break;

		// Bishop
		case 'B':
			if (blnColor) { cout << m_pstrAscii_Bishop_Filled[intLineNumber]; }
			else { cout << m_pstrAscii_Bishop_Clear[intLineNumber]; }
			break;

		// Rook
		case 'R':
			if (blnColor) { cout << m_pstrAscii_Rook_Filled[intLineNumber]; }
			else { cout << m_pstrAscii_Rook_Clear[intLineNumber]; }
			break;

		// Queen
		case 'Q':
			if (blnColor) { cout << m_pstrAscii_Queen_Filled[intLineNumber]; }
			else { cout << m_pstrAscii_Queen_Clear[intLineNumber]; }
			break;

		// King
		case 'K':
			if (blnColor) { cout << m_pstrAscii_King_Filled[intLineNumber]; }
			else { cout << m_pstrAscii_King_Clear[intLineNumber]; }
			break;

		// Pawn
		case 'P':
			if (blnColor) { cout << m_pstrAscii_Pawn_Filled[intLineNumber]; }
			else { cout << m_pstrAscii_Pawn_Clear[intLineNumber]; }
			break;
	
		// Empty square
		case '-':
			if (blnColor) { cout << m_pstrAscii_Empty_Square[intLineNumber]; }
			else { cout << m_pstrAscii_Empty_Square[intLineNumber]; }
			break;
	}

	cout << "   |   ";
}



// --------------------------------------------------------------------------------
// Name: SwapSquares()
// Abstract: Swaps the contents of two squares (two indecies of the Pieces vector)
//			 This is used when a piece moves to an empty square. Therefore, we
//			 swap the piece with the "empty square piece". This is also used for
//			 castling.
// --------------------------------------------------------------------------------
void Board::SwapSquares(int intPiece1, int intPiece2)
{
	swap(m_vecPositions[intPiece1], m_vecPositions[intPiece2]);
	m_vecPositions[intPiece2].IncrementMoveCount();
}



// --------------------------------------------------------------------------------
// Name: CapturePiece()
// Abstract: Swaps the contents of two squares (two indecies of the Pieces vector)
//			 This is used when a piece moves to an empty square. Therefore, we
//			 swap the piece with the "empty square piece".
// --------------------------------------------------------------------------------
void Board::CapturePiece(int intPiece1, int intPiece2)
{
	Piece EmptySquare('-', "empty square", 16, true); // create blank square blueprint
	swap(m_vecPositions[intPiece1], m_vecPositions[intPiece2]); // swap the start and the destination squares
	m_vecPositions[intPiece1] = EmptySquare; // wipe the starting square to a hypen, because the captured piece will be here
	m_vecPositions[intPiece2].IncrementMoveCount();
}



// --------------------------------------------------------------------------------
// Name: GetPositionIndex()
// Abstract: Takes a 2-character string, representing a square on the chess board,
// and returns the corresponding integer to be used in communication with an
// index in the Positions vector
// --------------------------------------------------------------------------------
int Board::GetPositionIndex(int intColumn, int intRow)
{
	int intIndexPosition = 0;

	// Convert incoming ascii value for Row representation to actual row.
	// Values are flipped across axis between 4 and 5 because the board vector starts at
	// a8, not a1 on the board. Each is lessened by one in order to account for zero-based
	// index numbering of the board vector.
	switch (intRow)
	{
		case 49: intRow = 7; break;
		case 50: intRow = 6; break;
		case 51: intRow = 5; break;
		case 52: intRow = 4; break;
		case 53: intRow = 3; break;
		case 54: intRow = 2; break;
		case 55: intRow = 1; break;
		case 56: intRow = 0; break;
	default:
		intRow = 0; break;
	}
	
	// set the index position based on column and file
	if (intColumn == 'a') { intIndexPosition = 0 + (8 * intRow); }
	else if (intColumn == 'b') { intIndexPosition = 1 + (8 * intRow); }
	else if (intColumn == 'c') { intIndexPosition = 2 + (8 * intRow); }
	else if (intColumn == 'd') { intIndexPosition = 3 + (8 * intRow); }
	else if (intColumn == 'e') { intIndexPosition = 4 + (8 * intRow); }
	else if (intColumn == 'f') { intIndexPosition = 5 + (8 * intRow); }
	else if (intColumn == 'g') { intIndexPosition = 6 + (8 * intRow); }
	else if (intColumn == 'h') { intIndexPosition = 7 + (8 * intRow); }
	else { intIndexPosition = -1; } // -1 so the caller can determine if everything turned out ok

	return intIndexPosition;
}



// --------------------------------------------------------------------------------
// Name: GetPieceIndex()
// Abstract: Retrieves the given piece's location index in the board vector. Piece
// is given only as an ascii value (or char). Returns -1 if piece does not exist.
// -2 if more than one piece of same type can make the move.
// This is partially improperly named--It does check for where the piece is, but
// also must be used to find a destination spot. Enter 0 for intPieceFile and/or
// intPieceRow if these are not supplied by the calling procedure.
// --------------------------------------------------------------------------------
int Board::GetPieceIndex(int intPieceAsciiValue, int intPieceFile, int intPieceRow, int intDesiredPosition, bool blnWhiteOrBlackTurn)
{
	int intIndex = 0;
	int intPieceIndex = -1;
	bool blnMoveIsPossible = false;
	int intColumnIdentifier = 0;

	// if a pawn
	if (intPieceAsciiValue >= 97 && intPieceAsciiValue <= 104)
	{
		// find the 'column identifier' to be used to find the indicies of the given start column
		intColumnIdentifier = intPieceAsciiValue - 97;

		for (intIndex = 0; intIndex < 64; intIndex++)
		{
			if (m_vecPositions[intIndex].ReturnNotationName() == 'P' &&
				m_vecPositions[intIndex].ReturnPieceColor() == blnWhiteOrBlackTurn &&
				(intIndex - intColumnIdentifier) % 8 == 0)
			{
				// check to see if it can make the move
				blnMoveIsPossible = m_vecPositions[intIndex].CheckIfValidMove(intIndex, intDesiredPosition, blnWhiteOrBlackTurn);

				if (blnMoveIsPossible == true) { intPieceIndex = intIndex; }
			}
		}
	}
	// if not a pawn, and no file or row given
	else if(intPieceFile == 0 && intPieceRow == 0)
	{
		for (intIndex = 0; intIndex < 64; intIndex++)
		{
			if (m_vecPositions[intIndex].ReturnNotationName() == intPieceAsciiValue &&
				m_vecPositions[intIndex].ReturnPieceColor() == blnWhiteOrBlackTurn)
			{
				// first, check to see if another piece of same type has already been verified
				// during this For loop to make the move.
				if (blnMoveIsPossible == true &&
					CheckMovePath(intIndex, intDesiredPosition) && m_vecPositions[intIndex].CheckIfValidMove(intIndex, intDesiredPosition, blnWhiteOrBlackTurn))
				{
					intPieceIndex = -2; break; // -2 represents that 2 or more pieces can make the move
				}

				// check to see if it can make the move
				if (CheckMovePath(intIndex, intDesiredPosition) && m_vecPositions[intIndex].CheckIfValidMove(intIndex, intDesiredPosition, blnWhiteOrBlackTurn))
				{
					blnMoveIsPossible = true;
				}
				else { blnMoveIsPossible = false; }

				if (blnMoveIsPossible == true) { intPieceIndex = intIndex; }
			}
		}
	}
	// if not a pawn, and only the file is given
	else if (intPieceFile != 0 && intPieceRow == 0)
	{
		for (intIndex = intPieceFile - 97; intIndex < 64; intIndex += 8)
		{
			if (m_vecPositions[intIndex].ReturnNotationName() == intPieceAsciiValue &&
				m_vecPositions[intIndex].ReturnPieceColor() == blnWhiteOrBlackTurn)
			{
				// first, check to see if another piece of same type has already been verified
				// during this For loop to make the move.
				if (blnMoveIsPossible == true &&
					m_vecPositions[intIndex].CheckIfValidMove(intIndex, intDesiredPosition, blnWhiteOrBlackTurn) == true)
				{
					intPieceIndex = -2; break; // -2 represents that 2 or more pieces can make the move
				}

				// check to see if it can make the move
				blnMoveIsPossible = m_vecPositions[intIndex].CheckIfValidMove(intIndex, intDesiredPosition, blnWhiteOrBlackTurn);

				if (blnMoveIsPossible == true) { intPieceIndex = intIndex; }
			}
		}
	}
	// if not a pawn, and only the row is given
	else if (intPieceFile == 0 && intPieceRow != 0)
	{
		int intStartIndex = 0;

		if (intPieceRow == 8) { intStartIndex = 0; }
		else if (intPieceRow == 7) { intStartIndex = 8; }
		else if (intPieceRow == 6) { intStartIndex = 16; }
		else if (intPieceRow == 5) { intStartIndex = 24; }
		else if (intPieceRow == 4) { intStartIndex = 32; }
		else if (intPieceRow == 3) { intStartIndex = 40; }
		else if (intPieceRow == 2) { intStartIndex = 48; }
		else if (intPieceRow == 1) { intStartIndex = 56; }

		for (intIndex = intStartIndex; intIndex < intStartIndex + 8; intIndex++)
		{
			if (m_vecPositions[intIndex].ReturnNotationName() == intPieceAsciiValue &&
				m_vecPositions[intIndex].ReturnPieceColor() == blnWhiteOrBlackTurn)
			{
				// first, check to see if another piece of same type has already been verified
				// during this For loop to make the move.
				if (blnMoveIsPossible == true &&
					m_vecPositions[intIndex].CheckIfValidMove(intIndex, intDesiredPosition, blnWhiteOrBlackTurn) == true)
				{
					intPieceIndex = -2; break; // -2 represents that 2 or more pieces can make the move
				}

				// check to see if it can make the move
				blnMoveIsPossible = m_vecPositions[intIndex].CheckIfValidMove(intIndex, intDesiredPosition, blnWhiteOrBlackTurn);

				if (blnMoveIsPossible == true) { intPieceIndex = intIndex; }
			}
		}
	}
	// if not a pawn, and both row and file are given
	else if (intPieceFile != 0 && intPieceRow != 0)
	{
		intIndex = GetPositionIndex(intPieceFile, intPieceRow);

		if (m_vecPositions[intIndex].ReturnNotationName() == intPieceAsciiValue &&
			m_vecPositions[intIndex].ReturnPieceColor() == blnWhiteOrBlackTurn)
		{
			// check to see if it can make the move
			blnMoveIsPossible = m_vecPositions[intIndex].CheckIfValidMove(intIndex, intDesiredPosition, blnWhiteOrBlackTurn);

			if (blnMoveIsPossible == true) { intPieceIndex = intIndex; }
		}
	}

	return intPieceIndex;
}



// --------------------------------------------------------------------------------
// Name: GetNotationName()
// Abstract: Retrieves the notation name of the piece at the given square on the
// board.
// --------------------------------------------------------------------------------
char Board::GetNotationName(int intSquareIndex)
{
	char chrNotationName = 0;
	
	chrNotationName = m_vecPositions[intSquareIndex].ReturnNotationName();

	return chrNotationName;
}



// --------------------------------------------------------------------------------
// Name: GetPieceColor()
// Abstract: Retrieves the color of the piece at the given square on the board.
// --------------------------------------------------------------------------------
bool Board::GetPieceColor(int intSquareIndex)
{
	bool blnWhiteOrBlack = true;

	blnWhiteOrBlack = m_vecPositions[intSquareIndex].ReturnPieceColor();

	return blnWhiteOrBlack;
}



// --------------------------------------------------------------------------------
// Name: CheckMovePath()
// Abstract: Checks if there are any pieces in the way from start index to
// destination index.
// --------------------------------------------------------------------------------
bool Board::CheckMovePath(int intPieceStartIndex, int intDestinationIndex)
{
	bool blnMovePathIsClear = false;

	int intStartToDestinationDifference = 0;
	int intMoveIncrement = 0; // This number will basically say if the move is diagonal or orthogonal.
	int intIndex = 0;

	intStartToDestinationDifference = intPieceStartIndex - intDestinationIndex;

	// only need to check the move path if moving piece is not a knight
	if (m_vecPositions[intPieceStartIndex].ReturnNotationName() != 'N')
	{
		// checks for left-to-right movement
		if (intStartToDestinationDifference >= -7 && intStartToDestinationDifference <= 7)
		{
			intMoveIncrement = 1;
			blnMovePathIsClear = true;
		}

		// checks for up-and-down and diagonal movement (finds the move increment for the board array)
		if (intStartToDestinationDifference % 7 == 0) { intMoveIncrement = 7; blnMovePathIsClear = true; } // northeast/southwest
		else if (intStartToDestinationDifference % 9 == 0) { intMoveIncrement = 9; blnMovePathIsClear = true; } // northwest/southeast
		else if (intStartToDestinationDifference % 8 == 0) { intMoveIncrement = 8; blnMovePathIsClear = true; } // up/down

		// continue if movement type check has passed
		if (blnMovePathIsClear == true)
		{
			// correct the increment to negative if needed, to ensure full correct direction
			if (intStartToDestinationDifference > 0) { intMoveIncrement = -intMoveIncrement; }

			// increment through each move towards the destination, and check for a piece on each square
			for (intIndex = intPieceStartIndex + intMoveIncrement; intIndex != intDestinationIndex; intIndex += intMoveIncrement)
			{
				// if the currently iterated square is not clear, then return false
				if (m_vecPositions[intIndex].ReturnNotationName() != '-')
				{
					blnMovePathIsClear = false;
					break;
				}
			}
		}
	}
	else { blnMovePathIsClear = true; }

	return blnMovePathIsClear;
}



// --------------------------------------------------------------------------------
// Name: IsKingInCheck()
// Abstract: Takes hypothetical position of a king, and uses the current board
// position to see if a king on the given square would be in check 
// --------------------------------------------------------------------------------
bool Board::IsKingInCheck(bool blnWhiteOrBlackTurn, int intPosition)
{
	int intIndex;
	char chrPiece;

	bool IsInCheck = false;

	// check horizontal pathway, left, until a piece is hit --------------------------------------------------------------------------
	intIndex = intPosition;
	while (intIndex % 8 != 0)
	{
		intIndex -= 1;
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();
		if (chrPiece != '-')
		{
			// Because we've found a piece that is directly in a line with the king,
			// we see if it is threatening the king based on how the piece moves.

			// check if it is the opponent's piece
			if (m_vecPositions[intIndex].ReturnPieceColor() == !blnWhiteOrBlackTurn)
			{
				if (chrPiece == 'Q' || chrPiece == 'R')
				{
					IsInCheck = true;
					break;
				}
				else { break; }
			}
			else { break; }
		}
	}

	// check horizontal pathway, right, until a piece is hit --------------------------------------------------------------------------
	intIndex = intPosition;
	while ((intIndex - 7) % 8 != 0)
	{
		intIndex += 1;
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();
		if (chrPiece != '-')
		{
			// Because we've found a piece that is directly in a line with the king,
			// we see if it is threatening the king based on how the piece moves.

			// check if it is the opponent's piece
			if (m_vecPositions[intIndex].ReturnPieceColor() == !blnWhiteOrBlackTurn)
			{
				if (chrPiece == 'Q' || chrPiece == 'R')
				{
					IsInCheck = true;
					break;
				}
				else { break; }
			}
			else { break; }
		}
	}

	// check vertical pathway, up, until a piece is hit -------------------------------------------------------------------------------
	intIndex = intPosition;
	while (intIndex > 7)
	{
		intIndex -= 8;
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();
		if (chrPiece != '-')
		{
			// Because we've found a piece that is directly in a line with the king,
			// we see if it is threatening the king based on how the piece moves.

			// check if it is the opponent's piece
			if (m_vecPositions[intIndex].ReturnPieceColor() == !blnWhiteOrBlackTurn)
			{
				if (chrPiece == 'Q' || chrPiece == 'R')
				{
					IsInCheck = true;
					break;
				}
				else { break; }
			}
			else { break; }
		}
	}

	// check vertical pathway, down, until a piece is hit -----------------------------------------------------------------------------
	intIndex = intPosition;
	while (intIndex < 56)
	{
		intIndex += 8;
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();
		if (chrPiece != '-')
		{
			// Because we've found a piece that is directly in a line with the king,
			// we see if it is threatening the king based on how the piece moves.

			// check if it is the opponent's piece
			if (m_vecPositions[intIndex].ReturnPieceColor() == !blnWhiteOrBlackTurn)
			{
				if (chrPiece == 'Q' || chrPiece == 'R')
				{
					IsInCheck = true;
					break;
				}
				else { break; }
			}
			else { break; }
		}
	}

	// check diagonal pathway, northwest, until a piece is hit ------------------------------------------------------------------------
	intIndex = intPosition;
	while (intIndex % 8 != 0 && intIndex > 7)
	{
		intIndex -= 9;
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();
		if (chrPiece != '-')
		{
			// Because we've found a piece that is directly in a line with the king,
			// we see if it is threatening the king based on how the piece moves.

			// check if it is the opponent's piece
			if (m_vecPositions[intIndex].ReturnPieceColor() == !blnWhiteOrBlackTurn)
			{
				// from this direction, attacking pawn must be black
				if (chrPiece == 'P' && intIndex == intPosition - 9 && !blnWhiteOrBlackTurn == false)
				{
					IsInCheck = true;
					break;
				}

				if (chrPiece == 'Q' || chrPiece == 'B')
				{
					IsInCheck = true;
					break;
				}
				else { break; }
			}
			else { break; }
		}
	}

	// check diagonal pathway, southwest, until a piece is hit ------------------------------------------------------------------------
	intIndex = intPosition;
	while (intIndex % 8 != 0 && intIndex < 56)
	{
		intIndex += 7;
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();
		if (chrPiece != '-')
		{
			// Because we've found a piece that is directly in a line with the king,
			// we see if it is threatening the king based on how the piece moves.

			// check if it is the opponent's piece
			if (m_vecPositions[intIndex].ReturnPieceColor() == !blnWhiteOrBlackTurn)
			{
				// from this direction, attacking pawn must be white
				if (chrPiece == 'P' && intIndex == intPosition + 7 && !blnWhiteOrBlackTurn == true)
				{
					IsInCheck = true;
					break;
				}

				if (chrPiece == 'Q' || chrPiece == 'B')
				{
					IsInCheck = true;
					break;
				}
				else { break; }
			}
			else { break; }
		}
	}

	// check diagonal pathway, southeast, until a piece is hit ------------------------------------------------------------------------
	intIndex = intPosition;
	while ((intIndex - 7) % 8 != 0 && intIndex < 56)
	{
		intIndex += 9;
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();
		if (chrPiece != '-')
		{
			// Because we've found a piece that is directly in a line with the king,
			// we see if it is threatening the king based on how the piece moves.

			// check if it is the opponent's piece
			if (m_vecPositions[intIndex].ReturnPieceColor() == !blnWhiteOrBlackTurn)
			{
				// from this direction, attacking pawn must be white
				if (chrPiece == 'P' && intIndex == intPosition + 9 && !blnWhiteOrBlackTurn == true)
				{
					IsInCheck = true;
					break;
				}

				if (chrPiece == 'Q' || chrPiece == 'B')
				{
					IsInCheck = true;
					break;
				}
				else { break; }
			}
			else { break; }
		}
	}

	// check diagonal pathway, northeast, until a piece is hit ------------------------------------------------------------------------
	intIndex = intPosition;
	while ((intIndex - 7) % 8 != 0 && intIndex > 7)
	{
		intIndex -= 7;
		chrPiece = m_vecPositions[intIndex].ReturnNotationName();
		if (chrPiece != '-')
		{
			// Because we've found a piece that is directly in a line with the king,
			// we see if it is threatening the king based on how the piece moves.

			// check if it is the opponent's piece
			if (m_vecPositions[intIndex].ReturnPieceColor() == !blnWhiteOrBlackTurn)
			{
				// from this direction, attacking pawn must be black
				if (chrPiece == 'P' && intIndex == intPosition - 7 && !blnWhiteOrBlackTurn == false)
				{
					IsInCheck = true;
					break;
				}

				if (chrPiece == 'Q' || chrPiece == 'B')
				{
					IsInCheck = true;
					break;
				}
				else { break; }
			}
			else { break; }
		}
	}


	// check for attacking Knights ---------------------------------------------------------------------------------------------
	if (IsInCheck == false) // only check for check-by-knight if checks for all other types of pieces turns up false
	{
		// Here are the 'L' patterns that should be seen as emitting from the center of the graph. Consider the king's position to be the center,
		// and a potential knight to be at the end of each 'L' pattern.
		//  
		//   A_____B
		//  H	|   C
		//  |___|___|
		//  |	|   |
		//  G __|__ D
		//    F   E

		intIndex = intPosition;
		int intA = intPosition - 17;
		int intB = intPosition - 15;
		int intC = intPosition - 6;
		int intD = intPosition + 10;
		int intE = intPosition + 17;
		int intF = intPosition + 15;
		int intG = intPosition + 6;
		int intH = intPosition - 10;

		if (intPosition == 0) // if starting in file 'a' and row 8
		{
			int aintDirections[2] = { intD, intE };
			IsInCheck = CheckKnightPatternArray(aintDirections, 2, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 8)// if starting in file 'a' and row 7
		{
			int aintDirections[3] = { intD, intE, intC };
			IsInCheck = CheckKnightPatternArray(aintDirections, 3, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 48) // if starting in file 'a' and row 2
		{
			int aintDirections[3] = { intB, intC, intD };
			IsInCheck = CheckKnightPatternArray(aintDirections, 3, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 56) // if starting in file 'a' and row 1
		{
			int aintDirections[2] = { intB, intC };
			IsInCheck = CheckKnightPatternArray(aintDirections, 2, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 1) // if starting in file 'b' and row 8
		{
			int aintDirections[3] = { intE, intF, intD };
			IsInCheck = CheckKnightPatternArray(aintDirections, 3, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 9) // if starting in file 'b' and row 7
		{
			int aintDirections[4] = { intE, intF, intD, intC };
			IsInCheck = CheckKnightPatternArray(aintDirections, 4, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 49) // if starting in file 'b' and row 2
		{
			int aintDirections[4] = { intA, intB, intD, intC };
			IsInCheck = CheckKnightPatternArray(aintDirections, 4, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 57) // if starting in file 'b' and row 1
		{
			int aintDirections[3] = { intA, intB, intC };
			IsInCheck = CheckKnightPatternArray(aintDirections, 3, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 6) // if starting in file 'g' and row 8
		{
			int aintDirections[3] = { intE, intF, intG };
			IsInCheck = CheckKnightPatternArray(aintDirections, 3, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 14) // if starting in file 'g' and row 7
		{
			int aintDirections[4] = { intE, intF, intG, intH };
			IsInCheck = CheckKnightPatternArray(aintDirections, 4, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 54) // if starting in file 'g' and row 2
		{
			int aintDirections[4] = { intA, intB, intG, intH };
			IsInCheck = CheckKnightPatternArray(aintDirections, 4, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 62) // if starting in file 'g' and row 1
		{
			int aintDirections[3] = { intA, intB, intH };
			IsInCheck = CheckKnightPatternArray(aintDirections, 3, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 7) // if starting in file 'h' and row 8
		{
			int aintDirections[2] = { intG, intF };
			IsInCheck = CheckKnightPatternArray(aintDirections, 2, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 15) // if starting in file 'h' and row 7
		{
			int aintDirections[3] = { intG, intF, intH };
			IsInCheck = CheckKnightPatternArray(aintDirections, 3, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 55) // if starting in file 'h' and row 2
		{
			int aintDirections[3] = { intG, intA, intH };
			IsInCheck = CheckKnightPatternArray(aintDirections, 3, blnWhiteOrBlackTurn);
		}
		else if (intPosition == 63) // if starting in file 'h' and row 1
		{
			int aintDirections[2] = { intH, intA };
			IsInCheck = CheckKnightPatternArray(aintDirections, 2, blnWhiteOrBlackTurn);
		}
		else if (intPosition >= 0 && intPosition <= 7) // if starting in row 8, and not limited by right or left edge
		{
			int aintDirections[4] = { intG, intD, intF, intE };
			IsInCheck = CheckKnightPatternArray(aintDirections, 4, blnWhiteOrBlackTurn);
		}
		else if (intPosition >= 8 && intPosition <= 15) // if starting in row 7, and not limited by right or left edge
		{
			int aintDirections[6] = { intG, intD, intF, intE, intC, intH };
			IsInCheck = CheckKnightPatternArray(aintDirections, 6, blnWhiteOrBlackTurn);
		}
		else if (intPosition >= 48 && intPosition <= 55) // if starting in row 2, and not limited by right or left edge
		{
			int aintDirections[6] = { intC, intH, intB, intA, intG, (intPosition + 10) };
			IsInCheck = CheckKnightPatternArray(aintDirections, 6, blnWhiteOrBlackTurn);
		}
		else if (intPosition >= 56 && intPosition <= 63) // if starting in row 1, and not limited by right or left edge
		{
			int aintDirections[4] = { intC, intH, intB, intA };
			IsInCheck = CheckKnightPatternArray(aintDirections, 4, blnWhiteOrBlackTurn);
		}
		else if (intPosition % 8 == 0) // if starting in file 'a' and not limited by top or bottom edge
		{
			int aintDirections[4] = { intE, intB, intC, intD };
			IsInCheck = CheckKnightPatternArray(aintDirections, 4, blnWhiteOrBlackTurn);
		}
		else if ((intPosition - 1) % 8 == 0) // if starting in file 'b' and not limited by top or bottom edge
		{
			int aintDirections[6] = { intE, intB, intC, intD, intA, intF };
			IsInCheck = CheckKnightPatternArray(aintDirections, 6, blnWhiteOrBlackTurn);
		}
		else if ((intPosition - 6) % 8 == 0) // if starting in file 'g' and not limited by top or bottom edge
		{
			int aintDirections[6] = { intE, intB, intG, intH, intA, intF };
			IsInCheck = CheckKnightPatternArray(aintDirections, 6, blnWhiteOrBlackTurn);
		}
		else if ((intPosition - 7) % 8 == 0) // if starting in file 'h' and not limited by top or bottom edge
		{
			int aintDirections[4] = { intA, intF, intG, intH };
			IsInCheck = CheckKnightPatternArray(aintDirections, 4, blnWhiteOrBlackTurn);
		}
		else
		{
			// As default, from the king's point of view, set all 8 squares for checking for a knight's check.
			int aintDirections[8] = { intA, intB, intC, intD, intE, intF, intG, intH };
			IsInCheck = CheckKnightPatternArray(aintDirections, 8, blnWhiteOrBlackTurn);
		}
	}

	return IsInCheck;
}



// --------------------------------------------------------------------------------
// Name: CheckKnightPatternArray()
// Abstract: Checks all values in the given array against the board position,
//			 and returns true if an opposing knight piece is found on the board
//			 position that the value represents.
// --------------------------------------------------------------------------------
bool Board::CheckKnightPatternArray(int aintDirections[], int intArraySize, bool blnWhiteOrBlackTurn)
{
	bool blnIsInCheck = false;
	int intIndex = 0;

	for (intIndex = 0; intIndex < intArraySize; intIndex++)
	{
		if (m_vecPositions[aintDirections[intIndex]].ReturnNotationName() == 'N'
			&& m_vecPositions[aintDirections[intIndex]].ReturnPieceColor() == !blnWhiteOrBlackTurn)
		{
			blnIsInCheck = true;
			return blnIsInCheck;
		}
	}

	return blnIsInCheck;
}



// --------------------------------------------------------------------------------
// Name: GetKingIndex()
// Abstract: Finds the index of the current player's king. Returns -1 if no king
// is found, but this should not happen.
// --------------------------------------------------------------------------------
int Board::GetKingIndex(bool blnWhiteOrBlackTurn)
{
	int intKingIndex = -1;
	int intIndex = 0;
	char chrNotationName;
	bool blnWhiteOrBlack;

	for (intIndex = 0; intIndex <= 63; intIndex++)
	{
		chrNotationName = m_vecPositions[intIndex].ReturnNotationName();
		blnWhiteOrBlack = m_vecPositions[intIndex].ReturnPieceColor();
		if (chrNotationName == 'K' && blnWhiteOrBlack == blnWhiteOrBlackTurn)
		{
			intKingIndex = intIndex;
			break;
		}
	}

	return intKingIndex;
}