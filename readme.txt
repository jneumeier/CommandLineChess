*********************************************************
Command Line Chess - Readme
*********************************************************

Written by: 		John Neumeier
Language:		C++
Started:		March 2022
Current Version:	v0.1


*********************
How To Run:
*********************
- Clone this repository into Visual Studio and press Run
- Or, drag the .exe file in the debug folder into your command prompt and press Enter.



*********************
About This Program:
*********************

This is a command-line implementation of chess. Pieces are represented by upper and lower-case letters, representing white and black pieces, respectively. This program uses standard algebraic notation exclusively, in order to make moves. It is currently a two-human player game. I would like to start implementing a computer opponent after all game mechanics and user interface design has been completed.

The game currently has core mechanics in place, and pieces can be moved and captured, all while adhering to individual piece moving rules.


*********************
To Implement:
*********************
- ensure capture mechanic is implemented in all other move calls, rather than just the "Rxa5" 4-char call
- castling
- game concept of king being in check
- game concept of checkmate
- vectors to hold captured pieces
- display captured pieces
- Title screen with main menu before starting the game
- Option to display the main menu at any time
- more stuff later!!!
