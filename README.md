# TicTacToe-Game

This is a Tic-Tac-Toe game with unit tests. 
The repository contains one C++ code and one excutable file. 
The purpose of each function explained as below. Please take a look at the code to get more details.

|    Function Name |      Purpose           | 
| -------------        |:-------------:| 
| `MoveResult move(int i, int j)`     | Decide and return the result after one movement by giving the coordinate on the board. | 
| `MoveResult move_generator(Strategy strategy)`      | Return the result after one movement by giving a specific strategy.      |   
| `bool is_game_finished(MoveResult move_result)` | Decide if the game is finished.      | 
| `string move_result_to_string(MoveResult move_result)` | Show a readable result as string format.      |
| `void print_board()` | Print what current board looks like by traverse each grid.      |