#include "MV.h"

MV::MV()
{
    /*** Carrega loader na memoria ***/
    writeData(memoria[0], 'c', '1');
    writeData(memoria[1], '9', '1');
    writeData(memoria[2], '0', '0');
    writeData(memoria[3], 'c', '1');
    writeData(memoria[4], '9', '1');
    writeData(memoria[5], '0', '1');
    writeData(memoria[6], 'c', '1');
    writeData(memoria[7], '9', '1');
    writeData(memoria[8], '0', '2');
    writeData(memoria[9], '8', '1');
    writeData(memoria[10], '0', '0');
    writeData(memoria[11], '4', '0');
    writeData(memoria[12], '3', '6');
    writeData(memoria[13], '9', '0');
    writeData(memoria[14], '1', '4');
    writeData(memoria[15], '8', '1');
    writeData(memoria[16], '0', '1');
    writeData(memoria[17], '9', '0');
    writeData(memoria[18], '1', '5');
    writeData(memoria[19], 'c', '1');
    writeData(memoria[20], '9', '0');
    writeData(memoria[21], '0', '0');
    writeData(memoria[22], '8', '1');
    writeData(memoria[23], '0', '1');
    writeData(memoria[24], '4', '0');
    writeData(memoria[25], '3', '5');
    writeData(memoria[26], '9', '1');
    writeData(memoria[27], '0', '1');
    writeData(memoria[28], '8', '1');
    writeData(memoria[29], '0', '2');
    writeData(memoria[30], '5', '0');
    writeData(memoria[31], '3', '5');
    writeData(memoria[32], '9', '1');
    writeData(memoria[33], '0', '2');
    writeData(memoria[34], '1', '0');
    writeData(memoria[35], '3', '4');
    writeData(memoria[36], '0', '0');
    writeData(memoria[37], '0', '9');
    writeData(memoria[38], '8', '1');
    writeData(memoria[39], '0', '0');
    writeData(memoria[40], '4', '0');
    writeData(memoria[41], '3', '6');
    writeData(memoria[42], '9', '0');
    writeData(memoria[43], '3', '2');
    writeData(memoria[44], '8', '1');
    writeData(memoria[45], '0', '1');
    writeData(memoria[46], '9', '0');
    writeData(memoria[47], '3', '2');
    writeData(memoria[48], '8', '0');
    writeData(memoria[49], '3', '7');
    writeData(memoria[50], '9', '0');
    writeData(memoria[51], '0', '0');
    writeData(memoria[52], 'b', '1');
    writeData(memoria[53], '0', '1');
    writeData(memoria[54], '9', '0');
    writeData(memoria[55], 'b', '2');
}

MV::~MV()
{
    //dtor
}

void MV::writeData(char mem[2],char x, char y) {
    mem[0] = x;
    mem[1] = y;
}

string MV::simulador(string arquivo, string user, int inicio)
{
    ifstream object;
    ofstream output;
    stringstream sstream;
    string nome, nomeO, op1 = "", op2 = "", result;
    int pc = 0,ci, temp, epc = 0;
    int ant = 1000;
    bool indirect = 0;
    char aux0, aux1, aux2, aux3;
    int op1_c, op2_c;
    char ac[2];
    nome = "./"+user+"/"+arquivo+"_o.txt";
    nomeO = "./"+user+"/"+arquivo+"_dumper_o.txt";
    object.open(nome.c_str());
    output.open(nomeO.c_str());
    ac[0] = 0; ac[1] = 0;

    while (pc < 4096) {
        aux0 = memoria[pc][0];
        aux1 = memoria[pc][1];
        switch (aux0) {
            case '0':   aux2 = memoria[pc+1][0]; /*J ou JP */
                        aux3 = memoria[pc+1][1];
                        pc = getEndereco(aux1, aux2, aux3);
                        indirect = 0;
                        break;

            case '1':   if (ac[0] == '0' && ac[1] == '0') { /* JZ ou Z*/
                            aux2 = memoria[pc+1][0];
                            aux3 = memoria[pc+1][1];
                            pc = getEndereco(aux1, aux2, aux3);
                        }
                        else pc += 2;
                        indirect = 0;
                        break;

            case '2':   if (ac[0] > 55) { /*JN ou N */
                            aux2 = memoria[pc+1][0];
                            aux3 = memoria[pc+1][1];
                            pc = getEndereco(aux1, aux2, aux3);
                            break;
                        }
                        else pc += 2;
                        indirect = 0;
                        break;

            case '3':   if (aux1 == '2') { /* CN ou C*/
                            indirect = 1;
                        }
                        pc += 1;
                        break;

            case '4':   aux2 = memoria[pc+1][0];   /* + */
                        aux3 = memoria[pc+1][1];
                        temp = getEndereco(aux1, aux2, aux3);
                        op1 = "";
                        op2 = "";
                        op1 += ac[0]; op1 += ac[1];
                        op2 += memoria[temp][0];  op2 += memoria[temp][1];
                        op1_c = stoi( op1, nullptr, 16 );
                        op2_c = stoi( op2, nullptr, 16 );
                        temp = op1_c + op2_c;
                        tranformaResultado(temp, &ac[0], &ac[1]);
                        pc += 2;
                        indirect = 0;
                        break;

            case '5':   aux2 = memoria[pc+1][0];   /* - */
                        aux3 = memoria[pc+1][1];
                        temp = getEndereco(aux1, aux2, aux3);
                        op1 = "";
                        op2 = "";
                        op1 += ac[0]; op1 += ac[1];
                        op2 += memoria[temp][0];  op2 += memoria[temp][1];
                        op1_c = stoi( op1, nullptr, 16 );
                        op2_c = stoi( op2, nullptr, 16 );
                        temp = op1_c - op2_c;
                        tranformaResultado(temp, &ac[0], &ac[1]);
                        pc += 2;
                        indirect = 0;
                        break;

            case '6':   aux2 = memoria[pc+1][0];   /* * */
                        aux3 = memoria[pc+1][1];
                        temp = getEndereco(aux1, aux2, aux3);
                        op1 = "";
                        op2 = "";
                        op1 += ac[0]; op1 += ac[1];
                        op2 += memoria[temp][0];  op2 += memoria[temp][1];
                        op1_c = stoi( op1, nullptr, 16 );
                        op2_c = stoi( op2, nullptr, 16 );
                        temp = op1_c * op2_c;
                        tranformaResultado(temp, &ac[0], &ac[1]);
                        pc += 2;
                        indirect = 0;
                        break;

            case '7':   aux2 = memoria[pc+1][0];   /* / */
                        aux3 = memoria[pc+1][1];
                        temp = getEndereco(aux1, aux2, aux3);
                        op1 = "";
                        op2 = "";
                        op1 += ac[0]; op1 += ac[1];
                        op2 += memoria[temp][0];  op2 += memoria[temp][1];
                        op1_c = stoi( op1, nullptr, 16 );
                        op2_c = stoi( op2, nullptr, 16 );
                        temp = op1_c / op2_c;
                        tranformaResultado(temp, &ac[0], &ac[1]);
                        pc += 2;
                        indirect = 0;
                        break;

            case '8':   aux2 = memoria[pc+1][0];    /*L  ou LD */
                        aux3 = memoria[pc+1][1];
                        temp = getEndereco(aux1, aux2, aux3);
                        ac[0] = memoria[temp][0];
                        ac[1] = memoria[temp][1];
                        pc += 2;
                        indirect = 0;
                        break;

            case '9':   aux2 = memoria[pc+1][0];    /* M ou MM */
                        aux3 = memoria[pc+1][1];
                        temp = getEndereco(aux1, aux2, aux3);
                        memoria[temp][0] = ac[0];
                        memoria[temp][1] = ac[1];
                        pc += 2;
                        indirect = 0;
                        break;

            case 'a':   aux2 = memoria[pc+1][0];    /*S  ou SC */
                        aux3 = memoria[pc+1][1];
                        pc = getEndereco(aux1, aux2, aux3);
                        epc = pc+2;
                        indirect = 0;
                        break;

            case 'b':   if (aux1 == '1') { /* OS ou O*/
                            pc = inicio;
                        }
                        else if (aux1 == '2') { /* OS ou O*/
                            return " Programa executado com sucesso";
                        }
                        indirect = 0;
                        break;

            case 'c':   /* IO ou I*/
                        if (aux1 == '1') { /* GD */
                            char z;
                            temp = 0;
                            while (temp < 2) {
                                object.get(z);
                                if (z != ' ' and z != '\n' ) {
                                    ac[temp] = z;
                                    temp++;
                                }
                            }
                        }
                        else if (aux1 == '2') { /*  */
                            //ac =
                        }
                        else if (aux1 == '3') { /* pega byte do teclado */
                            string in;
                            cin >> in;
                            if  (in.length() != 2)
                                return " Erro ao adquirir byte do teclado";
                            else {
                                ac[0] = in[0];
                                ac[1] = in[1];
                            }
                        }
                        else if (aux1 == '4') { /* imprime byte + space na tela */
                            cout << ac[0] << ac[1] << " ";
                        }
                        else if (aux1 == '5') { /* imprime \n na tela */
                            cout << endl;
                        }
                        indirect = 0;
                        pc += 1;
                        break;

        }
    }
    return "Endereço fora da região de trabalho";
}
/*    while (testar.good()) {
        testar.get(z);
        if (z != ' ' and z != '\n' ) {
            ac[a] = z;
            //cout << "ac[ " << a << " ] :" <<  ac[a] << endl;
            a++;
        }
        if (a == 2) {
            mem[b][0] = ac[0];
            mem[b++][1] = ac[1];
            a = 0;
        }
    }*/
/*
char x = 'f', y = 'f';
    string szTest = "", result;
    stringstream sstream;
    int temp;
    szTest += x; szTest += y;
    char chTest = stoi( szTest, nullptr, 16 );
    std::cout << szTest << ": " << static_cast<int>(chTest)  << std::endl;
    temp = static_cast<int>(chTest) -2;

    sstream << std::hex << temp;
    result = sstream.str();
    std::cout << temp  << " : " << result.substr(6,2)  << std::endl;
*/

int MV::getEndereco(char aux1, char aux2, char aux3){
    int c,d,u;
    c = charToInt(aux1);
    d = charToInt(aux2);
    u = charToInt(aux3);

    return c*16*16 + d*16 + u;

}

void MV::tranformaResultado(int result, char* ac1, char* ac2) {
    int aux1, aux2;
    aux1 = result % 16;
    aux2 = (result /16) % 16;
    *ac1 = intToChar(aux2);
    *ac2 = intToChar(aux1);
}


int MV::charToInt(char aux) {
    int u;
    switch(aux) {
        case '0':   u = 0;
                    break;
        case '1':   u = 1;
                    break;
        case '2':   u = 2;
                    break;
        case '3':   u = 3;
                    break;
        case '4':   u = 4;
                    break;
        case '5':   u = 5;
                    break;
        case '6':   u = 6;
                    break;
        case '7':   u = 7;
                    break;
        case '8':   u = 8;
                    break;
        case '9':   u = 9;
                    break;
        case 'a':   u = 10;
                    break;
        case 'b':   u = 11;
                    break;
        case 'c':   u = 12;
                    break;
        case 'd':   u = 13;
                    break;
        case 'e':   u = 14;
                    break;
        case 'f':   u = 15;
                    break;
        default:    u = 15;
                    break;
    }
    return u;
}

char MV::intToChar(int x) {
    switch(x) {
        case 0:   return '0';

        case 1:   return '1';

        case 2:   return '2';

        case 3:   return '3';

        case 4:   return '4';

        case 5:   return '5';

        case 6:   return '6';

        case 7:   return '7';

        case 8:   return '8';

        case 9:   return '9';

        case 10:   return 'a';

        case 11:   return 'b';

        case 12:   return 'c';

        case 13:   return 'd';

        case 14:   return 'e';

        case 15:   return 'f';
    }
}

