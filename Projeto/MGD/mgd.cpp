//MÓDULO DE GERENCIAMENTO DE DADOS
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "mgd.h"
#include "..\MVB\mvb.h"

#define SERVIDOR_MGD

/* Classes */
using namespace std;

TestaSistema::TestaSistema ()
{
    ifstream arquivo ("dados/Master.txt"); // ou: ifstream arquivo; arquivo.open ("dados/Master.txt");

    if ( !arquivo )
    {
        throw InicializarSistema ();
    }
}

//Cadastra um usuário Master no sistema
InicializarSistema::InicializarSistema ()
{
    ofstream arquivo ("dados/Master.txt");

    //Não há espaço em disco
    if ( arquivo.fail () )
    {
        cout << "Nao ha espaco suficiente em disco!\n\n";
        abort ();
    }
    //Cadastrando um usuário Master inicial
    else
    {
        arquivo <<  "              m_user|123456789|     12345";

        arquivo.close ();

        incluir_registro (1);

    }
}

//Checa a existencia de um arquivo
ArquivoExiste::ArquivoExiste (const char * n_arquivo)
{
    this->nome_arquivo = n_arquivo;

    ifstream arquivo (this->nome_arquivo);

    this->existe = arquivo.fail () ? false:true;

    arquivo.close ();
}

//Retorna a existência do arquivo
bool ArquivoExiste::getExistencia ()
{
    return this->existe;
}

//Cadastro de usuário Master
Cadastrar::Cadastrar (const string nome, const int matricula, const string senha)
{
    //Aqui, nao ha verificacao da existencia do arquivo de usuarios Master, pois,
    //para que este codigo seja alcancado, eh necessario que a criacao deste
    //arquivo jah tenha sido feita na primeira execucao do sistema.
    int tam_registro = 42; //Tamanho de um registro

    int posicao = incluir_registro (1);

    //Inserir no final do arquivo
    if (posicao == -1)
    {
        ofstream arquivo ("dados/Master.txt", ios_base::app);

        arquivo << "+" << nome << "|" << matricula << "|" << senha;

        arquivo.close ();
    }
    else
    {
        ofstream arquivo ("dados/Master.txt", ios_base::in);

        arquivo.seekp (posicao*tam_registro, ios_base::beg);

        arquivo << nome << "|" << matricula << "|" << senha;

        arquivo.close ();
    }
}

//Cadastro de Professor
Cadastrar::Cadastrar (const string nome, const int matricula, const string senha, const string disciplina)
{
    bool existe;
    int tam_registro = 53; //Tamanho de um registro
    int posicao = incluir_registro (2);

    ArquivoExiste arq ("dados/Professor.txt");

    existe = arq.getExistencia ();

    //O arquivo jah existe e o registro sera inserido no meio do arquivo
    if (existe && posicao >= 0)
    {
        ofstream arquivo ("dados/Professor.txt", ios_base::in);

        arquivo.seekp (tam_registro*posicao, ios_base::beg);

        arquivo << nome << "|" << matricula << "|" << senha << "|" << disciplina;

        arquivo.close ();
    }
    //O arquivo jah existe e o registro sera inserido no final do arquivo
    else if (existe)
    {
        ofstream arquivo ("dados/Professor.txt", ios_base::app);

        arquivo << "+" << nome << "|" << matricula << "|" << senha << "|" << disciplina;

        arquivo.close ();
    }
    //O arquivo ainda não existe
    else
    {
        ofstream arquivo ("dados/Professor.txt");

        arquivo << nome << "|" << matricula << "|" << senha << "|" << disciplina;

        arquivo.close ();
    }
}

//Cadastro de Aluno
Cadastrar::Cadastrar (const string nome, const int matricula, const string senha, const char turma)
{
    bool existe;
    int tam_registro = 44; //Tamanho de um registro
    int posicao = incluir_registro (3);

    ArquivoExiste arq ("dados/Aluno.txt");

    existe = arq.getExistencia ();

    //O arquivo jah existe e o registro sera inserido no meio do arquivo
    if (existe && posicao >= 0)
    {
        ofstream arquivo ("dados/Aluno.txt", ios_base::in);

        arquivo.seekp (tam_registro*posicao, ios_base::beg);

        arquivo << nome << "|" << matricula << "|" << senha << "|" << turma;

        arquivo.close ();
    }
    //O arquivo jah existe e o registro sera inserido no final do arquivo
    else if (existe)
    {
        ofstream arquivo ("dados/Aluno.txt", ios_base::app);

        arquivo << "+" << nome << "|" << matricula << "|" << senha << "|" << turma;

        arquivo.close ();
    }
    //O arquivo ainda não existe
    else
    {
        ofstream arquivo ("dados/Aluno.txt");

        arquivo << nome << "|" << matricula << "|" << senha << "|" << turma;

        arquivo.close ();
    }
}

/* Funções */
//Checa os dados de um Master
bool checar_user (const string nome, const int matricula, const string senha, const char *nome_arquivo)
{
    int mat;
    char c;
    char *n_suporte = 0;
    char *s_suporte = 0;
    int status; //Indica se o registro ainda esta disponivel ou se ja foi deletado (checa o arquivo de vetor de bits)
    long int posicao = 0;
    FILE *arquivo = fopen (nome_arquivo, "r");

    //O arquivo falhou
    if ( arquivo == 0)
    {
        return false;
    }
    //O arquivo abriu
    else
    {
        n_suporte = (char *) malloc (21*sizeof (char));
        s_suporte = (char *) malloc (11*sizeof (char));

        n_suporte[20] = '\0';
        s_suporte[10] = '\0';

        do
        {
            //Lendo o nome
            fscanf (arquivo, "%20c", n_suporte);
            fscanf (arquivo, "%c", &c);

            string n (n_suporte);

            //Lendo a matrícula
            fscanf (arquivo, "%d", &mat);
            fscanf (arquivo, "%c", &c);

            //Lendo a senha
            fscanf (arquivo, "%10c", s_suporte);

            string s (s_suporte);

            //Verificando o status do registro
            status = obter_status (1, posicao);

            if (n == nome && s == senha && mat == matricula && status == 1)
            {
                return true;
            }

            if (!feof (arquivo))
            {
                fscanf (arquivo, "%c", &c); // '+'
            }

            posicao++;
        }
        while ( !feof (arquivo) );

        return false;
    }
}

//Checa os dados de um Professor
bool checar_user (const string nome, const int matricula, const string senha, const string disciplina, const char *nome_arquivo)
{
    int mat;
    char c;
    char *n_suporte = 0;
    char *s_suporte = 0;
    char *disci_suporte = 0;
    int status; //Indica se o registro ainda esta disponivel ou se ja foi deletado (checa o arquivo de vetor de bits)
    long int posicao = 0;
    FILE *arquivo = fopen (nome_arquivo, "r");

    //O arquivo falhou
    if ( arquivo == 0)
    {
        return false;
    }
    //O arquivo abriu
    else
    {
        n_suporte = (char *) malloc (21*sizeof (char));
        s_suporte = (char *) malloc (11*sizeof (char));
        disci_suporte = (char *) malloc (11*sizeof (char));

        n_suporte[20] = '\0';
        s_suporte[10] = '\0';
        disci_suporte[10] = '\0';

        do
        {
            //Lendo o nome
            fscanf (arquivo, "%20c", n_suporte);
            fscanf (arquivo, "%c", &c);

            string n (n_suporte);

            //Lendo a matrícula
            fscanf (arquivo, "%d", &mat);
            fscanf (arquivo, "%c", &c);

            //Lendo a senha
            fscanf (arquivo, "%10c", s_suporte);
            fscanf (arquivo, "%c", &c);

            string s (s_suporte);

            //Lendo a disciplina
            fscanf (arquivo, "%10c", disci_suporte);

            string disci (disci_suporte);

            //Verificando o status do registro
            status = obter_status (2, posicao);

            if (n == nome && s == senha && mat == matricula && disci == disciplina && status == 1)
            {
                return true;
            }

            if (!feof (arquivo))
            {
                fscanf (arquivo, "%c", &c); // '+'
            }

            posicao++;
        }
        while ( !feof (arquivo) );

        return false;
    }
}

//Checa os dados de um Aluno
bool checar_user (const string nome, const int matricula, const string senha, const char turma, const char *nome_arquivo)
{
    int mat;
    char c;
    char *n_suporte = 0;
    char *s_suporte = 0;
    char t;
    int status; //Indica se o registro ainda esta disponivel ou se ja foi deletado (checa o arquivo de vetor de bits)
    long int posicao = 0;
    FILE *arquivo = fopen (nome_arquivo, "r");

    //O arquivo falhou
    if ( arquivo == 0)
    {
        return false;
    }
    //O arquivo abriu
    else
    {
        n_suporte = (char *) malloc (21*sizeof (char));
        s_suporte = (char *) malloc (11*sizeof (char));

        n_suporte[20] = '\0';
        s_suporte[10] = '\0';

        do
        {
            //Lendo o nome
            fscanf (arquivo, "%20c", n_suporte);
            fscanf (arquivo, "%c", &c);

            string n (n_suporte);

            //Lendo a matrícula
            fscanf (arquivo, "%d", &mat);
            fscanf (arquivo, "%c", &c);

            //Lendo a senha
            fscanf (arquivo, "%10c", s_suporte);
            fscanf (arquivo, "%c", &c);

            string s (s_suporte);

            //Lendo a turma
            fscanf (arquivo, "%c", &t);

            //Verificando o status do registro
            status = obter_status (3, posicao);

            if (n == nome && s == senha && mat == matricula && t == turma && status == 1)
            {
                return true;
            }

            if (!feof (arquivo))
            {
                fscanf (arquivo, "%c", &c); // '+'
            }

            posicao++;
        }
        while ( !feof (arquivo) );

        return false;
    }
}

//Busca a posicao do registro de um usuario
long int checar_user (const string nome, const int matricula, const int nivel)
{
    int mat;
    char lixo[22];
    char *n_suporte = 0;
    int status; //Indica se o registro ainda esta disponivel ou se ja foi deletado (checa o arquivo de vetor de bits)
    long int posicao = 0;

    FILE *arquivo = 0;

    switch (nivel)
    {
    //Master
    case 1:
        arquivo = fopen ("dados/Master.txt", "r");

        //O arquivo falhou
        if ( arquivo == 0 )
        {
            return -1;
        }
        //O arquivo abriu
        else
        {
            n_suporte = (char *) malloc (21*sizeof (char));

            n_suporte[20] = '\0';

            do
            {
                //Lendo o nome
                fscanf (arquivo, "%20c", n_suporte);
                fscanf (arquivo, "%c", &lixo[0]);

                string n (n_suporte);

                //Lendo a matrícula
                fscanf (arquivo, "%d", &mat);

                //Avancando os dados desnecessarios
                fscanf (arquivo, "%11c", lixo);

                //Verificando o status do registro
                status = obter_status (1, posicao);

                if (n == nome && mat == matricula && status == 1)
                {
                    return posicao;
                }

                if (!feof (arquivo))
                {
                    fscanf (arquivo, "%c", &lixo[0]); // '+'
                }

                posicao++;
            }
            while ( !feof (arquivo) );

        return -1;
        }
        break;
    //Professor
    case 2:
        arquivo = fopen ("dados/Professor.txt", "r");

        //O arquivo falhou
        if ( arquivo == 0 )
        {
            return -1;
        }
        //O arquivo abriu
        else
        {
            n_suporte = (char *) malloc (21*sizeof (char));

            n_suporte[20] = '\0';

            do
            {
                //Lendo o nome
                fscanf (arquivo, "%20c", n_suporte);
                fscanf (arquivo, "%c", &lixo[0]);

                string n (n_suporte);

                //Lendo a matrícula
                fscanf (arquivo, "%d", &mat);

                //Avancando os dados desnecessarios
                fscanf (arquivo, "%22c", lixo);

                //Verificando o status do registro
                status = obter_status (2, posicao);

                if (n == nome && mat == matricula && status == 1)
                {
                    return posicao;
                }

                if (!feof (arquivo))
                {
                    fscanf (arquivo, "%c", &lixo[0]); // '+'
                }

                posicao++;
            }
            while ( !feof (arquivo) );

        return -1;
        }

        break;
    //Aluno
    case 3:
        arquivo = fopen ("dados/Aluno.txt", "r");

        //O arquivo falhou
        if ( arquivo == 0 )
        {
            return -1;
        }
        //O arquivo abriu
        else
        {
            n_suporte = (char *) malloc (21*sizeof (char));

            n_suporte[20] = '\0';

            do
            {
                //Lendo o nome
                fscanf (arquivo, "%20c", n_suporte);
                fscanf (arquivo, "%c", &lixo[0]);

                string n (n_suporte);

                //Lendo a matrícula
                fscanf (arquivo, "%d", &mat);

                //Avancando os dados desnecessarios
                fscanf (arquivo, "%13c", lixo);

                //Verificando o status do registro
                status = obter_status (3, posicao);

                if (n == nome && mat == matricula && status == 1)
                {
                    return posicao;
                }

                if (!feof (arquivo))
                {
                    fscanf (arquivo, "%c", &lixo[0]); // '+'
                }

                posicao++;
            }
            while ( !feof (arquivo) );

        return -1;
        }

        break;
    }
}

//Checa os dados de um usuario, com o objetivo de exclui-lo (ver funcaos 'soliciar_excluir_......')
bool excluir_user (const string nome, const int matricula, const int nivel)
{
    int posicao;

    posicao = checar_user (nome, matricula, nivel);

    if (posicao == -1)
    {
        return false;
    }
    else
    {
        alterar_status_registro (nivel, (long int) posicao, 0);

        return true;
    }
}
