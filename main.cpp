#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <limits>
#include <stdlib.h>
#include <stdint.h>
#include "polinomio.h"
#include <cstring>
using namespace std;

///cria um poly com uma sequencia de zero e adiona no ultimo 1.0 se D>1
void Poly::create(unsigned Grau){
    D = Grau + 1;
    a = new double[D];
    for(unsigned i=0; i < D; i++){
        a[i] = 0.0;
    }
    if(D > 1){
        a[Grau] = 1.0;
    }
}

/// copia um polinomio
void Poly::copia(const Poly& P){
///Cria um polinomio com mesmo grau ao que vai ser copiado
    create(P.getGrau());
    for(unsigned i= 0;i < P.D ;i++){a[i] = P.a[i];}
}

///se o polinomio no P.a[G]== 0 eu tenho q redimensionar ele para G-1
void Poly::newP(){
    Poly prov;
    do{
        prov.recriar(getGrau()- 1);
        for(int i = 0; i <prov.D; i++){
            prov.a[i] = a[i];
        }
        delete[] a;
        D = prov.getGrau()+1;
        a = prov.a;
    }while(prov[prov.getGrau()] == 0);
}

///renicia um polinomio por meio do grau
void Poly::recriar(unsigned Grau)
{
///reinicia um polino e inicia um novo pelo grau
    if(a != nullptr){
///se o polinomio apontava para algo
        delete[] a;
    }
///cria um polinomio pelo grau
    create(Grau);
}

 void Poly::operator=(const Poly& P2)
{
///pergunto se os polinomio não apontam para a mesma area
    if(this!= &P2){
///se os polinomios forem de mesma Dimenção eu igualo  os coeficientes
        if(D == P2.D){
            for(unsigned i = 0; i < D; i++){a[i] = P2[i];}
        }
        else{
            if(a != nullptr){
                delete[] a;
            }
            copia(P2);
        }
    }
}

///Entrada
istream &operator>>(istream& I,Poly& P){
 ///se o polinomio for null = erro
    if(P.empty()){
        cerr<<"polinomio de grau desconhecido";
        return I;
    }
    for(int i =P.getGrau();i >= 0;i--){
        cout<<"X^"<<i;
        I>>P.a[i];
        if(i== P.getGrau()&&P[i]==0){
            do{
                cerr<<"Digite um valor diferente de zero"<<endl;
                cout<<"X^"<<i;
                I>>P.a[i];
            }while(P[i] == 0);
        }
    }
    return I;
}
///saida de dados
ostream &operator<<(ostream& O,const Poly& P){
// Se grau < 0, não faz nada
    if(P.empty()){
        return O;
    }
    for(int i = P.getGrau();i>=0;i--){
        if(P.getCoef(i) == 0.0){
            if(i == 0 && P.getGrau() == 0){
                O<<P[i];
            }
         }
        else{
             if(P.getCoef(i) < 0.0){
                O<<'-';
             }
             else{
                if(i != P.getGrau()){O<<'+';}
             }
             if(abs(P.getCoef(i))!=1.0||i==0){O<<abs(P.getCoef(i));}
             if(i!=0){
                if(abs(P.getCoef(i)) != 1.0){O<<'*';}
                O<<'X';
                if(i>1){O<<'^'<<i;}
             }
        }
    }
    return O;
}

Poly Poly::operator+(const Poly& P2)const
{
///inicializo um prov por default
    Poly prov;
    if(empty()){
/// se o polinomio a esquerda foi nullo eu retorno prov como uma copia do da direita
        return P2;
    }
    if(P2.empty()){
        return *this;
    }
    prov.recriar(max(getGrau(),P2.getGrau()));
    for (unsigned i = 0;i <= prov.getGrau(); i++){
        prov.a[i] = getCoef(i) + P2.getCoef(i);
    }
    if(prov[prov.getGrau()] == 0){prov.newP();}
return prov;
}
///Subtrai polinomios

Poly Poly::operator-(const Poly &P2)const
{
    Poly prov;
    if(empty()){
        return -P2;
    }
    if(P2.empty()){
        return *this;
    }
    prov.recriar(max(getGrau(),P2.getGrau()));
    for (unsigned i = 0; i <= prov.getGrau(); i++){
        prov.a[i] = getCoef(i) - P2.getCoef(i);
    }
    if(prov[prov.getGrau()] == 0){prov.newP();}
    return prov;
}
///Menos unario
Poly Poly::operator-()const
 {
     Poly prov;
     if(empty()){
        cerr<<"polinomio de grau indefinido";
        return prov;
     }
     prov.recriar(getGrau());
     for(unsigned i=0; i< D;i++) prov.a[i]= - getCoef(i);
     return prov;
 }

///Multipla polinomios

Poly Poly::operator*(const Poly &P2)const
{
    Poly prov;
    if (empty()||P2.empty()){
        return prov;
    }
    if(isZero()||P2.isZero()){
        prov.recriar(0);
        return prov;
    }
    unsigned Grau = getGrau() + P2.getGrau();
    prov.recriar(Grau);
    prov.a[Grau] = 0.0;
    for (unsigned i = 0; i < D; i++){
        for(unsigned j = 0; j <P2.D ; j++){
            prov.a[i+j]  += getCoef(i) * P2.getCoef(j);
        }
    }
    return prov;
}
 void Poly::setCoef(const int i,const double& A){
    if(i < D){
        if(i == getGrau()&& A == 0){
            if(D!=1){
                cerr<<"valor invalido para posição"<<endl;
            }
            else{
                a[i] = A;
            }
        }
        else{
            a[i] = A;
        }
    }
    else{
        cerr<<"indice invalido";
    }
}

 double Poly::getValor(double& x)const
 {
     //pergunto se to tentando saber o valor de um polinomio vazio
    if(empty()){return 0.0;}
    double valor = 0;
    //começo do segundo pois o 0 é o termo independente
    for (unsigned i = 0; i <D ;i++){
        valor += a[i]*pow(x,i);
    }
    return valor;
 }

bool Poly::salvar(const string& arquivo)const{
    fstream file_out;
    file_out.open(arquivo,std::ios_base::out);
    if(!file_out.is_open()){
        cerr<<"erro na abertura do arquivo"<<arquivo;
        return false;
    }
    else{
        file_out<<"POLY "<<D<<endl;
           for (int i = 0; i < D; i++){
            file_out<<getCoef(i)<<' ';
            }
    }
    file_out.close();
    return true;
 }
bool Poly::ler(const string& arquivo){
     fstream file_in;
     string title;
     double c = 0.0;
     Poly prov;
     file_in.open(arquivo,std::ios_base::in);
     if(!file_in.is_open()){
        return false;
     }
     file_in>>title;
     if(title != "POLY"){
        return false;
     }
    file_in>>prov.D;
    prov.recriar(prov.getGrau());
    for(int i = 0;i < prov.D;i++){
        file_in >> prov.a[i];
    }
    if(prov.getCoef(prov.getGrau()) == 0 && prov.getGrau() > 0){
        return false;
    }
    file_in>>c;
    if(c != 0.0){
            return false;
    }
    *this = prov;
    return true;
 }
