#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "mvb.h"


/*
Inclusão do cabeçalho de teste
*/

extern "C" //Possibilita a inclusao de arquivos escritos em C dentro de arquivos C++
{
    #include "CuTest.h"
}

using namespace std;

#define MASTER 1
#define PROFESSOR 2
#define ALUNO 3
#define NIVEL_INVALIDO 4
#define OCUPADO 1
#define LIVRE 0

class ExecutarTestes
{
public:
    ExecutarTestes();
};

/*
Declaração dos protótipos das funções.
*/

void teste_obter_posicao_livre_inexistente (CuTest *teste);
void teste_obter_posicao_livre_nivel_invalido (CuTest *teste);
void teste_alterar_status_inexistente (CuTest *teste);
void teste_obter_status_inexistente (CuTest *teste);
void teste_incluir_primeiro_registro (CuTest *teste);
void teste_incluir_registro (CuTest *teste);
void teste_alterar_status_nivel_usuario_errado (CuTest *teste);
void teste_alterar_status_posicao_muito_grande_invalido (CuTest *teste);
void teste_alterar_status_valor_invalido (CuTest *teste);
void teste_alterar_status_existente (CuTest *teste);
void teste_incluir_registro_meio (CuTest *teste);

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

    CuSuiteAdd (suite, CuTestNew ("Obter posicao livre arquivo inexistente.", teste_obter_posicao_livre_inexistente));
    CuSuiteAdd (suite, CuTestNew ("Obter posicao livre com um nivel de usuario invalido.", teste_obter_posicao_livre_nivel_invalido));
    CuSuiteAdd (suite, CuTestNew ("Alterar status de um registro em um arquivo inexistente.", teste_alterar_status_inexistente));
    CuSuiteAdd (suite, CuTestNew ("Obter status arquivo inexistente.", teste_obter_status_inexistente));
    CuSuiteAdd (suite, CuTestNew ("Incluir primeiro registro.", teste_incluir_primeiro_registro));
    CuSuiteAdd (suite, CuTestNew ("Incluir registro no fim do arquivo.", teste_incluir_registro));
    CuSuiteAdd (suite, CuTestNew ("Alterar status com um nivel de usuario invalido.", teste_alterar_status_nivel_usuario_errado));
    CuSuiteAdd (suite, CuTestNew ("Alterar status de um registro em uma posicao inexistente.", teste_alterar_status_posicao_muito_grande_invalido));
    CuSuiteAdd (suite, CuTestNew ("Alterar status com um valor de status errado (diferente de '0' e de '1'.", teste_alterar_status_valor_invalido));
    CuSuiteAdd (suite, CuTestNew ("Alterar status de um registro existente.", teste_alterar_status_existente));
    CuSuiteAdd (suite, CuTestNew ("Incluir registro no meio do arquivo.", teste_incluir_registro_meio));


    /*
        Executa o conjunto de testes e apresenta os resultados.
    */

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

/*
Casos de Teste
*/

void teste_obter_posicao_livre_inexistente (CuTest *teste)
{
    int esperado = -2;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    CuAssertIntEquals (teste, esperado, a->obter_posicao_livre ());
    CuAssertIntEquals (teste, esperado, b->obter_posicao_livre ());
    CuAssertIntEquals (teste, esperado, c->obter_posicao_livre ());

    delete a;
    delete b;
    delete c;
}

void teste_obter_posicao_livre_nivel_invalido (CuTest *teste)
{
    int esperado = -3;

    Registro *a = new Registro (NIVEL_INVALIDO);

    CuAssertIntEquals (teste, esperado, a->obter_posicao_livre ());
}

void teste_alterar_status_inexistente (CuTest *teste)
{
    int esperado = -2;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    CuAssertIntEquals (teste, esperado, a->alterar_status_registro (OCUPADO));
    CuAssertIntEquals (teste, esperado, b->alterar_status_registro (OCUPADO));
    CuAssertIntEquals (teste, esperado, c->alterar_status_registro (OCUPADO));

    delete a;
    delete b;
    delete c;
}

void teste_obter_status_inexistente (CuTest *teste)
{
    int esperado = -1;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    a->setPos (0);
    b->setPos (0);
    c->setPos (0);

    CuAssertIntEquals (teste, esperado, a->getStatus ());
    CuAssertIntEquals (teste, esperado, b->getStatus ());
    CuAssertIntEquals (teste, esperado, c->getStatus ());

    delete a;
    delete b;
    delete c;
}

void teste_incluir_primeiro_registro (CuTest *teste)
{
    int esperado = -1;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    CuAssertIntEquals (teste, esperado, a->incluir_registro ());
    CuAssertIntEquals (teste, esperado, b->incluir_registro ());
    CuAssertIntEquals (teste, esperado, c->incluir_registro ());

    delete a;
    delete b;
    delete c;
}

void teste_incluir_registro (CuTest *teste)
{
    int esperado = -1;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    CuAssertIntEquals (teste, esperado, a->incluir_registro ());
    CuAssertIntEquals (teste, esperado, b->incluir_registro ());
    CuAssertIntEquals (teste, esperado, c->incluir_registro ());

    delete a;
    delete b;
    delete c;
}

void teste_alterar_status_nivel_usuario_errado (CuTest *teste)
{
    int esperado = -4;

    Registro *a = new Registro (NIVEL_INVALIDO);

    CuAssertIntEquals (teste, esperado, a->alterar_status_registro (LIVRE));

    delete a;
}

void teste_alterar_status_posicao_muito_grande_invalido (CuTest *teste)
{
    int esperado = -3;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    a->setPos (3);
    b->setPos (3);
    c->setPos (3);

    CuAssertIntEquals (teste, esperado, a->alterar_status_registro (LIVRE));
    CuAssertIntEquals (teste, esperado, b->alterar_status_registro (LIVRE));
    CuAssertIntEquals (teste, esperado, c->alterar_status_registro (LIVRE));

    delete a;
    delete b;
    delete c;
}

void teste_alterar_status_valor_invalido (CuTest *teste)
{
    int esperado = -1;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    CuAssertIntEquals (teste, esperado, a->alterar_status_registro (2));
    CuAssertIntEquals (teste, esperado, b->alterar_status_registro (2));
    CuAssertIntEquals (teste, esperado, c->alterar_status_registro (2));

    delete a;
    delete b;
    delete c;
}

void teste_alterar_status_existente (CuTest *teste)
{
    int esperado = 0;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    a->setPos (0);
    b->setPos (0);
    c->setPos (0);

    CuAssertIntEquals (teste, esperado, a->alterar_status_registro (LIVRE));
    CuAssertIntEquals (teste, esperado, b->alterar_status_registro (LIVRE));
    CuAssertIntEquals (teste, esperado, c->alterar_status_registro (LIVRE));

    delete a;
    delete b;
    delete c;
}

void teste_incluir_registro_meio (CuTest *teste)
{
    int esperado = 0;

    Registro *a = new Registro (MASTER);
    Registro *b = new Registro (PROFESSOR);
    Registro *c = new Registro (ALUNO);

    CuAssertIntEquals (teste, esperado, a->incluir_registro ());
    CuAssertIntEquals (teste, esperado, b->incluir_registro ());
    CuAssertIntEquals (teste, esperado, c->incluir_registro ());

    delete a;
    delete b;
    delete c;
}
