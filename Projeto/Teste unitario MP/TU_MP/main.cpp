#include <iostream>
#include "mp.h"

/*
Inclusão do cabeçalho de teste
*/

extern "C" //Possibilita a inclusao de arquivos escritos em C dentro de arquivos C++
{
    #include "CuTest.h"
}

using namespace std;

class ExecutarTestes
{
public:
    ExecutarTestes();
};

/*
Declaração dos protótipos das funções.
*/

void teste_gets (CuTest *teste);
void teste_cadastrar_checar_usuario (CuTest *teste);
void teste_checar_aluno_nome_matricula (CuTest *teste);
void teste_excluir_usuario (CuTest *teste);

void teste_notas_aluno (CuTest *teste);
void teste_notas_professor (CuTest *teste);

int main(int argc, char *argv[])
{
    ExecutarTestes *testes = new ExecutarTestes ();

    getchar ();

    delete testes;

    return 0;
}

//Função que executa os casos de teste
ExecutarTestes::ExecutarTestes ()
{
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    /*
        Cria o conjunto de testes.
    */

    //Testes com dados de usuarios
    CuSuiteAdd (suite, CuTestNew ("Criar objeto de usuario e retornar os dados possiveis", teste_gets));
    CuSuiteAdd (suite, CuTestNew ("Cadastrar um usuario e checar os dados desse usuario", teste_cadastrar_checar_usuario));
    CuSuiteAdd (suite, CuTestNew ("Checar um aluno pelo nome e matricula", teste_checar_aluno_nome_matricula));
    CuSuiteAdd (suite, CuTestNew ("Excluir um usuario", teste_excluir_usuario));

    //Testes com notas
    CuSuiteAdd (suite, CuTestNew ("Notas consultadas por um aluno", teste_notas_aluno));
    CuSuiteAdd (suite, CuTestNew ("Notas consultadas por um professor", teste_notas_professor));

    /*
        Executa o conjunto de testes e apresenta os resultados.
    */

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

void teste_gets (CuTest *teste)
{
    int esperado = 1;
    string nome_p ("              p_user");
    string nome_a ("              a_user");
    string matricula ("123456789");
    string senha ("     12345");
    string disciplina ("       POO");
    char turma = 'A';

    Professor *professor = new Professor (nome_p, matricula, senha, disciplina);
    Aluno *aluno = new Aluno (nome_a, matricula, senha, turma);

    if (professor->getDisciplina () == disciplina && aluno->getNome () == nome_a && aluno->getMatricula () == matricula)
    {
        delete professor;
        delete aluno;

        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        delete professor;
        delete aluno;

        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_cadastrar_checar_usuario (CuTest *teste)
{
    bool resultado;
    int esperado = 1;
    Checa_estado_sistema sistema;

    //Cadastro
    string nome_m ("              Master");
    string nome_p ("              p_user");
    string nome_a ("              a_user");
    string matricula ("123456789");
    string senha ("     12345");
    string disciplina ("       POO");
    char turma = 'A';

    Master *master = new Master (nome_m, matricula, senha);
    Professor *professor = new Professor (nome_p, matricula, senha, disciplina);
    Aluno *aluno = new Aluno (nome_a, matricula, senha, turma);

    master->cadastrar ();
    professor->cadastrar ();
    aluno->cadastrar ();

    delete master;
    delete professor;
    delete aluno;

    //Checagem
    bool resultado1, resultado2, resultado3;
    User user;

    resultado1 = user.existe_user (nome_m, matricula, senha);
    resultado2 = user.existe_user (nome_p, matricula, senha, disciplina);
    resultado3 = user.existe_user (nome_a, matricula, senha, turma);

    if (resultado1 && resultado2 && resultado3)
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_checar_aluno_nome_matricula (CuTest *teste)
{
    bool resultado;
    int esperado = 1;
    string nome_a ("              a_user");
    string matricula ("123456789");
    User user;

    resultado = user.existe_user (nome_a, matricula);

    if (resultado)
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }

}

void teste_excluir_usuario (CuTest *teste)
{
    int esperado = 1;
    bool resultado;
    string nome_m ("              Master");
    string matricula ("123456789");
    string senha ("     12345");
    User user;

    resultado = user.solicitar_excluir_user (nome_m, matricula, 1);

    if (resultado)
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_notas_aluno (CuTest *teste)
{
    int esperado = 1;
    string nome_a ("              a_user");
    string matricula ("123456789");
    string disciplina ("       POO");
    vector<Nota>::iterator i;
    Notas *n = new Notas (nome_a, matricula);

    i = n->conjunto_notas->begin ();

    if (i->getDisciplina () == disciplina && i->getN1 () == (float) 9.8 && i->getN2 () == (float) -1.0 && i->getN3 () == (float) 8.8 && i->getN4 () == (float) 9.9)
    {
        delete n;

        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        delete n;

        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_notas_professor (CuTest *teste)
{
    int esperado = 1;
    string nome_a ("              a_user");
    string matricula ("123456789");
    string disciplina ("       POO");
    vector<Nota>::iterator i;
    Notas *n = new Notas (nome_a, matricula, disciplina);

    i = n->conjunto_notas->begin ();

    if (i->getDisciplina () == disciplina && i->getN1 () == (float) 9.8 && i->getN2 () == (float) -1.0 && i->getN3 () == (float) 8.8 && i->getN4 () == (float) 9.9)
    {
        delete n;

        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        delete n;

        CuAssertIntEquals (teste, esperado, 0);
    }
}
