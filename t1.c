
//Project Name: Trabalho Estrutura de Dados 1 
//Authors: Guilherme Mello Oliveira, Caio Silva Poli 

#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define true 1
#define false 0

struct no{

    char nome[20];
    char rua[20];
    char numero[5];
    char cidade[20];
    char estado[20];

    struct no *prox;

};

typedef struct no no_t;

// Prototipos
no_t *criar_no(void);
void inserir(no_t **, no_t *);
void mostrar_lista(no_t *);
int remover( no_t **, char []);
no_t *pesquisar( no_t *, char []);
void continuar(int *);

int main(void){

    no_t *inicio, *cadastro;
    char nome[20];
    int controle, op;

    inicio=NULL;
    cadastro=NULL;

    // Menu
    controle=1;
    while( controle) {
        printf("============== Menu ============\n");
        printf("0. Sair \n");
        printf("1. Inserir \n");
        printf("2. Mostrar Nomes\n");
        printf("3. Pesquisar por Nome \n");
        printf("4. Remover por Nome \n");
        printf("Opção: ");

        __fpurge(stdin);
        scanf("%d", &op);

        switch(op){

            case 0: // Sair 
                controle = 0;
                break;

            case 1: // Inserir 

                inserir(&inicio, criar_no()); 
                system("clear");

                break;

            case 2: // Mostrar 
                if( inicio == NULL ){
                    printf("A lista está vazia.\n");
                    continuar(&controle);
                }
                
                else{
                    mostrar_lista(inicio);
                    continuar(&controle);
                }


                break;

            case 3: // Pesquisar 
                if( inicio == NULL ){
                    printf("A lista está vazia.\n");
                    continuar(&controle);
                }
                else{

                        printf("\nNome: ");
                        __fpurge(stdin);
                        fgets(nome,20,stdin);
                        cadastro = pesquisar(inicio,nome);

                        if( cadastro == NULL ){
                            printf("Nome não cadastrado.\n");
                            continuar(&controle);
                        }
                        else{
                            printf("Rua: %s Numero: %s", cadastro->rua, cadastro->numero);
                            printf("Cidade: %s Estado: %s", cadastro->cidade, cadastro->estado);
                            continuar(&controle);
                        }
                    }

                break;

            case 4: // Remover 
                if( inicio == NULL ){
                    printf("A lista está vazia.\n");
                    continuar(&controle);
                }
                else{
                    printf("Nome: ");
                    __fpurge(stdin); // limpa o buffer do teclado
                    fgets(nome,20,stdin);
                    nome[0]=toupper(nome[0]); 

                    if( remover(&inicio, nome) == true){
                        printf("Removido.\n");
                    }
                    else{
                        printf("Não está na lista.\n");
                    }
                    continuar(&controle);
                }
                break;

            default:
                printf("Erro, opção inválida.\n");
                continuar(&controle);
                break;

        }// end switch
    }// end while

	return 0;

}

no_t *criar_no(void){
    // Função para criar um novo nó para ser inserido na função inserir
    
    no_t *novo;

    // criar o novo nó
    if( (novo = calloc(1, sizeof(no_t))) == NULL )
        printf("Erro na alocação");
    else{

        // inicializar o novo nó
        
        printf("Nome: ");
        do{
            __fpurge(stdin); // Limpa o buffer do teclado LINUX
            fgets(novo->nome, 20, stdin);
            
            if( (novo->nome[0] >= 32 && novo->nome[0] <= 64) ||
               (novo->nome[0] >= 91 && novo->nome[0] <= 96 )){
                printf("Nome inválido.\nNome: ");
            } 

        // seleciona apenas caracteres [A-Z,a-z] para o primeiro caracter
        }while( (novo->nome[0] >= 32 && novo->nome[0] <= 64) ||
               (novo->nome[0] >= 91 && novo->nome[0] <= 96 )); 

       novo->nome[0]=toupper(novo->nome[0]);

        printf("Rua: ");
        do{

            __fpurge(stdin); // Limpa o buffer do teclado LINUX
            fgets(novo->rua, 20, stdin);

            if( (novo->rua[0] >= 32 && novo->rua[0] <= 64) ||
               (novo->rua[0] >= 91 && novo->rua[0] <= 96 )){
                printf("Rua inválida.\nRua: ");
            } 

        // seleciona apenas caracteres [A-Z,a-z] para o primeiro caracter
        }while( (novo->rua[0] >= 32 && novo->rua[0] <= 64) ||
               (novo->rua[0] >= 91 && novo->rua[0] <= 96 )); 


        printf("Numero: ");
        do{ 
            __fpurge(stdin); // Limpa o buffer do teclado LINUX
            fgets(novo->numero,5,stdin); 
            
            if( (atoi(novo->numero) <= 0)){
               printf("Número inválido.\nNumero:"); 
            }
        } 
        while( atoi(novo->numero) <= 0 ); // atoi converte string para inteiro

        printf("Cidade: ");
        do{
             __fpurge(stdin); // Limpa o buffer do teclado LINUX
             fgets(novo->cidade, 20, stdin);

             if( (novo->cidade[0] >= 32 && novo->cidade[0] <= 64) ||
               (novo->cidade[0] >= 91 && novo->cidade[0] <= 96 )){
                 printf("Cidade inválida.\nCidade: ");
             } 
             
        // seleciona apenas caracteres [A-Z,a-z] para o primeiro caracter
        }while( (novo->cidade[0] >= 32 && novo->cidade[0] <= 64) ||
               (novo->cidade[0] >= 91 && novo->cidade[0] <= 96 )); 

        printf("Estado: ");
        do{
            __fpurge(stdin); // Limpa o buffer do teclado LINUX
            fgets(novo->estado, 20, stdin);

            if( (novo->estado[0] >= 32 && novo->estado[0] <= 64) ||
               (novo->estado[0] >= 91 && novo->estado[0] <= 96 )){
                printf("Estado inválido.\nEstado: ");
            } 
        
        // seleciona apenas caracteres [A-Z,a-z] para o primeiro caracter
        }while( (novo->estado[0] >= 32 && novo->estado[0] <= 64) ||
               (novo->estado[0] >= 91 && novo->estado[0] <= 96 )); 

        novo->prox = NULL;
    }
    
    return novo;
}

void inserir(no_t **inicio, no_t *novo){
    // Função para inserir novo nó em uma lista já ordenada
    
    no_t *p;
    p = *inicio;

    // Verificar se o nome já foi cadastrado
    if( pesquisar(*inicio, novo->nome) != NULL ){
            printf("\n Erro: Nome já cadastrado.\n");
    }
    else{
    
        // A lista está vazia ou tem apenas o primeiro nome já é maior ou igual
        // que o novo nome
        if( p == NULL || ( strcmp(p->nome, novo->nome) >= 0 ) ){

            novo->prox = *inicio;
            *inicio = novo;
        }
        else{
            
            // Fazer p apontar para o nó onde o novo nó sera inserido antes
            p=*inicio;
            while( p->prox != NULL && strcmp(p->prox->nome, novo->nome) < 0 ) {
                p = p->prox;
            }

            // inserir o novo nó
            novo->prox =  p->prox;
            p->prox = novo;
        }
    }

}

void mostrar_lista( no_t *inicio){
    // Função para mostrar a lista

    no_t *p;
    p = inicio;

    printf("\nNomes:\n");
    while( p != NULL ){
        printf("%s", p->nome);
        p=p->prox;
    }

}

int remover( no_t **inicio, char nome[]){

    no_t *p, *aux; 

     // Transforma em uppercase a primeira letra do nome
     // para ter uma verificação consistente com os outros nomes na lista
     nome[0] = toupper(nome[0]);

     p = *inicio;
    // Remover primeira posição
    if( strcmp(p->nome,nome) == 0 ){

        *inicio = p->prox; 
        free(p);

        return true;

    }

    else{

        // Procurar a posição do nome na lista
        while( strcmp(nome, p->nome) != 0 && p->prox != NULL){
            p = p->prox;
        }

        // p está na ultima posição e nome não apareceu na lista
        if( p->prox == NULL && strcmp(nome,p->nome) !=0 ){

            return false;
        }

        // Remover última posição na lista e nome apareceu na lista
        else if( p->prox == NULL ){

            // fazer p apontar para o penultimo
            for(p=*inicio; p->prox->prox != NULL; p = p->prox); 

            free(p->prox);
            p->prox = NULL;

            return true;

        }

        // p está em qualquer posição no meio da lista 
        // remover esta posição
        else {

            // fazer p apontar para a posição anterior 
            aux = p; 
            for(p=*inicio; p->prox != aux; p = p->prox); 

            aux = p->prox->prox; 
            free(p->prox);
            p->prox = aux;

            return true;

        }
    }
}

no_t *pesquisar( no_t *inicio, char nome[]){

    no_t *p;

    if((p=calloc(1, sizeof(no_t))) == NULL){
        printf("Erro na alocação.\n");
        return NULL;
    }
    else{

        p = inicio;
        while( p != NULL && strcmp(p->nome, nome) != 0 ) {
            p = p->prox; 
        }
        
        if( p != NULL )
            return p;
        else
            return NULL;
    }
}

void continuar(int *controle){
    char continuar;

        printf("\nContinuar ? S/N: ");
        do{
            scanf("\n%c", &continuar);
            continuar = toupper(continuar);
            if( continuar != 'S' && continuar != 'N'){
                printf("\nValor inválido.\nDigite S para Sim, N para Não: ");
            }

        }while( continuar != 'S' && continuar != 'N');
        
        if(continuar == 'N')
            *controle = 0;

        system("clear");

}
