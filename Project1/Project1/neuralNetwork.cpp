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

std::vector<float>* NeuralNetwork::computeResult(std::vector<float>* input, std::vector<float>* expectedOutput) {
	
	if (input->size() != this->layers.front()->getNumCells()) {
		std::cout << "input data size is different from neural network input size" << std::endl;
		return nullptr;
	}
	else if (expectedOutput->size() != this->layers.back()->getNumCells()) {
		std::cout << "output data size is different from expected output data size" << std::endl;
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
					//DEBO CALCULAR AQU� EL VALOR CON CALCULATE VALUE?? NO DEBE HACERSE NING�N CALCULO PORQUE ENTONCES 
					//TE CARGAS EL INPUT QUE ACABAS DE SETEARLE. POR TANTO EL BIAS DE LA C�LULA ES UN DATO IN�TIL...
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

		//cost calculation
		float cost = 0;
		for (int i = 0; i < this->output->size(); i++)
			cost += pow(((*this->output)[i] - (*expectedOutput)[i]), 2);


		std::cout << "One iteration took " << iterationTime.getTimeElapsed() << "ms to complete, the cost was " << cost << std::endl;
	}
	return this->output;
}

bool NeuralNetwork::backPropagation(std::vector<float>* expectedOutput, Layer* CL, int currentIndex, std::vector<float>* gradient) {
	//this function should return a vector with a size of all transmitters + all biases and how they should change for the given input
	Layer* PL = CL->getPreviousLayer();
	int sizeCL = CL->getNumCells();
	int sizePL = PL->getNumCells();

	//hacer aqu� cambios necesarios en pesos y bias(de las neuronas de esta capa) y calcular expectedOutputPL
	std::vector<Neuron*>* cellsCL = CL->getCells();

	std::vector<float> diffValues(sizeCL);
	std::vector<float> costs(sizePL);

	for (int i = 0; i < sizeCL; i++) {
		std::vector<Transmitter*>* trans = (*cellsCL)[i]->getInputs();
		float diffValue = Neuron::toDiffFunction((*cellsCL)[i]->getInputValue());
		diffValues[i] = diffValue;
		int cost = 2 * ((*cellsCL)[i]->getValue() - (*expectedOutput)[i]);
		costs[i] = cost;
		//(*gradient)[currentIndex] = Neuron::toDiffFunction((*cells)[i]->getInputValue()) * 2 * ((*cells)[i]->getValue() - (*expectedOutput)[i]); //c�lculo del cambio en bias
		(*gradient)[currentIndex] += diffValue * cost; //c�lculo del cambio en bias
		currentIndex++;
		int numInputs = trans->size();
		for (int j = 0; j < numInputs; j++) {
			(*gradient)[currentIndex + j] += (*trans)[j]->getValue() * diffValue * cost; //c�lculo del cambio en weight
		}
		currentIndex += numInputs;
	}
	std::vector<float> expectedOutputPL(sizePL);
	std::vector<Neuron*>* cellsPL = PL->getCells();
	for (int i = 0; i < sizePL; i++) {
		std::vector<Transmitter*>* trans = (*cellsPL)[i]->getOutputs();
		int value = 0;
		//float diffValue = Neuron::toDiffFunction((*cellsCL)[i]->getInputValue());
		for (int j = 0; j < sizeCL/*trans->size()*/; j++) {
			value += (*trans)[j]->getWeight() * diffValues[j] * costs[j];
		}
		expectedOutputPL[i] = value;
	}

	//fin calculo gradiente
	if (PL != this->layers.front())
		this->backPropagation(&expectedOutputPL, PL, currentIndex, gradient);
	return true;
}

bool NeuralNetwork::deepLearn(std::vector<std::vector<float>>* inputs, std::vector<std::vector<float>>* expectedOutputs) { //cambiar para que reciba un vector de vectores con todos los resultados esperados
	int sizeInputs = inputs->size();
	int sizeOutputs = expectedOutputs->size();
	if (sizeInputs != sizeOutputs) {
		std::cout << "input data size is different from expectedOutputs data size" << std::endl;
		return false;
	} 
	else {
		
		
		//Comprobaci�n de los datos
		bool check= true;
		int rightSize = this->layers.front()->getNumCells();
		for (int i = 0; i < sizeInputs; i++) {
			if ((*inputs)[i].size() != rightSize)
				check = false;
		}
		rightSize = this->layers.back()->getNumCells();
		for (int i = 0; i < sizeOutputs; i++) {
			if ((*expectedOutputs)[i].size() != rightSize)
				check = false;
		}
		if (!check) return false;
		
		//Creaci�n del vector que guarda todos los parametros
		std::vector<float*> actualParameters;
		for (int i = this->layers.size()-1; i >= 0; i++) {
			for (int j = 0; j < this->layers[i]->getNumCells(); j++) {
				std::vector<Neuron*>* cells = this->layers[i]->getCells();
				actualParameters.push_back((*cells)[j]->getBiasPTR());
				for (int w = 0; w < (*cells)[j]->getInputs()->size(); w++) {
					std::vector<Transmitter*>* trans = (*cells)[j]->getInputs();
					actualParameters.push_back((*trans)[w]->getWeightPTR());
				}
			}
		}
		int sizeParameters = actualParameters.size();
		//Creaci�n de la variable que almacena el gradiente
		std::vector<float> gradient(sizeParameters);
		for (int i = 0; i < gradient.size(); i++) {
			gradient[i] = 0;
		}

		//BackPropagation
		int &iterations = sizeInputs;
		Timer backPropagationTime = Timer();
		for (int i = 0; i < iterations; i++) {
			this->computeResult(&((*inputs)[i]), &((*expectedOutputs)[i]));
			this->backPropagation(&((*expectedOutputs)[i]), this->layers.back(), 0, &gradient);
		}
		float totalTime = backPropagationTime.getTimeElapsed();

		//Aplicaci�n del gradiente a los par�metros
		for (int i = 0; i < sizeParameters; i++) {
			*(actualParameters[i]) += gradient[i] / iterations;
		}

		//Cleaning and ending
		actualParameters.clear();
		gradient.clear();
		std::cout << "Learning from " << iterations << " samples took around " << totalTime / (float)iterations << "ms per sample" << std::endl;
	}
	return true;
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