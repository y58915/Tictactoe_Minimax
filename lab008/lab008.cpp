#include <time.h>
#include <iostream>
using namespace std;

void showBoard(int ** board, int row, int column);
void player(int ** board);
void AI(int ** board);
bool noSpace(int ** board);
bool hasWinner(int ** board);

pair<int, int> minimax_decision(int ** board, int row, int column);
int max_value(int ** board, int row, int column);
int min_value(int ** board, int row, int column);
int terminal_test(int ** board, int row, int column);

const int EMPTY = 0;
const int PLAYX = -1;
const int PLAYO = 1;

int turn = 1; // records whose turn it is (1st player or 2nd player)
bool switcher;
bool tempSwitcher;


int main()
{
	// randomize seed for generating random numbers
	srand((unsigned)time(NULL));

	int row = 3;
	int column = 3;

	// allocate memory for the board
	int** board = new int*[row];
	for (int i = 0; i< row; i++) {
		board[i] = new int[column];
	}

	// initialize the board to be empty
	for (int i = 0; i< row; i++) {
		for (int j = 0; j< column; j++) {
			board[i][j] = EMPTY;
		}
	}

	// board[][] is the current state
	showBoard(board, row, column);

	int begin;
	cin >> begin;
	if (begin == 0)
		switcher = true;
	else
		switcher = false;

	do
	{
		if (switcher)
		{
			player(board);
		}
		else
		{
			AI(board);
		}
		turn++;
		showBoard(board, row, column);
	} while (!noSpace(board) && !hasWinner(board));

	if (hasWinner(board))
	{
		if (switcher)
		{
			cout << "Unfortunately, AI wins";
		}
		else
		{
			cout << "congratulations! you wins";
		}
	}

	else if (noSpace(board))
	{
		cout << "Draw Game!";
	}

	// deallocate memory for the board
	for (int i = 0; i< row; i++) {
		delete[] board[i];
	}
	delete[] board;

	cerr << endl;
	cout.flush();
	system("pause");
	return 0;
}



// Shows the board on the screen
void showBoard(int ** board, int row, int column)
{
	cerr << "The current board:" << endl;
	for (int i = 0; i< row; i++) {
		for (int j = 0; j< column; j++) {
			if (board[i][j] == PLAYX)
				cerr << "X" << " ";
			else if (board[i][j] == PLAYO)
				cerr << "O" << " ";
			else
				cerr << "-" << " ";
		}
		cerr << endl;
	}
}


void player(int ** board)
{
	int row, column;
	do
	{
		do
		{
			cin >> row >> column;
		} while (column < 0 || column > 2 || row < 0 || row > 2);
		if (board[row][column] == EMPTY)
		{
			board[row][column] = PLAYX;
			switcher = false;
		}
	} while (switcher);

}


void AI(int ** board)
{
	int row, column;

	pair<int, int> newMove = minimax_decision(board, 3, 3);
	row = newMove.first;
	column = newMove.second;
	board[row][column] = PLAYO;
	switcher = true;
	cout << row << " " << column << endl;
}

// checks the current board for a winner
// Returns the current state of the board:
// 1 = AI wins, -1 = opponent wins
// 0 = tie, -2 = game not finished
int terminal_test(int ** board, int row, int column)
{
	int state;
	if (hasWinner(board))
	{
		if (tempSwitcher)
			state = 1;
		else
			state = -1;
	}
	else if (noSpace(board))
		state = 0;
	else
		state = -2;

	return state;
}



// minimax decision
// Returns best action with coordinates (X, Y)
// This function has been completed for you
pair<int, int> minimax_decision(int ** board, int row, int column)
{
	int X = -1, Y = -1;
	int returnVal = -100;

	for (int i = 0; i< row; i++) {
		for (int j = 0; j< column; j++) {

			if (board[i][j] == EMPTY)
			{
				board[i][j] = PLAYO;
				tempSwitcher = true;

				int newVal = min_value(board, row, column);

				if (newVal > returnVal)
				{
					returnVal = newVal;
					X = i;
					Y = j;
				}
				board[i][j] = EMPTY;
			}
		}
	}

	return pair<int, int>(X, Y);
}


// max value, returns a utility value of -1/0/1
int max_value(int ** board, int row, int column)
{
	int value = terminal_test(board, row, column);
	if (value == -2)
	{
		int X = -1, Y = -1;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {

				if (board[i][j] == EMPTY)
				{
					if (tempSwitcher)
					{
						board[i][j] = PLAYX;
						tempSwitcher = false;
					}
					else
					{
						board[i][j] = PLAYO;
						tempSwitcher = true;
					}

					int newVal = min_value(board, row, column);

					if (newVal > value)
					{
						value = newVal;
						X = i;
						Y = j;
					}
					if (board[i][j] == PLAYO)
						tempSwitcher = false;
					else
						tempSwitcher = true;
					board[i][j] = EMPTY;

				}
			}
		}
	}

	return value;
}



// min value, returns a utility value of -1/0/1
int min_value(int ** board, int row, int column)
{
	int value = terminal_test(board, row, column);
	if (value == -2)
	{
		int X = -1, Y = -1;

		for (int i = 0; i< row; i++) {
			for (int j = 0; j< column; j++) {
				
				if (board[i][j] == EMPTY)
				{
					if (tempSwitcher)
					{
						board[i][j] = PLAYX;
						tempSwitcher = false;
					}
					else
					{
						board[i][j] = PLAYO;
						tempSwitcher = true;
					}
	

					int newVal = max_value(board, row, column);

					if (newVal < value)
					{
						value = newVal;
						X = i;
						Y = j;
					}
					if (board[i][j] == PLAYO)
						tempSwitcher = false;
					else
						tempSwitcher = true;
					board[i][j] = EMPTY;
				}
			}
		}
	}

	return value;
}

bool noSpace(int ** board)
{
	bool noSpace = true;
	int i = 0;
	while (noSpace && i < 3)
	{
		int j = 0;
		while (noSpace && j < 3)
		{
			if (board[i][j] == 0)
			{
				noSpace = false;
			}
			j++;
		}
		i++;
	}
	return noSpace;
}

bool hasWinner(int ** board)
{
	bool win = false;
	int i = 0;
	int j = 0;
	int total;
	while (!win && i < 3)
	{
		total = board[i][0] + board[i][1] + board[i][2];
		if (total == 3 || total == -3)
		{
			win = true;
		}
		i++;
	}
	while (!win && j < 3)
	{
		total = board[0][j] + board[1][j] + board[2][j];
		if (total == 3 || total == -3)
		{
			win = true;
		}
		j++;
	}
	if (!win)
	{
		total = board[0][0] + board[1][1] + board[2][2];
		if (total == 3 || total == -3)
		{
			win = true;
		}
	}
	if (!win)
	{
		total = board[0][2] + board[1][1] + board[2][0];
		if (total == 3 || total == -3)
		{
			win = true;
		}
	}
	return win;
}