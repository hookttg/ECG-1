#include <iostream>

#include <Eigen/Dense>

using namespace std;

VectorXd LDA_class(const MatrixXd& training1, const MatrixXd& training2, const MatrixXd& test){
    
    /*generalnie ten skrypt ma byc funkcja ktora na wejsciu przyjmie
     zbior uczacy i testowy. Zbiory te beda wynikami dzialania innego
     skryptu ktory wczyta dane do macierzy z txt.
     Jakby cos to to robilam to na bazie jeszcze starego algo zeby
     nie tracic czasu czekajac az skonczysz. */
    
    /*deklaracja maceirzy danych uczacych (ofc randomowa do testow),
     ktora teoretycznie ma byc na wejsciu funkcji*/
    /*
    Eigen::MatrixXd m(6,4);
    m << 1, 2, 3, 1,
    4, 5, 6, 1,
    7, 8, 9, 1,
    2, 3, 4, 1,
    2, 5, 6, 7,
    5, 2, 6, 7;
    std::cout << m << std::endl;*/
    
    //liczba cech
    int featureNumber = training1.cols();
    // teraz zakladam ze bedzie tyle samo obiektow klasy VE i N
    // liczba probek klasy VE (2) zbioru uczacego
    double c1 = training1.rows()/2;
    // liczba probek klasy N (1) zbioru uczacego
    double c2 = training2.rows()/2;
    // liczba wszystkich probek zbioru uczacego
    double N;
    N = c1 + c2;
    // prawdopodobienstwo wystapienia klasy VE
    double piC1;
    piVE = c1/N;
    // prawdopodobienstwo wystapienia klasy N
    double piC2;
    piN = c2/N;
    
    ////////////////////////////////////////////////////////////////////
    // podzial macierzy na dwie - VE i N
    /*
    Eigen::MatrixXd VEtr(3,4);
    VEtr << 1, 2, 3, 1,
    4, 5, 6, 1,
    7, 8, 9, 1;
    
    Eigen::MatrixXd Ntr(3,4);
    Ntr <<  2, 3, 4, 1,
    2, 5, 6, 7,
    5, 2, 6, 7;*/
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
    Eigen::RowVectorXd u1(featureNumber); //dekalaracja wektora mu dla VE
    u1 = (training1.colwise().sum())/c1;
    Eigen::RowVectorXd u2(featureNumber); //deklaracja wektora mu dla N
    u2 = (training2.colwise().sum())/c2;
    
    //sigma
    
    Eigen::MatrixXd E1(featureNumber, featureNumber);
    Eigen::MatrixXd E2(featureNumber, featureNumber);
    Eigen::MatrixXd sigma(featureNumber, featureNumber);
    Eigen::MatrixXd t(featureNumber, featureNumber);
    
    for(int i=0; i<c1; i++){
        t= ((training1.row(i)-u1).transpose()*(training1.row(i)-u1))/(N-2);
        E1 = E1 + t;
    }
    for(int i=0; i<c2; i++){
        t= ((training2.row(i)-u2).transpose()*(training2.row(i)-u2))/(N-2);
        E2 = E2 + t;
    }
    
    sigma = E1+E2;
    
    cout << "E1: " << endl << E1 <<endl;
    cout << "E2: " << endl << E2 <<endl;
    cout << "sigma: " << sigma << endl;
    
    // obliczenie wspolczynnikow funkcji klasyfikujacej
    Eigen::RowVectorXd u(featureNumber);
    Eigen::MatrixXd a(featureNumber,1);
    Eigen::MatrixXd a0(1,1);
    Eigen::MatrixXd logpi(1,1);
    
    u = u1-u2;
    a = sigma.inverse()*u.transpose();
    logpi << log(piC1/piC2);
    a0 = logpi-(((u1+u2)*sigma.inverse()*(u1-u2).transpose())/2);
    cout << "a0 = " << a0 << endl;
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
     /*
    Eigen::MatrixXd test(4,4);
    test << 1, 2, 3, 4,
    3, 4, 2, 2,
    7, 3, 5, 1,
    9, 5, 2, 5;*/
    
    // Dlugosc zbioru testowego
    int testLen = test.rows();
    // wektor wynikow
    Eigen::VectorXd klasyfikacja(testLen);
    Eigen::MatrixXd f(1,1);
    Eigen::MatrixXd temp(1,1);
 
    f << 0;
   for(int i=0; i<=testLen; i++){

        for(int j=0; j<=featureNumber; j++){
            temp << test(i,j)*a(j,0);
            cout << "temp: " << temp << endl;
            f = f+temp;
            cout << "f: " << endl << f << endl;
        }
        
        if(f(0,0)<0){
            klasyfikacja(i)=1; //VE
        }
        else{
            klasyfikacja(i)=2; //N
        }
    }
    
    cout << "klasyfikacja: " << endl << klasyfikacja << endl;

    return klasyfikacja;
    
    //tu sobie wypisuje wyniki
    cout << "suma * sigma-1: : " << (u1+u2)*sigma.inverse() << endl;
    cout << "trans: " << endl <<  (u1-u1).transpose() << endl;
    cout << "suma * sigma-1*transpose: " << (((u1+u2)*sigma.inverse()*(u1-u2).transpose())/2).size() << endl;
    cout << "a0: " << endl << a0 << endl;
    cout << "u: " << endl << u << endl;
    cout << "sigma -1" << endl << sigma.inverse() << endl;
    cout << "a: " << endl << a << endl;
    
    // tu sobie wypisuje wszystko co policzylam:
    cout << "Liczba cech: " << featureNumber << endl;
    cout << "k1: " << c1 << endl;
    cout << "k2: " << c2 << endl;
    cout << "N: " << N << endl;
    cout << "piC1: " << piC1 << endl;
    cout << "piC2: " << piC2 << endl;
    cout << "mu VE: " << endl << uVE << endl; 
    cout << "mu N: " << endl << uN << endl;
    
}
