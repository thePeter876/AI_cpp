#pragma once
#include "layer.h"
#include "layer_Input.h"
#include "layer_Hidden.h"
class Layer_Output : public Layer
{
private:
	//std::vector<Neuron*> cells;
	std::vector<float> outputs;
	Layer *previousLayer;
public:
	//Constructors
	/*Layer_Output(Layer* pl) :previousLayer(pl) {
		pl->setNextLayer(this);
	}*/
	Layer_Output(int num = 1, Layer* pl = nullptr, std::string n = "Unnamed");
	/*Layer_Output(Layer_Input* pl) :previousLayer(pl) {
		pl->setNextLayer(this);
	}*/ //put here the case of hidden layer

	//Get and set
	inline Layer* getPreviousLayer() { return previousLayer; }
	inline std::vector<float>* getOutputs() { return &outputs; }
	inline void setPreviousLayer(Layer* pl) { previousLayer = pl; }

	//AI functions
	void createCells();
	std::string getInfo();
	//Destroy
	~Layer_Output() {}
};

