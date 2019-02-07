#pragma once
#define E 2.71828
#include <vector>
#include "transmitter.h"
#include <math.h>
#include <string>
class Transmitter;
class Neuron
{
private:
	//Vars
	float value;
	float bias;
	std::vector<Transmitter*> inputs;
	std::vector<Transmitter*> outputs;
public:
	static std::string function;
	//Constructor
	Neuron(float b = 0.0) : bias(b) {}
	
	//Get and Set
	inline float getValue() { return value; }
	inline float getBias() { return bias; }
	inline std::vector<Transmitter*>* getInputs() { return &inputs; }
	inline std::vector<Transmitter*>* getOutputs() { return &outputs; }
	inline void setValue(float v) { value = v; }
	inline void setBias(float b) { bias = b; }
	inline void setInputs(std::vector<Transmitter*>* i) { inputs = *i; }
	inline void setOutputs(std::vector<Transmitter*>* o) { outputs = *o; }
	inline void addOutput(Transmitter* t) { this->outputs.push_back(t); }
	inline void addInput(Transmitter* t) { this->inputs.push_back(t); }

	//AI functions
	float calculateValue();
	void sendToOutputs();


	//Destroy
	~Neuron() {}

};
