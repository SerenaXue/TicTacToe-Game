#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

class TicTacToe
{
public:
	// Present status of each grid on the board. 
	// One player represented as X and the opposing player is O.
	enum Mark
	{
		X = 0,
		O = 1,
		EMPTY = 2,
	};

	// Present the result after each movement.
	enum MoveResult
	{
		X_WINS = 0,
		O_WINS = 1,
		TIE = 2,
		UNFINISHED = 3,
		INVALID_MOVE = 4,
	};

	// Strategy type, here only has random generation strategy.
	// Could has optimal strategy option being added.
	enum Strategy
	{
		RANDOM = 0,
	};

	TicTacToe(int n) : 
		n(n),
		board(n, vector<Mark>(n, TicTacToe::EMPTY)),
		play_x_turn(true),
		rows(n),
		cols(n),
		diag(0),
		rev_diag(0),
		move_counter(0) {}

	// Decide and return the result after one movement
	// by giving the coordinate on the board.
	MoveResult move(int i, int j);
	// Return the result after one movement by giving a specific strategy.
	MoveResult move_generator(Strategy strategy);
	// Decide if the game is finished.
	bool is_game_finished(MoveResult move_result);
	// Show a readable result as string format.
	string move_result_to_string(MoveResult move_result);
	// Print what current board looks like by traverse.
	void print_board();

private:
	// n is the size of grid.
	int n;
	vector<vector<Mark>> board;
	// A flag to mark if the current player is X
	bool play_x_turn;

	vector<int> rows, cols;
	// Count of grid in diagonal and anti-diagonal that are not empty
	int diag, rev_diag;
	// Total steps of movement
	int move_counter;
};

TicTacToe::MoveResult TicTacToe::move(int i, int j) {
	// First, check if the coordinate is valid
	if (i < 0 || i >= n || j < 0 || j >= n || board[i][j] != TicTacToe::EMPTY) {
		cout << "================" << endl;
		cout << move_result_to_string(TicTacToe::INVALID_MOVE);
		return TicTacToe::INVALID_MOVE;
	}

	board[i][j] = play_x_turn ? X : O;
	move_counter++;
	// 1 represents player X contribute to row i, colume j, diagonal and anti-diagonal,
	// -1 represents player O contribute to row i, colume j, diagonal and anti-diagonal
	const int count = play_x_turn ? 1 : -1;
	rows[i] += count;
	cols[j] += count;
	diag += i == j ? count : 0;
	rev_diag += i == n - j - 1 ? count : 0;

	const bool wins =
		abs(rows[i]) == n || abs(cols[j]) == n ||
		abs(diag) == n || abs(rev_diag) == n;
	const auto result = wins ? 
		(play_x_turn ? TicTacToe::X_WINS : TicTacToe::O_WINS) : 
		(move_counter == n * n ? TicTacToe::TIE : TicTacToe::UNFINISHED);
	
	// Update player's turn
	play_x_turn = !play_x_turn;
	
	print_board();
	cout << move_result_to_string(result) << endl;
	return result;
}

TicTacToe::MoveResult TicTacToe::move_generator(TicTacToe::Strategy strategy) {
	int i = 0, j = 0;
	if (strategy == TicTacToe::RANDOM) {
    	srand(time(NULL));
		i = rand() % n;
		j = rand() % n;
		while (board[i][j] != TicTacToe::EMPTY) {
			i = rand() % n;
			j = rand() % n;
		}
	}

	return move(i, j);
}

bool TicTacToe::is_game_finished(MoveResult move_result) {
	return move_result == TicTacToe::X_WINS || 
		move_result == TicTacToe::O_WINS || 
		move_result == TicTacToe::TIE;
}

void TicTacToe::print_board() {
	cout << "================" << endl;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			switch (board[i][j]) {
				case TicTacToe::X: cout << "X"; break;
				case TicTacToe::O: cout << "O"; break;
				case TicTacToe::EMPTY: cout << "_"; break;
			}
		}
		cout << endl;
	}
}

string TicTacToe::move_result_to_string(MoveResult move_result) {
	switch (move_result) {
		case TicTacToe::X_WINS: return "X wins";
		case TicTacToe::O_WINS: return "O wins";
		case TicTacToe::TIE: return "Tie";
		case TicTacToe::UNFINISHED: return "Continue";
		case TicTacToe::INVALID_MOVE: return "Invalid move!";
	}	
}

// Unit test for method "move"
void TestTicTacToe(TicTacToe* game, int i, int j, TicTacToe::MoveResult expected_result) {
	auto result = game->move(i,j);
	if (result != expected_result) {
		cout << "Result is not correct!" << endl;
		cout << "movement: " << i << "," << j 
			 << " expected result: " << game->move_result_to_string(expected_result)
			 << " actural result: " << game->move_result_to_string(result) << endl;
	} else {
		cout << "Test passed!" << endl;
	}
}

// Run unit test
void run_unit_test() {
	unique_ptr<TicTacToe> game(new TicTacToe(3));
	TestTicTacToe(game.get(), 1, 1, TicTacToe::UNFINISHED);
	TestTicTacToe(game.get(), 1, 1, TicTacToe::INVALID_MOVE);
	TestTicTacToe(game.get(), 2, 0, TicTacToe::UNFINISHED);
	TestTicTacToe(game.get(), 2, 1, TicTacToe::UNFINISHED);
	TestTicTacToe(game.get(), 1, 0, TicTacToe::UNFINISHED);
	TestTicTacToe(game.get(), 0, 1, TicTacToe::X_WINS);
}

int main() {
	run_unit_test();

	unique_ptr<TicTacToe> game(new TicTacToe(3));
	while (true) {
		auto result = game->move_generator(TicTacToe::RANDOM);
		if (game->is_game_finished(result)) {
			break;
		}
	}
	return 0;
}