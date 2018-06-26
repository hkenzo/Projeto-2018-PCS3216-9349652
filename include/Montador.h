#ifndef MONTADOR_H
#define MONTADOR_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "MV.h"

using namespace std;

class Montador
{
    public:
        Montador();
        virtual ~Montador();
        string montar(string arquivo, string user);
        vector<string> Separate_Space(string s);
        vector<string> Separate_expression(string s, char c);
        string replaceChar(string str, char ch1, char ch2);
        int verificarOperando(int passo, int op, vector<std::string>* symbol, vector<int>* symbolV, vector<std::string> separated, int ci, int org);
    protected:

    private:
};

#endif // MONTADOR_H
