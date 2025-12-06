#include <iostream>

#include "../utils/Timer.hpp"
#include "../utils/Types.hpp"
#include "../utils/Utils.hpp"

bool part2 = false;

int main(int argc, char* argv[]) {
	StringVector input = Utils::LoadFile(argc, argv, part2);

	Timer timer = Timer();
	timer.Start();

	timer.End();

	return 0;
}
