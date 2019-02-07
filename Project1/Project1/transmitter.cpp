#include "transmitter.h"
Transmitter_Inner::Transmitter_Inner(Neuron* o, Neuron* d) {
	this->origin = o;
	this->destiny = d;
	this->weight = 0.0;
	this->transportedValue = 0.0;

	o->addOutput(this);
	d->addInput(this);
}

/*Transmitter_Input::Transmitter_Input(Neuron* d) {
	this->destiny = d;
	this->transportedValue = 0.0;

	d->addInput(this);
}
*/
/*Transmitter_Output::Transmitter_Output(Neuron* o) {
	this->origin = o;
	this->transportedValue = 0.0;

	o->addOutput(this);
}*/