#include <iostream>

class FCNeuron{
public:
	double inputValue;
	double reluValue;
	
	void updateRelu(){
		tanh(inputValue);
	}
};