#include <iostream>
#include <cmath>
#include <random>

#define FILTER_SIZE = 5
#define FILTER_NUMBER_FIRST = 6
#define FILTER_NUMBER_SECOND = 16
#define FIRST_CONVLAYER_SIZE = 28
#define FIRST_POOLAYER_SIZE = 14
#define SECOND_CONVLAYER_SIZE = 10
#define SECOND_FILTER_SIZE = 10
#define SECOND_POOLAYER_SIZE = 5
#define THIRD_CONVLAYER_SIZE = 120
#define INPUT_SIZE = 32

class NetworkAdmin{
private:
	//	input
	double input[INPUT_SIZE][INPUT_SIZE];

	// layer matrixes
	ConvNeuron convOneArr[FILTER_NUMBER_FIRST][FIRST_CONVLAYER_SIZE][FIRST_CONVLAYER_SIZE];
	double convOneBias[FILTER_NUMBER_FIRST];
	double poolingOneArr[FILTER_NUMBER_FIRST][FIRST_POOLAYER_SIZE][FIRST_POOLAYER_SIZE];
	ConvNeuron convTwoArr[FILTER_NUMBER_SECOND][SECOND_CONVLAYER_SIZE][SECOND_CONVLAYER_SIZE];
	double convOneBias[FILTER_NUMBER_SECOND];
	double poolingOneArr[FILTER_NUMBER_SECOND][SECOND_POOLAYER_SIZE][SECOND_POOLAYER_SIZE];
	double convThreeArr[THIRD_CONVLAYER_SIZE];
	
	FCNeuron fcLayerOne[THIRD_CONVLAYER_SIZE];
	FCNeuron fcLayerTwo[86];
	FCNeuron fcLayerThree[10];
	
	
	// filters
	double firstLayerFilter[FILTER_NUMBER_FIRST][FILTER_SIZE][FILTER_SIZE];
	double secondLayerFilter[FILTER_NUMBER_SECOND][FILTER_SIZE][FILTER_SIZE];
	double thirdLayerFilter[THIRD_CONVLAYER_SIZE][FILTER_SIZE][FILTER_SIZE];
	
	double tanhDerivative(double value){//TEKRAR BAK BURAYA EKSIK VAR
		return 1 - power(tanh(value),2)
	}
	
	void matriceMult(int filterNumber, int row, int column){
		int filterRowCounter = 0;
		int filterColumnCounter = 0;
		int convSum = 0;
		switch(filterNumber){
			case 6:
				for(int i = 0; i < filterNumber; i++){//width
					for(int j = column; j < column + 5; j++){//row
						for(int k = row; k < row + 5; k++){//column
							convSum = firstLayerFilter[i][filterRowCounter][filterColumnCounter]*input[j][k];
						}
						filterColumnCounter = 0;
					}
					filterRowCounter = 0;
					convOneArr[i][j][k] = convSum + convOneBias[i];
				}
				break;
			
			case 16:
				for(int i = 0; i < filterNumber; i++){//width
					for(int j = column; j < column + 5; j++){//row
						for(int k = row; k < row + 5; k++){//column
							convSum = secondLayerFilter[i][filterRowCounter][filterColumnCounter]*input[j][k];
						}
						filterColumnCounter = 0;
					}
					filterRowCounter = 0;
					convOneArr[i][j][k] = convSum + convOneBias[i];
				}
				break;
			
			case 120:
				for(int i = 0; i < filterNumber; i++){//width
					for(int j = column; j < column + 5; j++){//row
						for(int k = row; k < row + 5; k++){//column
							convSum = thirdLayerFilter[i][filterRowCounter][filterColumnCounter]*input[j][k];
						}
						filterColumnCounter = 0;
					}
					filterRowCounter = 0;
					convOneArr[i][j][k] = convSum + convOneBias[i];
				}
				break;
			
			default:
				break;
		}
	}
	
	void convolution(int pad = 0, int stride = 1, string name){
		if(pad =! 0) {
			//SONRA BAK
		}
		else{
			switch(name){
				case layerOne:
					for(i = 0; i < FILTER_NUMBER_FIRST; i++){
						for(j = 0; j < INPUT_SIZE-FILTER_SIZE+1; j++){
							matriceMult(FILTER_NUMBER_FIRST, i, j);
						}
					}
				case layerTwo:
					
				case layerThree:
				
				default:
					cout << "DEFAULT CASE"<<endl;
					break;
			}
		}
		
		
	}
	
	
public:
	
	NetworkAdmin(){
		uniform_real_distribution<double> unif(-0.185,0.185);
		
		default_random_engine re;
		//filling filters with random values
		for(int i=0; i<FILTER_NUMBER_FIRST; i++){
			for(int j=0; j < FILTER_SIZE; j++){
				for(int k=0; k < FILTER_SIZE; k++){
					convOneArr[i][j][k]= unif(re);
				}
			}
		}
		
		uniform_real_distribution<double> unif(-0.104,0.104);
		
		for(int i=0; i<FILTER_NUMBER_FIRST; i++){
			for(int j=0; j < FILTER_SIZE; j++){
				for(int k=0; k < FILTER_SIZE; k++){
					convTwoArr[i][j][k]= unif(re);
				}
			}
		}
		
		uniform_real_distribution<double> unif(-0.210,0.210);

		for(int i=0; i<FILTER_NUMBER_FIRST; i++){
			for(int j=0; j < FILTER_SIZE; j++){
				for(int k=0; k < FILTER_SIZE; k++){
					convThreeArr[i][j][k]= unif(re);
				}
			}
		}
	}
	
	~NetworkAdmin(){
		
	};


};