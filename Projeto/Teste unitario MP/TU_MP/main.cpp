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

void teste_cadastrar_checar_usuario (CuTest *teste);
/*
void teste_checar_user_sem_arquivos (CuTest *teste);
void teste_abrir_arquivo_inexistente (CuTest *teste);
void teste_inicializar_sistema (CuTest *teste);
void teste_checa_dados_usuario_Master (CuTest *teste);
void teste_checa_dados_usuario_Master_errado (CuTest *teste);
void teste_cadastrar_checar_usuario (CuTest *teste);
void teste_checa_dados_aluno_nome_matricula (CuTest *teste);
void teste_excluir_usuario (CuTest *teste);
void teste_checa_dados_usuario_deletado (CuTest *teste);
void teste_excluir_usuario_inexistente (CuTest *teste);

void teste_recuperar_notas_aluno (CuTest *teste);
void teste_recuperar_notas_professor (CuTest *teste);
*/

int main(int argc, char *argv[])
{
    Checa_estado_sistema sistema ();

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

    //////////////////////////
    //Testes com dados de usuarios
    CuSuiteAdd (suite, CuTestNew ("Cadastrar um usuario e checar os dados desse usuario", teste_cadastrar_checar_usuario));


    /*
    CuSuiteAdd (suite, CuTestNew ("Checa dados dos usuarios sem a existencia dos arquivos", teste_checar_user_sem_arquivos));
    CuSuiteAdd (suite, CuTestNew ("Abrir um arquivo inexistente", teste_abrir_arquivo_inexistente));
    CuSuiteAdd (suite, CuTestNew ("Inicializacao do sistema", teste_inicializar_sistema));
    CuSuiteAdd (suite, CuTestNew ("Checar dados usuario Master", teste_checa_dados_usuario_Master));
    CuSuiteAdd (suite, CuTestNew ("Checar dados usuario Master errado", teste_checa_dados_usuario_Master_errado));
    CuSuiteAdd (suite, CuTestNew ("Cadastrar um usuario e checar os dados desse usuario", teste_cadastrar_checar_usuario));
    CuSuiteAdd (suite, CuTestNew ("Checar dados de um aluno apenas com nome e matricula", teste_checa_dados_aluno_nome_matricula));
    CuSuiteAdd (suite, CuTestNew ("Excluir um usuario", teste_excluir_usuario));
    CuSuiteAdd (suite, CuTestNew ("Excluir um usuario ja deletado (inexistente)", teste_excluir_usuario_inexistente));
    CuSuiteAdd (suite, CuTestNew ("Checar dados usuario deletado", teste_checa_dados_usuario_deletado));

    //Testes com notas
    CuSuiteAdd (suite, CuTestNew ("Recuperar notas de um aluno", teste_recuperar_notas_aluno));
    CuSuiteAdd (suite, CuTestNew ("Recuperar notas de um professor", teste_recuperar_notas_professor));


    //////////////////////////
    /*
        Executa o conjunto de testes e apresenta os resultados.
    */

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

void teste_cadastrar_checar_usuario (CuTest *teste)
{
    bool resultado;
    int esperado = 1;

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

/*

void teste_checar_user_sem_arquivos (CuTest *teste)
{
    bool resultado1, resultado2, resultado3;
    int esperado = 1;
    string nome ("              m_user"); // um nome qualquer
    string matricula ("123456789"); // uma matricula qualquer
    string senha ("     12345"); // uma senha qualquer
    string disciplina ("       POO"); // uma disciplina qualquer
    char turma = 'A'; // uma turma qualquer
    Checar_user user;

    resultado1 = user.checar_user (nome, matricula, senha);
    resultado2 = user.checar_user (nome, matricula, senha, disciplina);
    resultado3 = user.checar_user (nome, matricula, senha, turma);

    if (!resultado1 && !resultado2 && !resultado3)
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_abrir_arquivo_inexistente (CuTest *teste)
{
    int esperado = 1;

    ArquivoExiste arq ("dados/Master.txt");

    if (arq.getExistencia ())
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
    else
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
}

void teste_inicializar_sistema (CuTest *teste)
{
    int esperado = 1;

    try
    {
        TestaSistema sistema;

        CuAssertIntEquals (teste, esperado, 0);
    }
    catch (InicializarSistema init)
    {
        ArquivoExiste arq ("dados/Master.txt");

        if (arq.getExistencia ())
        {
            CuAssertIntEquals (teste, esperado, 1);
        }
        else
        {
            CuAssertIntEquals (teste, esperado, 0);
        }
    }
}

void teste_checa_dados_usuario_Master (CuTest *teste)
{
    bool resultado;
    int esperado = 1;
    string nome ("              m_user");
    string matricula ("123456789");
    string senha ("     12345");
    Checar_user user;

    resultado = user.checar_user (nome, matricula, senha);

    if (resultado)
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_checa_dados_usuario_Master_errado (CuTest *teste)
{
    bool resultado;
    int esperado = 1;
    Checar_user user;

    resultado = user.checar_user ("              Jose A", "123456789", "     12345");

    if (!resultado)
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
}



void teste_checa_dados_aluno_nome_matricula (CuTest *teste)
{
    bool resultado;
    int esperado = 1;
    string nome_a ("              a_user");
    string matricula ("123456789");
    Checar_user user;

    resultado = user.checar_user (nome_a, matricula);

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
    bool resultado;
    int esperado = 1;

    //Cadastramos um novo usuario
    string nome_m ("            n_m_user");
    string nome_p ("            n_p_user");
    string nome_a ("            n_a_user");
    string matricula ("123456789");
    string senha ("     12345");
    string disciplina ("       POO");
    char turma = 'A';

    Cadastrar *master = new Cadastrar (nome_m, matricula, senha);
    Cadastrar *professor = new Cadastrar (nome_p, matricula, senha, disciplina);
    Cadastrar *aluno = new Cadastrar (nome_a, matricula, senha, turma);

    delete master;
    delete professor;
    delete aluno;

    //Checamos o novo usuario
    bool resultado1, resultado2, resultado3;
    Checar_user user;

    resultado1 = user.checar_user (nome_m, matricula, senha);
    resultado2 = user.checar_user (nome_p, matricula, senha, disciplina);
    resultado3 = user.checar_user (nome_a, matricula, senha, turma);

    //Vamos deletar o novo usuario
    if (resultado1 && resultado2 && resultado3)
    {
        Excluir_user usuario;

        resultado1 = usuario.excluir_user (nome_m, matricula, 1);
        resultado2 = usuario.excluir_user (nome_p, matricula, 2);
        resultado3 = usuario.excluir_user (nome_a, matricula, 3);

        //Usuario deletado com sucesso
        if (resultado1 && resultado2 && resultado3)
        {
            CuAssertIntEquals (teste, esperado, 1);
        }
        //Usuario nao deletado...
        else
        {
            CuAssertIntEquals (teste, esperado, 0);
        }
    }
    //Falha no cadastro ou na checagem
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_excluir_usuario_inexistente (CuTest *teste)
{
    bool resultado;
    int esperado = 1;

    //Cadastramos um novo usuario
    string nome_m ("            n_m_user");
    string nome_p ("            n_p_user");
    string nome_a ("            n_a_user");
    string matricula ("123456789");
    string senha ("     12345");
    string disciplina ("       POO");
    char turma = 'A';
    bool resultado1, resultado2, resultado3;

    Excluir_user usuario;

    resultado1 = usuario.excluir_user (nome_m, matricula, 1);
    resultado2 = usuario.excluir_user (nome_p, matricula, 2);
    resultado3 = usuario.excluir_user (nome_a, matricula, 3);

    if (!resultado1 && !resultado2 && !resultado3)
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_checa_dados_usuario_deletado (CuTest *teste)
{
    int esperado = 1;
    string nome_m ("            n_m_user");
    string nome_p ("            n_p_user");
    string nome_a ("            n_a_user");
    string matricula ("123456789");
    string senha ("     12345");
    string disciplina ("       POO");
    char turma = 'A';
    bool resultado1, resultado2, resultado3;
    Checar_user user;

    resultado1 = user.checar_user (nome_m, matricula, senha);
    resultado2 = user.checar_user (nome_p, matricula, senha, disciplina);
    resultado3 = user.checar_user (nome_a, matricula, senha, turma);

    if (!resultado1 && !resultado2 && !resultado3)
    {
        CuAssertIntEquals (teste, esperado, 1);
    }
    //Falha no cadastro ou na checagem
    else
    {
        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_recuperar_notas_aluno (CuTest *teste)
{
    int esperado = 1;
    string matricula ("123456789");
    int qnt_notas;
    Recupera_Notas *n = new Recupera_Notas ();

    qnt_notas = n->obter_conjunto_notas (matricula, " ");

    if (qnt_notas == 2)
    {
        Nota n1;
        Nota n2;

        n1 = n->obter_uma_nota ();
        n2 = n->obter_uma_nota ();

        if (n2.getDisciplina() == "       POO" && n2.getN1() == (float) 9.8 && n2.getN2 () == (float) -1.0 && n2.getN3 () == (float) 8.8 && n2.getN4 () == (float) 9.9 && n1.getDisciplina() =="       IDJ" && n1.getN1 () == (float) 8.0 && n1.getN2 () == (float) 8.0 && n1.getN3 () == (float) 7.0 && n1.getN4 () == (float) -1.0)
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
    else
    {
        delete n;

        CuAssertIntEquals (teste, esperado, 0);
    }
}

void teste_recuperar_notas_professor (CuTest *teste)
{
    int esperado = 1;
    string matricula ("123456789");
    string disciplina ("       POO");
    int qnt_notas;
    Recupera_Notas *n = new Recupera_Notas ();

    qnt_notas = n->obter_conjunto_notas (matricula, disciplina);

    if (qnt_notas == 1)
    {
        Nota n1;

        n1 = n->obter_uma_nota ();

        if (n1.getDisciplina() == "       POO" && n1.getN1() == (float) 9.8 && n1.getN2 () == (float) -1.0 && n1.getN3 () == (float) 8.8 && n1.getN4 () == (float) 9.9)
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
    else
    {
        delete n;

        CuAssertIntEquals (teste, esperado, 0);
    }
}

*/
