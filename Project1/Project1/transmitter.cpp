#include "transmitter.h"
Transmitter::Transmitter(Neuron* o, Neuron* d) {
	this->origin = o;
	this->destiny = d;
	this->weight = 0.0;
	//this->transportedValue = 0.0;

	o->addOutput(this);
	d->addInput(this);
}
const float& Transmitter::getValue() {
	return origin->getValue();
}