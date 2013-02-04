/**
* \mainpage M�dulo de Vetor de Bits
*
* \brief Este m�dulo � respons�vel pelo gerenciamento de espacos livres, possibilitando o reuso de memoria.
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
* \brief Esta fun��o inclui um registro no arquivo desejado de vetor de bits (a inclus�o � feita no primeiro espa�o livre encontrado).
*
* \param <opcao> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
*
* \retval <Valor_nao_negativo> - a posicao em que o registro foi incluido
* \retval <-1> - indica que o registro foi inserido no final do arquivo ou que o arquivo n�o existia e agora foi criado e preenchido com o novo dado
* \retval <-2> - indica que o valor passado como par�metro para a fun��o � inv�lido
*
*/
EXTERNO int incluir_registro (int);

/**
* \brief Esta fun��o busca e retorna a primeira posi��o livre no arquivo de vetor de bits desejado.
*
* \param <opcao> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
*
* \retval <Valor_nao_negativo> - a primeira posi��o livre do arquivo em quest�o
* \retval <-1> - indica que nao ha possicoes livres, ou seja, o novo registro deve ser inserido no final do arquivo
* \retval <-2> - tem-se o indicativo de que o arquivo de vetor de bits desejado ainda n�o existe
* \retval <-3> -  houve erro no valor do argumento da fun��o (o valor passado n�o � aceit�vel)
*
*/
EXTERNO int obter_posicao_livre (int);

/**
*\brief Esta fun��o altera o status (livre ou ocupado) de um registro no arquivo desejado.
*
* \param <opcao> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
* \param <posicao> - Recebe o valor que indica a posi��o relativa do registro � ser alterado
* \param <novo_status> - Recebe o valor do novo status do registro ('0', para livre; '1', para ocupado)
*
* \retval <0> - alteracao feita com sucesso
* \retval <-1> - indica que o novo valor que se quer atribuir ao registro � inv�lido (diferente de '0' e de '1')
* \retval <-2> - indica que o arquivo que se deseja alterar n�o existe
* \retval <-3> - indica que o registro que deve ser alterado n�o existe, ou seja, o tamanho do arquivo � menor do que a posi��o do registro que se quer alterar
* \retval <-4> - indica que o valor passado para o primeiro argumento � inv�lido
*
*/
EXTERNO int alterar_status_registro (int, long int, int );

/**
* \brief Esta fun��o checa o status (livre ou ocupado) de um registro no arquivo desejado.
*
* \param <opcao> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
* \param <posicao> - Recebe a posi��o relativa do registro desejado (para ler o primeiro registro, use o indice 0)
*
* \retval <1> - registro ocupado
* \retval <0> - registro livre
* \retval <-1> - indica que o arquivo desejado ainda � inexistente
* \retval <-2> - indica que o registro que deve ser alterado nao existe, ou seja, o tamanho do arquivo eh menor do que a posicao do registro que se quer alterar
* \retval <-3> - indica que o valor passado para o primeiro argumento eh invalido
*
*/
EXTERNO int obter_status (int, long int);

#endif	/* MVB_H */
