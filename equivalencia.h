/**
 * @author Gustavo Henrique da Silva Barbosa / GRR20190485
 */

#ifndef __EQUIVALENCIA__
#define __EQUIVALENCIA__

#include <bits/stdc++.h>
#include "transacao.h"

using namespace std;

/** @brief Realiza testes verificando se o escalonamento possui ou não equivalente
 * por visão.
* 
* @param escalonamento Listagem com todas as operações do escalonamento
* @param transacoes Vetor com a identificação das transações que serão processadas
* @return Retorna true se o escalonamento possui equivalente e false caso contrário
*/
bool verificaEquivalencia(vector<operacao> &escalonamento, vector<int>& transacoes);

#endif