//MÓDULO DE PERSISTÊNCIA
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
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
    this->conjunto_notas = NULL;

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

//Retorna o Boletim do Aluno
string Notas::getBoletim ()
{
    vector<Nota>::iterator i;
    char suporte;
    int n = -1;
    stringstream boletim (stringstream::in|stringstream::out);

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
    boletim << "Nome do aluno: " << nome_impressao << endl;
    boletim << "Matricula do aluno: " << matricula_impressao << endl;
    boletim << "-----------------------------------" << endl;

    //Nao ha notas para o aluno
    if (this->conjunto_notas->size () == 0)
    {
        boletim << "\nNao ha notas disponiveis!" << endl;
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

            boletim << "Disciplina: " << disciplina_impressao << endl;

            //Nota 1
            if (i->getN1 () < 0)
            {
                boletim << "Nota 1: Indisponivel" << endl;
            }
            else
            {
                boletim << "Nota 1: " << i->getN1 () << endl;
            }

            //Nota 2
            if (i->getN2 () < 0)
            {
                boletim << "Nota 2: Indisponivel" << endl;
            }
            else
            {
                boletim << "Nota 2: " << i->getN2 () << endl;
            }

            //Nota 3
            if (i->getN3 () < 0)
            {
                boletim << "Nota 3: Indisponivel" << endl;
            }
            else
            {
                boletim << "Nota 3: " << i->getN3 () << endl;
            }

            //Nota 4
            if (i->getN4 () < 0)
            {
                boletim << "Nota 4: Indisponivel" << endl;
            }
            else
            {
                boletim << "Nota 4: " << i->getN4 () << endl;
            }

            boletim << "-----------------------------------" << endl;
        }
    }

    return boletim.str ();

}

void Notas::adicionarNota (const string disci, const float n1, const float n2, const float n3, const float n4)
{
    Nota* nova_nota = new Nota ();

    nova_nota->setNota(disci, n1, n2, n3, n4);

    vector<Nota>::iterator i;

    i = this->conjunto_notas->begin ();

    int controle = 0;

    do
    {
        i++;

        if (conjunto_notas->size() == 0)
        {
            controle = 1;
        }
        else if (i == this->conjunto_notas->end ())
        {
            controle = 1;
        }
        else if (i->getDisciplina () == disci)
        {
            controle = 1;
        }
    }
    while (controle == 0);

    //A disciplina eh nova
    if (conjunto_notas->size() == 0 || i == this->conjunto_notas->end ())
    {
        this->conjunto_notas->push_back (*nova_nota);

        nova_nota->gravar(0, this->matricula, disci);
    }
    //A disciplina jah existe
    else
    {
        this->conjunto_notas->erase (i);

        this->conjunto_notas->push_back(*nova_nota);

        nova_nota->gravar(1, this->matricula, disci);
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
