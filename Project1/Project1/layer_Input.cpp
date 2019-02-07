#include "layer_Input.h"

Layer_Input::Layer_Input(int num, std::string n, Layer* nl) {
	this->setNumCells(num);
	this->setName(n);
	this->nextLayer = nl;
	if (nl != nullptr) nl->setPreviousLayer(this);
}

void Layer_Input::createCells() {
	int n = this->getNumCells();
	for (int i = 0; i < n; i++) {
		this->addCell(new Neuron());
	}
}

std::string Layer_Input::getInfo() {
	int numOfTransmitters = 0;
	for (int i = 0; i < this->getNumCells(); i++) {
		numOfTransmitters += (*this->getCells())[i]->getOutputs()->size();
	}
	std::string inf = this->getName() + ", " + std::to_string(this->getNumCells()) 
		+ " neurons. Transmitters to next layer: " + std::to_string(numOfTransmitters) 
		+ ". Next: " + this->getNextLayer()->getName() + ".";
	return inf;
}