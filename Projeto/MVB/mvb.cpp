/**
* \mainpage Módulo de Vetor de Bits
*
* \brief Este módulo é responsável pelo gerenciamento de espacos livres, possibilitando o reuso de memoria.
*
* Nao sao usados bits, sao usados inteiros nos valores '0' ou '1'.
*
*/

#include <iostream>
#include <fstream>
#include "mvb.h"

#define SERVIDOR_MVB

/* Classes */
using namespace std;

/* Funções */
 //Inlcui um registro no arquivo desejado
int incluir_registro (int opcao)
{
    FILE *arquivo = 0;
    int sucesso;
    int posicao;

    switch (opcao)
    {
        case 1:
            posicao = obter_posicao_livre (opcao);

            //Arquivo inexistente ou não há posições livres
            if (posicao == -1 || posicao == -2)
            {
                arquivo = fopen ("dados/vetor_bits_master.txt", "a+");
                fprintf(arquivo, "1");

                fclose(arquivo);

                return -1;
            }
            //Inclusão do novo registro
            else
            {
                sucesso = alterar_status_registro (opcao, posicao, 1);

                return posicao;
            }
            break;

        case 2:
            posicao = obter_posicao_livre (opcao);

            //Arquivo inexistente ou não há posições livres
            if (posicao == -1 || posicao == -2)
            {
                arquivo = fopen ("dados/vetor_bits_professor.txt", "a+");
                fprintf(arquivo, "1");

                fclose(arquivo);

                return -1;
            }
            //Inclusão do novo registro
            else
            {
                sucesso = alterar_status_registro (opcao, posicao, 1);

                return posicao;
            }
            break;

        case 3:
            posicao = obter_posicao_livre (opcao);

            //Arquivo inexistente ou não há posições livres
            if (posicao == -1 || posicao == -2)
            {
                arquivo = fopen ("dados/vetor_bits_aluno.txt", "a+");
                fprintf(arquivo, "1");

                fclose(arquivo);

                return -1;
            }
            //Inclusão do novo registro
            else
            {
                posicao = obter_posicao_livre (opcao);

                sucesso = alterar_status_registro (opcao, posicao, 1);

                return posicao;
            }
            break;
        default:
            return -2;
            break;
    }
}

// Busca e retorna a primeira posicao livre no arquivo desejado
int obter_posicao_livre (int opcao)
{
    FILE *arquivo = 0;
    long int posicao = -1;
    int status;

    switch (opcao)
    {
        case 1:
            arquivo = fopen ("dados/vetor_bits_master.txt", "r");

            if (arquivo == 0)
            {
                return -2;
            }

            while (!feof (arquivo) && posicao == -1)
            {
               fscanf (arquivo, "%1d", &status);

               if (status == 0)
               {
                   posicao = ftell (arquivo);
                   posicao--;
               }
            }

            fclose (arquivo);
            break;
        case 2:
            arquivo = fopen ("dados/vetor_bits_professor.txt", "r");

            if (arquivo == 0)
            {
                return -2;
            }

            while (!feof (arquivo) && posicao == -1)
            {
               fscanf (arquivo, "%1d", &status);

               if (status == 0)
               {
                   posicao = ftell (arquivo);
                   posicao--;
               }
            }

            fclose (arquivo);
            break;
        case 3:
            arquivo = fopen ("dados/vetor_bits_aluno.txt", "r");

            if (arquivo == 0)
            {
                return -2;
            }

            while (!feof (arquivo) && posicao == -1)
            {
               fscanf (arquivo, "%1d", &status);

               if (status == 0)
               {
                   posicao = ftell (arquivo);
                   posicao--;
               }
            }

            fclose (arquivo);
            break;
        default:
            return -3;
            break;
    }

    // Retorno da primeira posição livre no arquivo. Se não houver nenhuma posição livre, retorna-se -1, que indica que deve-se abrir o arquivo desejado com o modo "a", que grava no final do arquivo
    return (int) posicao;
}

 // Altera o status (livre ou ocupado) de um registro
int alterar_status_registro (int opcao, long int posicao, int novo_status)
{
    FILE *arquivo = NULL;
    long int suporte;
    long int tam_arquivo = -1;

    //Checa se o valor passado é válido
    if (novo_status != 0 && novo_status != 1)
    {
        return -1;
    }

    switch (opcao)
    {
        case 1:
            arquivo = fopen ("dados/vetor_bits_master.txt", "r+");

            //Checa se o arquivo existe
            if (arquivo == 0)
            {
                return -2;
            }

            //Calcula o tamanho do arquivo
            while (!feof (arquivo))
            {
                fscanf (arquivo, "%1ld", &suporte);
                tam_arquivo++;
            }

            //Checa se a posição a ser checada existe no arquivo
            if (posicao > tam_arquivo)
            {
                return -3;
            }

            //Altera o status do registro
            fseek (arquivo, posicao, SEEK_SET);

            fprintf(arquivo, "%d", novo_status);
            break;
        case 2:
            arquivo = fopen ("dados/vetor_bits_professor.txt", "r+");

            //Checa se o arquivo existe
            if (arquivo == 0)
            {
                return -2;
            }

            //Calcula o tamanho do arquivo
            while (!feof (arquivo))
            {
                fscanf (arquivo, "%1ld", &suporte);
                tam_arquivo++;
            }

            //Checa se a posição a ser checada existe no arquivo
            if (posicao > tam_arquivo)
            {
                return -3;
            }

            //Altera o status do registro
            fseek (arquivo, posicao, SEEK_SET);

            fprintf (arquivo, "%d", novo_status);
            break;
        case 3:
            arquivo = fopen ("dados/vetor_bits_aluno.txt", "r+");

            //Checa se o arquivo existe
            if (arquivo == 0)
            {
                return -2;
            }

            //Calcula o tamanho do arquivo
            while (!feof (arquivo))
            {
                fscanf (arquivo, "%1ld", &suporte);
                tam_arquivo++;
            }

            //Checa se a posição a ser checada existe no arquivo
            if (posicao > tam_arquivo)
            {
                return -3;
            }

            //Altera o status do registro
            fseek (arquivo, posicao, SEEK_SET);

            fprintf(arquivo, "%d", novo_status);
            break;
        default:
            return -4;
            break;
    }

    fclose (arquivo);
    return 0;
}

// Checa o status de um registro (livre ou ocupado)
int obter_status (int opcao, long int posicao)
{
    FILE *arquivo = NULL;
    int status;
    long int suporte;
    long int tam_arquivo = -1;

    switch (opcao)
    {
        case 1:
            arquivo = fopen ("dados/vetor_bits_master.txt", "r");

            //Checa se o arquivo existe
            if (arquivo == 0)
            {
                return -1;
            }

            //Calcula o tamanho do arquivo
            while (!feof (arquivo))
            {
                fscanf (arquivo, "%1ld", &suporte);
                tam_arquivo++;
            }
            tam_arquivo--;

            //Checa se a posição a ser checada existe no arquivo
            if (posicao > tam_arquivo)
            {
                return -2;
            }

            //Busca o valor do registro
            fseek (arquivo, posicao, SEEK_SET);

            fscanf (arquivo, "%1d", &status);
            break;
        case 2:
            arquivo = fopen ("dados/vetor_bits_professor.txt", "r");

            //Checa se o arquivo existe
            if (arquivo == 0)
            {
                return -1;
            }

            //Calcula o tamanho do arquivo
            while (!feof (arquivo))
            {
                fscanf (arquivo, "%1ld", &suporte);
                tam_arquivo++;
            }

            //Checa se a posição a ser checada existe no arquivo
            if (posicao > tam_arquivo)
            {
                return -2;
            }

            //Busca o valor do registro
            fseek (arquivo, posicao, SEEK_SET);

            fscanf (arquivo, "%1d", &status);
            break;
        case 3:
            arquivo = fopen ("dados/vetor_bits_aluno.txt", "r");

            //Checa se o arquivo existe
            if (arquivo == 0)
            {
                return -1;
            }

            //Calcula o tamanho do arquivo
            while (!feof (arquivo))
            {
                fscanf (arquivo, "%1ld", &suporte);
                tam_arquivo++;
            }

            //Checa se a posição a ser checada existe no arquivo
            if (posicao > tam_arquivo)
            {
                return -2;
            }

            //Busca o valor do registro
            fseek (arquivo, posicao, SEEK_SET);

            fscanf (arquivo, "%1d", &status);
            break;
        default:
            return -3;
            break;
    }

    fclose (arquivo);
    return status;
}
