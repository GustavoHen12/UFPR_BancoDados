#include <bits/stdc++.h>
#include "seriabilidade.h"
#include "equivalencia.h"

using namespace std;

/** @brief Função que processa as transações do escalonamento até o momento. Se
* foi adicionado uma nova transação no escalonamento, a identificação dessa é
* adicionado a lista de transações.
* 
* @param escalonamento Listagem com todas as operações do escalonamento correte
* @param transacoes Lista com todas as transações atuais
* @return Retorna true se o escalonamento é válido (se todas as transações foram comitadas),
* caso contrário false
*/
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

/** @brief Função que processa o escalonamento atual e imprime o resultado. Essa função
 * irá verificar a seriabilidade do agendamento e se ele possui um equivalente por visão.
 * O resultado é impresso da seguinte forma: [transações] [SS/NS] [NS/NV]
 * 
 * @param escalonamento Listagem com todas as operações do escalonamento correte
 * @param transacoes Vetor com o número de todas as transaçõe que devem ser processadas
*/
void processaEscalonamento(vector<operacao> &escalonamento, vector<int>& transacoes){
    bool isSeriavel, isEquivalente;
    // Realiza o teste de seriabilidade
    isSeriavel = verificaSeriabilidade(escalonamento);

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

        // Verifica se o agendamento está completo
        if(processaTransacoes(agendamento, transacoes)){
            cout << indice << " ";
            processaEscalonamento(agendamento, transacoes);
            agendamento.clear();
            transacoes.clear();
            indice++;
        }
    }
}