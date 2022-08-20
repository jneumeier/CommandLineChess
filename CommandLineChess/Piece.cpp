// --------------------------------------------------------------------------------
// Name: Piece
// Abstract: Class method definitions
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#include <vector>
#include "Piece.h"


// --------------------------------------------------------------------------------
// Name: Piece()
// Abstract: Class constructor
// --------------------------------------------------------------------------------
Piece::Piece()
{
	m_chrNotationName = '-';
	m_strFullName = "blank";
	m_intPosition = 0;
	m_blnWhiteOrBlack = false;
	m_intMoveCount = 0;
}


// --------------------------------------------------------------------------------
// Name: Piece()
// Abstract: Class constructor
// --------------------------------------------------------------------------------
Piece::Piece(char chrNotationName, string strFullName, int intPosition, bool blnWhiteOrBlack)
{
	m_chrNotationName = chrNotationName;
	m_strFullName = strFullName;
	m_intPosition = intPosition;
	m_blnWhiteOrBlack = blnWhiteOrBlack;
	m_intMoveCount = 0;
}


// --------------------------------------------------------------------------------
// Name: ReturnNotationName()
// Abstract: Returns the notation name of the Piece
// --------------------------------------------------------------------------------
char Piece::ReturnNotationName()
{
	return m_chrNotationName;
}

// --------------------------------------------------------------------------------
// Name: ReturnPieceColor()
// Abstract: Returns the color of the Piece as boolean. White/true. Black/false.
// --------------------------------------------------------------------------------
bool Piece::ReturnPieceColor()
{
	return m_blnWhiteOrBlack;
}


// --------------------------------------------------------------------------------
// Name: ReturnMoveCount()
// Abstract: Returns the number of times the piece has moved
// --------------------------------------------------------------------------------
int Piece::ReturnMoveCount()
{
	return m_intMoveCount;
}


// --------------------------------------------------------------------------------
// Name: IncrementMoveCount()
// Abstract: Increments by one, the number of times the piece has moved
// --------------------------------------------------------------------------------
void Piece::IncrementMoveCount()
{
	m_intMoveCount += 1;
}


// --------------------------------------------------------------------------------
// Name: Move()
// Abstract: Moves the piece
// --------------------------------------------------------------------------------
bool Piece::Move(int intTargetPosition)
{
	bool blnValidMove = false;

	// since a generic piece, let it move anywhere on the board (for testing, really)
	if (intTargetPosition >= 0 && intTargetPosition <= 63)
	{
		UpdatePosition(intTargetPosition);

		blnValidMove = true;
	}

	return blnValidMove;
}

// --------------------------------------------------------------------------------
// Name: UpdatePosition()
// Abstract: Updates the intPosition parameter of the Piece
// --------------------------------------------------------------------------------
void Piece::UpdatePosition(int intTargetPosition)
{
	m_intPosition = intTargetPosition;
}

// --------------------------------------------------------------------------------
// Name: CheckIfValidMove()
// Abstract: Checks if the proposed move is valid, only in terms of direction,
// and returns true if so.
// --------------------------------------------------------------------------------
bool Piece::CheckIfValidMove(int intCurrentPosition, int intDesiredPosition, bool blnWhiteOrBlackMove)
{
	bool blnValidMove = false;

	switch (ReturnNotationName())
	{
		// Knight
		case 'N':
			blnValidMove = CheckMovement_Knight(intCurrentPosition, intDesiredPosition, blnWhiteOrBlackMove);
			break;

		// Bishop
		case 'B':
			blnValidMove = CheckMovement_Bishop(intCurrentPosition, intDesiredPosition);
			break;

		// Rook
		case 'R':
			blnValidMove = CheckMovement_Rook(intCurrentPosition, intDesiredPosition);
			break;

		// Queen
		case 'Q':
			blnValidMove = CheckMovement_Rook(intCurrentPosition, intDesiredPosition);
			if (blnValidMove == false)
			{
				blnValidMove = CheckMovement_Bishop(intCurrentPosition, intDesiredPosition);
			}
			break;
		
		// King
		case 'K':
			blnValidMove = CheckMovement_King(intCurrentPosition, intDesiredPosition);
			break;

		// Pawn
		case 'P':
			blnValidMove = CheckMovement_Pawn(intCurrentPosition, intDesiredPosition, blnWhiteOrBlackMove);
			break;
	}

	return blnValidMove;
}


// --------------------------------------------------------------------------------
// Name: CheckMovement_Knight()
// Abstract: Checks if knight move is valid, and returns true if so.
// --------------------------------------------------------------------------------
bool Piece::CheckMovement_Knight(int intCurrentPosition, int intDesiredPosition, bool blnWhiteOrBlackMove)
{
	bool blnValidMove = false;

	// check all eight general landing possibilites

			// two up, one left
	if (intCurrentPosition - intDesiredPosition == 17) { blnValidMove = true; }
	// two up, one right
	else if (intCurrentPosition - intDesiredPosition == 15) { blnValidMove = true; }
	// two right, one up
	else if (intCurrentPosition - intDesiredPosition == 6) { blnValidMove = true; }
	// two right, one down
	else if (intCurrentPosition - intDesiredPosition == -10) { blnValidMove = true; }
	// down two, one right
	else if (intCurrentPosition - intDesiredPosition == -15) { blnValidMove = true; }
	// down two, one left
	else if (intCurrentPosition - intDesiredPosition == -17) { blnValidMove = true; }
	// two left, one down
	else if (intCurrentPosition - intDesiredPosition == -6) { blnValidMove = true; }
	// two left, one up
	else if (intCurrentPosition - intDesiredPosition == 10) { blnValidMove = true; }
	// not in any possible landing spot in relation to starting point
	else { blnValidMove = false; return blnValidMove; }


	// check if they are possible, given that the Knight is near a border

	// if starting in file 'a'
	if (intCurrentPosition % 8 == 0 || intCurrentPosition == 0)
	{
		// two up, one left
		if (intCurrentPosition - intDesiredPosition == 17) { blnValidMove = false; }
		// two down, one left
		else if (intCurrentPosition - intDesiredPosition == -15) { blnValidMove = false; }
		// one up, two left
		else if (intCurrentPosition - intDesiredPosition == 10) { blnValidMove = false; }
		// one down, two left
		else if (intCurrentPosition - intDesiredPosition == -6) { blnValidMove = false; }
		// else, valid move
		else
		{ 
			
			blnValidMove = true;
		}
	}
	// if starting in file 'h'
	if ((intCurrentPosition - 7) % 8 == 0 || intCurrentPosition == 7)
	{
		// two up, one right
		if (intCurrentPosition - intDesiredPosition == 15) { blnValidMove = false; }
		// two down, one right
		else if (intCurrentPosition - intDesiredPosition == -17) { blnValidMove = false; }
		// one up, two right
		else if (intCurrentPosition - intDesiredPosition == 6) { blnValidMove = false; }
		// one down, two right
		else if (intCurrentPosition - intDesiredPosition == -10) { blnValidMove = false; }
		// else, valid move
		else { blnValidMove = true; }
	}
	// if starting in row 8
	if (intCurrentPosition >= 0 && intCurrentPosition <= 7)
	{
		// up one, two right
		if (intCurrentPosition - intDesiredPosition == 10) { blnValidMove = false; }
		// up two, one right
		else if (intCurrentPosition - intDesiredPosition == 17) { blnValidMove = false; }
		// up two, one left
		else if (intCurrentPosition - intDesiredPosition == 15) { blnValidMove = false; }
		// up one, two left
		else if (intCurrentPosition - intDesiredPosition == 6) { blnValidMove = false; }
		// else, valid move
		else { blnValidMove = true; }
	}
	// if starting in row 1
	if (intCurrentPosition >= 56 && intCurrentPosition <= 63)
	{
		// down one, two right
		if (intCurrentPosition - intDesiredPosition == -6) { blnValidMove = false; }
		// down two, one right
		else if (intCurrentPosition - intDesiredPosition == -15) { blnValidMove = false; }
		// down two, one left
		else if (intCurrentPosition - intDesiredPosition == -17) { blnValidMove = false; }
		// down one, two left
		else if (intCurrentPosition - intDesiredPosition == -10) { blnValidMove = false; }
		// else, valid move
		else { blnValidMove = true; }
	}
	// if starting in file 'b'
	if ((intCurrentPosition - 1) % 8 == 0 || intCurrentPosition == 1)
	{
		// one up, two left
		if (intCurrentPosition - intDesiredPosition == 10) { blnValidMove = false; }
		// one down, two left
		else if (intCurrentPosition - intDesiredPosition == -6) { blnValidMove = false; }
		// else, valid move
		else { blnValidMove = true; }
	}
	// if starting in file 'g'
	if ((intCurrentPosition - 6) % 8 == 0 || intCurrentPosition == 6)
	{
		// one up, two right
		if (intCurrentPosition - intDesiredPosition == 6) { blnValidMove = false; }
		// one down, two right
		else if (intCurrentPosition - intDesiredPosition == -10) { blnValidMove = false; }
		// else, valid move
		else { blnValidMove = true; }
	}
	// if starting in row 7
	if (intCurrentPosition >= 8 && intCurrentPosition <= 15)
	{
		// up two, one right
		if (intCurrentPosition - intDesiredPosition == 17) { blnValidMove = false; }
		// up two, one left
		else if (intCurrentPosition - intDesiredPosition == 15) { blnValidMove = false; }
		// else, valid move
		else { blnValidMove = true; }
	}
	// if starting in row 2
	if (intCurrentPosition >= 48 && intCurrentPosition <= 55)
	{
		// down two, one right
		if (intCurrentPosition - intDesiredPosition == -15) { blnValidMove = false; }
		// down two, one left
		else if (intCurrentPosition - intDesiredPosition == -17) { blnValidMove = false; }
		// else, valid move
		else { blnValidMove = true; }
	}

	return blnValidMove;
}


// --------------------------------------------------------------------------------
// Name: CheckMovement_Bishop()
// Abstract: Checks if bishop move is valid, and returns true if so.
// --------------------------------------------------------------------------------
bool Piece::CheckMovement_Bishop(int intCurrentPosition, int intDesiredPosition)
{
	bool blnValidMove = false;

	// create a stepper so we can check where the bishop is at for each square it passes through
	int intSteppingPosition = intCurrentPosition;

	// southeast movement
	if ((intDesiredPosition - intCurrentPosition) % 9 == 0 && intDesiredPosition - intCurrentPosition > 0)
	{
		// step through each individual square-move so we can check if the piece is
		// in a column or file that may prevent further diagonal movement
		for (intSteppingPosition = intCurrentPosition;
			intSteppingPosition <= intDesiredPosition;
			intSteppingPosition += 9)
		{
			// if stepper is in file 'h'
			if ((intSteppingPosition - 7) % 8 == 0 || intSteppingPosition == 7)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			// if stepper is in row '1'
			if (intSteppingPosition >= 56 && intSteppingPosition <= 63)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			if (intSteppingPosition == intDesiredPosition) { blnValidMove = true; break; }
		}
	}

	// southwest movement
	if ((intDesiredPosition - intCurrentPosition) % 7 == 0 && intDesiredPosition - intCurrentPosition > 0)
	{
		// step through each individual square-move so we can check if the piece is
		// in a column or file that may prevent further diagonal movement
		for (intSteppingPosition = intCurrentPosition;
			intSteppingPosition <= intDesiredPosition;
			intSteppingPosition += 7)
		{
			// if stepper is in file 'a'
			if (intSteppingPosition % 8 == 0 || intSteppingPosition == 0)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			// if stepper is in row '1'
			if (intSteppingPosition >= 56 && intSteppingPosition <= 63)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			if (intSteppingPosition == intDesiredPosition) { blnValidMove = true; break; }
		}
	}

	// northwest movement
	if ((intCurrentPosition - intDesiredPosition) % 9 == 0 && intCurrentPosition - intDesiredPosition > 0)
	{
		// step through each individual square-move so we can check if the piece is
		// in a column or file that may prevent further diagonal movement
		for (intSteppingPosition = intCurrentPosition;
			intSteppingPosition >= intDesiredPosition;
			intSteppingPosition -= 9)
		{
			// if stepper is in file 'a'
			if (intSteppingPosition % 8 == 0 || intSteppingPosition == 0)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			// if stepper is in row '8'
			if (intSteppingPosition >= 0 && intSteppingPosition <= 7)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			if (intSteppingPosition == intDesiredPosition) { blnValidMove = true; break; }
		}
	}

	// northeast movement
	if ((intCurrentPosition - intDesiredPosition) % 7 == 0 && intCurrentPosition - intDesiredPosition > 0)
	{
		// step through each individual square-move so we can check if the piece is
		// in a column or file that may prevent further diagonal movement
		for (intSteppingPosition = intCurrentPosition;
			intSteppingPosition >= intDesiredPosition;
			intSteppingPosition -= 7)
		{
			// if stepper is in file 'h'
			if ((intSteppingPosition - 7) % 8 == 0 || intSteppingPosition == 7)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			// if stepper is in row '8'
			if (intSteppingPosition >= 0 && intSteppingPosition <= 7)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			if (intSteppingPosition == intDesiredPosition) { blnValidMove = true; break; }
		}
	}

	return blnValidMove;
}


// --------------------------------------------------------------------------------
// Name: CheckMovement_Rook()
// Abstract: Checks if rook move is valid, and returns true if so.
// --------------------------------------------------------------------------------
bool Piece::CheckMovement_Rook(int intCurrentPosition, int intDesiredPosition)
{
	bool blnValidMove = false;

	// create a stepper so we can check where the rook is at for each square it passes through
	int intSteppingPosition = intCurrentPosition;

	// right movement
	if (intDesiredPosition - intCurrentPosition <= 7 
		&& intDesiredPosition - intCurrentPosition > 0)
	{
		// step through each individual square-move so we can check if the piece is
		// in a column or file that may prevent further movement
		for (intSteppingPosition = intCurrentPosition;
			intSteppingPosition <= intDesiredPosition;
			intSteppingPosition += 1)
		{
			// if stepper is in file 'h'
			if ((intSteppingPosition - 7) % 8 == 0 || intSteppingPosition == 7)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			if (intSteppingPosition == intDesiredPosition) { blnValidMove = true; break; }
		}
	}

	// left movement
	if (intCurrentPosition - intDesiredPosition <= 7 
		&& intCurrentPosition - intDesiredPosition > 0)
	{
		// step through each individual square-move so we can check if the piece is
		// in a column or file that may prevent further movement
		for (intSteppingPosition = intCurrentPosition;
			intSteppingPosition >= intDesiredPosition;
			intSteppingPosition -= 1)
		{
			// if stepper is in file 'a'
			if (intSteppingPosition % 8 == 0 || intSteppingPosition == 0)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			if (intSteppingPosition == intDesiredPosition) { blnValidMove = true; break; }
		}
	}

	// up movement
	if ((intCurrentPosition - intDesiredPosition) % 8 == 0
		&& intCurrentPosition - intDesiredPosition > 0)
	{
		// step through each individual square-move so we can check if the piece is
		// in a column or file that may prevent further movement
		for (intSteppingPosition = intCurrentPosition;
			intSteppingPosition >= intDesiredPosition;
			intSteppingPosition -= 8)
		{
			// if stepper is in row '8'
			if (intSteppingPosition >= 0 && intSteppingPosition <= 7)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			if (intSteppingPosition == intDesiredPosition) { blnValidMove = true; break; }
		}
	}

	// down movement
	if ((intDesiredPosition - intCurrentPosition) % 8 == 0 
		&& intDesiredPosition - intCurrentPosition > 0)
	{
		// step through each individual square-move so we can check if the piece is
		// in a column or file that may prevent further movement
		for (intSteppingPosition = intCurrentPosition;
			intSteppingPosition <= intDesiredPosition;
			intSteppingPosition += 8)
		{
			// if stepper is in row '1'
			if (intSteppingPosition >= 56 && intSteppingPosition <= 63)
			{
				// only a false move if we haven't arrived at the destination
				if (intSteppingPosition != intDesiredPosition)
				{
					blnValidMove = false;
					break;
				}
			}

			if (intSteppingPosition == intDesiredPosition) { blnValidMove = true; break; }
		}
	}

	return blnValidMove;
}

// --------------------------------------------------------------------------------
// Name: CheckMovement_King()
// Abstract: Checks if rook move is valid, and returns true if so.
// --------------------------------------------------------------------------------
bool Piece::CheckMovement_King(int intCurrentPosition, int intDesiredPosition)
{
	bool blnValidMove = false;

	// right movement
	if (intDesiredPosition - intCurrentPosition == 1
		&& intDesiredPosition - intCurrentPosition > 0)
	{
		// if current position is in file 'h'
		if ((intCurrentPosition - 7) % 8 == 0 || intCurrentPosition == 7)
		{
			blnValidMove = false;
		}

		else {blnValidMove = true;}
	}

	// left movement
	if (intCurrentPosition - intDesiredPosition == 1
		&& intCurrentPosition - intDesiredPosition > 0)
	{
		// if current position is in file 'a'
		if (intCurrentPosition % 8 == 0 || intCurrentPosition == 0)
		{
			blnValidMove = false;
		}
			
		else { blnValidMove = true; }
	}

	// up movement
	if (intCurrentPosition - intDesiredPosition == 8
		&& intCurrentPosition - intDesiredPosition > 0)
	{
		// if stepper is in row '8'
		if (intCurrentPosition >= 0 && intCurrentPosition <= 7)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// down movement
	if (intDesiredPosition - intCurrentPosition == 8
		&& intDesiredPosition - intCurrentPosition > 0)
	{
		// if stepper is in row '1'
		if (intCurrentPosition >= 56 && intCurrentPosition <= 63)
		{
			blnValidMove = false;
		}

		else {blnValidMove = true;}
	}

	// southeast movement
	if (intDesiredPosition - intCurrentPosition == 9
		&& intDesiredPosition - intCurrentPosition > 0)
	{
		// if current position is in file 'h'
		if ((intCurrentPosition - 7) % 8 == 0 || intCurrentPosition == 7)
		{
			blnValidMove = false;
		}

		// if current position is in row '1'
		else if (intCurrentPosition >= 56 && intCurrentPosition <= 63)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// northwest movement
	if (intCurrentPosition - intDesiredPosition == 9
		&& intCurrentPosition - intDesiredPosition > 0)
	{
		// if current position is in file 'a'
		if (intCurrentPosition % 8 == 0 || intCurrentPosition == 0)
		{
			blnValidMove = false;
		}

		// if current position is in row '8'
		else if (intCurrentPosition >= 0 && intCurrentPosition <= 7)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// northeast movement
	if (intCurrentPosition - intDesiredPosition == 7
		&& intCurrentPosition - intDesiredPosition > 0)
	{
		// if current position is in row '8'
		if (intCurrentPosition >= 0 && intCurrentPosition <= 7)
		{
			blnValidMove = false;
		}

		// if current position is in file 'h'
		else if ((intCurrentPosition - 7) % 8 == 0 || intCurrentPosition == 7)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// southwest movement
	if (intDesiredPosition - intCurrentPosition == 7
		&& intDesiredPosition - intCurrentPosition > 0)
	{
		// if current position is in row '1'
		if (intCurrentPosition >= 56 && intCurrentPosition <= 63)
		{
			blnValidMove = false;
		}

		// if current position is in file 'a'
		else if (intCurrentPosition % 8 == 0 || intCurrentPosition == 0)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	return blnValidMove;
}

// --------------------------------------------------------------------------------
// Name: CheckMovement_Pawn()
// Abstract: Checks if pawn move is valid, and returns true if so.
// --------------------------------------------------------------------------------
bool Piece::CheckMovement_Pawn(int intCurrentPosition, int intDesiredPosition, bool blnWhiteOrBlackMove)
{
	bool blnValidMove = false;

	// up movement (white only)
	if (intCurrentPosition - intDesiredPosition == 8
		&& intCurrentPosition - intDesiredPosition > 0 && blnWhiteOrBlackMove == true)
	{
		// if current position is in row '8'
		if (intCurrentPosition >= 0 && intCurrentPosition <= 7)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// down movement, 2 squares (white only)
	if (intCurrentPosition - intDesiredPosition == 16
		&& intCurrentPosition - intDesiredPosition > 0 && blnWhiteOrBlackMove == true)
	{
		// if current position is in row '2' (start position for white pawns)
		if (intCurrentPosition >= 48 && intCurrentPosition <= 55)
		{
			blnValidMove = true;
		}

		else { blnValidMove = false; }
	}

	// down movement (black only)
	if (intDesiredPosition - intCurrentPosition == 8
		&& intDesiredPosition - intCurrentPosition > 0 && blnWhiteOrBlackMove == false)
	{
		// if current position is in row '1'
		if (intCurrentPosition >= 56 && intCurrentPosition <= 63)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// down movement, 2 squares (black only)
	if (intDesiredPosition - intCurrentPosition == 16
		&& intDesiredPosition - intCurrentPosition > 0 && blnWhiteOrBlackMove == false)
	{
		// if current position position is in row '7' (start position for black pawns)
		if (intCurrentPosition >= 8 && intCurrentPosition <= 15)
		{
			blnValidMove = true;
		}

		else { blnValidMove = false; }
	}

	// southeast movement (black only, capture only)
	if (intDesiredPosition - intCurrentPosition == 9
		&& intDesiredPosition - intCurrentPosition > 0 && blnWhiteOrBlackMove == false)
	{
		// if current position position is in file 'h'
		if ((intCurrentPosition - 7) % 8 == 0 || intCurrentPosition == 7)
		{
			blnValidMove = false;
		}

		// if current position is in row '1'
		else if (intCurrentPosition >= 56 && intCurrentPosition <= 63)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// northwest movement (white only, capture only)
	if (intCurrentPosition - intDesiredPosition == 9
		&& intCurrentPosition - intDesiredPosition > 0 && blnWhiteOrBlackMove == true)
	{
		// if current position is in file 'a'
		if (intCurrentPosition % 8 == 0 || intCurrentPosition == 0)
		{
			blnValidMove = false;
		}

		// if current position is in row '8'
		else if (intCurrentPosition >= 0 && intCurrentPosition <= 7)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// northeast movement (white only, capture only)
	if (intCurrentPosition - intDesiredPosition == 7
		&& intCurrentPosition - intDesiredPosition > 0 && blnWhiteOrBlackMove == true)
	{
		// if current position is in row '8'
		if (intCurrentPosition >= 0 && intCurrentPosition <= 7)
		{
			blnValidMove = false;
		}

		// if current position is in file 'h'
		else if ((intCurrentPosition - 7) % 8 == 0 || intCurrentPosition == 7)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	// southwest movement (black only, capture only)
	if (intDesiredPosition - intCurrentPosition == 7
		&& intDesiredPosition - intCurrentPosition > 0 && blnWhiteOrBlackMove == false)
	{
		// if current position is in row '1'
		if (intCurrentPosition >= 56 && intCurrentPosition <= 63)
		{
			blnValidMove = false;
		}

		// if current position is in file 'a'
		else if (intCurrentPosition % 8 == 0 || intCurrentPosition == 0)
		{
			blnValidMove = false;
		}

		else { blnValidMove = true; }
	}

	return blnValidMove;
}