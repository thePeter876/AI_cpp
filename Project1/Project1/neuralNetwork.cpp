#include "neuralNetwork.h"
NeuralNetwork::NeuralNetwork(int n, int *cells, std::string func)
{
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
	//delete info;
}

float* NeuralNetwork::computeResult(float input[], int inputSize) {
	
	if (inputSize != this->layers[0]->getNumCells()) {
		std::cout << "input data size is different from neural network input size" << std::endl;
		return nullptr;
	}
	else {
		//for(int i = 0; i < )
	}
}

void NeuralNetwork::showInfo() {
	for (int i = 0; i < this->layers.size(); i++) {
		std::cout << this->layers[i]->getInfo() << std::endl;
	}
}


