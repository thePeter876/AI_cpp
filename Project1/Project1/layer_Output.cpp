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
			//std::vector<Transmitter*> tList;
			std::vector<Neuron*>* plCells = this->previousLayer->getCells();
			int numberOfT = plCells->size();
			for (int j = 0; j < numberOfT; j++) {
				new Transmitter((*plCells)[j], cell);
				//tList.push_back(new Transmitter((*plCells)[j], cell));
			}
			//cell->setInputs(&tList);
		}
		this->addCell(cell);
	}
}

std::string Layer_Output::getInfo() {
	/*int numOfTransmitters = 0;
	for (int i = 0; i < this->getNumCells(); i++) {
		numOfTransmitters += (*this->getCells())[i]->getOutputs()->size();
	}*/
	std::string inf = this->getName() + ", " + std::to_string(this->getNumCells()) 
		+ " neurons. Prev: " + this->getPreviousLayer()->getName() + ".";
	return inf;
}