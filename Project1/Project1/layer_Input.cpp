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
		//Neuron* cell = new Neuron();
		//new Transmitter_Input(cell);
		//this->addCell(cell);
		this->addCell(new Neuron());
	}
}

/*void Layer_Input::processInputData() {
	std::vector<Neuron*>* cells = this->getCells();
	for (int i = 0; i < this->getNumCells(); i++) {
		this->cells[i]->sendToOutputs();
	}
}*/

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