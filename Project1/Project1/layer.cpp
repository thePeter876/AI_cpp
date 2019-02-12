#include "layer.h"

const std::string& Layer::getInfo() {
	
	std::string inf = std::string(this->name) + ", " + std::to_string(this->numCells) + "neurons.";
	return inf;
}


/*void Layer::processInputData() {
	std::vector<Neuron*>* cells = this->getCells();
	for (int i = 0; i < this->getNumCells(); i++) {
		this->cells[i]->sendToOutputs();
	}
}*/

void Layer::randomize(const int& minBias, const int& maxBias, const int& minWeight, const int& maxWeight) {
	for (int j = 0; j < this->numCells; j++) {
		this->cells[j]->randomize(minBias, maxBias, minWeight, maxWeight);
	}
}