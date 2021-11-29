/*
Author: Daniel Rodriguez Figueroa

A01612889

correcion act 1.1
*/

#include <iostream>
using namespace std;

class Funciones{
    public:
        Funciones();
        int sumaIterativa(int num);
        int sumaRecursiva(int num);
        int sumaDirecta(int num);
};

Funciones::Funciones(){}
int Funciones::sumaIterativa(int num){
    int sumi=0;
    for (int i = 0; i <= num; i++)
    {
        sumi+=i;
    }

    return sumi;
}
int Funciones::sumaRecursiva(int num){
    if (num==1)
    {
        return 1;
    }
    else{
        return(num+sumaRecursiva(num-1));
    }
}
int Funciones::sumaDirecta(int num){
    return(num*(num+1)/2);
}