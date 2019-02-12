#pragma once
#include "layer.h"
#include "layer_Input.h"
#include "layer_Output.h"
#include "neuron.h"
class Layer_Hidden : public Layer
{
protected:
	Layer *previousLayer;
	Layer *nextLayer;
public:
	//Constructors
	//Layer_Hidden(Layer* pl);
	Layer_Hidden(int num = 1, Layer* pl = nullptr, std::string n = "Unnamed");
	Layer_Hidden(int num = 1, Layer* pl = nullptr, Layer* nl = nullptr, std::string n ="Unnamed");

	//Get and Set
	inline Layer* getPreviousLayer() { return previousLayer; }
	inline Layer* getNextLayer() { return nextLayer; }
	inline void setPreviousLayer(Layer* pl) { previousLayer = pl; }
	inline void setNextLayer(Layer* nl) { nextLayer = nl; }
	
	//AI functions
	void createCells();
	//void processInputData();

	const std::string& getInfo();
	~Layer_Hidden() {}
};

