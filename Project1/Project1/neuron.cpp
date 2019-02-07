#include "neuron.h"


std::string Neuron::function;

float Neuron::getRand(int max, int min) {
	/*int range = max - min + 1;
	float v = rand() % range;
	v += min;
	std::cout << v << ", " << std::endl;
	return v;*/
	float v = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	//std::cout << v << ", " << std::endl;
	return v;
}

float Neuron::calculateValue() {
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
	return v;
}

void Neuron::sendToOutputs() {
	//this->calculateValue();
	for (int i = 0; i < this->outputs.size(); i++) {
		this->outputs[i]->setValue(this->value);
	}
}

void Neuron::randomize(int minBias, int maxBias, int minWeight, int maxWeight) {
	this->bias = Neuron::getRand(maxBias, minBias);
	for (int w = 0; w < this->outputs.size(); w++) {
		this->outputs[w]->setWeight(Neuron::getRand(minWeight, maxWeight));
	}
}