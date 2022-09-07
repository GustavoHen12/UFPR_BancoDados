#include "equivalencia.h"

int getPosicaoTransacao(vector<int>& ordem_tr, int transacao){
    for(int i = 0; i < ordem_tr.size(); i++){
        if(ordem_tr[i] == transacao){
            return i;
        }
    }
    return -1;
}

bool alterouOrdem(vector<operacao> &escalonamento, vector<int>& ordem_tr, int ti, bool leitura){
    for(int tj = 0; tj < ti; tj++){
        bool op = leitura ? escalonamento[tj].isEscrita() : escalonamento[tj].isLeitura();
        if(op
            && (escalonamento[tj].transacao != escalonamento[ti].transacao)
            && (escalonamento[tj].atributo == escalonamento[ti].atributo)
            && (getPosicaoTransacao(ordem_tr, escalonamento[tj].transacao) > getPosicaoTransacao(ordem_tr, escalonamento[ti].transacao))){
            // cout << getPosicaoTransacao(ordem_tr, escalonamento[tj].transacao) << " < " << getPosicaoTransacao(ordem_tr, escalonamento[ti].transacao) << "  ";
            return true;
        }
    }

    return false;
}

// Dois agendamentos S e S' são ditos visão equivalentes, se atenderem as seguintes condições:
// - O mesmo conjunto de transações e operações participam em S e S'
bool visaoValida(vector<operacao> &escalonamento, vector<int>& ordem_tr){
    bool valido = true;
    // Para cada r(x) de Ti, se o valor de x lido ja foi escrito por w(x) de Tj, ou seja, 
    // houve W(x) antes de R(x) em transações distintas, o mesmo deve permanecer para r(x) de Ti em S'
    for(int ti = 0; ti < escalonamento.size(); ti++){
        if(escalonamento[ti].isLeitura()){
            if(alterouOrdem(escalonamento, ordem_tr, ti, true)){
                valido = false;
                break;
            }
        } else if(escalonamento[ti].isEscrita()){
            if(alterouOrdem(escalonamento, ordem_tr, ti, false)){
                valido = false;
                break;
            }
        }
    }

    // Se o operador w(y) em Tk é a ultima escrita de y em S, 
    // então w(y) em Tk deve ser a última escrita em S'
    map<int, bool>transacoes_com_escrita;
    int ultima_escrita = -1;
    for(int i = 0; i < escalonamento.size(); i++){
        if(escalonamento[i].isEscrita()){
            transacoes_com_escrita[escalonamento[i].transacao] = true;
            ultima_escrita = escalonamento[i].transacao;
        }
    }

    if(ultima_escrita != -1){
        int indice_ultima_escrita = getPosicaoTransacao(ordem_tr, ultima_escrita);
        for(int i = indice_ultima_escrita + 1; i < ordem_tr.size(); i++){
            if(transacoes_com_escrita[ordem_tr[i]]){
                valido = false;
                break;
            }
        }
    }

    return valido;
}

bool verificaEquivalencia(vector<operacao> &escalonamento, vector<int>& transacoes){
    // Separa as transacoes
    vector<int> ordem_transacoes;
    bool visao_valida = false;
    sort(transacoes.begin(), transacoes.end());
    do{
        visao_valida = visaoValida(escalonamento, transacoes);
    } while(!visao_valida && next_permutation(transacoes.begin(), transacoes.end()));

    return visao_valida;
}