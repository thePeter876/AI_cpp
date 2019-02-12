#include "layer_Hidden.h"

Layer_Hidden::Layer_Hidden(int num, Layer* pl, std::string n)
{
	//this->setNumCells(num);
	this->numCells = num;
	if (pl != nullptr) {
		pl->setNextLayer(this);
		this->previousLayer = pl;
	}
	//this->setName(n);
	this->name = n;
}

Layer_Hidden::Layer_Hidden(int num, Layer* pl, Layer* nl, std::string n)
{
	//this->setNumCells(num);
	this->numCells = num;
	if (pl != nullptr) {
		pl->setNextLayer(this);
		this->previousLayer = pl;
	}
	if (nl != nullptr) {
		nl->setPreviousLayer(this);
		this->nextLayer = nl;
	}
	//this->setName((char*)n.c_str());
	this->name = (char*)n.c_str();
}


void Layer_Hidden::createCells() {
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

const std::string& Layer_Hidden::getInfo() {
	int numOfTransmitters = 0;
	for (int i = 0; i < this->numCells; i++) {
		numOfTransmitters += this->cells[i]->getOutputs()->size();
	}
	std::string inf = this->name + ", " + std::to_string(this->numCells) 
		+ " neurons. Transmitters to next layer: " + std::to_string(numOfTransmitters) + ". Prev: " 
		+ this->previousLayer->getName() + ", Next: " + this->nextLayer->getName() + ".";
	return inf;
}