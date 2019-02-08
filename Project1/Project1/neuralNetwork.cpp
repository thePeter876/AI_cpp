#include "neuralNetwork.h"



NeuralNetwork::NeuralNetwork(std::vector<int>* cells, std::string func)
{
	Neuron::function = func;
	this->createNetwork(cells);
}

NeuralNetwork::NeuralNetwork(const char* fileName) {
	this->readFromFile(fileName);
}

void NeuralNetwork::createNetwork(std::vector<int>* cells) {
	Timer creationTime = Timer();
	int n = cells->size();
	for (int i = 0; i < n; i++) {
		//name creation
		std::string buf = "L" + std::to_string(i);

		if (i > 0 && i < n - 1) {
			this->layers.push_back(new Layer_Hidden((*cells)[i], this->layers[i - 1], buf));
		}
		else if (i == 0) {
			this->layers.push_back(new Layer_Input((*cells)[i], buf.c_str()));
		}
		else if (i == n - 1) {
			this->layers.push_back(new Layer_Output((*cells)[i], this->layers[i - 1], buf.c_str()));
		}
	}
	for (int j = 0; j < this->layers.size(); j++) {
		this->layers[j]->createCells();
	}
	 std::cout << "Creating the network took " << creationTime.getTimeElapsed() << "ms to complete" << std::endl;
}

void NeuralNetwork::randomParameterize(float minBias, float maxBias, float minWeight, float maxWeight) {
	Timer parameterizeTime = Timer();
	int seed = Timer::getCurrentTime();
	srand(seed);

	for (int i = 0; i < this->layers.size(); i++) {
		this->layers[i]->randomize(minBias, maxBias, minWeight, maxWeight);
	}
	
	std::cout << "Parameterizing the network took " << parameterizeTime.getTimeElapsed() <<"ms to complete. Current seed is " << seed << std::endl;
}

std::vector<float>* NeuralNetwork::computeResult(std::vector<float>* input) {
	
	if (input->size() != this->layers[0]->getNumCells()) {
		std::cout << "input data size is different from neural network input size" << std::endl;
		return nullptr;
	}
	else {
		Timer iterationTime = Timer();
		int size = this->layers.size();
		this->output->clear();
		for (int i = 0; i < size; i++) {
			std::vector<Neuron*>* cells = this->layers[i]->getCells();
			if (i == 0) {
				for (int j = 0; j < this->layers[0]->getNumCells(); j++) {
					(*cells)[j]->setValue((*input)[j]);
					//DEBO CALCULAR AQUÍ EL VALOR CON CALCULATE VALUE?? NO DEBE HACERSE NINGÚN CALCULO PORQUE ENTONCES 
					//TE CARGAS EL INPUT QUE ACABAS DE SETEARLE. POR TANTO EL BIAS DE LA CÉLULA ES UN DATO INÚTIL...
					//(*cells)[j]->calculateValue();
					(*cells)[j]->sendToOutputs();
				}
			}
			else if (i == size - 1) {
				
				std::cout << "the output is: ";
				for (int j = 0; j < this->layers[i]->getNumCells(); j++) {
					float val = (*cells)[j]->calculateValue();
					//(*this->output)[j] = (*cells)[j]->getValue();
					this->output->push_back(val);
					//(*this->output)[j] = val;
					std::cout << val << ", ";
				}
				std::cout << std::endl;
			}
			else {
				for (int j = 0; j < this->layers[i]->getNumCells(); j++) {
					(*cells)[j]->calculateValue();
					(*cells)[j]->sendToOutputs();
				}
			}
		}
		std::cout << "One iteration took " << iterationTime.getTimeElapsed() << "ms to complete" << std::endl;
	}
	return this->output;
}

void NeuralNetwork::showInfo() {
	for (int i = 0; i < this->layers.size(); i++) {
		std::cout << this->layers[i]->getInfo() << std::endl;
	}
}

bool NeuralNetwork::saveToFile(const char* fileName) {
	
	std::ofstream myfile(fileName);
	if (myfile.is_open()) {
		Timer saveTime = Timer();
		int numLayers = this->layers.size();
		myfile << numLayers << ' ' <<  Neuron::function << std::endl;
		for (int i = 0; i < numLayers; i++) {
			myfile << "L: " << this->layers[i]->getName() << ' ' << this->layers[i]->getNumCells() << std::endl;
		}
		for (int i = 0; i < numLayers; i++) {
			for (int j = 0; j < this->layers[i]->getNumCells(); j++) {
				std::vector<Neuron*>* cells = this->layers[i]->getCells();
				myfile << "C: " << (*cells)[j]->getBias();
				std::vector<Transmitter*>* trans = (*cells)[j]->getInputs();
				for (int w = 0; w < (*trans).size(); w++) {
					myfile << ' ' << (*trans)[w]->getWeight();
				}
				myfile << std::endl;
			}
		}

		myfile.close();
		std::cout << "Saving the network took " << saveTime.getTimeElapsed() << "ms to complete" << std::endl;
	}
	else {
		std::cout << "Unable to open file";
		return false;
	}
	return true;
}

bool NeuralNetwork::readFromFile(const char* fileName) {
	this->clear();
	std::string line;
	std::ifstream myfile(fileName);

	//creation vars
	int numLayers;

	if (myfile.is_open())
	{
		//First line
		getline(myfile, line);
		std::istringstream lineStream(line);
		lineStream >> numLayers;
		lineStream >> Neuron::function;

		//Layer lines
		std::vector<int> numCells;
		for (int i = 0; i < numLayers; i++) {
			getline(myfile, line);
			lineStream = std::istringstream(line);
			int aux;
			lineStream >> line >> line >> aux;
			numCells.push_back(aux);
		}
		this->createNetwork(&numCells);

		//Cell lines
		for (int i = 0; i < numLayers; i++) {
			std::vector<Neuron*>* cells = this->layers[i]->getCells();
			for (int j = 0; j < this->layers[i]->getNumCells(); j++) {
				getline(myfile, line);
				lineStream = std::istringstream(line);
				float bias;
				lineStream >> line >> bias;
				(*cells)[j]->setBias(bias);
				std::vector<Transmitter*>* trans = (*cells)[j]->getInputs();
				for (int k = 0; k < trans->size(); k++) {
					float w;
					lineStream >> w;
					(*trans)[k]->setWeight(w);
				}
			}
		}


		myfile.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
		return false;
	}
	return true;
}

void NeuralNetwork::clear() {
	this->saveToFile("backup.txt");
	Timer cleanTime = Timer();
	for (int i = 0; i < this->layers.size(); i++) {
		std::vector<Neuron*>* cells = this->layers[i]->getCells();
		for (int j = 0; j < this->layers[i]->getNumCells(); j++) {
			std::vector<Transmitter*>* trans = (*cells)[j]->getInputs();
			for (int w = 0; w < trans->size(); w++) {
				delete (*trans)[w];
			}
			trans->clear();
		}
		cells->clear();
		delete this->layers[i];
	}
	this->layers.clear();
	std::cout << "Cleaning the network took " << cleanTime.getTimeElapsed() << "ms to complete" << std::endl;
}