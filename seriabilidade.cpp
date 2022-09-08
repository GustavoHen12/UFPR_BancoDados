#include "seriabilidade.h"

int inicio_ciclo, fim_ciclo;
map<int, int> nodos;

/**
 * @brief Função auxiliar para adicionar uma aresta do nodo da transação ti
 * para o nodo da transação tj 
 * 
 * @param g Grafo
 * @param tj Identificador da transação Ti
 * @param ti Identificador da transação Tj
 */
void adicionaAresta(vector<vector<int>>&g, int tj, int ti){
    int u = nodos[ti];
    int v = nodos[tj];

    if(find(g[u].begin(), g[u].end(), v) == g[u].end()){
        g[u].push_back(v);
    }
}

/**
 * @brief Algoritmo de busca em profundidade no grafo
 * 
 * @param v Nodo a partir do qual será executado
 * @param g Grafo (lista de adjacência)
 * @param cor Vetor para indicar se o nodo já foi visitado ou não
 * @param pai Vetor com o pai de cada nodo
 * @return true 
 * @return false 
 */
bool dfs(int v, vector<vector<int>>& g, vector<char>& cor, vector<int>& pai) {
    cor[v] = 1;
    for (int u : g[v]) {
        if (cor[u] == 0) {
            pai[u] = v;
            if (dfs(u, g, cor, pai))
                return true;
        } else if (cor[u] == 1) {
            fim_ciclo = v;
            inicio_ciclo = u;
            return true;
        }
    }
    cor[v] = 2;
    return false;
}

/**
 * @brief Função responsável por criar um grafo a partir do escalonamento
 * 
 * @param escalonamento Vetor com as operações do escalonamento
 * @param g O grafo é representado por uma lista de adjacência. Portanto deve ser passada
 * uma lista vazia, e ao final da execução essa deve estar preenchida corretamente
 * @return int Retorna a quantidade de transações presentes no escalonamento
 */
int criaGrafoSeriabilidade(vector<operacao> &escalonamento, vector<vector<int>>&g){
    // Cria mapeamento entre os nodos
    int quant_transacoes = 0;
    for(int i = 0; i < escalonamento.size(); i++){
        int transacao = escalonamento[i].transacao;
        if(nodos.count(transacao) <= 0){
            nodos[transacao] = quant_transacoes;
            quant_transacoes++;
        }
    }

    // Crie um nó para cada T do escalonamento S
    g.assign(quant_transacoes, vector<int>());

    for(int tj = 0; tj < escalonamento.size(); tj++){
        char atributo = escalonamento[tj].atributo;
        // Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
        if(escalonamento[tj].isLeitura()) {
            for(int ti = 0; ti < tj; ti++){
                if(escalonamento[ti].isEscrita() && escalonamento[ti].atributo == atributo && escalonamento[ti].transacao != escalonamento[tj].transacao){
                    adicionaAresta(g, escalonamento[tj].transacao, escalonamento[ti].transacao);
                }
            }
        } else if(escalonamento[tj].isEscrita()) {
            for(int ti = 0; ti < tj; ti++){
                // Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
                if(escalonamento[ti].isLeitura() && escalonamento[ti].atributo == atributo && escalonamento[ti].transacao != escalonamento[tj].transacao){
                    adicionaAresta(g, escalonamento[tj].transacao, escalonamento[ti].transacao);
                }
                // Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
                else if (escalonamento[ti].isEscrita() && escalonamento[ti].atributo == atributo && escalonamento[ti].transacao != escalonamento[tj].transacao){
                    adicionaAresta(g, escalonamento[tj].transacao, escalonamento[ti].transacao);
                }
            }
        }
    }

    return quant_transacoes;
}

/**
 * @brief Função para verificar se o escalonamento é ou não seriável.
 * A execução funciona em duas etapas, primeiramente é criado um grafo com
 * as arestas seguindo as regras estabelecidas, após isso é realizado uma busca no grafo
 * para verificar se ele possui ou não ciclos
 * 
 * @param escalonamento Vetor com todas as operações do escalonamento
 * @return true 
 * @return false 
 */
bool verificaSeriabilidade(vector<operacao> &escalonamento) {
    // Cria grafo
    vector<vector<int>> g;
    int size = criaGrafoSeriabilidade(escalonamento, g);

    // Testa para encontrar ciclo
    vector<char> cor(size, 0);
    vector<int> pai(size, -1);
    inicio_ciclo = -1;

    for (int v = 0; v < size; v++) {
        if (cor[v] == 0 && dfs(v, g, cor, pai))
            break;
    }

    return inicio_ciclo == -1;
}
