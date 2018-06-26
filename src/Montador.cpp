#include "Montador.h"

Montador::Montador()
{
    //ctor
}

Montador::~Montador()
{
    //dtor
}
string Montador::montar(string arquivo, string user){
    ifstream input;
    ofstream objectFile;
    string line, nome, nomeO, resposta;
    bool found = 0;
    int ci = 0, aux = 0, org = 0, cont = 0, passo = 1, inicio = 0;
    std::vector<std::string> separated;
    std::vector<std::string> symbol;
    std::vector<int> symbolV;
    MV* maquinavirtual = new MV();
    nome = "./"+user+"/"+arquivo+".txt";
    nomeO = "./"+user+"/"+arquivo+"_o.txt";
    objectFile.open(nomeO.c_str());
    while(passo < 3) {
        input.open(nome.c_str());
        if (input.fail())
            return "\n Erro: Arquivo nao encontrado";
        else {
            while (input.good()){ // se ainda houver dados para ler
                getline(input, line); // pega uma linha
               // cout << line << endl;
                separated = Separate_Space(line); // separa em um vector de strings as partes separadas por espaço
                if (separated.size() == 3) { // rotina quando há rótulo
                    for (unsigned int i = 0; i < symbol.size(); i++) {
                        if (symbol.at(i) == separated.at(0)) {
                            if (symbolV.at(i) == -1) {
                                symbolV.at(i) = ci+org;
                            }
                            else if (passo == 1) {
                                input.close();
                                objectFile.close();
                                return "\n Erro: redeclaracao de rotulo";
                            }
                            found = 1;
                        }
                    }
                    if (!found && passo == 1) {
                        symbol.push_back(separated.at(0));
                        symbolV.push_back(ci+org);
                    }
                    found = 0;
                    aux = 1;
                }

                /**** MNEMONICOS ****/


                if (separated.at(aux) == "JP" || separated.at(aux) == "J") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 0 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                            cont = 1;
                        }
                        else {
                            objectFile << " " << 0 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "JZ" || separated.at(aux) == "Z") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 1 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << 1 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                   }
                    ci += 2;
                }
                else if (separated.at(aux) == "JN" || separated.at(aux) == "N") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 2 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << 2 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "CN" || separated.at(aux) == "C") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        objectFile << " " << 3 << std::setw(1) << std::hex << temp;
                        cont += 1;
                    }
                    ci += 1;
                }
                else if (separated.at(aux) == "+") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 4 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << 4 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "-") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 5 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << 5 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "*") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 6 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << 6 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "/") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 7 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << 7 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "LD" || separated.at(aux) == "L") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 8 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << 8 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "MM" || separated.at(aux) == "M") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << 9 << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << 9 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "SC" || separated.at(aux) == "S") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " " << "a" << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " " << "a" << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "OS" || separated.at(aux) == "O") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        objectFile << " " << "b" << std::setw(1) << std::hex << temp;
                        cont += 1;
                    }
                    ci += 1;
                }
                else if (separated.at(aux) == "IO" || separated.at(aux) == "I") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        objectFile << " " << "c" << std::setw(1) << std::hex << temp;
                        cont += 1;
                    }
                    ci += 1;
                }


                /*** PSEUDOINSTRUÇÕES ***/

                else if (separated.at(aux) == "@") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, 0);
                    if (passo == 2) {
                        //cout << temp << std::hex << " " << temp << " " << 0 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                        objectFile << " " << 0 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);

                        objectFile << " " << std::setw(2) << std::setfill('0')  << std::hex << (ci%0x100);
                        cont += 3;
                    }
                    org = temp;
                }
                else if (separated.at(aux) == "#") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    /*if (passo == 2) {
                        if (cont == 15)
                            objectFile << " " << 0 << std::setw(1) << std::hex << (temp/0x100) << endl << std::setw(2) << std::hex << (temp%0x100);
                        else
                            objectFile << " " << 0 << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                       cont += 2;
                    }*/
                    //ci += 2;
                    inicio = temp;

                }
                else if (separated.at(aux) == "$") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        if (cont == 15) {
                            objectFile << " "  << std::setw(1) << std::hex << (temp/0x100) << endl << " " << std::setw(2) << std::hex << (temp%0x100);
                        cont = 1;
                        }
                        else {
                            objectFile << " "  << std::setw(1) << std::hex << (temp/0x100) << " " << std::setw(2) << std::setfill('0')  << std::hex << (temp%0x100);
                            cont += 2;
                        }
                    }
                    ci += 2;
                }
                else if (separated.at(aux) == "K") {
                    int temp;
                    temp = verificarOperando(passo, aux + 1, &symbol, &symbolV, separated, ci, org);
                    if (passo == 2) {
                        objectFile << " " << std::setw(2) << std::hex << temp;
                        cont += 1;
                    }
                    ci += 1;
                }

                else {
                    input.close();
                    objectFile.close();
                    return "\n Erro: mnemonico <"+separated.at(aux)+"> nao encontrado";
                }
                if (cont > 15) {
                    if (cont == 16)
                        objectFile << endl;
                    cont = 0;
                }
                aux = 0;
            }
        }
        input.close();
        passo++;

        for (unsigned int i = 0; i < symbolV.size(); i++)
            if (symbolV.at(i) == -1)
                return " Erro: uso de rotulo <"+symbol.at(i)+"> nao declarado";

    }
    objectFile.close();
    resposta = maquinavirtual->simulador(arquivo,user,inicio);
    return resposta;
}


/*int firstInt = 0xab;
    int secInt = 0xff;
    std::cout << "the values 0xab + 0xff = 0x" <<std::hex << (firstInt+secInt);*/

int Montador::verificarOperando(int passo, int op, vector<std::string>* symbol, vector<int>* symbolV, vector<std::string> separated, int ci,int org) {
    std::size_t found = separated.at(op).find("+"); //procura + no operando
    std::size_t found2 = separated.at(op).find("-"); //procura - no operando
    std::vector<std::string> ope;
    string symb;
    bool f = 0, rotulo = 1;
    int x = -1, y = 0;
    if (found!=std::string::npos) {
        x = 1;
        ope = Separate_expression(separated.at(op),'+'); // separa em vector de string as partes separadas por '+'
    }
    else if (found2!=std::string::npos) {
        x = 2;
        ope = Separate_expression(separated.at(op),'-'); // separa em vector de string as partes separadas por '-'
    }
    else if  (atoi(separated.at(op).c_str()) == 0 && separated.at(op) != "0") {// operando é um rótulo
        symb = separated.at(op);
        for (int i = 0; i < symb.length(); i++)
            if ( (int(symb[i]) > 47 && int(symb[i]) < 58) || (int(symb[i]) > 96 && int(symb[i]) < 103) ) {
                rotulo = 0;
            }
            else {
                    rotulo = 1;
                    break;
            }
        if (rotulo) {
            for (unsigned int i = 0; i < symbol->size(); i++) {
                if (symbol->at(i) == symb) {
                    y = symbolV->at(i);
                    f = 1;
                    break;
                }
            }
            if (passo == 1 && f == 0) {
                symbol->push_back(symb);
                symbolV->push_back(-1);
                return -1;
            }
            return y;
        }
        rotulo = 1;
    }
    if (x > 0) {
        symb = ope.at(0);
        for (unsigned int i = 0; i < symbol->size(); i++) {
            if (symbol->at(i) == symb) {
                y = symbolV->at(i);
                f = 1;
                break;
            }
        }
        if (passo == 1 && f == 0) {
            symbol->push_back(symb);
            symbolV->push_back(-1);
            return -1;
        }
    }
    if (x == 1)
        return stoi(ope.at(1).c_str(),NULL,16) + y ;
    else if (x == 2)
        return -stoi(ope.at(1).c_str(),NULL,16) + y;
    else
        return stoi(separated.at(op).c_str(), NULL, 16);

}


vector<string> Montador::Separate_Space(string s){
   std::string str = replaceChar(s, '\t',' ');
   char split_char = ' ';

   std::istringstream split(str);
   std::vector<std::string> separated;
   for (std::string each; std::getline(split, each, split_char); separated.push_back(each));

	for (unsigned int i = 0 ; i < separated.size(); i++){
   		if (separated.at(i) == "") {
			separated.erase(separated.begin() + i);
			i--;
		}
 	}
	return separated;
}

string Montador::replaceChar(string str, char ch1, char ch2) {
  for (int i = 0; i < str.length(); ++i) {
    if (str[i] == ch1)
      str[i] = ch2;
  }

  return str;
}

vector<string> Montador::Separate_expression(string s, char c){
    std::string str(s);
    std::string each;
    char split_char = c;

    std::istringstream split(str);
    std::vector<std::string> separated;

    for (each; getline(split, each, split_char); separated.push_back(each));
	for ( unsigned int i = 0 ; i < separated.size(); i++){
   		if (separated.at(i) == "") {
			separated.erase(separated.begin() + i);
			i--;
		}
 	}
	return separated;
}


