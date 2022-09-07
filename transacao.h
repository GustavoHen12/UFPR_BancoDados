#ifndef __TRANSACAO__
#define __TRANSACAO__

class operacao {
    public:
        int timestamp;
        int transacao;
        char op;
        char atributo;

        operacao(int ts, int tr, char op_tr, char atr);
        bool isLeitura();
        bool isEscrita();
        bool isCommit();
};

#endif