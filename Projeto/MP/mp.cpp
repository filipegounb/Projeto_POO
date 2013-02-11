//MÓDULO DE PERSISTÊNCIA
#include <iostream>
#include <fstream>
#include <string>
#include "mp.h"
#include "..\MGD\mgd.h"
#include <vector>
#include <stdlib.h>

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

//Retorna a disciplina
string Professor::getDisciplina ()
{
    return this->disciplina;
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

//Retorna o nome
string Aluno::getNome ()
{
    return this->nome;
}

//Retorna a matricula
string Aluno::getMatricula ()
{
    return this->matricula;
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
bool User::existe_user (const string nome, const string matricula, const string senha, const char turma, const char *nome_arquivo)
{
    Checar_user user;

    return user.checar_user (nome, matricula, senha, turma, nome_arquivo);
}

//Checa os dados digitados para buscar um Aluno (nao precisa da senha do aluno nem da turma)
bool User::existe_user (const string nome, const string matricula, const char *nome_arquivo)
{
    Checar_user user;

    return user.checar_user (nome, matricula, nome_arquivo);
}

//Checa se um usuario existe e o deleta
bool User::solicitar_excluir_user (const string nome, const string matricula, const int nivel)
{
    bool sucesso;
    Excluir_user user;

    return sucesso = user.excluir_user (nome, matricula, nivel);
}

//Monta os dados do aluno com as notas
Notas::Notas (const string n, const string mat)
{
    this->nome = n;
    this->matricula = mat;
    this->disciplina = " "; //Um valor qualquer para indicar que esta vazio...

    this->PreencherNotas ();
}

//Monta os dados do aluno com as notas (acessado por um professor)
Notas::Notas (const string n, const string mat, const string disci)
{
    this->nome = n;
    this->matricula = mat;
    this->disciplina = disci;

    this->PreencherNotas ();
}

//Destrutor de 'Notas'
Notas::~Notas ()
{
    int i;
    int tam = conjunto_notas->size ();

    for (i = 0; i < tam; i++)
    {
        conjunto_notas->pop_back ();
    }

    free (conjunto_notas);
}

//Carrega todas as notas de um certo aluno, buscando pela matricula
void Notas::PreencherNotas ()
{
    Recupera_Notas n;
    int qnt_notas;
    int i;

    this->conjunto_notas = new vector<Nota> ();

    qnt_notas = n.obter_conjunto_notas (this->matricula, this->disciplina);

    for (i = 0; i < qnt_notas; i++)
    {
        this->conjunto_notas->push_back (n.obter_uma_nota ());
    }
}

//Imprime na tela todas as notas de um Aluno
void Notas::imprimir_notas ()
{
    vector<Nota>::iterator i;
    char suporte;
    int n = -1;

    //Filtrando os espaços anteriores ao nome
    do
    {
        n++;
        suporte = this->nome[n];
    }
    while (suporte == ' ');
    string nome_impressao (this->nome, n, 20);

    //Filtrando os espaços anteriores à matrícula
    n = -1;
    do
    {
        n++;
        suporte = this->matricula[n];
    }
    while (suporte == ' ');
    string matricula_impressao (this->matricula, n, 20);

    //Impressão
    cout << "Nome do aluno: " << nome_impressao << endl;
    cout << "Matricula do aluno: " << matricula_impressao << endl;
    cout << "-----------------------------------" << endl;

    //Nao ha notas para o aluno
    if (this->conjunto_notas->size () == 0)
    {
        cout << "\nNao ha notas disponiveis!" << endl;
    }
    //Ha notas para o aluno
    else
    {
        for (i = this->conjunto_notas->begin (); i != this->conjunto_notas->end (); i++)
        {
            string d (i->getDisciplina ());

            //Filtrando os espaços anteriores à disciplina
            n = -1;
            do
            {
                n++;
                suporte = d[n];
            }
            while (suporte == ' ');
            string disciplina_impressao (d, n, 20);

            cout << "Disciplina: " << disciplina_impressao << endl;

            //Nota 1
            if (i->getN1 () < 0)
            {
                cout << "Nota 1: Indisponivel" << endl;
            }
            else
            {
                cout << "Nota 1: " << i->getN1 () << endl;
            }

            //Nota 2
            if (i->getN2 () < 0)
            {
                cout << "Nota 2: Indisponivel" << endl;
            }
            else
            {
                cout << "Nota 2: " << i->getN2 () << endl;
            }

            //Nota 3
            if (i->getN3 () < 0)
            {
                cout << "Nota 3: Indisponivel" << endl;
            }
            else
            {
                cout << "Nota 3: " << i->getN3 () << endl;
            }

            //Nota 4
            if (i->getN4 () < 0)
            {
                cout << "Nota 4: Indisponivel" << endl;
            }
            else
            {
                cout << "Nota 4: " << i->getN4 () << endl;
            }

            cout << "-----------------------------------" << endl;
        }
    }
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
