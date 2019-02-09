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

	srand(Timer::getCurrentTime());
	std::vector<int> nums{ 2,100,100,2 };
	NeuralNetwork* network = new NeuralNetwork(&nums);
	//NeuralNetwork* network = new NeuralNetwork("network3.txt");
	network->showInfo();
	network->randomParameterize(-1.0,1.0,-1.0,1.0);
	network->saveToFile("network3.txt");

	std::vector<float> input{ 0.7, 0.3 };
	std::vector<float> expectedOutput{1.0,0.0};
	network->computeResult(&input, &expectedOutput);
	std::vector<std::vector<float>> inputs{ {0.7,0.3},{0.7,0.3},{0.7,0.3},{0.7,0.3} };
	std::vector<std::vector<float>> expectedOutputs{ {1.0,0.0},{1.0,0.0},{1.0,0.0},{1.0,0.0} };
	for (int i = 0; i < 5; i++) {
		network->deepLearn(&inputs, &expectedOutputs);
	}
	network->saveToFile("network4.txt");
	network->computeResult(&input, &expectedOutput);
	return 0;
}