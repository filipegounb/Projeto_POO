//MÓDULO DE GERENCIAMENTO DE DADOS
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

//Retorna a existência do arquivo
bool ArquivoExiste::getExistencia ()
{
    return this->existe;
}

//Cadastro de usuário Master
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
    /* Implementar um try-catch para lançar uma exceção aqui!!!!
    else //sucesso = -2
    {
        throw "deu pau aqui! valor inválido para o nível de usuário!
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
    //O arquivo ainda não existe
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
    //O arquivo ainda não existe
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

            //Lendo a matrícula
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

            //Lendo a matrícula
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

            //Lendo a matrícula
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

//Checa os dados de um Aluno (nao precisa da senha do aluno nem da turma)
bool Checar_user::checar_user (const string nome, const string matricula, const char *nome_arquivo)
{
    char *n_suporte = 0;
    char *mat_suporte = 0;
    char lixo[11];
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

        n_suporte[20] = '\0';
        mat_suporte[9] = '\0';

        do
        {
            //Lendo o nome
            fscanf (arquivo, "%20c", n_suporte);
            fscanf (arquivo, "%c", &lixo[0]);

            string n (n_suporte);

            //Lendo a matrícula
            fscanf (arquivo, "%9c", mat_suporte);
            fscanf (arquivo, "%c", &lixo[0]);

            string mat (mat_suporte);

            //Pulando a senha
            fscanf (arquivo, "%11c", lixo);

            //Pulando a turma
            fscanf (arquivo, "%c", &lixo[0]);

            //Verificando o status do registro
            Registro registro (3);
            registro.setPos (posicao);
            status = registro.getStatus ();

            if (n == nome && mat == matricula && status == 1)
            {
                return true;

                cout << "Nome: " << nome << " Matricula: " << matricula;
            }

            if (!feof (arquivo))
            {
                fscanf (arquivo, "%c", &lixo[0]); // '+'
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

                //Lendo a matrícula
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

                //Lendo a matrícula
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

                //Lendo a matrícula
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

        return true;
    }
}

//Seta as notas para uma disciplina
void Nota::setNota (const string disci, const float n1, const float n2, const float n3, const float n4)
{
    this->disciplina = disci;
    this->N1 = n1;
    this->N2 = n2;
    this->N3 = n3;
    this->N4 = n4;
}

//Retorna a disciplina
string Nota::getDisciplina ()
{
    return this->disciplina;
}

//Retorna a primeira nota
float Nota::getN1 ()
{
    return this->N1;
}

//Retorna a segunda nota
float Nota::getN2 ()
{
    return this->N2;
}

//Retorna a terceira nota
float Nota::getN3 ()
{
    return this->N3;
}

//Retorna a quarta nota
float Nota::getN4 ()
{
    return this->N4;
}

//Destrutor de 'Recupera_Notas'
Recupera_Notas::~Recupera_Notas ()
{
    int i;
    int tam = conjunto_notas->size ();

    for (i = 0; i < tam; i++)
    {
        conjunto_notas->pop_back ();
    }

    free (conjunto_notas);
}

//The following method is kind of confusing... Don't try to change this, just use it! It works!
void Nota::gravar (const int status, const string mat, const string disci)
{
    FILE* arquivo = NULL;

    char m[10];
    char d[11];

    m[9] = '\0';
    d[10] = '\0';

    for (unsigned int i = 0; i < mat.size (); i++)
    {
        m[i] = mat[i];
    }

    for (unsigned int i = 0; i < disci.size (); i++)
    {
        d[i] = disci[i];
    }

    arquivo = fopen ("dados/Notas.txt", "r");

    if (arquivo == NULL)
    {
        fclose (arquivo);

        arquivo = fopen ("dados/Notas.txt", "w");

        fprintf (arquivo, "%s|%s|%.1f|%.1f|%.1f|%.1f", m, d, N1, N2, N3, N4);

        fclose (arquivo);

        return;
    }

    arquivo = fopen ("dados/Notas.txt", "a+");

    //Grava no final do arquivo
    if (status == 0)
    {
        fprintf (arquivo, "+%s|%s|%.1f|%.1f|%.1f|%.1f", m, d, N1, N2, N3, N4);
    }
    //Procura o registro da nota e a escreve no arquivo
    else if (status == 1)
    {
        int posicao = -1;
        int parar = 0;
        int c1 = 0;
        int c2 = 0;
        char lixo[50];
        char mat_suporte[10];
        char disci_suporte[11];

        mat_suporte[9] = '\0';
        disci_suporte[10] = '\0';

        long int tam_registro = 36;

        do
        {
            c1 = 0;
            c2 = 0;

            posicao++;

            fscanf (arquivo, "%[^|]", mat_suporte);
            fscanf (arquivo, "%c", &lixo[0]);

            for (int i = 0; i < 10; i++)
            {
                if (mat_suporte[i] != m[i])
                {
                    c1 = 1;
                }
            }

            if (c1 == 0)
            {
                fscanf (arquivo, "%[^|]", disci_suporte);
                fscanf (arquivo, "%c", &lixo[0]);

                for (int i = 0; i < 11; i++)
                {
                    if (disci_suporte[i] != d[i])
                    {
                        c2 = 1;
                    }
                }

                if (c2 == 0)
                {
                    parar = 1;
                }
                else
                {
                    for (int i = 0; i < 15; i++)
                    {
                        fscanf (arquivo, "%c", &lixo[i]);
                    }
                    fscanf (arquivo, "%c", &lixo[0]);
                }

            }
            else
            {
                for (int i = 0; i < 26; i++)
                {
                    fscanf (arquivo, "%c", &lixo[i]);
                }
                fscanf (arquivo, "%c", &lixo[0]);
            }
        }
        while (parar == 0);

        fclose (arquivo);

        arquivo = fopen ("dados/Notas.txt", "r+");

        if (posicao == 0)
        {
            fseek(arquivo, 21, SEEK_SET);
        }
        else
        {
            fseek(arquivo, ( (long int) posicao) * (tam_registro + 1) + 21, SEEK_SET);
        }

        fprintf (arquivo, "%.1f|%.1f|%.1f|%.1f", N1, N2, N3, N4);
    }

    fclose (arquivo);
}

//Le e retorna o conjunto de notas de um certo aluno
int Recupera_Notas::obter_conjunto_notas (const string& matricula, const string& disciplina_professor, const char *nome_arquivo)
{
    string disciplina;
    float N1;
    float N2;
    float N3;
    float N4;

    this->conjunto_notas = new vector<Nota> ();

    FILE *arquivo = fopen (nome_arquivo, "r");

    if (arquivo == 0)
    {
        return 0;
    }

    Nota *nota = new Nota ();

    char lixo;
    char mat[10];
    char disci[11];

    mat[9] = '\0';
    disci[10] = '\0';

    //Nao eh necessario se preocupar com a disciplina
    if (disciplina_professor == " ")
    {
        do
        {
            fscanf (arquivo, "%9c", mat);

            //Le as notas
            if (mat == matricula)
            {
                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%10c", disci);
                disciplina.assign (disci);

                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%f", &N1);
                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%f", &N2);
                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%f", &N3);
                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%f", &N4);

                //Seta o objeto 'nota'
                nota->setNota (disciplina, N1, N2, N3, N4);

                //Insere a nota no conjunto de notas
                this->conjunto_notas->push_back (*nota);
            }
            //Avançamos até o próximo registro
            else
            {
                do
                {
                    fscanf (arquivo, "%c", &lixo);
                }
                while (lixo != '+' && !feof (arquivo));
            }

            if ( !feof (arquivo)) fscanf (arquivo, "%c", &lixo);
        }
        while ( !feof (arquivo) );
    }
    //Deve-se escolher a disciplina correta
    else
    {
        do
        {
            fscanf (arquivo, "%9c", mat);

            //Le as notas
            if (mat == matricula)
            {
                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%10c", disci);
                disciplina.assign (disci);


                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%f", &N1);
                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%f", &N2);
                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%f", &N3);
                fscanf (arquivo, "%c", &lixo); //Avançando '|'

                fscanf (arquivo, "%f", &N4);

                if (disciplina == disciplina_professor)
                {
                    //Seta o objeto 'nota'
                    nota->setNota (disciplina, N1, N2, N3, N4);

                    //Insere a nota no conjunto de notas
                    this->conjunto_notas->push_back (*nota);
                }
            }
            //Avançamos até o próximo registro
            else
            {
                do
                {
                    fscanf (arquivo, "%c", &lixo);
                }
                while (lixo != '+' && !feof (arquivo));
            }

            if ( !feof (arquivo)) fscanf (arquivo, "%c", &lixo);
        }
        while ( !feof (arquivo) );
    }

    return this->conjunto_notas->size ();
}

//Retorna um objeto Nota
Nota Recupera_Notas::obter_uma_nota ()
{
    Nota *nota = new Nota ();

    nota->setNota (this->conjunto_notas->back ().getDisciplina (), this->conjunto_notas->back ().getN1 (), this->conjunto_notas->back ().getN2 (), this->conjunto_notas->back ().getN3 (), this->conjunto_notas->back ().getN4 ());

    this->conjunto_notas->pop_back ();

    return *nota;
}
