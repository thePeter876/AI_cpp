#include "layer_Output.h"

Layer_Output::Layer_Output(int num,  Layer* pl, std::string n) {
	this->numCells = num;
	this->name = n;
	if (pl != nullptr) {
		this->previousLayer = pl;
		pl->setNextLayer(this);
	}
}

void Layer_Output::createCells() {
	for (int i = 0; i < this->numCells; i++) {
		Neuron* cell = new Neuron();
		if (this->previousLayer != nullptr) {
			std::vector<Neuron*>* plCells = this->previousLayer->getCells();
			int numberOfT = plCells->size();
			for (int j = 0; j < numberOfT; j++) {
				new Transmitter((*plCells)[j], cell);
			}
		}
		this->addCell(cell);
	}
}

const std::string& Layer_Output::getInfo() {
	std::string inf = this->name + ", " + std::to_string(this->numCells) 
		+ " neurons. Prev: " + this->getPreviousLayer()->getName() + ".";
	return inf;
}