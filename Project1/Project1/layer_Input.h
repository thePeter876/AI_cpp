#pragma once
#include "layer.h"
#include "layer_Hidden.h"
#include "layer_Output.h"
class Layer_Input : public Layer
{
private:
	//std::vector<Neuron*> cells;
	//std::vector<float> inputs;
	Layer *nextLayer;
public:
	//Constructors
	Layer_Input(int num = 1, std::string n = "Unnamed", Layer* nl = nullptr);
	/*Layer_Input(Layer* nl, int n) :nextLayer(nl) {
		nl->setPreviousLayer(this);
	}*/

	//Get and set
	inline Layer* getNextLayer() { return nextLayer; }
	//inline std::vector<float>* getInputs() { return &inputs; }
	inline void setNextLayer(Layer* nl) { nextLayer = nl; }
	//inline void setInputs(std::vector<float>* i) { inputs = *i; }
	
	//AI functions
	void createCells();
	//void processInputData();

	std::string getInfo();
	//Destroy
	~Layer_Input() {}
};

