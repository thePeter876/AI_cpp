#pragma once
#include "layer.h"
#include "layer_Hidden.h"
#include "layer_Input.h"
#include "layer_Output.h"
#include "neuron.h"
#include <vector>
#include <iostream>
#include <string>
#include "timer.h"
#include <fstream>
#include <sstream>
/*class NetWorkInfo {
private:
	int numLayers;
	int* numCells;
public:
	NetWorkInfo(int n, int* c) : numLayers(n), numCells(c) {}

	inline int getNumLayers() { return numLayers; }
	inline int* getNumCells() { return numCells; }
	inline void setNumLayers(int n) { numLayers = n; }
	inline void setNumCells(int* c) { numCells = c; }
	NetWorkInfo() {}
};*/



class NeuralNetwork
{
protected:
	std::vector<Layer*> layers;
	float *output;
public:
	NeuralNetwork(int n, int*c, std::string func = "sigmoid");
	NeuralNetwork(const char* fileName);
	void createNetwork(int n, int*c);
	float* computeResult(float input[], int inputSize);


	inline float* getOutput() { return output; }
	void randomParameterize(float minBias, float maxBias, float minWeight, float maxWeight);
	void showInfo();

	//FILES
	bool saveToFile(const char* fileName);
	bool readFromFile(const char* fileName);
	void clear();

	~NeuralNetwork() {}
};

