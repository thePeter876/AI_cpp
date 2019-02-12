#include "layer_Input.h"

Layer_Input::Layer_Input(int num, std::string n, Layer* nl) {
	this->numCells = num;
	this->name = n;
	this->nextLayer = nl;
	if (nl != nullptr) nl->setPreviousLayer(this);
}

void Layer_Input::createCells() {
	//int n = this->getNumCells();
	for (int i = 0; i < this->numCells; i++) {
		this->addCell(new Neuron());
	}
}

const std::string& Layer_Input::getInfo() {
	int numOfTransmitters = 0;
	for (int i = 0; i < this->numCells; i++) {
		numOfTransmitters += this->cells[i]->getOutputs()->size();
	}
	std::string inf = this->name + ", " + std::to_string(this->numCells)
		+ " neurons. Transmitters to next layer: " + std::to_string(numOfTransmitters) 
		+ ". Next: " + this->nextLayer->getName() + ".";
	return inf;
}