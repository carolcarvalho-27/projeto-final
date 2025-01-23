#include "Jogador.hpp"

#include <iostream>
#include <string>

using namespace std;

Jogador::Jogador(string apelido, string nome){
    _apelido = apelido;
    _nome = nome;
    for (int i=0; i<2; i++){
        reversi[i]=0;
        lig4[i]=0;
        velha[i]=0;
    }
}

/*Jogador::~Jogador(){
    delete[] reversi;
    delete[] lig4;
    delete[] velha;
}*/

void Jogador::atualizarDadosJogador(string jogo, char resultado){
    return;
}

string Jogador::getNome(){
    return(_nome);
}

string Jogador::getApelido(){
    return(_apelido);
}

int* Jogador::getHistReversi(){
    return(reversi);
}

int* Jogador::getHistLig4(){
    return(lig4);
}

int* Jogador::getHistVelha(){
    return(velha);
}
void Jogador::addHistReversi(int vitorias, int derrotas){
    reversi[0]+=vitorias;
    reversi[1]+=derrotas;
}

void Jogador::addHistLig4(int vitorias, int derrotas){
    lig4[0]+=vitorias;
    lig4[1]+=derrotas;
    return;
}

void Jogador::addHistVelha(int vitorias, int derrotas){
    velha[0]+=vitorias;
    velha[1]+=derrotas;
    return;
}
