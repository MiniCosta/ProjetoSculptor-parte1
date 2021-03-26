#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include "sculptor.h"

using namespace std;
//Exemplo que contém todos as funções
int main() {

string arquivoOFF="arquivoOFF";
Sculptor XboxSS(200,200,200);

XboxSS.setColor(0.99,0.99,0.99,1); //Cor Branca
XboxSS.putBox(0,0,0,60,15,31); // Retângulo original


//Trás

XboxSS.setColor(0,0,0,1.0); //Cor preta

XboxSS.cutBox(3,3,0,7,5,4); //Fazendo entrada de cabo #1
XboxSS.putBox(2,2,0,8,6,4);

for (int i=3;i<7;i++) { // Criando pequeno buraco para ficar mais real
    for (int j=3;j<5;j++) {
     XboxSS.cutVoxel(i,j,0);
    }
}

XboxSS.cutBox(11,3,0,15,5,5); //Fazendo entrada de cabo #2
XboxSS.putBox(10,2,0,16,6,4);

for (int i=11;i<15;i++) {
    for (int j=3;j<5;j++) {
     XboxSS.cutVoxel(i,j,0);
    }
}

//Cima

XboxSS.putEllipsoid(85,27,29,30,2,30); //Sáida de Ar

//Frente

XboxSS.putEllipsoid(110,20,59,5,5,3); // Botão de ligar
XboxSS.cutVoxel(55,10,31);


XboxSS.setColor(0.99,0.99,0.99,1);// Fazendo o X do botão
XboxSS.putVoxel(54,9,30);
XboxSS.putVoxel(55,10,30);
XboxSS.putVoxel(56,11,30);
XboxSS.putVoxel(54,11,30);
XboxSS.putVoxel(56,9,30);

XboxSS.setColor(0,0,0,1.0); //Cor preta
XboxSS.cutBox(3,3,27,7,5,31); //Fazendo entrada tipo USB
XboxSS.putBox(2,2,27,8,6,31);

for (int i=3;i<7;i++) { // Criando pequeno buraco para ficar mais real
    for (int j=3;j<5;j++) {
     XboxSS.cutVoxel(i,j,30);
    }
}

XboxSS.putBox(10,3,30,12,5,31); // Botão pequeno de pareamento

//Lados

for(int j=2;j<13;j=j+2) { // Exaustão lateral (Direita)
    for(int k=2;k<30;k=k+2) {
        XboxSS.putVoxel(59,j,k);
    }
}

for(int j=2;j<13;j=j+2) { // Exaustão lateral (Esquerda)
    for(int k=2;k<30;k=k+2) {
        XboxSS.putVoxel(0,j,k);
    }
}

XboxSS.writeOFF(arquivoOFF);
return 0;
}
