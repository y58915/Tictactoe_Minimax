# Tictactoe_Minimax
A Tic-tac-toe AI with Minimax algorithm


ab 8: Tic-Tac-Toe AI

 

For this lab, you will continue the work from your previous lab, which is Tic-Tac-Toe.

You will implement an AI for the game, using Minimax:

Change the way your AI chooses the next move from a random move to an optimal move chosen by the Minimax algorithm.

 

1. Find and make a copy of your project from Lab 6.

2. In Lab 6, you were asked to create a random Tic-Tac-Toe player.  Go through the code again and make sure you only use cout for the AI's moves.  Everything else, if you choose to output, should be done using cerr.  All cins should remain the same. Once you've done that, test your code using the provided Tic-Tac-Toe GUI.  If your code crashes the GUI, you may not have set up cout's correctly.

cerr is similar to cout. However, when using the GUI, everything you output with cerr goes to a log file. For example, cerr << 0 << " " << 1 << endl;  will write 0 1 to a log file in the same location as your exe file.

GUI: TicTacToeGameInterface.zip

This is a graphical interface that helps you visualize your algorithm. A sample minimax AI is included.

 

3. Now, find in your code where the AI produces a random move.  It would be the lines you wrote that may be similar to:

 newX = rand() % row;
 newY = rand() % column;
 while (board[newX][newY] != EMPTY)
 {
    newX = rand() % row;
    newY = rand() % column;
 }
Comment out all your random number generation lines.

4. Instead of generating random numbers, you will replace them with the call to Minimax.

pair<int, int> newMove = minimax_decision(board, row, column);

newX = newMove.first;
newY = newMove.second;
5. Add these function declarations to the top of your code:

pair<int, int> minimax_decision(int ** board, int row, int column);
int max_value(int ** board, int row, int column);
int min_value(int ** board, int row, int column);
int terminal_test(int ** board, int row, int column);
Add these function definitions:

 Tic-Tac-Toe Functions

Your main task is to fill in the content of the functions. You may add adidtional global variables but existing functions should not be changed. 

Pseudocode for Minimax can be found in the slides of lecture 12.

 

Requirements:

Your AI should use the Minimax algorithm to choose the next move.

You may use the existing function showBoard() at each turn to display the current status of the board (you'll find the output in the log file when running the GUI).  You may display anything else as you wish, using cerr .

 

 

Grading Rubric:


2 points for the code working with the GUI.

3 points for correctly implementing terminal_test()

5 points for correctly implementing the minimax functions max_value() and min_value()

Total: 10 points

 

Deliverables: 

The labs are graded and count towards your lab grades.

When you have finished the lab, raise your hand and inform the instructor. The instructor will come and check out your work. You will receive a checkmark (10 points for the lab) if everything runs according to the requirements.

If you have not finished the requirements during the lab session, you may submit your entire C++ project (including all project files such as the .sln file) as a zip file. Submit your code below only if you have not finished it during the lab session.

Keep your C++ file for future use.
