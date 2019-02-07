#include "neuron.h"


std::string Neuron::function;

void Neuron::calculateValue() {
	float v = 0.0;
	for (int i = 0; i < this->inputs.size(); i++) {
		v += this->inputs[i]->getValue() * this->inputs[i]->getWeight();
	}
	v += this->bias;

	if (Neuron::function == "sigmoid") {
		//Sigmoid Function
		v = 1 / (1 + pow(E, -v));
	}
	else if (Neuron::function == "ReLU") {
		//ReLU Function
		if (v < 0) v = 0;
	}
	else /*sigmoid by default*/{
		//Sigmoid Function
		v = 1 / (1 + pow(E, -v));
	}
	this->value = v;
}

void Neuron::sendToOutputs() {
	this->calculateValue();
	for (int i = 0; i < this->outputs.size(); i++) {
		this->outputs[i]->setValue(this->value);
	}
}