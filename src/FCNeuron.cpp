#include <iostream>

class FCNeuron{
public:
	double inputValue;
	double reluValue;
	
	double *weightMatrice;
	
	FCNeuron(int sizeOfWeightMatrice){
		weightMatrice = new double[sizeOfWeightMatrice];
	}
	
	FCNeuron(){	}
	
	~FCNeuron(){
		delete[] arr;
	}
	
	void updateRelu(){
		tanh(inputValue);
	}
};