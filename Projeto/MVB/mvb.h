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
* \brief Esta classe eh responsavel pelo gerenciamento dos espacos livres.
*
*/
class Registro
{
    long int posicao; //Para indicar o primeiro registro, usa-se o indice 0
    int nivel;
    int status;

    /**
    * \brief Este método checa o status (livre ou ocupado) de um registro no arquivo desejado.
    *
    * \param - Nao possui parametros de entrada
    *
    * \retval <1> - registro ocupado
    * \retval <0> - registro livre
    * \retval <-1> - indica que o arquivo desejado ainda é inexistente
    * \retval <-2> - indica que o registro que deve ser alterado nao existe, ou seja, o tamanho do arquivo eh menor do que a posicao do registro que se quer alterar
    * \retval <-3> - indica que o valor que indica o nivel do usuario eh invalido
    *
    */
    int obter_status ();
public:
    /**
    * \brief Este construtor seta o nivel do usuario.
    *
    * \param <n> - Recebe o nivel do usuario ('1' para adicionar Master; '2', para Professor; '3', para Aluno)
    *
    */
    Registro (int);

    /**
    * \brief Este método seta a posicao do registro e, automaticamente, verifica o status do registro.
    *
    * \param <p> - Recebe a posicao do registro
    *
    * \retval - Nao possui valor de retorno
    *
    */
    void setPos (long int);

    /**
    * \brief Este método retorna a posicao do registro.
    *
    * \param - Nao possui parametros de entrada
    *
    * \retval - Retorna a posicao do registro
    *
    */
    long int getPos ();

    /**
    * \brief Este método retorna o status do registro.
    *
    * \param - Nao possui parametros de entrada
    *
    * \retval - Retorna o status do registro
    *
    */
    int getStatus ();

    /**
    * \brief Este método inclui um registro no arquivo desejado de vetor de bits (a inclusão é feita no primeiro espaço livre encontrado).
    *
    * \param - Nao possui parametros de entrada
    *
    * \retval <0> - inclusao feita com sucesso
    * \retval <-1> - indica que o registro foi inserido no final do arquivo ou que o arquivo não existia e agora foi criado e preenchido com o novo dado
    * \retval <-2> - indica que o valor passado como parâmetro para a função é inválido
    *
    */
    int incluir_registro ();

    /**
    * \brief Este método busca e retorna a primeira posição livre no arquivo de vetor de bits desejado.
    *
    * \param - Nao possui parametros de entrada
    *
    * \retval <Valor_nao_negativo> - a primeira posição livre do arquivo em questão
    * \retval <-1> - indica que nao ha possicoes livres, ou seja, o novo registro deve ser inserido no final do arquivo
    * \retval <-2> - tem-se o indicativo de que o arquivo de vetor de bits desejado ainda não existe
    * \retval <-3> -  houve erro no valor do argumento da função (o valor passado não é aceitável)
    *
    */
    int obter_posicao_livre ();

    /**
    *\brief Este método altera o status (livre ou ocupado) de um registro no arquivo desejado.
    *
    * \param <novo_status> - Recebe o valor do novo status do registro ('0', para livre; '1', para ocupado)
    *
    * \retval <0> - alteracao feita com sucesso
    * \retval <-1> - indica que o novo valor que se quer atribuir ao registro é inválido (diferente de '0' e de '1')
    * \retval <-2> - indica que o arquivo que se deseja alterar não existe
    * \retval <-3> - indica que o registro que deve ser alterado não existe, ou seja, o tamanho do arquivo é menor do que a posição do registro que se quer alterar
    * \retval <-4> - indica que o valor passado para o primeiro argumento é inválido
    *
    */
    int alterar_status_registro (int);
};

#endif	/* MVB_H */
