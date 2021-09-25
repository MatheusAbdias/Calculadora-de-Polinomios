#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <limits>
#include <stdlib.h>
#include <stdint.h>
using namespace std;

class Poly{
private:
    //int não negativo tamanho do vetor
    unsigned D;
    // ponteiro para double
    double* a;
    void copia(const Poly& P);
    void create(unsigned Grau);
    void newP();
public:

    ///Metodos da calss Poly

    inline Poly() : D(0.0), a(nullptr){}  //default
    inline Poly(unsigned Grau){create(Grau);}//especifico
    inline Poly(const Poly& P){copia(P);}//por copia
    inline ~Poly(){delete[] a,D = 0;} //destrutor

    ///Metodos de consulta

    //retorna o grau
    inline int getGrau() const{return int(D)-1;}
    //retorna o coeficiente
    inline double getCoef(const unsigned& i )const {if( i>= D)return 0.0;return a[i];}
    //sobre carga do operador
    inline double operator[](const unsigned& i)const{return getCoef(i);}
    //função que retorna se o polinomio é vazio
    inline bool empty()const{if(D == 0)return true;else return false;}
    //se o polinomio tem apenas um termo nulo
    inline bool isZero()const{if(D == 1 && getCoef(0) == 0.0)return true;else return false;}
    //retorna o valor do poly no valor x
    inline double operator()(double& x)const{return getValor(x);}
    //retorna o valor do poly no valor x
    double getValor(double& x)const;
    //reinicia um polinomio e cria um novo com o grau passado
    void recriar(unsigned Grau);
    // Altera o coeficiente do polinomio
    void setCoef(const int i,const double& A);
    //salva o polinomio em um arquivo
    bool salvar(const string& arquivo)const;
    //ler um poly de um arquivo
    bool ler(const string& arquivo);

    ///Metodos de saida e entrada

    //entrada de dados
    friend istream &operator>>(istream& I,Poly& P);
    //saida de dados
    friend ostream &operator<<(ostream& O,const Poly& P);

    ///Operações especificas da calsse

    //sobrecarga da soma
    Poly operator+(const Poly &P2)const;
    // sobrecarga da subtração
    Poly operator-(const Poly &P2)const;
    Poly operator-()const;
    // sobrecarga da multiplicação
    Poly operator*(const Poly &P2)const;
    // igualA dois polinomios
    void operator=(const Poly& P2);
};

