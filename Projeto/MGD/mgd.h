//MÓDULO DE GERENCIAMENTO DE DADOS
#ifndef MGD_H
#define MGD_H

#include <fstream>
#include <string>

/* Classes */
using namespace std;

class TestaSistema
{
    public:
        /**
        * \brief Este construtor checa a existencia do arquivo "dados/Master.txt", requisito minimo para o sistema.
        *
        * Se o arquivo "dados/Master.txt" nao existir, chama-se a criacao deste arquivo.
        *
        * \param - Nao possui parametros de entrada
        *
        */
        TestaSistema ();
};

class InicializarSistema
{
    public:
        /**
        * \brief Este construtor cria o arquivo "dados/Master.txt", com os dados de um usuario master padrao (eh chamado pelo construtor da classe TestaSistema).
        *
        * \param - Nao possui parametros de entrada
        *
        */
        InicializarSistema ();
};

class ArquivoExiste
{
    bool existe;
    const char *nome_arquivo;
    public:
        /**
        * \brief Este construtor checa a existencia de um arquivo.
        *
        * \param <*n_arquivo> - Nome do arquivo a ser checado
        *
        */
        ArquivoExiste (const char *);

        /**
        * \brief Este metodo retorna o resultado obtido na verificacao de existencia de um arquivo pelo construtor da classe ArquivoExiste.
        *
        * \param - Nao possui parametros de entrada
        *
        * \return - Retorna 'true' se o arquivo existia; 'false', caso contrario
        *
        */
        bool getExistencia ();
};

//Efetiva um cadastro
class Cadastrar
{
    public:
        //Cada construtor efetiva o cadastro de um tipo de usuário
        /**
        * \brief Este construtor chama a acao de cadastrar um usuário Master.
        *
        * \param <nome> - Nome do usuário
        * \param <matricula> - Matricula do usuário
        * \param <senha> - Senha do usuário
        *
        */
        Cadastrar (const string, const int, const string);

        /**
        * \brief Este construtor chama a acao de cadastrar um Professor.
        *
        * \param <nome> - Nome do usuário
        * \param <matricula> - Matricula do usuário
        * \param <senha> - Senha do usuário
        * \param <disciplina> - Disciplina ministrada pelo usuario
        *
        */
        Cadastrar (const string, const int, const string, const string);

        /**
        * \brief Este construtor chama a acao de cadastrar um Aluno.
        *
        * \param <nome> - Nome do usuário
        * \param <matricula> - Matricula do usuário
        * \param <senha> - Senha do usuário
        * \param <turma> - Disciplina ministrada pelo usuario
        *
        */
        Cadastrar (const string, const int, const string, const char);
};



/* Funções */
#ifdef SERVIDOR_MP
#define EXTERNO
#else
#define EXTERNO extern
#endif

/**
* \brief Esta função checa os dados de um usuario Master.
*
* \param <nome> - Nome do usuário
* \param <matricula> - Matricula do usuário
* \param <senha> - Senha do usuário
* \param <*nome_arquivo> - Nome do arquivo que possui os dados (por padrao, tem o valor "dados/Master.txt")
*
* \return - Retorna 'true' se o conjunto de dados confere; 'false', caso contrario
*
*/
EXTERNO bool checar_user (const string, const int, const string, const char *nome_arquivo = "dados/Master.txt"); //Checa os dados de um Master

/**
* \brief Esta função checa os dados de um Professor.
*
* \param <nome> - Nome do usuário
* \param <matricula> - Matricula do usuário
* \param <senha> - Senha do usuário
* \param <disciplina> - Disciplina ministrada pelo usuario
* \param <*nome_arquivo> - Nome do arquivo que possui os dados (por padrao, tem o valor "dados/Professor.txt")
*
* \return - Retorna 'true' se o conjunto de dados confere; 'false', caso contrario
*
*/
EXTERNO bool checar_user (const string, const int, const string, const string, const char *nome_arquivo = "dados/Professor.txt");

/**
* \brief Esta função checa os dados de um Aluno.
*
* \param <nome> - Nome do usuário
* \param <matricula> - Matricula do usuário
* \param <senha> - Senha do usuário
* \param <turma> - Turma do usuário
* \param <*nome_arquivo> - Nome do arquivo que possui os dados (por padrao, tem o valor "dados/Aluno.txt")
*
* \return - Retorna 'true' se o conjunto de dados confere; 'false', caso contrario
*
*/
EXTERNO bool checar_user (const string, const int, const string, const char, const char *nome_arquivo = "dados/Aluno.txt");

/**
* \brief Esta função checa a existencia de um usuario, com o objetivo de exclui-lo.
*
* \param <nome> - Nome do usuário
* \param <matricula> - Matricula do usuário
* \param <nivel> - Nivel do usuario que se deseja checar
*
* \retval <Valor_nao_nulo> - A posicao do registro do usuario no arquivo
* \retval <-1> - O usuario solicitado nao foi encontrado
*
*/
EXTERNO long int checar_user (const string, const int, const int);

/**
* \brief Esta funcao solicita a checagem da existencia de um usuario e, se ele existir, o deleta.
*
* \param <nome> - Nome do usuario
* \param <matricula> - Matricula do usuario
* \param <nivel> - Nivel do usuario que se deseja checar
*
* \return - Retorna 'true' se o usuario foi deletado; 'false', caso contrario
*
*/
EXTERNO bool excluir_user (const string, const int, const int);

#endif	/* MGD_H */
