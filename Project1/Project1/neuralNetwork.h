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

class NeuralNetwork
{
protected:
	std::vector<Layer*> layers;
	std::vector<float>* output = new std::vector<float>;
	int computeTime = 0.0;
public:
	static float learnSpeed;
	NeuralNetwork(std::vector<int>* cells, std::string func = "sigmoid");
	NeuralNetwork(const char* fileName);
	inline int getComputeTime(){ return computeTime; }
	inline void resetComputeTime() { this->computeTime = 0.0; }

	void createNetwork(std::vector<int>* cells);
	std::vector<float>* computeResult(std::vector<float>* input, std::vector<float>* expectedOutput);
	bool backPropagation(std::vector<float>* expectedOutput, Layer* currentLayer, int currentIndex, std::vector<float>* gradient);
	bool deepLearn(std::vector<std::vector<float>>* inputs,std::vector<std::vector<float>>* expectedOutputs, float speed = 0.1);

	inline std::vector<float>* getOutput() { return output; }
	void randomParameterize(float minBias, float maxBias, float minWeight, float maxWeight);
	void showInfo();

	//FILES
	bool saveToFile(const char* fileName);
	bool readFromFile(const char* fileName);
	void clear();

	~NeuralNetwork() {}
	
};

