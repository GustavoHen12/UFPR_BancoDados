#include"transacao.h"

operacao::operacao(int ts, int tr, char op_tr, char atr){
    timestamp = ts;
    transacao = tr;
    op = op_tr;
    atributo = atr;
}

bool operacao::isEscrita(){
    return op == 'W';
}

bool operacao::isLeitura(){
    return op == 'R';
}

bool operacao::isCommit(){
    return op == 'C';
}