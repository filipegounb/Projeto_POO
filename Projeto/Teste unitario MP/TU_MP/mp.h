/**
* \mainpage Módulo de Persistência
*
* \brief Este módulo é responsável por garantir a integridade dos dados e do sistema.
*/
#ifndef MP_H
#define	MP_H

#include <string>
#include <vector>
#include "mgd.h"

using namespace std;

/**
* \brief Esta classe eh a classe base para as classes que representam usuários. É uma classe abstrata que exige a criação do método "cadastrar".
*
*/
class Usuario
{
protected:
    string nome;
    string matricula;
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
    Master (const string, const string, const string);

    /**
    * \brief Este metodo chama o cadastro de usuario Master.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    *
    */
    void cadastrar ();
};

/**
* \brief Esta classe representa um Professor.
*
*/
class Professor : public Usuario
{
    string disciplina;
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
    Professor (const string, const string, const string, const string);

    /**
    * \brief Este metodo chama o cadastro de Professor.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    *
    */
    void cadastrar ();

    /**
    * \brief Este metodo retorna a disciplina do Professor.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Retorna a disciplina do Professor
    *
    */
    string getDisciplina ();
};

/**
* \brief Esta classe representa um Aluno.
*
*/
class Aluno : public Usuario
{
    char turma; //O sistema é implementado para apenas uma série, ou seja, especificaremos apenas a letra da turma
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
    Aluno (const string, const string, const string, const char);

    /**
    * \brief Este metodo chama o cadastro de Aluno.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    *
    */
    void cadastrar ();

    /**
    * \brief Este metodo retorna o nome do Aluno.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Retorna o nome do Aluno
    *
    */
    string getNome ();

    /**
    * \brief Este metodo retorna a matricula do Aluno.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Retorna a matricula do Aluno
    *
    */
    string getMatricula ();
};

/**
* \brief Esta classe checa o estado do sistema (inicializado ou não inicializado).
*
*/
class Checa_estado_sistema
{
public:
    /**
    * \brief Este construtor checa se já existe algum usuário Master cadastrado (estado minimo para o sistema)
    *
    * \param - Nao possui parametros de entrada
    *
    */
    Checa_estado_sistema ();
};

/**
* \brief Esta classe checa a existencia de usuarios e solicita a exlusao de usuarios.
*
*/
class User
{
public:
    /**
    * \brief Este metodo solicita a checagem da existencia de um usuário Master com os dados recebidos.
    *
    * \param <nome> - Nome do usuario
    * \param <matricula> - Matricula do usuario
    * \param <senha> - Senha do usuario
    * \param <*nome_arquivo> - Arquivo que armazena os dados dos usuarios Master cadastrados (por padrao, tem o valor "dados/Master.txt")
    *
    * \return - Retorna 'true' se o usuario existe; 'false', caso contrario
    *
    */
    bool existe_user (const string, const string, const string, const char *nome_arquivo = "dados/Master.txt");

    /**
    * \brief Este metodo solicita a checagem da existencia de um Professor com os dados recebidos.
    *
    * \param <nome> - Nome do usuario
    * \param <matricula> - Matricula do usuario
    * \param <senha> - Senha do usuario
    * \param <disci> - Disciplina ministrada pelo usuario
    * \param <*nome_arquivo> - Arquivo que armazena os dados dos professores cadastrados (por padrao, tem o valor "dados/Professor.txt")
    *
    * \return - Retorna 'true' se o usuario existe; 'false', caso contrario
    *
    */
    bool existe_user (const string, const string, const string, const string, const char *nome_arquivo = "dados/Professor.txt");

    /**
    * \brief Este metodo solicita a checagem da existencia de um Aluno com os dados recebidos.
    *
    * \param <nome> - Nome do usuario
    * \param <matricula> - Matricula do usuario
    * \param <senha> - Senha do usuario
    * \param <turma> - Turma do usuario
    * \param <*nome_arquivo> - Arquivo que armazena os dados dos alunos cadastrados (por padrao, tem o valor "dados/Aluno.txt")
    *
    * \return - Retorna 'true' se o usuario existe; 'false', caso contrario
    *
    */
    bool existe_user (const string, const string, const string, const char, const char *nome_arquivo = "dados/Aluno.txt");

    /**
    * \brief Este metodo solicita a checagem da existencia de um Aluno com os dados recebidos.
    *
    * \param <nome> - Nome do usuario
    * \param <matricula> - Matricula do usuario
    * \param <*nome_arquivo> - Arquivo que armazena os dados dos alunos cadastrados (por padrao, tem o valor "dados/Aluno.txt")
    *
    * \return - Retorna 'true' se o usuario existe; 'false', caso contrario
    *
    */
    bool existe_user (const string, const string,const char *nome_arquivo = "dados/Aluno.txt");

    /**
    * \brief Este metodo solicita a exclusao de um usuario.
    *
    * \param <nome> - Nome do usuario
    * \param <matricula> - Matricula do usuario
    * \param <nivel> - Nivel de acesso do usuario
    *
    * \retval <true> - Usuario excluido com sucesso
    * \retval <false> - O usuario solicitado nao foi encontrado
    *
    */
    bool solicitar_excluir_user (const string, const string, const int);
};

/**
* \brief Esta classe armazena o conjunto de notas de um aluno.
*
*/
class Notas
{
    string nome;
    string matricula;
    string disciplina;
    vector<Nota> *conjunto_notas;

    /**
    * \brief Este metodo recupera todas as notas de um aluno.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    *
    */
    void PreencherNotas ();

public:
    /**
    * \brief Este construtor cria um objeto que armazena o Nome, a Matricula e todas as notas de um certo aluno.
    *
    * \param <n> - Nome do usuario
    * \param <mat> - Matricula do usuario
    *
    */
    Notas (const string, const string);

    /**
    * \brief Este construtor cria um objeto que armazena o Nome, a Matricula, a Disciplina e todas as notas de um certo aluno (eh acessado por Professor).
    *
    * \param <n> - Nome do usuario
    * \param <mat> - Matricula do usuario
    * \param <disci> - Disciplina do usuario
    *
    */
    Notas (const string, const string, const string);

    /**
    * \brief Este destrutor libera o ponteiro de vetor de notas.
    *
    * \param - Nao possui parametros de entrada
    *
    */
    ~Notas ();

    /**
    * \brief Este metodo imprime na tela as notas do aluno.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    *
    */
    void imprimir_notas ();
};

#endif	/* MP_H */
