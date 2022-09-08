#include <bits/stdc++.h>
#include "seriabilidade.h"
#include "equivalencia.h"

using namespace std;

bool processaTransacoes (vector<operacao> &escalonamento, vector<int>& transacoes) {
    vector<int> tx_commit;
    for(int i = 0; i < escalonamento.size(); i++){
        // Verifica se adiciona alguma transacao a lista
        if(find(transacoes.begin(), transacoes.end(), escalonamento[i].transacao) == transacoes.end()){
            transacoes.push_back(escalonamento[i].transacao);
        }
        // Verifica se a transacao foi commitada
        if(escalonamento[i].isCommit()){
            tx_commit.push_back(escalonamento[i].transacao);
        }
    }

    return tx_commit.size() == transacoes.size();
}

void processaEscalonamento(vector<operacao> &escalonamento, vector<int>& transacoes){
    bool isSeriavel, isEquivalente;
    // Realiza o teste de seriabilidade
    isSeriavel = verificaSeriabilidade(escalonamento, transacoes);

    // Realiza o teste de equivalencia
    isEquivalente = verificaEquivalencia(escalonamento, transacoes);

    // Imprime resultado
    sort(transacoes.begin(), transacoes.end());
    for(int i = 0; i < transacoes.size(); i++) cout << transacoes[i] << (i < transacoes.size()-1 ? "," : " ");
    cout << (isSeriavel ? "SS" : "NS") << " ";
    cout << (isEquivalente ? "SV" : "NV");
    cout << endl;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    vector<operacao> agendamento;
    vector<int> transacoes;
    
    // Le entrada
    int ts, transacao;
    char op, var;
    int indice = 1;
    while(cin >> ts >> transacao >> op >> var){
        operacao op_transacao = operacao(ts, transacao, op, var);
        agendamento.push_back(op_transacao);

        if(processaTransacoes(agendamento, transacoes)){
            cout << indice << " ";
            processaEscalonamento(agendamento, transacoes);
            agendamento.clear();
            transacoes.clear();
            indice++;
        }
    }
}