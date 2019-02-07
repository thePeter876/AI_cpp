#include "neuralNetwork.h"



NeuralNetwork::NeuralNetwork(NetWorkInfo* info, std::string func)
{
	Neuron::function = func;
	int num = info->getNumLayers();
	int* cells = info->getNumCells();

	for (int i = 0; i < num; i++) {
		//name creation
		std::string buf = "L" + std::to_string(i);
		
		if (i > 0 && i < num-1) {
			this->layers.push_back(new Layer_Hidden(cells[i],this->layers[i-1], buf));
		}
		else if (i == 0) {
			this->layers.push_back(new Layer_Input(cells[i], buf.c_str()));
		}
		else if (i == num - 1) {
			this->layers.push_back(new Layer_Output(cells[i], this->layers[i - 1], buf.c_str()));
		}
	}
	for (int j = 0; j < this->layers.size(); j++) {
		this->layers[j]->createCells();
	}
	delete info;
}

void NeuralNetwork::showInfo() {
	for (int i = 0; i < this->layers.size(); i++) {
		std::cout << this->layers[i]->getInfo() << std::endl;
	}
}


