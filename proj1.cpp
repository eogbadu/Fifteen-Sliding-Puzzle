/********************************************************************
 ** File:      Proj1.cpp                                  
 ** Project:   CMSC 202 Project 1, Spring 2020             
 ** Author:    Ekele Ogbadu                                
 ** Date:      12 Feb 2020  
 ** Section:   43
 ** Email:     eogbadu1@umbc.edu  
 **
 ** This file contains the main driver program for project 1.
 ** This program is a common sliding puzzle called fifteen. It 
 ** involves a frame of numbered square tiles in random order with 
 ** one tile missing. The object is to place the tiles in order by
 ** making sliding moves that use the empty space.
 ********************************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

// Declare constants
const int ROW            = 0; // Position of row in an array
const int COLUMN         = 1;  // Position of column in an array
const int NUM_ROWS       = 4; // The number of rows in the board
const int NUM_COLS       = 4; // The number of columns in the board
const int LOAD_FILE      = 1; // Number choice to load a file
const int LOAD_DEFAULT   = 2; // Number choice to load default game
const int MAX_LENGTH     = 100; // Maximum length of file name
const int JUSTIFY_SPACE  = 4; // Justification width to print board.
// Function Declarations

//------------------------------------------------------------------------
// Name:            PrintGame
// PreCondition:    A 2-dimensional array already exists.
// PostCondition:   Prints out a 2-dimensional array.
//------------------------------------------------------------------------
void PrintGame(int gameField[][NUM_COLS]);

//------------------------------------------------------------------------
// Name:            CheckDirection
// PreCondition:    A 2-dimensional array and an initial position
//                  exists.
// PostCondition:   Direction is validated and if good tiles are swapped.
//------------------------------------------------------------------------
bool CheckDirection(int gameField[][NUM_COLS], int currentPosition[]);

//------------------------------------------------------------------------
// Name:            SwapTiles
// PreCondition:    A 2-dimensional array exists, position to swap tile
//                  from and location of nearby zero is valid.
// PostCondition:   Tiles have been successfully swapped.
//------------------------------------------------------------------------
void SwapTiles(int gameField[][NUM_COLS], int currentPosition[],
	       int zeroPostion[]);

//------------------------------------------------------------------------
// Name:            CheckForZero
// PreCondition:    A 2-dimensional array exists, user has entered
//                  position.
// PostCondition:   Location of nearby zero is found and assigned.
//------------------------------------------------------------------------
bool CheckForZero(int gameField[][NUM_COLS], int currentPosition[],
		  int zeroPosition[]);

//------------------------------------------------------------------------
// Name:            SelectTile
// Precondition:    A 2-dimensional array exists.
// PostCondition:   Tile has been selected to swap based on user input.
//------------------------------------------------------------------------
void SelectTile(int gameField[][NUM_COLS], int currentPosition[]);

//------------------------------------------------------------------------
// Name:            StartGame
// PreCondition:    A 2-dimensional array exists and user has entered
//                  choice on whether to load file or use default file.
// PostCondition:   File is loaded is valid.
//------------------------------------------------------------------------
void StartGame(int input, int gameField[][NUM_COLS]);

//------------------------------------------------------------------------
// Name:            IsGameOver
// PreCondition:    A 2-dimensional array exists.
// PostCondition:   Game is checked to see if user has won the game.
//                  Message is printed if user has won.
//------------------------------------------------------------------------
bool IsGameOver(int gameField[][NUM_COLS]);

//------------------------------------------------------------------------
// Name:            LoadFile
// PreCondition:    A 2-dimensional array exists.
// PostCondition:   File is read and values are assigned to the
//                  2-dimensional array.
//------------------------------------------------------------------------
bool LoadFile(int gameField[][NUM_COLS]);

int main ()
{
  // Declare variables
  bool moreGames = true; // To check if the user wants to keep playing
  int input; // User selection on whether to load a file or not
  char playAgain; // If user wants to play again


  // Print out welcome message
  cout << "Welcome to the Fifteen Game" << endl;
  
  // While the user wants to keep playing
  while (moreGames == true)
  {
    // Declare 2-dimensional array which represents the field.                
    int myArray[NUM_ROWS][NUM_COLS] =
    {
     {1, 2, 3, 4},
     {5, 6, 7, 8},
     {9, 10, 11, 12},
     {13, 14, 0, 15}

    };
    
    // The default postion the user starts at 
    int currentPosition[2] = {0, 0};

    // Get input
    cout << "Would you like to load a board?" << endl;
    cout << "1. Yes\n2. No \n";
    cin >> input;
    
    // Check that input is correct
    while (input != 1 && input != 2)
    {
      cout << "Error!!! Wrong input detected! Try Again!" << endl;
      cout << "1. Yes\n2. No \n";
      cin >> input;
    }

    // Start game and print the field
    StartGame(input, myArray);
    PrintGame(myArray);

    // Loop until game is complete
    do
    {
      SelectTile(myArray, currentPosition);
      PrintGame(myArray);
      
    } while (!IsGameOver(myArray));

    // Ask user is they want to play again
    cout << "Congrats you've won!" << endl;
    cout << "Play again? (y/n): ";
    cin >> playAgain;

    // Validate input
    while ((tolower(playAgain) != 'y') && (tolower(playAgain) != 'n'))
    {
      cout << "Wrong Choice!! Try Again!" << endl;
      cout << "Play again? (y/n): ";
      cin >> playAgain;
    }

    switch (playAgain)
    {
    case 'y': 
    case 'Y':
      moreGames = true;
      break;
    case 'n':
    case 'N':
      cout << "Thank you for playing the game of fifteen!" << endl;
      moreGames = false;
    }
  }
  
  return 0;
}

// IsGameOver
// Given a 2-dimensional array, loops through the board to check if the
// numbers are arranged in ascending order with the zero(blank) at the
// lower right corner. 
bool IsGameOver(int gameField[][NUM_COLS])
{
  // Declare variables
  int n = 1; // Count variable
  int totalNumbers = (NUM_ROWS * NUM_COLS) - 1; // number of elements minus 1

  // Use for loops to go through each element in the 2-dimensional
  // array
  for (int i = 0; i < NUM_ROWS; i++)
  {
    for (int j = 0; j < NUM_COLS; j++)
    {
	if (gameField[i][j] == n)
	{
	  if (n < totalNumbers)
	  {
	    n++;
	  }
	  else
	  {
	    n = 0;
	  } 
	}
	else
	{
	  cout << "No winner" << endl;
	  return false;
	}
    }
  }
  return true;
}

// StartGame
// Given a 2-dimensional array and input from user on whether to load
// a file or play default game, starts the game and prints out messages
// if game is started or not.
void StartGame(int input, int gameField[][NUM_COLS])
{
  bool fileLoaded; // Boolean to check if file loaded properly

  // Check input from user on whether to laod game
  // or play default
  switch(input)
  {
  case 1:
    fileLoaded = LoadFile(gameField);
    if (!fileLoaded)
    {
      cout << "Can't let you play right now, goodbye!" << endl;
      exit(1);
    }
    break;
  case 2:
     cout << "Loading default..." << endl;
     break;
  }
}

// LoadFile
// Given a 2-dimensional array, asks the user for a file to open,
// checks that the file is good to go and reads in values from the
// file into the 2-dimensional array.
bool LoadFile(int gameField[][NUM_COLS])
{
  // Declare variables
  ifstream inStream;
  char fileName[MAX_LENGTH];
  int number;

  // Get file name from user and open it
  cout << "What is the file name?" << endl;
  cin >> fileName;
  inStream.open(fileName);

  // Check that file opened properly
  // Print out error message if it failed to open
  if (inStream.fail())
  {
    cout << "File failed to load.\n";
    return false;
  }
  // If it opened properly, read in values from file
  // into array
  else
  {
    for (int i = 0; i < NUM_ROWS; i++)
    {
      for (int j = 0; j < NUM_COLS; j++)
      {
	inStream >> number;
	gameField[i][j] = number;
      }
    }
  }
  // Close the file
  inStream.close();
  
  return true;
}

// SelectTile
// Given a 2-dimensional array and an array representing the current
// positon, Gets, validates user input for current position and
// assigns it to the current position array.
void SelectTile(int gameField[][NUM_COLS], int currentPosition[])
{
  // Declare variables
  int row; // Holds a row position
  int col; // Holds a column position
  bool goodDirection; // Bool to hold if direction is valid

  // Get input
  cout << "What is the row (left) and column (top) to slide?" << endl;
  cout << "Row: ";
  cin >> row;
  cout << "Column: ";
  cin >> col;

  // Change position to user selection
  currentPosition[ROW] = row;
  currentPosition[COLUMN] = col;

  // Check direction
  goodDirection = CheckDirection(gameField, currentPosition);
  while (goodDirection == false)
  {
    PrintGame(gameField); // Print the field
    cout << "What is the row (left) and column (top) to slide?" << endl;
    cout << "Row: ";
    cin >> row;
    cout << "Column: ";
    cin >> col;

    // Change position to user selection
    currentPosition[ROW] = row;
    currentPosition[COLUMN] = col;

    // Check direction
    goodDirection = CheckDirection(gameField, currentPosition);
  }

}

// CheckForZero
// Given a 2-dimensional array, an array holding the current position
// the user would like to move from and an array for the position the
// zero will occupy, the zero position is located and assigned to the
// array representing the zero position. A message is printed stating
// where the user will be moved to.
bool CheckForZero(int gameField[][NUM_COLS], int currentPosition[],
		  int zeroPosition[])
{
  // Declare variables
  int row  = currentPosition[ROW]; // User selected row
  int col  = currentPosition[COLUMN]; // User selected column
  int fRow = row - 1; // Row position on the game field
  int fCol = col - 1; // Column position on the game field

  // Perform checks to find where the zero is

  // Check Rows
  // ----------
  // Check if zero is below tile on the first row 
  if ((row == 1) && (gameField[fRow + 1][fCol] == 0))
  {
    cout << "The tile slid down" << endl;
    zeroPosition[ROW] = row + 1;
    zeroPosition[COLUMN] = col;
    return true;
  }
  // Check if between the the first and last row
  else if (row > 1 && row < NUM_ROWS)
  {
    // Check if zero is above tile
    if (gameField[fRow - 1][fCol] == 0)
    {
      cout << "The tile slid up" << endl;
      zeroPosition[ROW] = row - 1;
      zeroPosition[COLUMN] = col;
      return true;
    }
    // Check if zero is below tile
    else if (gameField[fRow + 1][fCol] == 0)
    {
      cout << "The tile slid down" << endl;
      zeroPosition[ROW] = row + 1;
      zeroPosition[COLUMN] = col;
      return true;
    }
  }
  // Check if zero is above tile on the last row  
  else if ((row == NUM_ROWS) && (gameField[fRow - 1][fCol] == 0))
  {
    cout << "The tile slid up" << endl;
    zeroPosition[ROW] = row - 1;
    zeroPosition[COLUMN] = col;
    return true;
  }

  // Check Columns
  // -------------
  // Check if zero is to the right of the tile in the first column  
  if ((col == 1) && (gameField[fRow][fCol + 1] == 0))
  {
    cout << "The tile slid right" << endl;
    zeroPosition[ROW] = row;
    zeroPosition[COLUMN] = col + 1;
    return true;
  }
  // Check between the first and last column
  else if (col > 1 && col < NUM_COLS)
  {
    // Check if zero is to the left of the tile
    if (gameField[fRow][fCol - 1] == 0)
    {
      cout << "The tile slid left" << endl;
      zeroPosition[ROW] = row;
      zeroPosition[COLUMN] = col - 1;
      return true;
    }
    // Check if zero is to the right of the tile
    else if (gameField[fRow][fCol + 1] == 0)
    {
      cout << "The tile slid right" << endl;
      zeroPosition[ROW] = row;
      zeroPosition[COLUMN] = col + 1;
      return true;
    }
  }
  // Check if zero is to the left of the tile on the last column
  else if ((col == NUM_COLS) && (gameField[fRow][fCol - 1] == 0))
  {
    cout << "The tile slid left" << endl;
    zeroPosition[ROW] = row;
    zeroPosition[COLUMN] = col - 1;

    return true;
  }

  return false;
    
}

// CheckDirection
// Given a 2-dimensional array and an array holding the current position
// to switch from, checks that the position is not a blank and if not
// calls functions to check for the zero location and then perform a swap
// if everything is valid.
bool CheckDirection(int gameField[][NUM_COLS], int currentPosition[])
{
  // Declare variables
  int row = currentPosition[ROW];
  int col = currentPosition[COLUMN];
  int zeroPosition[2] = {0, 0};

  // Check if row is out bounds 
  if (row < 1 || row > NUM_ROWS)
  {
    cout << "Your row value is out of bounds" << endl;
    return false;
  }

  // Check if column is out of bounds
  if (col < 1 || col > NUM_COLS)
  {
    cout << "Your column value is out of bounds" << endl;
    return false;
  }

  // Check if the tile to slide is a zero (blank)
  if (gameField[row - 1][col - 1] == 0)
  {
    cout << "You chose the blank" << endl;
    cout << "That tile cannot slide" << endl;
    return false;
  }

  // Check for a zero and swap if everything is valid
  if(CheckForZero(gameField, currentPosition, zeroPosition))
  {
    SwapTiles(gameField, currentPosition, zeroPosition);
    return true;
  }
  else
  {
    return false;
  }
}

// SwapTiles
// Given a 2-dimensional array, the an array holding the position to
// switch from and an array representing the position of the blank
// space represented by the zero, swaps the number of the number at the
// current postion and the zero.
void SwapTiles(int gameField[][NUM_COLS], int currentPosition[], int zeroPosition[])
{
  // Declare variables
  int temp;
  int row = zeroPosition[ROW];
  int col = zeroPosition[COLUMN];
  int currentRow = currentPosition[ROW];
  int currentCol = currentPosition[COLUMN];

  
  currentRow--;
  currentCol--;

  // Perform swap
  temp = gameField[currentRow][currentCol];
  gameField[currentRow][currentCol] = 0;
  gameField[row - 1][col - 1] = temp;
  
}

// PrintGame
// Given a 2-dimensional array, prints out the game field
// with numbers 1 - 15 and a 0 to represent the blank space.
void PrintGame(int gameField[][NUM_COLS])
{
  cout << endl;
  for (int i = 1; i <= NUM_COLS; i++)
  {
    cout << "    " << i;
  }

  for (int i = 0; i < NUM_ROWS; i++)
  {
    cout << endl << i + 1 << '|';
    
    for (int j = 0; j < NUM_COLS; j++)
    {
      cout << setw(JUSTIFY_SPACE) << gameField[i][j] << '|';
    }
  }
  
  cout << endl;
}
