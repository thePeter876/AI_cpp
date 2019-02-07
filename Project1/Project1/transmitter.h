#pragma once
#include "neuron.h"
class Neuron;

class Transmitter
{
	Neuron* origin;
	Neuron* destiny;
	float weight;
	float transportedValue;
public:
	//Constructor
	Transmitter(Neuron* o, Neuron* d);

	//Get and Set
	inline float getWeight() { return weight; }
	inline float getValue() { return transportedValue; }
	inline void setWeight(float w) { weight = w; }
	inline void setValue(float v) { transportedValue = v; }

	//Destroy
	~Transmitter() {}
};

