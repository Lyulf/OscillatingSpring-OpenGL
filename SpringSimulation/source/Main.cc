#include "SpringSimulation/Simulation.hh"


int main(int argc, char** argv) {
	Simulation simulation(&argc, argv, "Simulation", 800, 800, 500, 150);
	simulation.run();
	return 0;
}