/**
* \mainpage Módulo de Persistência
*
* \brief Este módulo é responsável por garantir a integridade dos dados e do sistema.
*/
#ifndef MP_H
#define	MP_H

#include<string>

/* Classes */
using namespace std;

/**
* \brief Esta classe eh a classe base para as classes que representam usuários. É uma classe abstrata que exige a criação do método "cadastrar".
*
*/
class Usuario
{
protected:
    string nome;
    int matricula;
    string senha;
public:
    virtual void cadastrar ()=0;
};

/**
* \brief Esta classe representa um usuario Master.
*
*/
class Master : public Usuario
{
public:
    /**
    * \brief Este construtor cria um objeto do tipo Master com os dados ja padronizados.
    *
    * \param <n> - Nome do usuario
    * \param <mat> - Matricula do usuario
    * \param <s> - Senha do usuario
    *
    */
    Master (const string, const int, const string);
    //~Master ();

    /**
    * \brief Este metodo chama o cadastro de usuario Master.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    *
    */
    void cadastrar ();
    //Me apague:
    void esc ();
};

/**
* \brief Esta classe representa um Professor.
*
*/
class Professor : public Usuario
{
public:
    /**
    * \brief Este construtor cria um objeto do tipo Professor com os dados ja padronizados.
    *
    * \param <n> - Nome do usuario
    * \param <mat> - Matricula do usuario
    * \param <s> - Senha do usuario
    * \param <disci> - Disciplina ministrada pelo usuario
    *
    */
    Professor (const string, const int, const string, const string);
    //~Professor ();

    /**
    * \brief Este metodo chama o cadastro de Professor.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    *
    */
    void cadastrar ();
    //Me apague:
    void esc ();
protected:
    string disciplina;
};

/**
* \brief Esta classe representa um Aluno.
*
*/
class Aluno : public Usuario
{
public:
    /**
    * \brief Este construtor cria um objeto do tipo Aluno com os dados ja padronizados.
    *
    * \param <n> - Nome do usuario
    * \param <mat> - Matricula do usuario
    * \param <s> - Senha do usuario
    * \param <t> - Turma do usuario
    *
    */
    Aluno (const string, const int, const string, const char);
    //~Aluno();

    /**
    * \brief Este metodo chama o cadastro de Aluno.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    *
    */
    void cadastrar ();
    //Me apague:
    void esc ();
protected:
    char turma; //O sistema é implementado para apenas uma série, ou seja, especificaremos apenas a letra da turma
};

/* Funções */
#ifdef SERVIDOR_MP
#define EXTERNO
#else
#define EXTERNO extern
#endif

/**
* \brief Esta funcao checa se já existe algum usuário Master cadastrado (estado minimo para o sistema)
*
* \param - Nao possui parametros de entrada
*
* \return - Nao possui valor de retorno
*
*/
EXTERNO void checa_estado_sistema ();

/**
* \brief Esta funcao solicita a checagem da existencia de um usuário Master com os dados recebidos.
*
* \param <*nome_arquivo> - Arquivo que armazena os dados dos usuarios Master cadastrados (por padrao, tem o valor "dados/Master.txt")
* \param <nome> - Nome do usuario
* \param <matricula> - Matricula do usuario
* \param <senha> - Senha do usuario
*
* \return - Retorna 'true' se o usuario existe; 'false', caso contrario
*
*/
EXTERNO bool existe_user (const string, const int, const string, const char *nome_arquivo = "dados/Master.txt");

/**
* \brief Esta funcao solicita a checagem da existencia de um Professor com os dados recebidos.
*
* \param <*nome_arquivo> - Arquivo que armazena os dados dos professores cadastrados (por padrao, tem o valor "dados/Professor.txt")
* \param <nome> - Nome do usuario
* \param <matricula> - Matricula do usuario
* \param <senha> - Senha do usuario
* \param <disci> - Disciplina ministrada pelo usuario
*
* \return - Retorna 'true' se o usuario existe; 'false', caso contrario
*
*/
EXTERNO bool existe_user (const string, const int, const string, const string, const char *nome_arquivo = "dados/Professor.txt");

/**
* \brief Esta funcao solicita a checagem da existencia de um Aluno com os dados recebidos.
*
* \param <*nome_arquivo> - Arquivo que armazena os dados dos alunos cadastrados (por padrao, tem o valor "dados/Aluno.txt")
* \param <nome> - Nome do usuario
* \param <matricula> - Matricula do usuario
* \param <senha> - Senha do usuario
* \param <t> - Turma do usuario
*
* \return - Retorna 'true' se o usuario existe; 'false', caso contrario
*
*/
EXTERNO bool existe_user (const string, const int, const string, const char, const char *nome_arquivo = "dados/Aluno.txt");

/**
* \brief Esta funcao solicita a exclusao de um usuario.
*
* \param <nome> - Nome do usuario
* \param <matricula> - Matricula do usuario
* \param <nivel> - Nivel de acesso do usuario
*
* \retval <true> - Usuario excluido com sucesso
* \retval <false> - O usuario solicitado nao foi encontrado
*
*/
EXTERNO bool solicitar_excluir_user (const string, const int, const int);

#endif	/* MP_H */
