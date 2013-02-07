//MÓDULO DE INTERFACE DE USUARIO
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "miu.h"
#include "..\MP\mp.h"

#define SERVIDOR_MIU

/* Classes */
using namespace std;

//Master
Login::Login (const string n, const string mat, const string s, const int nivel)
{
    if (nivel != 1)
    {
        throw LoginDataException ("Valor invalido para nivel de usuario em 'Login'");
    }

    this->nome = n;
    this->matricula = mat;
    this->senha = s;
    this->nivel = nivel;
}

//Professor
Login::Login (const string n, const string mat, const string s, const string disci, const int nivel)
{
    if (nivel != 2)
    {
        throw LoginDataException ("Valor invalido para nivel de usuario em 'Login'");
    }

    this->nome = n;
    this->matricula = mat;
    this->senha = s;
    this->disciplina = disci;
    this->nivel = nivel;
}

//Aluno
Login::Login (const string n, const string mat, const string s, const char t, const int nivel)
{
    if (nivel != 3)
    {
        throw LoginDataException ("Valor invalido para nivel de usuario em 'Login'");
    }

    this->nome = n;
    this->matricula = mat;
    this->senha = s;
    this->turma = t;
    this->nivel = nivel;
}

//Realiza o login de Master
Master *Login::logar_m ()
{
    if (this->nivel == 1)
    {
            try
            {
                bool existe;

                existe = existe_user (this->nome, this->matricula, this->senha);

                if (existe)
                {
                    //A criação do objeto significa logar o usuário
                    Master *u = new Master (nome, matricula, senha);

                    return u;
                }
                else
                {
                    cout << "Dados nao conferem!" << endl;
                    return NULL;
                }
            }
            catch (...)
            {
                cout << "Ocorreu um erro desconhecido...\n\n";
                return NULL;
            }

    }
    else
    {
        throw LoginDataException ("Nivel de usuario invalido na classe 'Login'");
    }
}

//Realiza o login de Professor
Professor *Login::logar_p ()
{
    if (this->nivel == 2)
    {
            try
            {
                bool existe;

                existe = existe_user (this->nome, this->matricula, this->senha, this->disciplina);

                if (existe)
                {
                    //A criação do objeto significa logar o usuário
                    Professor *u = new Professor (nome, matricula, senha, disciplina);

                    return u;
                }
                else
                {
                    cout << "Dados nao conferem!" << endl;
                    return NULL;
                }
            }
            catch (...)
            {
                cout << "Ocorreu um erro desconhecido...\n\n";
                return NULL;
            }

    }
    else
    {
        throw LoginDataException ("Nivel de usuario invalido na classe 'Login'");
    }
}

//Realiza o login de Aluno
Aluno *Login::logar_a ()
{
    if (this->nivel == 3)
    {
            try
            {
                bool existe;

                existe = existe_user (this->nome, this->matricula, this->senha, this->turma);

                if (existe)
                {
                    //A criação do objeto significa logar o usuário
                    Aluno *u = new Aluno (nome, matricula, senha, turma);

                    return u;
                }
                else
                {
                    cout << "Dados nao conferem!" << endl;
                    return NULL;
                }
            }
            catch (...)
            {
                cout << "Ocorreu um erro desconhecido...\n\n";
                return NULL;
            }

    }
    else
    {
        throw LoginDataException ("Nivel de usuario invalido na classe 'Login'");
    }
}

//Cria a exceção
LoginDataException::LoginDataException (const string m = "Ocorreu um erro desconhecido")
{
    this->mensagem = m;
}

//Retorna a mensagem de erro
string LoginDataException::getException ()
{
    return mensagem;
}

padronizar::padronizar (string& n, string& mat, string& s)
{
    char n_suporte[] = "                    "; //20 espaços
    char s_suporte[] = "          "; //10 espaços
    char mat_suporte[] = "         "; //9 espaços
    unsigned int i = 0;

    //Padronizando o nome
    while (i < n.size () && i < 20)
    {
        n_suporte[19 - i] = n[(n.size () - 1) - i];
        i++;
    }
    n = n_suporte;

    //Padronizando a senha
    i = 0;
    while (i < s.size () && i < 10)
    {
        s_suporte[9 - i] = s[(s.size () - 1) - i];
        i++;
    }
    s = s_suporte;

    //Padronizando a matricula
    i = 0;
    while (i < mat.size () && i < 9)
    {
        mat_suporte[8 - i] = mat[(mat.size () - 1) - i];
        i++;
    }
    mat = mat_suporte;
}

padronizar::padronizar (string& n, string& mat, string& s, string& disci)
{
    char disci_suporte[] = "          "; //10 espaços
    unsigned int i = 0;

    //Padronizando o nome
    while (i < disci.size () && i < 10)
    {
        disci_suporte[9 - i] = disci[(disci.size () - 1) - i];
        i++;
    }
    disci = disci_suporte;

    //Padronizando nome, matricula e senha
    padronizar (n, mat, s);
}

padronizar::padronizar (string& n, string& mat)
{
    char n_suporte[] = "                    "; //20 espaços
    char mat_suporte[] = "         "; //9 espaços
    unsigned int i = 0;

    //Padronizando o nome
    while (i < n.size () && i < 20)
    {
        n_suporte[19 - i] = n[(n.size () - 1) - i];
        i++;
    }
    n = n_suporte;

    //Padronizando a matricula
    i = 0;
    while (i < mat.size () && i < 9)
    {
        mat_suporte[8 - i] = mat[(mat.size () - 1) - i];
        i++;
    }
    mat = mat_suporte;
}

interface_usuario::interface_usuario ()
{
    bool tentar_de_novo;
    bool menu;

    int nivel;
    int controle;
    int opcao;

    char turma;

    string senha;
    string nome;
    string disciplina;
    string matricula;

    char n_turma;

    string n_senha;
    string n_nome;
    string n_matricula;
    string n_disciplina;

    string lixo;

    //Checa se é o primeiro acesso ao programa
    checa_estado_sistema ();

    /******** TESTES *********/
/*
    string s1 ("Ola meu amigo!");
    cout << "s1: " << s1 << endl;

    string s2 (&s1[0], &s1[5]);
    cout << "s2: " << s2 << endl;

    s1[3] = '9';

    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;





    Aluno aluno ("Mateus Silva", 1242354, "minhasenha", 'A');
    aluno.cadastrar ();

    Professor prof ("Simone Brusci", 96784, "calc", "calculo");
    prof.cadastrar ();

    Master master ("Mateus Mendelson", 12345, "12345");
    master.cadastrar ();*/

    /******** /TESTES ********/

    do
    {
        system ("cls");

        cout << "**************************************" << endl;
        cout << "BEM-VINDO AO SISTEMA DE APOIO ESCOLAR!" << endl;
        cout << "**************************************\n" << endl;

        cout << "Para comecar, voce deve fazer seu login. Escolha seu nivel de usuario: " << endl;

        controle = 1;

        cout << "1) Master\n2) Professor\n3) Aluno\n4) Sair" << endl;

        cout << "Opcao: ";

        cin >> nivel;
        getchar ();

        switch (nivel)
        {
            /* Master */
            case 1:
                //Criacao e efetivação (ou não) do login
                try
                {
                    do
                    {
                        system ("cls");

                        //Entrada dos dados de login
                        cout << "\n\nNome: ";
                        getline (cin, nome);

                        cout << "Matricula: ";
                        getline (cin, matricula);

                        cout << "Senha: ";
                        getline (cin, senha);

                        padronizar p (nome, matricula, senha);

                        Login login (nome, matricula, senha, nivel);

                        Master *user = login.logar_m ();

                        if (user == 0)
                        {
                            tentar_de_novo = true;

                            cout << "\nPressione 'enter' para tentar de novo:" << endl;

                            getline (cin, lixo);
                        }
                        else
                        {
                            tentar_de_novo = false;
                        }
                    }
                    while (tentar_de_novo);

                    system ("cls");

                    do
                    {
                        //Menu
                        cout << "\n\n\n\nMenu:" << endl;
                        cout << "1) Cadastrar Master" << endl;
                        cout << "2) Excluir Master" << endl;
                        cout << "3) Cadastrar Professor" << endl;
                        cout << "4) Excluir Professor" << endl;
                        cout << "5) Cadastrar Aluno" << endl;
                        cout << "6) Excluir Aluno" << endl;
                        cout << "7) Log out" << endl;
                        cout << "Opcao: ";

                        cin >> opcao;

                        //Menu (tive problemas ao usar switch-case... error: jump to case label[-fpermissive]) o que eh isso?????????
                        if (opcao == 1)
                        {
                            getchar ();

                            system ("cls");
                            cout << "\n\n\n\n";
                            cout << "Nome: ";
                            getline (cin, n_nome);

                            cout << "Matricula: ";
                            getline (cin, n_matricula);

                            cout << "Senha: ";
                            getline (cin, n_senha);

                            padronizar p (n_nome, n_matricula, n_senha);

                            Master novo_master (n_nome, n_matricula, n_senha);
                            novo_master.cadastrar ();

                            cout << "Usuario Master Cadastrado com Sucesso!" << endl;

                            menu = true;
                        }
                        else if (opcao == 2)
                        {
                            bool resultado;

                            do
                            {
                                getline (cin, lixo);

                                //Para excluir um usuario, serao necessario apenas nome e matricula
                                cout << "\n\n\n\n";
                                cout << "Nome: ";
                                getline (cin, n_nome);

                                cout << "Matricula: ";
                                getline (cin, n_matricula);

                                padronizar p (n_nome, n_matricula);

                                resultado = solicitar_excluir_user (n_nome, n_matricula, 1);

                                if (resultado)
                                {
                                    cout << "\nUsuario Deletado com sucesso!" << endl;
                                }
                                else
                                {
                                    cout << "\nUsuario nao encontrado! Tente novamente." << endl;
                                }
                            }
                            while ( !resultado );

                            controle = 0;
                            menu = false;
                        }
                        else if (opcao == 3)
                        {
                            getchar ();

                            cout << "\n\n\n\n";
                            cout << "Nome: ";
                            getline (cin, n_nome);

                            cout << "Matricula: ";
                            getline (cin, n_matricula);

                            cout << "Senha: ";
                            getline (cin, n_senha, '\n');

                            cout << "Disciplina: ";
                            getline (cin, n_disciplina, '\n');

                            padronizar p (n_nome, n_matricula, n_senha, n_disciplina);

                            Professor novo_professor (n_nome, n_matricula, n_senha, n_disciplina);
                            novo_professor.cadastrar ();

                            cout << "Professor Cadastrado com Sucesso!" << endl;

                            menu = true;
                        }
                        else if (opcao == 4)
                        {
                            bool resultado;

                            do
                            {
                                getline (cin, lixo);

                                //Para excluir um usuario, serao necessario apenas nome e matricula
                                cout << "\n\n\n\n";
                                cout << "Nome: ";
                                getline (cin, n_nome);

                                cout << "Matricula: ";
                                getline (cin, n_matricula);

                                padronizar p (n_nome, n_matricula);

                                resultado = solicitar_excluir_user (n_nome, n_matricula, 2);

                                if (resultado)
                                {
                                    cout << "\nProfessor Deletado com sucesso!" << endl;
                                }
                                else
                                {
                                    cout << "\nProfessor nao encontrado! Tente novamente." << endl;
                                }
                            }
                            while ( !resultado );

                            controle = 0;

                            menu = true;
                        }
                        else if (opcao == 5)
                        {
                            getchar ();

                            cout << "\n\n\n\n";
                            cout << "Nome: ";
                            getline (cin, n_nome);

                            cout << "Matricula: ";
                            getline (cin, n_matricula);

                            cout << "Senha: ";
                            getline (cin, n_senha);

                            cout << "Turma: ";
                            cin >> n_turma;
                            getline (cin, lixo);

                            padronizar p (n_nome, n_matricula, n_senha);

                            Aluno novo_aluno (n_nome, n_matricula, n_senha, n_turma);
                            novo_aluno.cadastrar ();

                            cout << "Aluno Cadastrado com Sucesso!" << endl;

                            menu = true;
                        }
                        else if (opcao == 6)
                        {
                            bool resultado;

                            do
                            {
                                getline (cin, lixo);

                                //Para excluir um usuario, serao necessario apenas nome e matricula
                                cout << "\n\n\n\n";
                                cout << "Nome: ";
                                getline (cin, n_nome);

                                cout << "Matricula: ";
                                getline (cin, n_matricula);

                                padronizar p (n_nome, n_matricula);

                                resultado = solicitar_excluir_user (n_nome, n_matricula, 3);

                                if (resultado)
                                {
                                    cout << "\nAluno Deletado com sucesso!" << endl;
                                }
                                else
                                {
                                    cout << "\nAluno nao encontrado! Tente novamente." << endl;
                                }
                            }
                            while ( !resultado );

                            controle = 0;

                            menu = true;
                        }
                        //Log out
                        else
                        {
                            controle = 0;

                            menu = false;
                        }
                }
                while (menu);

                }
                catch (LoginDataException e)
                {
                    cout << "\n" << e.getException () << endl;
                }

                break;
            /* Professor */
            case 2:
                //Criacao e efetivação (ou não) do login
                try
                {
                    do
                    {
                        system ("cls");

                        //Entrada dos dados de login
                        cout << "\n\nNome: ";
                        getline (cin, nome);

                        cout << "Matricula: ";
                        getline (cin, matricula);

                        cout << "Senha: ";
                        getline (cin, senha, '\n');

                        cout << "Disciplina: ";
                        getline (cin, disciplina, '\n');

                        padronizar p (nome, matricula, senha, disciplina);

                        Login login (nome, matricula, senha, disciplina, nivel);

                        Professor *user = login.logar_p ();

                        if (user == 0)
                        {
                            tentar_de_novo = true;

                            cout << "\nPressione 'enter' para tentar de novo:" << endl;

                            getline (cin, lixo);
                        }
                        else
                        {
                            tentar_de_novo = false;
                        }
                    }
                    while (tentar_de_novo);

                    system ("cls");

                    do
                    {
                        //Menu
                        cout << "\n\n\n\nMenu:" << endl;
                        cout << "1) Cadastrar Aluno" << endl;
                        cout << "2) Postar Nota de Aluno (em construcao)" << endl;
                        cout << "3) Excluir Aluno" << endl;
                        cout << "4) Log out" << endl;
                        cout << "Opcao: ";

                        cin >> opcao;

                        if (opcao == 1)
                        {
                            getchar ();

                            cout << "\n\n\n\n";
                            cout << "Nome: ";
                            getline (cin, n_nome);

                            cout << "Matricula: ";
                            getline (cin, n_matricula);

                            cout << "Senha: ";
                            getline (cin, n_senha);

                            cout << "Turma: ";
                            cin >> turma;
                            getline (cin, lixo);

                            padronizar p (n_nome, n_matricula, n_senha);

                            Aluno novo_aluno (n_nome, n_matricula, n_senha, n_turma);
                            novo_aluno.cadastrar ();

                            cout << "Aluno Cadastrado com Sucesso!" << endl;

                            menu = true;
                        }
                        else if (opcao == 3)
                        {
                            bool resultado;

                            do
                            {
                                getline (cin, lixo);

                                //Para excluir um usuario, serao necessario apenas nome e matricula
                                cout << "\n\n\n\n";
                                cout << "Nome: ";
                                getline (cin, n_nome);

                                cout << "Matricula: ";
                                getline (cin, n_matricula);

                                padronizar p (n_nome, n_matricula);

                                resultado = solicitar_excluir_user (n_nome, n_matricula, 3);

                                if (resultado)
                                {
                                    cout << "\nAluno Deletado com sucesso!" << endl;
                                }
                                else
                                {
                                    cout << "\nAluno nao encontrado! Tente novamente." << endl;
                                }
                            }
                            while ( !resultado );

                            controle = 0;

                            menu = true;
                        }
                        //Log out
                        else
                        {
                            controle = 0;

                            menu = false;
                        }
                    }
                    while (menu);
                }
                catch (LoginDataException e)
                {
                    cout << "\n" << e.getException () << endl;
                }

                break;
            /* Aluno */
            case 3:
                try
                {
                    do
                    {
                        system ("cls");

                        //Entrada dos dados de login
                        cout << "\n\nNome: ";
                        getline (cin, nome);

                        cout << "Matricula: ";
                        getline (cin, matricula);

                        cout << "Senha: ";
                        getline (cin, senha);

                        cout << "Turma: ";
                        cin >> turma;
                        getline (cin, lixo);

                        padronizar p (nome, matricula, senha);

                        Login login (nome, matricula, senha, turma, nivel);

                        Aluno *user = login.logar_a ();

                        if (user == 0)
                        {
                            tentar_de_novo = true;

                            cout << "\nPressione 'enter' para tentar de novo:" << endl;

                            getline (cin, lixo);
                        }
                        else
                        {
                            tentar_de_novo = false;
                        }
                    }
                    while (tentar_de_novo);

                    system ("cls");

                    do
                    {
                        //Menu
                        cout << "\n\n\n\nMenu:" << endl;
                        cout << "1) Ver Notas (em construcao)" << endl;
                        cout << "4) Log out" << endl;
                        cout << "Opcao: ";

                        cin >> opcao;

                        if (opcao == 1)
                        {
                            //////////
                            menu = true;
                        }
                        //Log out
                        else
                        {
                            controle = 0;

                            menu = false;
                        }
                    }
                    while (menu);
                }
                catch (LoginDataException e)
                {
                    cout << "\n" << e.getException () << endl;
                }

                break;
            /* Sai do sistema */
            case 4:

                break;
            default:
                controle = 0;
                cout << "Opcao invalida!" << endl;

                break;
        }
    }
    while (controle == 0);
}
