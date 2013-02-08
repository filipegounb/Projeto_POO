//M�DULO DE GERENCIAMENTO DE DADOS
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "mgd.h"
#include "..\MVB\mvb.h"

using namespace std;

//Testa o sistema
TestaSistema::TestaSistema ()
{
    ifstream arquivo ("dados/Master.txt"); // ou: ifstream arquivo; arquivo.open ("dados/Master.txt");

    if ( !arquivo )
    {
        throw InicializarSistema ();
    }
}

//Cadastra um usu�rio Master no sistema
InicializarSistema::InicializarSistema ()
{
    ofstream arquivo ("dados/Master.txt");

    //N�o h� espa�o em disco
    if ( arquivo.fail () )
    {
        cout << "Nao ha espaco suficiente em disco!\n\n";
        abort ();
    }
    //Cadastrando um usu�rio Master inicial
    else
    {
        arquivo <<  "              m_user|123456789|     12345";

        arquivo.close ();

        Registro registro (1);

        registro.incluir_registro ();

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

//Retorna a exist�ncia do arquivo
bool ArquivoExiste::getExistencia ()
{
    return this->existe;
}

//Cadastro de usu�rio Master
Cadastrar::Cadastrar (const string nome, const string matricula, const string senha)
{
    //Aqui, nao ha verificacao da existencia do arquivo de usuarios Master, pois,
    //para que este codigo seja alcancado, eh necessario que a criacao deste
    //arquivo jah tenha sido feita na primeira execucao do sistema.
    int tam_registro = 42; //Tamanho de um registro
    Registro registro (1);

    int sucesso = registro.incluir_registro ();

    //Inserir no final do arquivo
    if (sucesso == -1)
    {
        ofstream arquivo ("dados/Master.txt", ios_base::app);

        arquivo << "+" << nome << "|" << matricula << "|" << senha;

        arquivo.close ();
    }
    else if (sucesso == 0)
    {
        ofstream arquivo ("dados/Master.txt", ios_base::in);

        arquivo.seekp (tam_registro*registro.getPos (), ios_base::beg);

        arquivo << nome << "|" << matricula << "|" << senha;

        arquivo.close ();
    }
    /* Implementar um try-catch para lan�ar uma exce��o aqui!!!!
    else //sucesso = -2
    {
        throw "deu pau aqui! valor inv�lido para o n�vel de usu�rio!
    }
    */
}

//Cadastro de Professor
Cadastrar::Cadastrar (const string nome, const string matricula, const string senha, const string disciplina)
{
    bool existe;
    int tam_registro = 53; //Tamanho de um registro
    Registro registro (2);

    int sucesso = registro.incluir_registro ();

    ArquivoExiste arq ("dados/Professor.txt");

    existe = arq.getExistencia ();

    //O arquivo jah existe e o registro sera inserido no meio do arquivo
    if (existe && sucesso >= 0)
    {
        ofstream arquivo ("dados/Professor.txt", ios_base::in);

        arquivo.seekp (tam_registro*registro.getPos (), ios_base::beg);

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
    //O arquivo ainda n�o existe
    else
    {
        ofstream arquivo ("dados/Professor.txt");

        arquivo << nome << "|" << matricula << "|" << senha << "|" << disciplina;

        arquivo.close ();
    }
}

//Cadastro de Aluno
Cadastrar::Cadastrar (const string nome, const string matricula, const string senha, const char turma)
{
    bool existe;
    int tam_registro = 44; //Tamanho de um registro
    Registro registro (3);

    int sucesso = registro.incluir_registro ();

    ArquivoExiste arq ("dados/Aluno.txt");

    existe = arq.getExistencia ();

    //O arquivo jah existe e o registro sera inserido no meio do arquivo
    if (existe && sucesso >= 0)
    {
        ofstream arquivo ("dados/Aluno.txt", ios_base::in);

        arquivo.seekp (tam_registro*registro.getPos (), ios_base::beg);

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
    //O arquivo ainda n�o existe
    else
    {
        ofstream arquivo ("dados/Aluno.txt");

        arquivo << nome << "|" << matricula << "|" << senha << "|" << turma;

        arquivo.close ();
    }
}

//Checa os dados de um Master
bool Checar_user::checar_user (const string nome, const string matricula, const string senha, const char *nome_arquivo)
{
    char c;
    char *n_suporte = 0;
    char *mat_suporte = 0;
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
        mat_suporte = (char *) malloc (10*sizeof (char));
        s_suporte = (char *) malloc (11*sizeof (char));

        n_suporte[20] = '\0';
        mat_suporte[9] = '\0';
        s_suporte[10] = '\0';

        do
        {
            //Lendo o nome
            fscanf (arquivo, "%20c", n_suporte);
            fscanf (arquivo, "%c", &c);

            string n (n_suporte);

            //Lendo a matr�cula
            fscanf (arquivo, "%9c", mat_suporte);
            fscanf (arquivo, "%c", &c);

            string mat (mat_suporte);

            //Lendo a senha
            fscanf (arquivo, "%10c", s_suporte);

            string s (s_suporte);

            //Verificando o status do registro
            Registro registro (1);
            registro.setPos (posicao);
            status = registro.getStatus ();

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
bool Checar_user::checar_user (const string nome, const string matricula, const string senha, const string disciplina, const char *nome_arquivo)
{
    char c;
    char *n_suporte = 0;
    char *mat_suporte = 0;
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
        mat_suporte = (char *) malloc (10*sizeof (char));
        s_suporte = (char *) malloc (11*sizeof (char));
        disci_suporte = (char *) malloc (11*sizeof (char));

        n_suporte[20] = '\0';
        mat_suporte[9] = '\0';
        s_suporte[10] = '\0';
        disci_suporte[10] = '\0';

        do
        {
            //Lendo o nome
            fscanf (arquivo, "%20c", n_suporte);
            fscanf (arquivo, "%c", &c);

            string n (n_suporte);

            //Lendo a matr�cula
            fscanf (arquivo, "%9c", mat_suporte);
            fscanf (arquivo, "%c", &c);

            string mat (mat_suporte);

            //Lendo a senha
            fscanf (arquivo, "%10c", s_suporte);
            fscanf (arquivo, "%c", &c);

            string s (s_suporte);

            //Lendo a disciplina
            fscanf (arquivo, "%10c", disci_suporte);

            string disci (disci_suporte);

            //Verificando o status do registro
            Registro registro (2);
            registro.setPos (posicao);
            status = registro.getStatus ();

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
bool Checar_user::checar_user (const string nome, const string matricula, const string senha, const char turma, const char *nome_arquivo)
{
    char c;
    char *n_suporte = 0;
    char *mat_suporte = 0;
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
        mat_suporte = (char *) malloc (10*sizeof (char));
        s_suporte = (char *) malloc (11*sizeof (char));

        n_suporte[20] = '\0';
        mat_suporte[9] = '\0';
        s_suporte[10] = '\0';

        do
        {
            //Lendo o nome
            fscanf (arquivo, "%20c", n_suporte);
            fscanf (arquivo, "%c", &c);

            string n (n_suporte);

            //Lendo a matr�cula
            fscanf (arquivo, "%9c", mat_suporte);
            fscanf (arquivo, "%c", &c);

            string mat (mat_suporte);

            //Lendo a senha
            fscanf (arquivo, "%10c", s_suporte);
            fscanf (arquivo, "%c", &c);

            string s (s_suporte);

            //Lendo a turma
            fscanf (arquivo, "%c", &t);

            //Verificando o status do registro
            Registro registro (3);
            registro.setPos (posicao);
            status = registro.getStatus ();

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
long int Checar_user::checar_user (const string nome, const string matricula, const int nivel)
{

    char lixo[22];
    char *n_suporte = 0;
    char *mat_suporte = 0;
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
            mat_suporte = (char *) malloc (10*sizeof (char));

            n_suporte[20] = '\0';
            mat_suporte[9] = '\0';

            do
            {
                //Lendo o nome
                fscanf (arquivo, "%20c", n_suporte);
                fscanf (arquivo, "%c", &lixo[0]);

                string n (n_suporte);

                //Lendo a matr�cula
                fscanf (arquivo, "%9c", mat_suporte);

                string mat (mat_suporte);

                //Avancando os dados desnecessarios
                fscanf (arquivo, "%11c", lixo);

                //Verificando o status do registro
                Registro registro (1);
                registro.setPos (posicao);
                status = registro.getStatus ();

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
            mat_suporte = (char *) malloc (10*sizeof (char));

            n_suporte[20] = '\0';
            mat_suporte[9] = '\0';

            do
            {
                //Lendo o nome
                fscanf (arquivo, "%20c", n_suporte);
                fscanf (arquivo, "%c", &lixo[0]);

                string n (n_suporte);

                //Lendo a matr�cula
                fscanf (arquivo, "%9c", mat_suporte);

                string mat (mat_suporte);

                //Avancando os dados desnecessarios
                fscanf (arquivo, "%22c", lixo);

                //Verificando o status do registro
                Registro registro (2);
                registro.setPos (posicao);
                status = registro.getStatus ();

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
            mat_suporte = (char *) malloc (10*sizeof (char));

            n_suporte[20] = '\0';
            mat_suporte[9] = '\0';

            do
            {
                //Lendo o nome
                fscanf (arquivo, "%20c", n_suporte);
                fscanf (arquivo, "%c", &lixo[0]);

                string n (n_suporte);

                //Lendo a matr�cula
                fscanf (arquivo, "%9c", mat_suporte);

                string mat (mat_suporte);

                //Avancando os dados desnecessarios
                fscanf (arquivo, "%13c", lixo);

                //Verificando o status do registro
                Registro registro (3);
                registro.setPos (posicao);
                status = registro.getStatus ();

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
bool Excluir_user::excluir_user (const string nome, const string matricula, const int nivel)
{
    int posicao;
    Checar_user user;

    posicao = user.checar_user (nome, matricula, nivel);

    if (posicao == -1)
    {
        return false;
    }
    else
    {
        Registro registro (nivel);
        registro.setPos ((long int) posicao);
        registro.alterar_status_registro (0);
        //alterar_status_registro (nivel, (long int) posicao, 0);

        return true;
    }
}
