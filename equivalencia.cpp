#include "equivalencia.h"

/**
 * @brief A partir da identificação da transação retorna a 
 * posição que ela é executada na nova ordenação
 * 
 * @param ordem_tr Ordenação das transações que se quer testar
 * @param transacao Identificação da transação
 * @return int 
 */
int getPosicaoTransacao(vector<int>& ordem_tr, int transacao){
    for(int i = 0; i < ordem_tr.size(); i++){
        if(ordem_tr[i] == transacao){
            return i;
        }
    }
    return -1;
}

/**
 * @brief Verifica se para uma determinada operação de leitura ou escrita sua ordem, executando
 * seguindo a "ordem_tr" foi alterada em relação ao escalonamento original, ou seja, verifica se
 * todas as escritas do atributo que eram realizadas antes, continuam sendo realizadas antes
 * 
 * @param escalonamento Vetor com as operações na ordem original
 * @param ordem_tr Ordenação das transações que se quer testar
 * @param ti Posição da operação que se deseja testar no vetor de escalonamento
 * @param leitura Se deve ser testado a leitura ou escrita
 * @return true se a ordem foi~ alterada
 * @return false caso contrário
 */
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

/** @brief A partir do escalonamento original, executa o algoritmo de teste de visão
 *  verificando se uma determinada ordem de execução é válida.
 * 
 * @param escalonamento Vetor com as operações na ordem original
 * @param ordem_tr Ordenação das transações que se quer testar
 * @return Retorna true se a ordem for válida e false caso contrário
*/
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

    // Regra: Se o operador w(y) em Tk é a ultima escrita de y em S, 
    // então w(y) em Tk deve ser a última escrita em S'

    // Pesquisa ultima escrita do escalonamento original
    // Verifica quais transações realizam escrita
    map<int, bool>transacoes_com_escrita;
    int ultima_escrita = -1;
    for(int i = 0; i < escalonamento.size(); i++){
        if(escalonamento[i].isEscrita()){
            transacoes_com_escrita[escalonamento[i].transacao] = true;
            ultima_escrita = escalonamento[i].transacao;
        }
    }

    // Verifica se a ordem se mantém
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

/** @brief Realiza testes verificando se o escalonamento possui ou não equivalente
 * por visão. O funcionamento consiste em gerar diversas permutações das transações
 * até encontrar alguma que seja válida.
* 
* @param escalonamento Listagem com todas as operações do escalonamento
* @param transacoes Vetor com a identificação das transações que serão processadas
* @return Retorna true se o escalonamento possui equivalente e false caso contrário
*/
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