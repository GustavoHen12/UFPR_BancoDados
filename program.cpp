#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define TIMESTAMP 0
#define TRANSACAO 1
#define OPERACAO 2
#define ATRIBUTO 3

char LEITURA = 'R', ESCRITA = 'W', COMMIT = 'C';

int inicio_ciclo, fim_ciclo;

int criaGrafoSeriabilidade(vector<tuple<int, int, char, char>> &escalonamento, vector<vector<int>>&g){
    // Cria mapeamento entre os nodos
    map<int, int> nodos;
    int quant_transacoes = 0;
    for(int i = 0; i < escalonamento.size(); i++){
        int transacao = get<TRANSACAO>(escalonamento[i]);
        if(nodos.count(transacao) <= 0){
            nodos[transacao] = quant_transacoes;
            quant_transacoes++;
        }
    }

    // Cria grafo
    g.assign(quant_transacoes, vector<int>());

    // Crie um nó para cada T do escalonamento S
    // Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
    // Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
    // Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
    for(int tj = 0; tj < escalonamento.size(); tj++){
        char operacao = get<OPERACAO>(escalonamento[tj]);
        if(operacao == LEITURA) {
            char atributo = get<ATRIBUTO>(escalonamento[tj]);
            for(int ti = 0; ti < tj; ti++){
                if((get<OPERACAO>(escalonamento[ti]) == ESCRITA)
                    && (get<ATRIBUTO>(escalonamento[ti]) == atributo)
                    && (get<TRANSACAO>(escalonamento[ti]) != get<TRANSACAO>(escalonamento[tj]))){
                        int u = nodos[get<TRANSACAO>(escalonamento[ti])];
                        int v = nodos[get<TRANSACAO>(escalonamento[tj])];
                        if(find(g[u].begin(), g[u].end(), v) == g[u].end()){
                            g[u].push_back(v);
                        }
                }
            }
        } else if(operacao == ESCRITA) {
            char atributo = get<ATRIBUTO>(escalonamento[tj]);
            for(int ti = 0; ti < tj; ti++){
                if((get<OPERACAO>(escalonamento[ti]) == LEITURA)
                    && (get<ATRIBUTO>(escalonamento[ti]) == atributo)
                    && (get<TRANSACAO>(escalonamento[ti]) != get<TRANSACAO>(escalonamento[tj]))){
                        int u = nodos[get<TRANSACAO>(escalonamento[ti])];
                        int v = nodos[get<TRANSACAO>(escalonamento[tj])];
                        if(find(g[u].begin(), g[u].end(), v) == g[u].end()){
                            g[u].push_back(v);
                        }
                } else if((get<OPERACAO>(escalonamento[ti]) == ESCRITA)
                    && (get<ATRIBUTO>(escalonamento[ti]) == atributo)
                    && (get<TRANSACAO>(escalonamento[ti]) != get<TRANSACAO>(escalonamento[tj]))){
                        int u = nodos[get<TRANSACAO>(escalonamento[ti])];
                        int v = nodos[get<TRANSACAO>(escalonamento[tj])];
                        if(find(g[u].begin(), g[u].end(), v) == g[u].end()){
                            g[u].push_back(v);
                        }
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

bool verificaSeriabilidade(vector<tuple<int, int, char, char>> &escalonamento, vector<int> &transacoes){
    // Cria grafo
    vector<vector<int>> g;
    int size = criaGrafoSeriabilidade(escalonamento, g);
    for(int i = 0; i < g.size(); i++){
        cout << i << ": ";
        for(int x:g[i]){
            cout << x << " ";
        }
        cout << endl;
    }

    // Testa para encontrar ciclo
    vector<char> cor(size, 0);
    vector<int> pai(size, -1);
    inicio_ciclo = -1;

    for (int v = 0; v < size; v++) {
        if (cor[v] == 0 && dfs(v, g, cor, pai))
            break;
    }

    cout << "Possui ciclo: " << (inicio_ciclo != -1) << endl;

    return inicio_ciclo != -1;
}

void processaEscalonamento(vector<tuple<int, int, char, char>> &escalonamento){
    bool isSeriavel, isEquivalente;
    vector<int> transacoes;
    // Primeiro realiza o teste de seriabilidade
    isSeriavel = verificaSeriabilidade(escalonamento, transacoes);
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    vector<tuple<int, int, char, char>> agendamento;

    // Le entrada
    int ts, transacao;
    char op, var;
    while(cin >> ts >> transacao >> op >> var){
        tuple<int, int, char, char> op_transacao = make_tuple(ts, transacao, op, var);

        agendamento.push_back(op_transacao);
        if(get<OPERACAO>(op_transacao) == 'C'){
            cout << "processa\n";
            processaEscalonamento(agendamento);
            agendamento.clear();
        }
    }
}