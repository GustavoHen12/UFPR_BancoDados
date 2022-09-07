#include "seriabilidade.h"

char LEITURA = 'R',ESCRITA = 'W', COMMIT = 'C';
int inicio_ciclo, fim_ciclo;
map<int, int> nodos;

void adicionaAresta(vector<vector<int>>&g, int tj, int ti){
    int u = nodos[ti];
    int v = nodos[tj];

    if(find(g[u].begin(), g[u].end(), v) == g[u].end()){
        g[u].push_back(v);
    }
}

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

bool verificaSeriabilidade(vector<operacao> &escalonamento, vector<int>& transacoes){
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
