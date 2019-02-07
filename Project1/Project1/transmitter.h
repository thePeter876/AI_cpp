#pragma once
#include "neuron.h"
class Neuron;

class Transmitter
{
protected:
	//Neuron* origin;
	//Neuron* destiny;
	//float weight;
	float transportedValue;
public:
	//Constructor
	Transmitter() {}

	//Get and Set
	inline float getValue() { return transportedValue; }
	inline void setValue(float v) { transportedValue = v; }
	inline virtual float getWeight() = 0;
	//Destroy
	~Transmitter() {}
};

/*class Transmitter_Input : public Transmitter
{
protected:
	Neuron* destiny;
public:
	Transmitter_Input(Neuron* d);
	inline float getWeight() { return 1.0; }
};

class Transmitter_Output : public Transmitter
{
protected:
	Neuron* origin;
public:
	Transmitter_Output(Neuron* o);
	inline float getWeight() { return 1.0; }
};*/

class Transmitter_Inner : public Transmitter {
protected:
	Neuron* origin;
	Neuron* destiny;
	float weight;
public:
	Transmitter_Inner(Neuron* o, Neuron* d);
	inline void setWeight(float w) { weight = w; }
	inline float getWeight() { return weight; }
};

