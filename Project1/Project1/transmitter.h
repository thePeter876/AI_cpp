#pragma once
#include "neuron.h"
class Neuron;

class Transmitter
{
private:
	Neuron* origin;
	Neuron* destiny;
	float weight;
	//float transportedValue;
public:
	//Constructor
	Transmitter(Neuron* o, Neuron* d);

	//Get and Set
	//inline float getValue() { return transportedValue; }
	const float& getValue();/* { return origin->getValue(); }*/
	//inline void setValue(float v) { transportedValue = v; }
	inline const float& getWeight() { return weight; }
	inline float* getWeightPTR() { return &weight; }
	inline void setWeight(const float &w) { weight = w; }
	//Destroy
	~Transmitter() {}
};

