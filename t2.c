
//Project Name: Trabalho de Estrutura de Dados 1
//Authors: Guilherme Mello Oliveira, Caio Silva Poli

#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct no{
    char nome[20];
    struct no *prox;
};

typedef struct no lista_c;

void inserir( lista_c *, char []);
lista_c *buscar( lista_c *, char[]);
void mostrar( lista_c *);
lista_c *remover( lista_c *, lista_c *, int );
void sorteio(lista_c *, lista_c *, int );
void continuar(int *);


int main(void){

    lista_c *cabeca;

    if( (cabeca = calloc(1,sizeof(lista_c))) == NULL )
        printf("Erro na alocação.\n");
    else{
        cabeca->prox = cabeca;
    }

    char nome[20];
    int controle, op, M;

    controle=1;
    while(controle){
        printf("=========MENU============\n");
        printf("0.Sair \n");
        printf("1.Inserir \n");
        printf("2.Mostrar\n");
        printf("3.Sorteio\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch(op){
            case 0:
                controle = 0;
                break;

            case 1: // Inserir
                printf("Nome: ");
                __fpurge(stdin);
                fgets(nome,20,stdin);

                nome[0]=toupper(nome[0]);

                inserir(cabeca,nome);
                 __fpurge(stdin);
                continuar(&controle);
                break;

            case 2: // Mostrar
                if( cabeca->prox == cabeca ){
                    printf("A lista está vazia.\n");
                    __fpurge(stdin);
                    continuar(&controle);
                }
                else{
                    mostrar(cabeca);
                    __fpurge(stdin);
                    continuar(&controle);
                }
                break;

            case 3: // Sorteio
                if( cabeca->prox == cabeca ){
                    printf("A lista está vazia.\n");
                    __fpurge(stdin);
                    continuar(&controle);
                }
                else{
                    printf("Nome inicial: ");
                    do{

                     __fpurge(stdin);
                     fgets(nome,20,stdin);
                     nome[0]=toupper(nome[0]);

                     if( buscar(cabeca,nome) == NULL){
                         printf("Nome não está na lista.\n");
                         printf("Nome inicial: ");
                     }

                    }while( buscar(cabeca,nome) == NULL );

                    printf("M: ");
                    __fpurge(stdin);
                    scanf("%d", &M);

                    sorteio(cabeca, buscar(cabeca,nome),M);

                    __fpurge(stdin);
                    continuar(&controle);
                }

                break;

            default:

                printf("Opção inválida.\n");
                continuar(&controle);

                break;

        }// end while
    }// end while

    return 0;
}

void inserir( lista_c *cabeca, char nome[]){

    lista_c *p, *novo;

    if( buscar(cabeca, nome) != NULL ){
        printf("\nErro: Nome já inserido\n");
    }
    else{
        // fazer p apontar para a ultima posição
        p = cabeca->prox;
        while( p->prox != cabeca ){
            p = p->prox;
        }

        if( (novo = calloc(1,sizeof(lista_c))) == NULL )
            printf("Erro na alocação.\n");
        else{
            strcpy(novo->nome, nome);
            novo->prox = cabeca;
            p->prox = novo;
        }
    }
}

lista_c *buscar( lista_c *cabeca, char nome[]){
    lista_c *p;

    p=cabeca->prox;
    while( p != cabeca && strcmp(p->nome, nome) != 0){
        p = p->prox;
    }

    if( p == cabeca ){
        return NULL;
    }
    else{
        return p;
    }
}

void mostrar( lista_c *cabeca ){
    
    lista_c *p;
    p=cabeca->prox;

    printf("\nNomes: \n");
    while( p != cabeca ){
        printf("%s", p->nome);
        p = p->prox;
    }
}

lista_c *remover( lista_c *cabeca, lista_c *inicio, int M){

   lista_c *p, *r;

   // faz p rodar M vezes na lista
   p=inicio;

   if( p == cabeca ) // caso p aponte para cabeça durante o processo
       p = p->prox;

   for( int i=0; i < M; i++){
       if( p->prox == cabeca )
           p = p->prox->prox; 
       else
            p = p->prox;
   } 

   // caso p apontar para a cabeça da lista
   // passar para o próximo nó
   //if( p == cabeca)
    //   p = p->prox;

   // se somente sobrar um ou tiver somente um elemento na lista
   // Mostrar o ganhador
   if( p->prox == cabeca && cabeca->prox == p){
       printf("Ganhador da Viagem: %s", p->nome);
       p=cabeca;
       free(p->prox);
       p->prox = p;

       return NULL;
   }
   // Eliminar os nomes
   else{

        // faz r apontar para o anterior que p está apontando
        // para eliminar p
        r = cabeca->prox;
        while( r->prox != p ){
            r = r->prox;
        }

        r->prox = p->prox;
        printf("Eliminado: %s", p->nome);
        free(p);

        return r->prox;
   }
}

void sorteio(lista_c *cabeca, lista_c *inicio, int M){

    lista_c *p;

    // Remove todos os elementos da lista até que sobre
    // somente um elemento. Os elementos são retirados a partir do próximo 
    // nó do último elemento removido
    
    p=inicio;
    do{
        p=remover(cabeca,p,M);

    }while( p != NULL );
}


void continuar(int *controle){
    char continuar;

    printf("\nContinuar ? S/N: ");
    do{
        scanf("%c", &continuar);
        continuar = toupper(continuar);

        if( continuar != 'S' && continuar != 'N') 
            printf("\nValor inválido, digite S para Sim, N para Não: ");

    }while( continuar != 'S' && continuar != 'N'); 

    if( continuar == 'N')
        *controle = 0;

    system("clear");

}








