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
		Neuron* cell = new Neuron();
		new Transmitter_Input(cell);
		/*if (this->nextLayer != nullptr) {
			//std::vector<Transmitter*> t;
			std::vector<Neuron*>* nlCells = this->nextLayer->getCells();
			int numberOfT = nlCells->size();
			for (int j = 0; j < numberOfT;j++) {
				new Transmitter(cell, (*nlCells)[j]);
				//t.push_back(new Transmitter(cell,(*nlCells)[j]));
			}
			//cell->setOutputs(&t);
		}*/
		this->addCell(cell);
		//this->addCell(new Neuron());
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