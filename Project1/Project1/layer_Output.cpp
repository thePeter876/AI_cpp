#include "layer_Output.h"

Layer_Output::Layer_Output(int num,  Layer* pl, std::string n) {
	this->setNumCells(num);
	this->setName(n);
	if (pl != nullptr) {
		this->previousLayer = pl;
		pl->setNextLayer(this);
	}
}

void Layer_Output::createCells() {
	int n = this->getNumCells();
	for (int i = 0; i < n; i++) {
		Neuron* cell = new Neuron();
		if (this->previousLayer != nullptr) {
			std::vector<Neuron*>* plCells = this->previousLayer->getCells();
			int numberOfT = plCells->size();
			for (int j = 0; j < numberOfT; j++) {
				new Transmitter((*plCells)[j], cell);
			}
		}
		//new Transmitter_Output(cell);
		this->addCell(cell);
	}
}

std::string Layer_Output::getInfo() {
	std::string inf = this->getName() + ", " + std::to_string(this->getNumCells()) 
		+ " neurons. Prev: " + this->getPreviousLayer()->getName() + ".";
	return inf;
}