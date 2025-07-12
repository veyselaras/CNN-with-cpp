#include <iostream>
#include <cmath>
#include <random>
#include <vector>

#using namespace std;

#define FILTER_SIZE = 5
#define FILTER_NUMBER_FIRST = 6
#define FILTER_NUMBER_SECOND = 16
#define FILTER_NUMBER_THIRD = 120
#define FIRST_CONVLAYER_SIZE = 28
#define FIRST_POOLAYER_SIZE = 14
#define SECOND_CONVLAYER_SIZE = 10
#define SECOND_FILTER_SIZE = 10
#define SECOND_POOLAYER_SIZE = 5
#define INPUT_SIZE = 32

//YOU MUST START ALL BIAS AT 0 DON'T FORGET!! 

class NetworkAdmin{
private:
	//	input matrice
	double input[INPUT_SIZE][INPUT_SIZE];

	// convolutional layer matrices
	ConvNeuron convOneArr[FILTER_NUMBER_FIRST][FIRST_CONVLAYER_SIZE][FIRST_CONVLAYER_SIZE];
	double convOneBias[FILTER_NUMBER_FIRST];
	double poolingOneArr[FILTER_NUMBER_FIRST][FIRST_POOLAYER_SIZE][FIRST_POOLAYER_SIZE];
	ConvNeuron convTwoArr[FILTER_NUMBER_SECOND][SECOND_CONVLAYER_SIZE][SECOND_CONVLAYER_SIZE];
	double convTwoBias[FILTER_NUMBER_SECOND];
	double poolingTwoArr[FILTER_NUMBER_SECOND][SECOND_POOLAYER_SIZE][SECOND_POOLAYER_SIZE];
	double convThreeArr[FILTER_NUMBER_THIRD];
	double convThreeBias[FILTER_NUMBER_THIRD];

	// fully connected layers matrices
	vector<FCNeuron> fcLayerOne;
	fcLayerOne.reserve(120);
	double fcLayerOneBias[120];
	
	vector<FCNeuron> fcLayerTwo;
	fcLayerTwo.reserve(86);
	double fcLayerTwoBias[86];
	
	vector<FCNeuron> fcLayerThree;
	fcLayerThree.reserve(20);
	double fcLayerThreeBias[10];
	
	// filters
	double firstLayerFilter[FILTER_NUMBER_THIRD][FILTER_SIZE][FILTER_SIZE];
	double secondLayerFilter[FILTER_NUMBER_SECOND][FILTER_SIZE][FILTER_SIZE];
	double thirdLayerFilter[THIRD_CONVLAYER_SIZE][FILTER_SIZE][FILTER_SIZE];
	
	
	void matriceMult(int filterNumber, int row, int column){
		int filterRowCounter = 0;
		int filterColumnCounter = 0;
		int convSum = 0;
		switch(filterNumber){
			case 6:
				for(int i = 0; i < filterNumber; i++){//width
					for(int j = row; j < row + 5; j++){//row
						for(int k = column; k < column + 5; k++){//column
							convSum = firstLayerFilter[i][filterRowCounter][filterColumnCounter]*input[j][k];
							filterColumnCounter++;
						}
						filterRowCounter++;
						filterColumnCounter = 0;
					}
					filterRowCounter = 0;
					convOneArr[i][row][column].inputValue = convSum + convOneBias[i];
					convOneArr[i][row][column].updateRelu();
				}
				break;
			
			case 16:
				for(int i = 0; i < filterNumber; i++){//width
					for(int j = row; j < row + 5; j++){//row
						for(int k = column; k < column + 5; k++){//column
							convSum = secondLayerFilter[i][filterRowCounter][filterColumnCounter]*input[j][k];
							filterColumnCounter++;
						}
						filterRowCounter++;
						filterColumnCounter = 0;
					}
					filterRowCounter = 0;
					convTwoArr[i][row][column].inputValue = convSum + convSecondBias[i];
					convTwoArr[i][row][column].updateRelu();
				}
				break;
			
			case 120:
				for(int i = 0; i < filterNumber; i++){//width
					for(int j = row; j < row + 5; j++){//row
						for(int k = column; k < column + 5; k++){//column
							convSum = thirdLayerFilter[i][filterRowCounter][filterColumnCounter]*input[j][k];
							filterColumnCounter++;
						}
						filterRowCounter++;
						filterColumnCounter = 0;
					}
					filterRowCounter = 0;
					convThreeArr[i].inputValue = convSum + convThreeBias[i];
					convThreeArr[i].updateRelu();
				}
				break;
			
			default:
				break;
		}
	}
	
	
	void fcLayerConv(){
		double convSum = 0;
		for (int i = 0; i < 120; i++){
			if(fcLayerOne.size() != 120)
				fcLayerOne.emplace_back(86);
			fcLayerOne[i].inputValue = convThreeArr[i].reluValue;
			fcLayerOne[i].updateRelu();
		}
			
		for (int i = 0; i < 86; i++){
			if(fcLayerOne.size() != 86)
				fcLayerTwo.emplace_back(10);
			for(int j = 0; j < 120; j++)
				convSum += fcLayerOne[j].reluValue*fcLayerOne[j]->weightMatrice[i];
			fcLayerTwo[i].inputValue = convSum + fcLayerTwoBias[i];
			fcLayerTwo[i].updateRelu();
		}
			
		for (int i = 0; i < 10; i++){
			if(fcLayerOne.size() != 10)
				fcLayerThree.emplace_back();
			for(int j = 0; j < 86; j++)
				convSum += fcLayerTwo[j].reluValue*fcLayerTwo[j]->weightMatrice[i];
			fcLayerThree[i].inputValue = convSum + fcLayerThreeBias[i];
			fcLayerThree[i].updateRelu();
		}
	}
	
	void convolution(int pad = 0, int stride = 1, string name){
		if(pad =! 0) {
			//SONRA BAK
		}
		else{
			switch(name){
				case "layerOne":
					for(int i = 0; i < INPUT_SIZE-FILTER_SIZE+1; i++){
						for(int j = 0; j < INPUT_SIZE-FILTER_SIZE+1; j++){
							matriceMult(FILTER_NUMBER_FIRST, i, j);
						}
					}
					break;
				case "layerTwo":
					for(int i = 0; i < FIRST_CONVLAYER_SIZE-FILTER_SIZE+1; i++){
						for(int j = 0; j < FIRST_CONVLAYER_SIZE-FILTER_SIZE+1; j++){
							matriceMult(FILTER_NUMBER_SECOND, i, j);
						}
					}
					break;
				case "layerThree":
					matriceMult(FILTER_NUMBER_THIRD, 0, 0);
				default:
					cout << "DEFAULT CASE"<<endl;
					break;
			}
			fcLayerConv();
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
		
	}


};