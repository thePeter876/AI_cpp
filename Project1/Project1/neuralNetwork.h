#pragma once
#include "layer.h"
#include "layer_Hidden.h"
#include "layer_Input.h"
#include "layer_Output.h"
#include "neuron.h"
#include <vector>
#include <iostream>
#include <string>
class NetWorkInfo {
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
};



class NeuralNetwork
{
private:
	std::vector<Layer*> layers;
public:
	NeuralNetwork(NetWorkInfo* info, std::string func = "sigmoid");




	void showInfo();
	~NeuralNetwork() {}
};

