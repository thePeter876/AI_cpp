#include "neuralNetwork.h"



NeuralNetwork::NeuralNetwork(int n, int *cells, std::string func)
{
	Timer creationTime = Timer();
	Neuron::function = func;
	for (int i = 0; i < n; i++) {
		//name creation
		std::string buf = "L" + std::to_string(i);

		if (i > 0 && i < n - 1) {
			this->layers.push_back(new Layer_Hidden(cells[i], this->layers[i - 1], buf));
		}
		else if (i == 0) {
			this->layers.push_back(new Layer_Input(cells[i], buf.c_str()));
		}
		else if (i == n - 1) {
			this->layers.push_back(new Layer_Output(cells[i], this->layers[i - 1], buf.c_str()));
		}
	}
	for (int j = 0; j < this->layers.size(); j++) {
		this->layers[j]->createCells();
	}
	std::cout << "Creating the network took " << creationTime.getTimeElapsed() << "ms to complete" << std::endl;
}


void NeuralNetwork::randomParameterize(float minBias, float maxBias, float minWeight, float maxWeight) {
	int seed = Timer::getCurrentTime();
	std::cout << "Current seed is " << seed << std::endl;
	srand(seed);

	for (int i = 0; i < this->layers.size(); i++) {
		this->layers[i]->randomize(minBias, maxBias, minWeight, maxWeight);
	}
	
}

float* NeuralNetwork::computeResult(float input[], int inputSize) {
	
	if (inputSize != this->layers[0]->getNumCells()) {
		std::cout << "input data size is different from neural network input size" << std::endl;
		return nullptr;
	}
	else {
		Timer* iterationTime = new Timer();
		//for(int i = 0; i < )
		int size = this->layers.size();
		delete[] output;
		this->output = new float[this->layers[size - 1]->getNumCells()];
		for (int i = 0; i < size; i++) {
			std::vector<Neuron*>* cells = this->layers[i]->getCells();
			if (i == 0) {
				for (int j = 0; j < this->layers[0]->getNumCells(); j++) {
					(*cells)[j]->setValue(input[j]);
					//DEBO CALCULAR AQUÍ EL VALOR CON CALCULATE VALUE??
					(*cells)[j]->calculateValue();
					(*cells)[j]->sendToOutputs();
				}
			}
			else if (i == size - 1) {
				
				std::cout << "the output is: ";
				for (int j = 0; j < this->layers[i]->getNumCells(); j++) {
					float val = (*cells)[j]->calculateValue();
					this->output[j] = (*cells)[j]->getValue();
					this->output[j] = val;
					std::cout << val << ", ";
				}
				//std::cout << std::endl;
			}
			else {
				for (int j = 0; j < this->layers[i]->getNumCells(); j++) {
					(*cells)[j]->calculateValue();
					(*cells)[j]->sendToOutputs();
				}
			}
		}
		std::cout << "One iteration took " << iterationTime->getTimeElapsed() << "ms to complete" << std::endl;
		delete iterationTime;
	}
	return this->output;
}

void NeuralNetwork::showInfo() {
	for (int i = 0; i < this->layers.size(); i++) {
		std::cout << this->layers[i]->getInfo() << std::endl;
	}
}


