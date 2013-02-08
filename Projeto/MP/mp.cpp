//MÓDULO DE PERSISTÊNCIA
#include <iostream>
#include <fstream>
#include <string>
#include "mp.h"
#include "..\MGD\mgd.h"

using namespace std;
//Métodos para Master
//Construtor
Master::Master (const string n, const string mat, const string s)
{
    nome = n;
    matricula = mat;
    senha = s;
}

//Chama a execução do cadastro
void Master::cadastrar ()
{
    Cadastrar usuario (nome, matricula, senha);
}

//Métodos para Professor
//Construtor
Professor::Professor (const string n, const string mat, const string s, const string disci)
{
    nome = n;
    matricula = mat;
    senha = s;
    disciplina = disci;
}

//Chama a execução do cadastro
void Professor::cadastrar ()
{
    Cadastrar usuario (nome, matricula, senha, disciplina);
}

//Métodos para Aluno
//Construtor
Aluno::Aluno (const string n, const string mat, const string s, const char t)
{
    nome = n;
    matricula = mat;
    senha = s;
    turma = t;
}

//Chama a execução do cadastro
void Aluno::cadastrar ()
{
    Cadastrar usuario (nome, matricula, senha, turma);
}

//Checa o estado do sistema (inicializado ou não inicializado)
Checa_estado_sistema::Checa_estado_sistema ()
{
    ArquivoExiste arquivo ( (char *) &"dados/Master.txt");

    //Ainda não há nenhum usuário Master cadastrado
    if ( !arquivo.getExistencia () )
    {
        InicializarSistema ini;
    }
    //Há algum usuário Master cadastrado
    else
    {
        //Do nothing
    }
}

//Checa os dados de um usuario Master
bool User::existe_user (const string nome, const string matricula, const string senha, const char *nome_arquivo)
{
    Checar_user user;

    return user.checar_user (nome, matricula, senha, nome_arquivo);
}

//Checa os dados digitados por um Professor
bool User::existe_user (const string nome, const string matricula, const string senha, const string disci, const char *nome_arquivo)
{
    Checar_user user;

    return user.checar_user (nome, matricula, senha, disci, nome_arquivo);
}

//Checa os dados digitados por um Aluno
bool User::existe_user (const string nome, const string matricula, const string senha, const char t, const char *nome_arquivo)
{
    Checar_user user;

    return user.checar_user (nome, matricula, senha, t, nome_arquivo);
}

//Checa se um usuario existe e o deleta
bool User::solicitar_excluir_user (const string nome, const string matricula, const int nivel)
{
    bool sucesso;
    Excluir_user user;

    return sucesso = user.excluir_user (nome, matricula, nivel);
}

//Imprimem os valores no objeto, somente para testes.
void Master::esc ()
{
    cout << "Nome: " << nome << endl;
    cout << "Matricula: " << matricula << endl;
    cout << "Senha: " << senha << endl;
}

void Professor::esc ()
{
    cout << "Nome: " << nome << endl;
    cout << "Matricula: " << matricula << endl;
    cout << "Senha: " << senha << endl;
    cout << "Disciplina: " << disciplina << endl;
}

void Aluno::esc ()
{
    cout << "Nome: " << nome << endl;
    cout << "Matricula: " << matricula << endl;
    cout << "Senha: " << senha << endl;
    cout << "Turma: " << turma << endl;

}
