#ifndef MV_H
#define MV_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

using namespace std;

class MV
{
    public:
        MV();
        virtual ~MV();
        string simulador(string arquivo, string user, int inicio);
        char memoria[4095][2]; // 4095 = 0xFFF;
        void writeData(char mem[2], char x, char y);
        int getEndereco(char aux1, char aux2, char aux3);
        int charToInt(char aux);
        char intToChar(int x);
        void tranformaResultado(int result, char* ac1, char* ac2);

    protected:

    private:
};

#endif // MV_H
