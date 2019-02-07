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
	/*time_t timeInSec;
	time(&timeInSec);*/
	
	//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	Timer myTimer = Timer();

	int nums[4]{784,16,16,10};
	NetWorkInfo* structure = new NetWorkInfo(4, nums);
	NeuralNetwork* network = new NeuralNetwork(structure,"ReLU");
	std::cout << "Creating the network took " << myTimer.getTimeElapsed() << "ms to complete" << std::endl;
	network->showInfo();

	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "Creating the network took " <<  << "ms to complete" << std::endl;
	

	/*time_t passed;
	time(&passed);
	std::cout << "Completed in: "<< (passed - timeInSec) << std::endl;*/
	int i = 0;
}