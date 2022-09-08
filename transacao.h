/**
 * @author Gustavo Henrique da Silva Barbosa / GRR20190485
 */

#ifndef __TRANSACAO__
#define __TRANSACAO__
/**
 * @brief Objeto para representar uma operação, ou seja,
 * uma linha do agendamento.
 * 
 */
class operacao {
    public:
        int timestamp;
        int transacao;
        char op;
        char atributo;

        /**
         * @brief Controi uma nova operação
         * 
         * @param ts Timestamp
         * @param tr Transação
         * @param op_tr Operação
         * @param atr Atributo
         */
        operacao(int ts, int tr, char op_tr, char atr);

        /**
         * @brief Método para verificar se a operação é de leitura
         * 
         * @return true 
         * @return false 
         */
        bool isLeitura();

        /**
         * @brief Método para verificar se a operação é de escrita
         * 
         * @return true 
         * @return false 
         */
        bool isEscrita();

        /**
         * @brief Método para verificar se a operação é um commit
         * 
         * @return true 
         * @return false 
         */
        bool isCommit();
};

#endif