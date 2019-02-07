#include "layer_Hidden.h"

Layer_Hidden::Layer_Hidden(int num, Layer* pl, std::string n)
{
	this->setNumCells(num);
	if (pl != nullptr) {
		pl->setNextLayer(this);
		this->previousLayer = pl;
	}
	this->setName(n);
}

Layer_Hidden::Layer_Hidden(int num, Layer* pl, Layer* nl, std::string n)
{
	this->setNumCells(num);
	if (pl != nullptr) {
		pl->setNextLayer(this);
		this->previousLayer = pl;
	}
	if (nl != nullptr) {
		nl->setPreviousLayer(this);
		this->nextLayer = nl;
	}
	this->setName((char*)n.c_str());
}


void Layer_Hidden::createCells() {
	int n = this->getNumCells();
	for (int i = 0; i < n; i++) {
		Neuron* cell = new Neuron();
		if (this->previousLayer != nullptr) {
			std::vector<Neuron*>* plCells = this->previousLayer->getCells();
			int numberOfT = plCells->size();
			for (int j = 0; j < numberOfT; j++) {
				new Transmitter_Inner((*plCells)[j], cell);
			}
		}
		this->addCell(cell);
	}
}

/*void Layer_Hidden::processInputData() {
	std::vector<Neuron*>* cells = this->getCells();
	for (int i = 0; i < this->getNumCells(); i++) {
		this->cells[i]->sendToOutputs();
	}
}*/


std::string Layer_Hidden::getInfo() {
	int numOfTransmitters = 0;
	for (int i = 0; i < this->getNumCells(); i++) {
		numOfTransmitters += (*this->getCells())[i]->getOutputs()->size();
	}
	std::string inf = this->getName() + ", " + std::to_string(this->getNumCells()) 
		+ " neurons. Transmitters to next layer: " + std::to_string(numOfTransmitters) + ". Prev: " 
		+ this->getPreviousLayer()->getName() + ", Next: " + this->getNextLayer()->getName() + ".";
	return inf;
}