/*ESTE PROGRAMA ESCRITO NA LINGUAGEM C RECEBE UM ARQUIVO NO 
FORMATO .DIN IMPRIME O TOTAL DE ACESSOS À MEMÓRIA, O NUMERO 
DE ACESSO ÀS INTRUÇÕES, O NUMERO DE ACESSO AOS DADOS, 
O NUMERO DE LEITURAS E O NÚMERO DE ESCRITAS REALIZADAS*/

/*Bibliotecas utilizadas*/
#include <stdio.h>
#include <string.h>

int main() {    
    
    int finalizar = 0; /*Variável de inicialização 0 = programa continua, 1 = finaliza programa*/
    printf("Olá, seja bem vindo! Este programa analisa arquivos no formato .din.\n");
    printf("O arquivo a ser lido deve estar no mesmo diretório deste programa.\n");
    printf("Evite nomes de arquivo com espaços.\n");
    
    while(finalizar == 0) {
        /*Informações do arquivo*/
        FILE *arquivo;
        char nomeDoArquivo[264];
        char *extensao;
        char *tipoDeAcesso; /*0 == Leitura, 1 == Escrita, 2 == Busca*/
        char *endereco; /*Conjunto de Bytes Endereçáveis pelo processador*/
        char *sobra;
        char acessoValido;
        char conteudoDaLinha[BUFSIZ]; /*Conteúdo por linha */
        int linhasLidas = 0;
        int leituras = 0;
        int escritas = 0;
        int buscas = 0;        

        /*Obter o nome do arquivo a ser analisado*/
        printf("Digite o nome do arquivo a ser lido (diferencie letras maiusculas/minúsculas).\n");
        scanf("%s", nomeDoArquivo);
       
        /*Verificar se a extensão existe no nome do arquivo*/
        extensao = strstr(nomeDoArquivo, ".din");
        if(extensao == NULL){
            strcat(nomeDoArquivo, ".din");
        }
        /*Abrir arquivo*/ 
        arquivo = fopen(nomeDoArquivo,"r");

        /*Se o arquivo não for encontrado*/
        if(arquivo == NULL){
            printf("Erro ao abrir o arquivo, verifique o nome inserido (diferencie letras maiúsculas e minúsculas) e se o arquivo está no mesmo diretório do programa.\n");
            printf("Caso o nome do arquivo tenha espaços, remova eles e tente novamente.\n");
            printf("Tentar novamente - Digite 0, Finalizar o programa - Digite 1.\n");
            scanf("%d", &finalizar);
            
            /*Se o usuário desejar tentar abrir o arquivo novamente, repetir processo*/
            if(finalizar == 0){
                printf("Insira o nome (caso esteja no mesmo diretório) ou o caminho do arquivo no formato .din que você deseja saber informações.\n");
                scanf("%s", nomeDoArquivo);
                if(extensao == NULL){
                    strcat(nomeDoArquivo, ".din");
                    arquivo = fopen(nomeDoArquivo,"r");
                }
                /*Caso o arquivo não seja encontrado novamente mostrar erro e encerrar programa*/
                arquivo = fopen(nomeDoArquivo,"r");
                if(arquivo == NULL){
                    perror("Não foi possível abrir seu arquivo, verifique o nome ou diretório.\nPrograma finalizado");
                    return -1;
                }
            /*Ou se usuário desejar, parar programa*/
            } else {
                printf("Programa finalizado.\n");
                return 0;
            }
        }        

        while(fgets(conteudoDaLinha, BUFSIZ, arquivo) != NULL ){
            /*Em cada linha separar o tipo de acesso e o endereço de memória*/
            linhasLidas += 1;
            tipoDeAcesso = strtok(conteudoDaLinha, " ");
            endereco = strtok(NULL, " ");
            sobra = strtok(NULL, " ");
            /*Se chegar no final do arquivo não fazer mais leituras (break)*/
            if(tipoDeAcesso == NULL && endereco == NULL){
                break;
            }
            /*Verificar se o tipo de acesso é valido ou não*/
            if(tipoDeAcesso[0] == '0' || tipoDeAcesso[0] == '1' || tipoDeAcesso[0] == '2'){
                acessoValido = '1';
            } else {
                acessoValido = '0';
            }
            /*Se houver mais de dois campos (haverá um campo de sobra)*/
            if (acessoValido == '1' && sobra != NULL){
                printf("LINHA %d INVÁLIDA COM MAIS DE 2 CAMPOS!!!!!\n", linhasLidas);
            }
            /*Ou então se houver apenas um campo*/
            else if(acessoValido == '1' && endereco == NULL){
                printf("LINHA %d INVÁLIDA COM APENAS UM CAMPO!!!!!\n", linhasLidas);
            }
            /*Ou então se a linha estiver vazia*/
            else if(acessoValido == '0' && endereco == NULL){
                printf("LINHA %d COM FORMATO INVÁLIDO!!!!!\n", linhasLidas);
            }
             /*Ou então se o tipo de acesso for inválido*/
            else if(acessoValido == '0' && endereco != NULL){
                printf("LINHA %d COM FORMATO INVÁLIDO!!!!!\n", linhasLidas);
            }
            /*Ou então se não caso nenhum erro tenha ocorrido incrementar leitura na memória*/
            else if(tipoDeAcesso[0] == '0' && endereco != NULL){
                leituras += 1;
            }
            /*Ou então se não for leitura incrementar escrita na memória*/
            else if(tipoDeAcesso[0] == '1' && endereco != NULL){
                escritas += 1;
            }
            /*Ou então se não for uma leitura e nem uma escrita incrementar busca na memória*/
            else if(tipoDeAcesso[0] == '2' && endereco != NULL){
                buscas += 1;
            }
            /*Se nenhuma das sentenças forem satisfeitas*/
            else{
                printf("OCORREU UM ERRO NA LEITURA DO SEU ARQUIVO NA LINHA: %d\n", linhasLidas);
                printf("Programa finalizado!");
                return -1;
            }
        }
        /*Saída das informações ao usuário*/
        printf("\tInformações do arquivo \"%s\": \n\t", nomeDoArquivo);
        printf("- Total de Acessos à memória:     %d.\n\t", leituras + escritas + buscas);
        printf("- Acessos aos Dados na memória:   %d.\n\t", escritas + leituras);
        printf("- Leituras realizadas na memória: %d.\n\t", leituras);
        printf("- Escritas realizadas na memória: %d.\n\t", escritas);
        printf("- Buscas realizadas na memória:   %d.\n\t\n", buscas);

        /*Fechar arquivo*/
        fclose(arquivo);
        
        /*Verificar se o usuário deseja executar outra operação*/
        printf("Deseja ter informações sobre outro arquivo .din? SIM - Digite 0, NÃO - Digite 1\n");
        scanf("%d", &finalizar);
    }
    printf("Programa finalizado.\n");
    return 0;
}