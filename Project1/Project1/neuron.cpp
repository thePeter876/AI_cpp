#include "neuron.h"


std::string Neuron::function;

const float& Neuron::getRand(const int &max, const int &min) {
	float v = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	return v;
}

const float& Neuron::toFunction(const float& x) {
	float real = x;
	if (Neuron::function == "sigmoid") {
		//Sigmoid Function
		real = 1 / (1 + pow(E, -real));
	}
	else if (Neuron::function == "ReLU") {
		//ReLU Function
		if (real < 0) real = 0;
	}
	else /*sigmoid by default*/ {
		//Sigmoid Function
		real = 1 / (1 + pow(E, -real));
	}
	return real;
}

const float& Neuron::toDiffFunction(const float& x) {
	float real = x;
	if (Neuron::function == "sigmoid") {
		//Sigmoid Function
		real = pow(E, -real) / pow((pow(E, -real) + 1), 2);
	}
	else if (Neuron::function == "ReLU") {
		//ReLU Function
		if (real < 0) real = 0;
		else real = 1;
	}
	else /*sigmoid by default*/ {
		//Sigmoid Function
		real = pow(E, -real) / pow((pow(E, -real) + 1), 2);
	}
	return real;
}

const float& Neuron::calculateValue() {
	float v = 0.0;
	for (int i = 0; i < this->inputs.size(); i++) {
		v += this->inputs[i]->getValue() * this->inputs[i]->getWeight();
	}
	v += this->bias;
	this->inputValue = v;

	v = Neuron::toFunction(v);
	this->functionValue = v;
	return v;
}

/*void Neuron::sendToOutputs() {
	//this->calculateValue();
	for (int i = 0; i < this->outputs.size(); i++) {
		this->outputs[i]->setValue(this->functionValue);
	}
}*/

void Neuron::randomize(const int &minBias, const int &maxBias, const int &minWeight, const int &maxWeight) {
	this->bias = Neuron::getRand(maxBias, minBias);
	for (int w = 0; w < this->outputs.size(); w++) {
		this->outputs[w]->setWeight(Neuron::getRand(minWeight, maxWeight));
	}
}