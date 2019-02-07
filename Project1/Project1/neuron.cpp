#include "neuron.h"


std::string Neuron::function;

inline void Neuron::calculateValue() {
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
	
	
}