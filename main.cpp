#include <iostream>
#include "Jogador.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <map>

// Struct auxiliar para ler as linhas do arquivo e gravar na classe jogador
struct Data {
    std::string apelido;
    std::string nome;
    std::vector<int> numeros;
};

bool isNumber(const std::string& str) {
    if (str.empty()) return false;
    for (char ch : str) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

// Função para ler a linha do arquivo e guardar as informações na classe jogador
Jogador lerLinha(const std::string& linha) {
    std::istringstream iss(linha);
    Data data;
    std::string palavra;

    // Ler o apelido
    iss >> data.apelido;

    // Ler o nome até encontrar o primeiro número
    while (iss >> palavra) {
        if (isNumber(palavra)) {
            data.numeros.push_back(std::stoi(palavra));
            break;
        } else {
            if (!data.nome.empty()) data.nome += " ";
            data.nome += palavra;
        }
    }

    // Ler os números restantes
    int numero;
    while (iss >> numero) {
        data.numeros.push_back(numero);
    }

    Jogador Jogadorx(data.apelido, data.nome);

    Jogadorx.addHistReversi(data.numeros[0], data.numeros[1]);
    Jogadorx.addHistLig4(data.numeros[2], data.numeros[3]);
    Jogadorx.addHistVelha(data.numeros[4], data.numeros[5]);

    return Jogadorx;
}

using namespace std;

int main() {
    //Abrir o arquivo
    std::ifstream arquivo("jogadores.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    //Lê as linhas do arquivo e registra as informações dos jogadores em maps
    std::string linha;
    map<string,Jogador> players_nick;
    map<string,Jogador> players_name;

    while (std::getline(arquivo, linha)) {
        Jogador Jogador1 = lerLinha(linha);

        players_nick.insert(pair<string, Jogador>(Jogador1.getApelido(),Jogador1));
        players_name.insert(pair<string, Jogador>(Jogador1.getNome(),Jogador1));
    }
    arquivo.close();

    std::string ler_entrada;
    std::string operacao, ordenar, ler_apelido, ler_nome, nick1, nick2;
    char jogo;

    do{

        // Recebe a linha digitada pelo usuário - a primeira string indica a operação
        std::getline(std::cin, ler_entrada);
        //Armazena a operação, o apelido e o nome em strings correspondentes
        std::istringstream ss(ler_entrada);
        ss >> operacao;

        //Cadastrar jogador
        if (operacao == "CJ"){
            ss >> ler_apelido;
            std::getline(ss, ler_nome);

            if (!ler_nome.empty() && ler_nome[0] == ' ') {
                ler_nome.erase(0, 1);
            }

            if(ler_nome == ""){
                std::cout << "ERRO: Dados incorretos " << std::endl;
            }

            else if(players_nick.find(ler_apelido)!= players_nick.end()){
                std::cout << "ERRO: Jogador repetido" << std::endl;
            }

            else if(players_nick.find(ler_apelido) == players_nick.end()){
                Jogador Jogador1(ler_apelido, ler_nome);
                players_nick.insert(pair<string, Jogador>(Jogador1.getApelido(),Jogador1));
                players_name.insert(pair<string, Jogador>(Jogador1.getNome(),Jogador1));
                std::cout << "Jogador " << ler_apelido << " cadastrado com sucesso" << std::endl;
            }
            // else() Lançar exceção?
        }

        //Remover Jogador
        if (operacao == "RJ"){
            ss >> ler_apelido;

            if(players_nick.find(ler_apelido) != players_nick.end()){
                auto iter = players_nick.find(ler_apelido);
                ler_nome = iter->second.getNome();

                players_nick.erase(ler_apelido);
                players_name.erase(ler_nome);
                std::cout << "Jogador " << ler_apelido << " removido com sucesso" << std::endl;
            }

            else if(players_nick.find(ler_apelido)== players_nick.end()){
                std::cout << "ERRO: Jogador inexistente" << std::endl;
            }
        }

        //Listar jogadores
        if (operacao == "LJ"){
            ss >> ordenar;
            if (ordenar == "A"){
                 map<string,Jogador>::iterator it;

                for (it = players_nick.begin(); it != players_nick.end(); it++) {

                    int* vetor_reversi = it->second.getHistReversi();
                    int* vetor_lig4 = it->second.getHistLig4();
                    int* vetor_velha = it->second.getHistVelha();

                    std::cout << it->first << "  " << it->second.getNome() << std::endl;
                    std::cout << "REVERSI - V:" << vetor_reversi[0] << " D:" << vetor_reversi[1] << std::endl;
                    std::cout << "LIG4 - V:" << vetor_lig4[0] << " D:" << vetor_lig4[1] << std::endl;
                    std::cout << "VELHA - V:" << vetor_velha[0] << " D:" << vetor_velha[1] << "\n" << std::endl;
                }

            }

            if (ordenar == "N"){
                 map<string,Jogador>::iterator it;

                for (it = players_name.begin(); it != players_name.end(); it++) {

                    int* vetor_reversi = it->second.getHistReversi();
                    int* vetor_lig4 = it->second.getHistLig4();
                    int* vetor_velha = it->second.getHistVelha();

                    std::cout << it->second.getApelido() << "  " << it->second.getNome() << std::endl;
                    std::cout << "REVERSI - V:" << vetor_reversi[0] << " D:" << vetor_reversi[1] << std::endl;
                    std::cout << "LIG4 - V:" << vetor_lig4[0] << " D:" << vetor_lig4[1] << std::endl;
                    std::cout << "VELHA - V:" << vetor_velha[0] << " D:" << vetor_velha[1] << "\n" << std::endl;
                }
            }
        }

        //Executar partidas
        if (operacao == "EP"){
            ss >> jogo;
            ss >> nick1;
            ss >> nick2;

            if((nick1 == "") || (nick2 == "")){
                std::cout << "ERRO: Dados incorretos " << std::endl;
            }

            else if((players_nick.find(nick1) == players_nick.end()) || (players_nick.find(nick2) == players_nick.end()))
                std::cout << "ERRO: Jogador inexistente" << std::endl;


        }



        //Limpando as strings de leitura
        nick1.clear();
        nick2.clear();
        ler_nome.clear();
        ler_apelido.clear();

    }while (operacao != "FS");

    //Abrindo o arquivo para gravação
    std::ofstream historico("jogadores.txt");

    if (!historico.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita.\n";
        return 1;
    }

    map<string,Jogador>::iterator it;

    for (it = players_name.begin(); it != players_name.end(); it++) {
        int* vetor_reversi = it->second.getHistReversi();
        int* vetor_lig4 = it->second.getHistLig4();
        int* vetor_velha = it->second.getHistVelha();

        historico << it->second.getApelido() << " " << it->second.getNome() << " " << vetor_reversi[0] << " " << vetor_reversi[1]
        << " " << vetor_lig4[0] << " " << vetor_lig4[1] << " " << vetor_velha[0] << " " << vetor_velha[1] << "\n";

    }

    historico.close();

    return 0;
}
