//MÓDULO DE VETOR DE BITS
#include <iostream>
#include <fstream>
#include "mvb.h"

#define SERVIDOR_MVB

/* Classes */
using namespace std;

//Construtor (seta o nível de usuário)
Registro::Registro (int n)
{
    this->nivel = n;
    this->posicao = -10;
    this->status = -1;
}

//Seta a posicao do registro
void Registro::setPos (long int p)
{
    this->posicao = p;

    this->status = this->obter_status ();
}

//Retorna a posicao
long int Registro::getPos ()
{
    return this->posicao;
}

//Retorna o status do registro
int Registro::getStatus ()
{
    return this->status;
}

 //Inlcui um registro no arquivo desejado
int Registro::incluir_registro ()
{
    FILE *arquivo = 0;
    int sucesso;

    switch (this->nivel)
    {
        case 1:
            this->posicao = this->obter_posicao_livre ();

            //Arquivo inexistente ou não há posições livres
            if (this->posicao == -1 || this->posicao == -2)
            {
                arquivo = fopen ("dados/vetor_bits_master.txt", "a+");
                fprintf(arquivo, "1");

                fclose(arquivo);

                this->posicao = -1;
                return this->posicao;
            }
            //Inclusão do novo registro
            else
            {
                sucesso = this->alterar_status_registro (1);

                return 0;
            }
            break;

        case 2:
            this->posicao = this->obter_posicao_livre ();

            //Arquivo inexistente ou não há posições livres
            if (this->posicao == -1 || this->posicao == -2)
            {
                arquivo = fopen ("dados/vetor_bits_professor.txt", "a+");
                fprintf(arquivo, "1");

                fclose(arquivo);

                this->posicao = -1;
                return this->posicao;
            }
            //Inclusão do novo registro
            else
            {
                sucesso = this->alterar_status_registro (1);

                return 0;
            }
            break;

        case 3:
            this->posicao = this->obter_posicao_livre ();

            //Arquivo inexistente ou não há posições livres
            if (this->posicao == -1 || this->posicao == -2)
            {
                arquivo = fopen ("dados/vetor_bits_aluno.txt", "a+");
                fprintf(arquivo, "1");

                fclose(arquivo);

                this->posicao = -1;
                return this->posicao;
            }
            //Inclusão do novo registro
            else
            {
                this->posicao = this->obter_posicao_livre ();

                sucesso = this->alterar_status_registro (1);

                return 0;
            }
            break;
        default:
            return -2;
            break;
    }
}

// Busca e retorna a primeira posicao livre no arquivo desejado
int Registro::obter_posicao_livre ()
{
    FILE *arquivo = 0;
    long int p = -1;
    int status;

    switch (this->nivel)
    {
        case 1:
            arquivo = fopen ("dados/vetor_bits_master.txt", "r");

            if (arquivo == 0)
            {
                return -2;
            }

            while (!feof (arquivo) && p == -1)
            {
               fscanf (arquivo, "%1d", &status);

               if (status == 0)
               {
                   p = ftell (arquivo);
                   p--;
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

            while (!feof (arquivo) && p == -1)
            {
               fscanf (arquivo, "%1d", &status);

               if (status == 0)
               {
                   p = ftell (arquivo);
                   p--;
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

            while (!feof (arquivo) && p == -1)
            {
               fscanf (arquivo, "%1d", &status);

               if (status == 0)
               {
                   p = ftell (arquivo);
                   p--;
               }
            }

            fclose (arquivo);
            break;
        default:
            return -3;
            break;
    }

    // Retorno da primeira posição livre no arquivo. Se não houver nenhuma posição livre, retorna-se -1, que indica que deve-se abrir o arquivo desejado com o modo "a", que grava no final do arquivo
    this->posicao = p;
    this->status = 0;
    return (int) p;
}

 // Altera o status (livre ou ocupado) de um registro
int Registro::alterar_status_registro (int novo_status)
{
    FILE *arquivo = NULL;
    long int suporte;
    long int tam_arquivo = -1;

    //Checa se o valor passado é válido
    if (novo_status != 0 && novo_status != 1)
    {
        return -1;
    }

    switch (this->nivel)
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
int Registro::obter_status ()
{
    FILE *arquivo = NULL;
    int status;
    long int suporte;
    long int tam_arquivo = -1;

    switch (this->nivel)
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
