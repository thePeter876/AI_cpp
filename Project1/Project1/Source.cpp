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
	Timer myTimer = Timer();
	int nums[4]{784,16,16,10};
	NeuralNetwork* network = new NeuralNetwork(4,nums,"ReLU");
	std::cout << "Creating the network took " << myTimer.getTimeElapsed() << "ms to complete" << std::endl;
	network->showInfo();
	return 0;
}