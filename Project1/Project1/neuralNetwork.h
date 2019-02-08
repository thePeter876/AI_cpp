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
	std::vector<float>* output = new std::vector<float>;
public:
	NeuralNetwork(std::vector<int>* cells, std::string func = "sigmoid");
	NeuralNetwork(const char* fileName);
	void createNetwork(std::vector<int>* cells);
	std::vector<float>* computeResult(std::vector<float>* input);
	bool backPropagation(std::vector<float>* expectedOutput, Layer* currentLayer, int currentIndex, std::vector<float>* gradient);
	bool deepLearn(std::vector<std::vector<float>>* inputs,std::vector<std::vector<float>>* expectedOutputs);

	inline std::vector<float>* getOutput() { return output; }
	void randomParameterize(float minBias, float maxBias, float minWeight, float maxWeight);
	void showInfo();

	//FILES
	bool saveToFile(const char* fileName);
	bool readFromFile(const char* fileName);
	void clear();

	~NeuralNetwork() {}
};

