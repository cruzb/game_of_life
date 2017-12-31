#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>

class game_of_life {
public:
	game_of_life();
	game_of_life(std::istream& in, std::ostream& out);
	game_of_life(std::string& filename);
	void run(std::ostream& out);
private:
	int num_neighbors(int row, int col);
	void step();

	std::vector<std::vector<bool>> grid;
	int delay = 3;

};

game_of_life::game_of_life() {

}
game_of_life::game_of_life(std::istream& in, std::ostream& out) {

}
game_of_life::game_of_life(std::string& filename) {
	std::ifstream in(filename);
	//if (!in.is_open()) std::cout << "FAIL" << std::endl;
	std::string buffer;
	int rows, cols;
	in >> buffer;
	rows = stoi(buffer);
	in >> buffer;
	cols = stoi(buffer);
	grid.resize(rows);
	for (int r = 0; r < rows; r++)
		grid[r].resize(cols, false);

	char entry;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			in.get(entry);
			if(entry == '\n')
				in.get(entry);
			if (entry == '.' || entry == '*')
				grid[r][c] = true;
		}
	}
}
void game_of_life::step() {
	std::vector<std::vector<bool> > new_grid = grid;

	for (int r = 0; r < grid.size(); r++) {
		for (int c = 0; c < grid[0].size(); c++) {
			if (grid[r][c]) {
				int neighbors = num_neighbors(r, c);

				// less than two neighbors - die from underpopulation
				if (neighbors < 2) 
					new_grid[r][c] = false;
				// die to overpopulation
				if (neighbors > 3) 
					new_grid[r][c] = false;
			}
			else {
				if (num_neighbors(r, c) == 3)
					new_grid[r][c] = true;
			}
		}
	}
	grid = new_grid;
}
void game_of_life::run(std::ostream& out) {
	while (true) { // print
		for (int r = 0; r < grid.size(); r++) {
			for (int c = 0; c < grid[0].size(); c++) {
				if(grid[r][c])
					out << '.';
				else out << ' ';
			}
			out << std::endl;
		}


		step();
		std::this_thread::sleep_for(std::chrono::seconds(delay));
		system("cls");
	}
}

int game_of_life::num_neighbors(int row, int col) {
	int sum = 0;

	if (row - 1 >= 0 && col - 1 >= 0) // top left
		sum += grid[row - 1][col - 1];
	if (row - 1 >= 0) // top
		sum += grid[row - 1][col];
	if (row - 1 >= 0 && col + 1 < grid[0].size()) // top right
		sum += grid[row - 1][col + 1];

	if (col - 1 >= 0) // left
		sum += grid[row][col - 1];
	if (col + 1 < grid[0].size()) // right
		sum += grid[row][col + 1];

	if (row + 1 < grid.size() && col - 1 >= 0) // bottom left
		sum += grid[row + 1][col - 1];
	if (row + 1 < grid.size()) // bottom
		sum += grid[row + 1][col];
	if (row + 1 < grid.size() && col + 1 < grid[0].size()) // bottom right
		sum += grid[row + 1][col + 1];
	
	return sum;
}
