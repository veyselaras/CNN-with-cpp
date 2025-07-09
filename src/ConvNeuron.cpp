#include <iostream>

class ConvNeuron{
public:
	double inputValue;
	double reluValue;
	
	void updateRelu(){
		tanh(inputValue);
	}
};