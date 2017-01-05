#include <iostream>
#include <fstream>
#include <Eigen/Dense>
using namespace std;


Eigen::MatrixXd readCSV(std::string file, int rows, int cols) {

    
  std::ifstream in(file);
  
  std::string line;

  int row = 0;
  int col = 0;

  Eigen::MatrixXd data = Eigen::MatrixXd(rows, cols);

  if (in.is_open()) {

    while (std::getline(in, line)) {

      char *ptr = (char *) line.c_str();
      int len = line.length();

      col = 0;

      char *start = ptr;
      for (int i = 0; i < len; i++) {

        if (ptr[i] == ';') {
          data(row, col++) = atof(start);
          start = ptr + i + 1;
        }
      }
      data(row, col) = atof(start);

      row++;
    }

    in.close();
  }
  return data;
}


int main(){
    
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile("training.csv");
    
    while (std::getline(myfile, line))
        ++number_of_lines;
    std::cout << "Number of lines in text file: " << number_of_lines;
    

    
    cout<<readCSV("training.csv",number_of_lines,4);
    return 0;
}