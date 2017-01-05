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
    // prawdopodobienstwo wystapienia klasy VE
    double piVE;
    piVE = kVE/N;
    // prawdopodobienstwo wystapienia klasy N
    double piN;
    piN = kN/N;
    
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
    
    
    // obliczenie mu i sigmy
    
    // mu
    Eigen::RowVectorXd uVE(liczbaCech); //dekalaracja wektora mu dla VE
    uVE = (VEtr.colwise().sum())/kVE;
    Eigen::RowVectorXd uN(liczbaCech); //deklaracja wektora mu dla N
    uN = (Ntr.colwise().sum())/kN;
    
    //sigma
    
    Eigen::MatrixXd E1(liczbaCech, liczbaCech);
    Eigen::MatrixXd E2(liczbaCech, liczbaCech);
    Eigen::MatrixXd sigma(liczbaCech, liczbaCech);
    Eigen::MatrixXd t(liczbaCech, liczbaCech);
    
    for(int i=0; i<kN; i++){
        t= ((Ntr.row(i)-uN).transpose()*(Ntr.row(i)-uN))/(N-2);
        E1 = E1 + t;
    }
    for(int i=0; i<kVE; i++){
        t= ((VEtr.row(i)-uVE).transpose()*(VEtr.row(i)-uVE))/(N-2);
        E2 = E2 + t;
    }
    
    sigma = E1+E2;
    
    cout << "E1: " << endl << E1 <<endl;
    cout << "E2: " << endl << E2 <<endl;
    cout << "sigma: " << sigma << endl;
    
    // obliczenie wspolczynnikow funkcji klasyfikujacej
    Eigen::RowVectorXd u(liczbaCech);
    Eigen::VectorXd a(liczbaCech);
    Eigen::MatrixXd a0(1,1);
    Eigen::MatrixXd logpi(1,1);
    
    u = uN-uVE;
    a = sigma.inverse()*u.transpose();
    logpi << log(piN/piVE);
    a0 = logpi-(((uN+uVE)*sigma.inverse()*(uN-uVE).transpose())/2);
    /* komentarz do wspolczynnikow a
     Generalnie to jest problem z ta sigma^(-1). Inaczej liczy mi to cpp
     a inaczej matlab dla tych samych danych. Wiec koniec koncow
     wspolczynniki a wychodza w cpp inne. Ale moze byc to spowodowane
     tym ze moja macierz testowa jest bez sensu, bo wyznacznik maciezy
     jest bliski 0 (wiec nie istnieje dla niej macierz odwrotna) i
     matlab zwraca warning ze cos jest nie halo.
     Tak czy siak dopiero jak wladujemy tu prawdziwe dane to bedzie
     mozna sprawdzic czy ta sigma(-1) jest ok
     */
    
    // warunek klasyfikacji
    
    // niech to bedzie randomowy zbior testowy
    Eigen::MatrixXd test(4,4);
    test << 1, 2, 3, 4,
    3, 4, 2, 2,
    7, 3, 5, 1,
    9, 5, 2, 5;
    
    // Dlugosc zbioru testowego
    int testDl = 4;
    // wektor wynikow
    Eigen::VectorXd klasyfikacja(testDl);
    Eigen::MatrixXd f(1,1);
    //Do tego momentu wszystko dziala, ta petla for ponizej nie hula
    //////////////////////////////////////////////////////
    for(int i=0; i<4; i++){
        f(1,1) = a0(1,1);
        for(int j=0; j<liczbaCech; j++){
            f(1,1) = f(1,1)+test(i,j)*a(j); // tu jest blad, podejrzewam ze zle typy danych (macierzy)
        }
        
        if(f(1,1)>=0){
            klasyfikacja(i)=1; //N
        }
        else{
            klasyfikacja(i)=2; //VE
        }
    }
    
    cout << "klasyfikacja: " << endl << klasyfikacja << endl;
    /////////////////////////////////////////////////////////
    
    //tu sobie wypisuje wyniki
    cout << "suma * sigma-1: : " << (uN+uVE)*sigma.inverse() << endl;
    cout << "trans: " << endl <<  (uN-uVE).transpose() << endl;
    cout << "suma * sigma-1*transpose: " << (((uN+uVE)*sigma.inverse()*(uN-uVE).transpose())/2).size() << endl;
    cout << "a0: " << endl << a0 << endl;
    cout << "u: " << endl << u << endl;
    cout << "sigma -1" << endl << sigma.inverse() << endl;
    cout << "a: " << endl << a << endl;
    
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
