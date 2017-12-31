#include "game_of_life.h"
#include <iostream>
#include <string>

int main() {
	std::string file = "input.txt";
	game_of_life g(file);
	g.run(std::cout);
}