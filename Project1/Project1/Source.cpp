#include "neuron.h"
#include "transmitter.h"
#include "layer.h"
#include "layer_Input.h"
#include "layer_Output.h"
#include "neuralNetwork.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include "timer.h"
#include <string>
int main(int argc, char argv[]) {
	/*int nums[4]{2,2,1,1};
	NeuralNetwork* network = new NeuralNetwork(4,nums,"sigmoid");
	network->randomParameterize(-5.0, 5.0, -5.0, 5.0);
	float in[2]{ 1.0,4.3 };
	//float in[784];
	float* ou;
	ou = network->computeResult(in, 2);
	network->showInfo();
	network->saveToFile("network.txt");
	network->clear();*/

	/*NeuralNetwork* network = new NeuralNetwork("network.txt");
	float in[2]{ 1.0,4.3 };
	network->computeResult(in, 2);
	network->showInfo();
	network->saveToFile("network2.txt");
	network->clear();*/

	int nums[4]{ 20,10,5,4 };
	NeuralNetwork* network = new NeuralNetwork(4, nums, "ReLU");
	network->randomParameterize(-5, 5, -5, 5);
	network->showInfo();

	std::cout << std::endl;

	network->readFromFile("network.txt");
	//float in[2]{ 1.0,4.3 };
	//network->computeResult(in, 2);
	network->showInfo();
	//network->saveToFile("network2.txt");
	//network->clear();
	return 0;
}