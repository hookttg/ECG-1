#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){

	//int Ntestsamples=10;
	double classify_result[10]={1,2,4,3,6,2,1,8,9,10};
	

	/* przy wczytywaniu pliku testowego bedziemy liczyc rowniez jego dlugosc ponizszym kodem (z readcsv) wiec bedzie dana liczba wierszy
	int number_of_lines = 0;
    std::string line;
    std::ifstream myfile("test.csv");
    
    while (std::getline(myfile, line))
        ++number_of_lines;
    std::cout << "Number of lines in text file: " << number_of_lines;
    */

    int testLength=10;
	ofstream outfile ("classify_result.csv");

	if (outfile.is_open()){
	
		for(int i=0;i<testLength;i++){
			outfile<<classify_result[i]<<";";
		}
	}

	outfile.close();
}