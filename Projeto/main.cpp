/**
* \mainpage Projeto de Programação Orientada a Objetos
*
* \brief Projeto para a matéria de POO, 2012/2.
*
* \paragraph <Arquitetura>
* O estilo arquitetural seguido no sistema é o de Layers.
*
* \paragraph <Arquitetura>
* Há 4 (quatro) camadas na hierarquia:
*
* \paragraph <Arquitetura>
* - MIU (Módulo de Interface com o Usuário): é o módulo responsável por se comunicar com os usuários pela tela do computador e, também, por receber
* os dados digitados. Ainda, tem a responsabilidade de padronizar os dados para poder utilizá-los nas outras camadas. É cliente do MP.
*
* \paragraph <Arquitetura>
* - MP (Módulo de Persistência): é o módulo responsável por manter a integridade dos dados. Define as principais classes do sistema, que definem
* os tipos de usuários. Este módulo recebe as requisições do MIU e retorna os dados requisitados e executa cadastros e exclusões.
* é servidor do MIU e cliente do MGD. Obs.: o método "imprimir_notas" da classe "Notas" caracteriza uma quebra da hierarquia, mas este método
* ainda será alterado e este defeito corrigido. Desconsiderar os métodos "esc ()" nas classes de usuários, pois estes são métodos utilizados para
* teste e serão removidos ao final do desenvolvimento.
*
* \paragraph <Arquitetura>
* - MGD (Módulo de Gerenciamento de Dados): faz o acesso direto aos arquivos contendo os dados. Lê, escreve e altera os registros e retorna os dados
* requisitados pelo MP. Para saber o estado dos registros (se foi deletado ou não), solicita-se informações do MVB. É servidor do MP e cliente do MVB.
*
* \paragraph <Arquitetura>
* - MVB (Módulo de Vetor de Bits): é responsável pelo gerenciamento e reaproveitamento de espaços livres. Gerencia os arquivos que indicam se um registro
* foi deletado ou não. Basicamente, tem a função de alterar, criar, ler e retornar o estado de um determinado registro. É servidor do MGD.
* Apesar do nome, sua implementação não foi feita com bits de verdade; mas, com inteiros '0' e '1' que fazem o papel de bits.
*
* \paragraph <Design>
* Restrições de Design: na aplicação final, não será permitido que outro módulo se comunique diretamente com o usuário, além do MIU. Os únicos módulos que devem
* acessar arquivos são o MGD (exclusivamente arquivos de dados) e o MVB (exclusivamente arquivos de vetores de bits).
*
* \paragraph <Design>
* É importante seguir o contrato estabelecido com o usuário para a entrada dos dados:
*
* - Nome: tem tamanho máximo de 20 caracteres;
*
* - Matricula: tem tamanho máximo de 9 caracteres;
*
* - Senha: tem tamanho máximo de 10 caracteres;
*
* - Disciplina: tem tamanho máximo de 10 caracteres;
*
* - Turma: deve ter o tamanho exato de 1 caracter.
*
* No desenvolvimento, foi buscado o tratamento de erros (desobediência) na entrada destes dados, porém não garantimos que a quebra dessas regras seja sempre tratada sem problemas.
* Erros podem ocorrer.
*
* \paragraph <Pastas>
* Os arquivos que representam cada módulo estão dentro de um diretório que possui o nome do próprio módulo. Ainda, é importante consultar o arquivo LEIAME
* no diretório raiz do projeto.
*
*/
#include "MIU\miu.h"

using namespace std;

int main(int argc, char** argv)
{
    interface_usuario tela;

    return 0;
}

