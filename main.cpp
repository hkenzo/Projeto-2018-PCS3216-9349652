#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <windows.h>
#include <fstream>
#include "Montador.h"
//#include <regex>


using namespace std;

int main()
{
    string user, in, temp;
    std::size_t found;
    int op = -1;
    DIR *dir;
    struct dirent *lsdir;
    ifstream code;
    string line, program;
    Montador* M = new Montador();
//	std::smatch matchs;


    cout << " \n Projeto 2018 PCS3416 " << endl;
    cout << " Heitor Koga 9349652 "<< endl;

    /**   Tela de Login **/
    cout << endl <<  " == LOGIN ==" << endl << endl;
    cout << " Digite o usuario: ";
    cin >> user;

    /**Verifica se usuario já existe, caso contrario, cria pasta e copia os programas de ./programs **/
    if (CreateDirectory(user.c_str(), NULL)) { // cria pasta para usuario
        dir = opendir("./programs");
        ifstream ifs;
        ofstream ofs;
        string temp;
        std::size_t found;
        /* copia os arquivos .txt de ./programs para a pasta do usuário */
        while ((lsdir = readdir(dir)) != NULL) {
            temp = lsdir->d_name;
            found = temp.find(".txt"); //procura arquivos do tipo ".txt"
            if (found!=std::string::npos) {
                string temp2 = "./"+user+"/"+temp;
                temp = "./programs/"+temp;
                ifs.open(temp.c_str(), std::ios::binary);
                ofs.open(temp2.c_str(), std::ios::binary);

                ofs << ifs.rdbuf(); // copia arquivo
                ifs.close();
                ofs.close();
            }
        }
        closedir(dir);
    }

    while(op != 0) {
        cout << endl <<  " == Comandos disponiveis ==" << endl << endl;
        cout << " $DIR - informa os programas do usuario disponiveis no sistema" << endl;
        cout << " $DEL - remove do sistema um programa do usuario "<< endl;
        cout << " $RUN - inicia a execucao de um programa do usuario " << endl;
        cout << " $END - encerra operacao do sistema e reporta informacoes coletadas"<< endl << endl;
        cout << " Digite um comando: ";
        cin >> in;

        /* Verificação do comando digitado*/
        found = in.find("DIR");
        if (found!=std::string::npos)
            op = 1;
        found = in.find("dir");
        if (found!=std::string::npos)
            op = 1;
        found = in.find("DEL");
        if (found!=std::string::npos)
            op = 2;
        found = in.find("del");
        if (found!=std::string::npos)
            op = 2;
        found = in.find("RUN");
        if (found!=std::string::npos)
            op = 3;
        found = in.find("run");
        if (found!=std::string::npos)
            op = 3;
        found = in.find("END");
        if (found!=std::string::npos)
            op = 4;
        found = in.find("end");
        if (found!=std::string::npos)
            op = 4;

        switch (op) {
            case 1: temp = "./"+user;
                    dir = opendir(temp.c_str());
                    cout << endl << " Programas disponiveis: " << endl;
                    while ((lsdir = readdir(dir)) != NULL) {

                        string temp = lsdir->d_name;
                        std::size_t found = temp.find(".txt"); //procura arquivos do tipo ".txt"

                        if (found!=std::string::npos) {
                            string tempSemTxt = temp.substr(0, temp.find("."));
                            cout << "    " << tempSemTxt << endl;
                        }
                    }
                    op = -1;
                    break;

            case 2:
                    op = -1;
                    break;

            case 3: cin >> in; // pega o nome do programa a ser executado
                    program = M->montar(in, user); // usa a função "montar" do montador M e guarda a resposta em program
                    cout << endl << program << endl;
                    op = -1;
                    break;

            case 4:
                    op = 0;
                    break;

            default: cout << endl << " Erro: operando invalido, tente novamente" << endl << endl;
                    break;
        }

    }
    return 0;
}





