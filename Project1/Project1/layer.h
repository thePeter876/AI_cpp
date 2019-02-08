#pragma once
#include "neuron.h"
#include <vector>
#include <string>
class Layer
{
protected:
	std::vector<Neuron*> cells;
	int numCells;
	std::string name;
	//Layer *nextLayer, *previousLayer;
public:
	//Constructor
	//Layer(Layer* pl) : previousLayer(pl) {}
	//Layer(Layer* pl, Layer* nl) : previousLayer(pl), nextLayer(nl) {}
	Layer() {}

	//Get and set
	inline void setName(std::string n) { name = n; }
	inline std::string getName() { return name; }
	inline void setNumCells(int n) { numCells = n; }
	inline int getNumCells() { return numCells; }
	inline std::vector<Neuron*>* getCells() { return &cells; }
	inline void addCell(Neuron* n) { this->cells.push_back(n); }
	inline virtual Layer* getPreviousLayer() { return this; }
	inline virtual Layer* getNextLayer() { return this; }
	//inline void setPreviousLayer(Layer* pl) { previousLayer = pl; }
	//inline void setNextLayer(Layer* nl) { nextLayer = nl; }

	//AI functions
	void randomize(int minBias, int maxBias, int minWeight, int maxWeight);
	void processInputData();
	virtual void createCells() = 0;
	virtual void setNextLayer(Layer* nl) {}
	virtual void setPreviousLayer(Layer* pl) {}

	virtual std::string getInfo();
	//Destroy
	~Layer() {}
};

