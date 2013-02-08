/**
* \mainpage Módulo de Interface de Usuário
*
* \brief Este módulo é responsável por interagir com o usuário (receber e mostrar dados).
*/
#ifndef MIU_H
#define	MIU_H

#include <string>
#include "..\MP\mp.h"

using namespace std;

/**
* \brief Esta classe eh responsavel por obter e exibir a data e a hora no instante em que cada menu eh acessado.
*
*/
class Data_Hora
{
    int hrs;
    int minutos;
    int dia;
    int mes;
    int ano;
    string data;
    string hora;

    /**
    * \brief Este metodo converte um numero de 1 a 12 para o mes correspondente, textualmente.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Retorna o mes desejado, em texto
    */
    string ConverteMes ();

    /**
    * \brief Este metodo constroi os textos da data e da hora.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    */
    void ConstroiDataHora ();
public:
    /**
    * \brief Este metodo imprime a data e a hora no momento do acesso ao menu, na tela.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    */
    void ImprimeDataHora ();
};

/**
* \brief Esta classe eh responsavel por lidar com os processos necessarios para fazer o login de um usuario.
*
*/
class Login
{
    string nome;
    string matricula;
    string senha;
    string disciplina;
    char turma;
    int nivel;
    char *nome_arquivo;


    public:
        /**
        * \brief Este construtor cria um objeto do tipo Login com os dados que o usuario digitou, ja padronizados, para Master.
        *
        * \param <n> - Nome do usuario
        * \param <mat> - Matricula do usuario
        * \param <s> - Senha do usuario
        * \param <nivel> - Nivel do usuario
        *
        */
        Login (const string, const string, const string, const int);

        /**
        * \brief Este construtor cria um objeto do tipo Login com os dados que o usuario digitou, ja padronizados, para Professor.
        *
        * \param <n> - Nome do usuario
        * \param <mat> - Matricula do usuario
        * \param <s> - Senha do usuario
        * \param <disci> - Disciplina ministrada pelo usuario
        * \param <nivel> - Nivel do usuario
        *
        */
        Login (const string, const string, const string, const string, const int);

        /**
        * \brief Este construtor cria um objeto do tipo Login com os dados que o usuario digitou, ja padronizados, para Aluno.
        *
        * \param <n> - Nome do usuario
        * \param <mat> - Matricula do usuario
        * \param <s> - Senha do usuario
        * \param <t> - Turma do usuario
        * \param <nivel> - Nivel do usuario
        *
        */
        Login (const string, const string, const string, const char, const int);

        /**
        * \brief Este metodo checa a existencia de um usuario e, se existir, executa a acao de logar, para Master.
        *
        * \param - Nao possui parametros de entrada
        *
        * \return - Se os dados conferem, retorna um objeto do tipo Master; se nao, retorna NULL
        */
        Master *logar_m ();

        /**
        * \brief Este metodo checa a existencia de um usuario e, se existir, executa a acao de logar, para Professor.
        *
        * \param - Nao possui parametros de entrada
        *
        * \return - Se os dados conferem, retorna um objeto do tipo Professor; se nao, retorna NULL
        */
        Professor *logar_p ();

        /**
        * \brief Este metodo checa a existencia de um usuario e, se existir, executa a acao de logar, para Aluno.
        *
        * \param - Nao possui parametros de entrada
        *
        * \return - Se os dados conferem, retorna um objetivo do tipo Aluno; se nao, retorna NULL
        */
        Aluno *logar_a ();
};

/**
* \brief Esta classe eh responsavel por receber as mensagens de excecao e armazena-las
*
*/
class LoginDataException
{
    string mensagem;

    public:
        /**
        * \brief Este construtor recebe a mensagem de erro e a armazena
        *
        * \param <m> - Mensagem de erro (por padrao, a mensagem de erro eh "Ocorreu um erro desconhecido")
        *
        */
        LoginDataException (const string);

        /**
        * \brief Este metodo retorna a mensagem de erro
        *
        * \param - Nao possui parametros de entrada
        *
        * \return - Retorna a mensagem de erro
        *
        */
        string getException ();
};

/**
* \brief Esta classe padroniza as entradas digitadas por um usuário.
*
*/
class padronizar
{
public:
    /**
    * \brief Este construtor padroniza o comprimento das entradas nome, senha e matricula.
    *
    * Para o caso do nome, adiciona-se espacos a esquerda do que foi digitado;
    *
    * Para o caso da matricula, adiciona-se "noves" (9's) a esquerda do que foi digitado (um numero nao-nulo);
    *
    * Para o caso da senha, adiciona-se espacos a esquerda do que foi digitado.
    *
    * \param <n> - Nome do usuario
    * \param <mat> - Matricula do usuario
    * \param <s> - Senha do usuario
    *
    */
    padronizar (string&, string&, string&);

    /**
    * \brief Este construtor padroniza o comprimento das entradas nome, senha, matricula e disciplina.
    *
    * Para o caso do nome, adiciona-se espacos a esquerda do que foi digitado;
    *
    * Para o caso da matricula, adiciona-se "noves" (9's) a esquerda do que foi digitado (um numero nao-nulo);
    *
    * Para o caso da senha, adiciona-se espacos à esquerda do que foi digitado;
    *
    * Para o caso da disciplina, adiciona-se espaços a direita do que foi digitado.
    *
    * \param <n> - Nome do usuario
    * \param <mat> - Matricula do usuario
    * \param <s> - Senha do usuario
    * \param <disci> - Disciplina ministrada pelo usuario
    *
    */
    padronizar (string&, string&, string&, string&);

    /**
    * \brief Este construtor padroniza o comprimento das entradas nome e matricula.
    *
    * Para o caso do nome, adiciona-se espacos a esquerda do que foi digitado;
    *
    * Para o caso da matricula, adiciona-se "noves" (9's) a esquerda do que foi digitado (um numero nao-nulo).
    *
    * \param <n> - Nome do usuario
    * \param <mat> - Matricula do usuario
    *
    */
    padronizar (string&, string&);
};

/**
* \brief Esta classe eh responsavel por apresentar os menus ao usuario.
*
**/
class Menu
{
    Data_Hora dh;
public:
    /**
    * \brief Este metodo imprime o menu inicial.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    */
    void menu_inicial ();

    /**
    * \brief Este metodo imprime o menu para usuarios Master.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    */
    void menu_master ();

    /**
    * \brief Este metodo imprime o menu para Professor.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    */
    void menu_professor ();

    /**
    * \brief Este metodo imprime o menu para Aluno.
    *
    * \param - Nao possui parametros de entrada
    *
    * \return - Nao possui valor de retorno
    */
    void menu_aluno ();
};

/**
* \brief Esta classe eh responsavel por se comunicar pela tela do computador com o usuario.
*
**/
class interface_usuario
{
    Menu m; //Representa os menus
public:
    /**
    * \brief Este construtor eh responsavel por se comunicar pela tela do computador com o usuario.
    *
    * Eh importante notar o contrato que deve ser estabelecido com o usuario para a entrada dos dados:
    *
    * Nome: tem tamanho maximo de 20 caracteres;
    *
    * Matricula: tem tamanho maximo de 9 caracteres;
    *
    * Senha: tem tamanho maximo de 10 caracteres;
    *
    * Disciplina: tem tamanho maximo de 10 caracteres;
    *
    * Turma: deve ter o tamanho exato de 1 caracter.
    *
    * \param - Nao possui parametros de entrada
    *
    */
    interface_usuario ();
};

#endif	/* MIU_H */
