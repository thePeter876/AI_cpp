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

	std::vector<int> nums{ 784,16,16,10 };
	NeuralNetwork* network = new NeuralNetwork(&nums/*, "ReLU"*/);
	network->randomParameterize(-1.0, 1.0, -1.0, 1.0);
	network->showInfo();
	//network->saveToFile("networkCheckValues.txt");
	std::vector<float> input;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 784; i++) {
			input.push_back(Neuron::getRand(1.0, 0.0));
		}
		network->computeResult(&input);
		input.clear();
	}
	//Queda demostrado que la red es capaz de devolver como output disti ntos valores si se le mandan distintos input

	std::cout << std::endl;

	//network->readFromFile("networkBoard.txt");
	//float in[2]{ 1.0,4.3 };

	/*std::vector<float> in{ 1.0,4.3 };
	network->computeResult(&in);
	in[0] = 3.0;
	in[1] = 6.0;
	network->computeResult(&in);
	network->showInfo();*/
	//network->saveToFile("network2.txt");
	//network->clear();
	return 0;
}