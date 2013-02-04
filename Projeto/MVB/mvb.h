/**
* \mainpage Módulo de Vetor de Bits
*
* \brief Este módulo é responsável pelo gerenciamento de espacos livres, possibilitando o reuso de memoria.
*
* Nao sao usados bits, sao usados inteiros nos valores '0' ou '1'.
*
*/
#ifndef MVB_H
#define	MVB_H

#ifdef SERVIDOR_MVB
#define EXTERNO
#else
#define EXTERNO extern
#endif

/**
* \brief Esta função inclui um registro no arquivo desejado de vetor de bits (a inclusão é feita no primeiro espaço livre encontrado).
*
* \param <opcao> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
*
* \retval <Valor_nao_negativo> - a posicao em que o registro foi incluido
* \retval <-1> - indica que o registro foi inserido no final do arquivo ou que o arquivo não existia e agora foi criado e preenchido com o novo dado
* \retval <-2> - indica que o valor passado como parâmetro para a função é inválido
*
*/
EXTERNO int incluir_registro (int);

/**
* \brief Esta função busca e retorna a primeira posição livre no arquivo de vetor de bits desejado.
*
* \param <opcao> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
*
* \retval <Valor_nao_negativo> - a primeira posição livre do arquivo em questão
* \retval <-1> - indica que nao ha possicoes livres, ou seja, o novo registro deve ser inserido no final do arquivo
* \retval <-2> - tem-se o indicativo de que o arquivo de vetor de bits desejado ainda não existe
* \retval <-3> -  houve erro no valor do argumento da função (o valor passado não é aceitável)
*
*/
EXTERNO int obter_posicao_livre (int);

/**
*\brief Esta função altera o status (livre ou ocupado) de um registro no arquivo desejado.
*
* \param <opcao> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
* \param <posicao> - Recebe o valor que indica a posição relativa do registro à ser alterado
* \param <novo_status> - Recebe o valor do novo status do registro ('0', para livre; '1', para ocupado)
*
* \retval <0> - alteracao feita com sucesso
* \retval <-1> - indica que o novo valor que se quer atribuir ao registro é inválido (diferente de '0' e de '1')
* \retval <-2> - indica que o arquivo que se deseja alterar não existe
* \retval <-3> - indica que o registro que deve ser alterado não existe, ou seja, o tamanho do arquivo é menor do que a posição do registro que se quer alterar
* \retval <-4> - indica que o valor passado para o primeiro argumento é inválido
*
*/
EXTERNO int alterar_status_registro (int, long int, int );

/**
* \brief Esta função checa o status (livre ou ocupado) de um registro no arquivo desejado.
*
* \param <opcao> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
* \param <posicao> - Recebe a posição relativa do registro desejado (para ler o primeiro registro, use o indice 0)
*
* \retval <1> - registro ocupado
* \retval <0> - registro livre
* \retval <-1> - indica que o arquivo desejado ainda é inexistente
* \retval <-2> - indica que o registro que deve ser alterado nao existe, ou seja, o tamanho do arquivo eh menor do que a posicao do registro que se quer alterar
* \retval <-3> - indica que o valor passado para o primeiro argumento eh invalido
*
*/
EXTERNO int obter_status (int, long int);

#endif	/* MVB_H */
