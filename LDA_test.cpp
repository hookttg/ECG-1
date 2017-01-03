#include <iostream>

#include <Eigen/Dense>

using namespace std;

int main() {

/*generalnie ten skrypt ma byc funkcja ktora na wejsciu przyjmie
zbior uczacy i testowy. Zbiory te beda wynikami dzialania innego
skryptu ktory wczyta dane do macierzy z txt.
Jakby cos to to robilam to na bazie jeszcze starego algo zeby
nie tracic czasu czekajac az skonczysz. */

/*deklaracja maceirzy danych uczacych (ofc randomowa do testow),
ktora teoretycznie ma byc na wejsciu funkcji*/

  Eigen::MatrixXd m(6,4);
  m << 1, 2, 3, 1,
       4, 5, 6, 1,
       7, 8, 9, 1,
       2, 3, 4, 1,
       2, 5, 6, 7,
       5, 2, 6, 7;
  std::cout << m << std::endl;

//liczba cech
int liczbaCech = m.cols();
// teraz zakladam ze bedzie tyle samo obiektow klasy VE i N
// liczba probek klasy VE (2) zbioru uczacego
double kVE = m.rows()/2;
// liczba probek klasy N (1) zbioru uczacego
double kN = m.rows()/2;
// liczba wszystkich probek zbioru uczacego
double N;
N = kN + kVE;

////////////////////////////////////////////////////////////////////
// podzial macierzy na dwie - VE i N

Eigen::MatrixXd VEtr(3,4);
VEtr << 1, 2, 3, 1,
      4, 5, 6, 1,
      7, 8, 9, 1;

Eigen::MatrixXd Ntr(3,4);
Ntr <<  2, 3, 4, 1,
      2, 5, 6, 7,
      5, 2, 6, 7;
// na pale, nie moge wykminic jak to zrobic, ponizej masz jak probowalam

//Eigen::MatrixXd VEtr(kVE,liczbaCech);
//Eigen::MatrixXd Ntr(kN, liczbaCech);
//VEtr << m.block<kVE,4>(0,0);

//Map<MatrixXd,0, OuterStride<>> (VEtr(m.data(), (m.rows()/2), m.cols()));
//cout << VEtr << endl;
// Ntr = m.block<kN,liczbaCech>(kVE+1,0);
// cout << "VEtr: " << endl << VEtr << endl;
// cout << "Ntr: " << endl << Ntr << endl;
//////////////////////////////////////////////////////////////////
double piVE;
piVE = kVE/N; // prawdopodobienstwo wystapienia klasy VE
double piN;
piN = kN/N; // prawdopodobienstwo wystapienia klasy N

// obliczenie mu i sigmy

// mu
Eigen::RowVectorXd uVE(liczbaCech); //dekalaracja wektora mu dla VE
uVE = (VEtr.colwise().sum())/kVE;
Eigen::RowVectorXd uN(liczbaCech); //deklaracja wektora mu dla N
uN = (Ntr.colwise().sum())/kN;

//sigmy jeszcze nie ma

// tu sobie wypisuje wszystko co policzylam:
cout << "Liczba cech: " << liczbaCech << endl;
cout << "kVE: " << kVE << endl;
cout << "kN: " << kN << endl;
cout << "N: " << N << endl;
cout << "piVE: " << piVE << endl;
cout << "piN: " << piN << endl;
cout << "mu VE: " << endl << uVE << endl; 
cout << "mu N: " << endl << uN << endl;

}

