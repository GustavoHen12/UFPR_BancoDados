#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define TIMESTAMP 0
#define AGENDAMENTO 1
#define OPERACAO 2
#define ATRIBUTO 3

// Crie um nó para cada T do escalonamento S
// Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
// Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
// Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti

bool verificaSeriabilidade(vector<tuple<int, int, char, char>> &escalonamento, vector<int> &transacoes){
    // Cria grafo

    // para cada linha do escalonamento
        // ind = j

    return false;
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
        if(get<ATRIBUTO>(op_transacao) == 'C'){
            processaEscalonamento(agendamento);
            agendamento.clear();
        }
    }
}