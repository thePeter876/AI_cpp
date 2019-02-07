#include "layer.h"

std::string Layer::getInfo() {
	
	std::string inf = std::string(this->name) + ", " + std::to_string(this->numCells) + "neurons.";
	return inf;
}


void Layer::processInputData() {
	std::vector<Neuron*>* cells = this->getCells();
	for (int i = 0; i < this->getNumCells(); i++) {
		this->cells[i]->sendToOutputs();
	}
}