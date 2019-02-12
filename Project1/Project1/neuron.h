#pragma once
#define E 2.71828
#include <vector>
#include "transmitter.h"
#include <math.h>
#include <string>
#include <iostream>
//#include "neuralNetwork.h"
class Transmitter;
class Neuron
{
protected:
	//Vars
	float inputValue;
	float functionValue;
	float bias;
	std::vector<Transmitter*> inputs;
	std::vector<Transmitter*> outputs;
public:
	static const float& getRand(const int& max, const int& min);
	static const float& toFunction(const float& x);
	static const float& toDiffFunction (const float& x);
	static std::string function;
	//Constructor
	Neuron(float b = 0.0) : bias(b) {}
	
	//Get and Set
	inline float& getValue() { return functionValue; }
	inline const float& getInputValue() { return inputValue; }
	inline const float& getBias() { return bias; }
	inline float* getBiasPTR() { return &bias; }
	inline std::vector<Transmitter*>* getInputs() { return &inputs; }
	inline std::vector<Transmitter*>* getOutputs() { return &outputs; }
	inline void setValue(const float& v) { functionValue = v; }
	inline void setBias(const float& b) { bias = b; }
	inline void setInputs(std::vector<Transmitter*>* i) { inputs = *i; }
	inline void setOutputs(std::vector<Transmitter*>* o) { outputs = *o; }
	inline void addOutput(Transmitter* t) { this->outputs.push_back(t); }
	inline void addInput(Transmitter* t) { this->inputs.push_back(t); }

	//AI functions
	void randomize(const int &minBias, const int &maxBias, const int &minWeight, const int &maxWeight);
	const float& calculateValue();
	//void sendToOutputs();


	//Destroy
	~Neuron() {}

};
