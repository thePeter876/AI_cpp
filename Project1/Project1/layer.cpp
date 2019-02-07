#include "layer.h"

std::string Layer::getInfo() {
	
	std::string inf = std::string(this->name) + ", " + std::to_string(this->numCells) + "neurons.";
	return inf;
}
