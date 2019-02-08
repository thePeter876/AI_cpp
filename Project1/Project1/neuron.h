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
	static float getRand(int max, int min = 0.0);
	static float toFunction(float x);
	static float toDiffFunction(float x);
	static std::string function;
	//Constructor
	Neuron(float b = 0.0) : bias(b) {}
	
	//Get and Set
	inline float getValue() { return functionValue; }
	inline float getInputValue() { return inputValue; }
	inline float getBias() { return bias; }
	inline float* getBiasPTR() { return &bias; }
	inline std::vector<Transmitter*>* getInputs() { return &inputs; }
	inline std::vector<Transmitter*>* getOutputs() { return &outputs; }
	inline void setValue(float v) { functionValue = v; }
	inline void setBias(float b) { bias = b; }
	inline void setInputs(std::vector<Transmitter*>* i) { inputs = *i; }
	inline void setOutputs(std::vector<Transmitter*>* o) { outputs = *o; }
	inline void addOutput(Transmitter* t) { this->outputs.push_back(t); }
	inline void addInput(Transmitter* t) { this->inputs.push_back(t); }

	//AI functions
	void randomize(int minBias, int maxBias, int minWeight, int maxWeight);
	float calculateValue();
	void sendToOutputs();


	//Destroy
	~Neuron() {}

};
