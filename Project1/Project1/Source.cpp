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
	int nums[4]{2,2,1,1};
	NeuralNetwork* network = new NeuralNetwork(4,nums,"sigmoid");
	network->randomParameterize(-5.0, 5.0, 1.0, -1.0);
	float in[2]{ 1.0,4.3 };
	//float in[784];
	float* ou;
	ou = network->computeResult(in, 2);
	network->showInfo();
	
	return 0;
}