#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <string>

using namespace std;

class Jogador{
protected:
    string _apelido;
    string _nome;
    int reversi[2];
    int lig4[2];
    int velha[2];

public:

    Jogador(string apelido, string nome);

    //~Jogador();

    void atualizarDadosJogador(string jogo, char resultado);
    string getNome();
    string getApelido();

    int* getHistReversi ();
    int* getHistLig4 ();
    int* getHistVelha ();

    void addHistReversi(int vitorias, int derrotas);
    void addHistLig4(int vitorias, int derrotas);
    void addHistVelha(int vitorias, int derrotas);
};

#endif
