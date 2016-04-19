
//Project Name: Trabalho de Estrutura de Dados 1
//Authors: Guilherme Mello Oliveira, Caio Silva Poli

#include<stdio.h>
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
        printf("=========MENU============");
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

            case 1:
                printf("Nome: ");
                scanf("%s", &nome);
                inserir(cabeca,nome);
                break;

            case 2:
                if( cabeca->prox == cabeca ){
                    printf("A lista está vazia.\n");
                    continuar();
                }
                else{
                    mostrar(cabeca);
                    continuar();
                }
                break;

            case 3:
                if( cabeca->prox == cabeca ){
                    printf("A lista está vazia.\n");
                    continuar();
                }
                else{
                    printf("Nome inicial: ");
                    do{

                     scanf("%s", &nome);
                     if( buscar(cabeca,nome) == NULL)
                         printf("Nome não está na lista.\n");

                    }while( buscar(cabeca,nome) == NULL );

                    printf("M: ");
                    scanf("%d", &M);
                    sorteio(cabeca, buscar(cabeca,nome),M);
                    continuar();
                }

                break;
            default:
                printf("Opção inválida.\n");
                continuar();
                break;

        }// end while
    }// end while

    return 0;
}

void inserir( lista_c *cabeca, char nome[]){

    lista_c *p, *novo;

    if( buscar(cabeca, nome) != NULL ){
        printf("Erro: Nome já inserido");
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

    printf("Lista: ");
    while( p != cabeca ){
        printf("%s ", p->nome);
        p = p->prox;
    }
    printf("\n");
}

lista_c *remover( lista_c *cabeca, lista_c *inicio, int M){

   lista_c *p, *r;

   // faz p rodar M vezes na lista
   p=inicio;
   for( int i=0; i < M; i++){
        p = p->prox;
   } 

   // caso p acabe pontando para a cabeça da lista
   if( p == cabeca)
       p = p->prox;

   // se somente sobrar um elemento na lista
   if( p->prox == cabeca && cabeca->prox == p){
       printf("Ganhador da Viagem: %s\n", p->nome);
       return NULL;
   }
   else{

        r = cabeca->prox;
        while( r->prox != p ){
            r = r->prox;
        }

        r->prox = p->prox;
        printf("Eliminado: %s\n", p->nome);
        free(p);

        return r->prox;
   }
}

void sorteio(lista_c *cabeca, lista_c *inicio, int M){

    lista_c *p;
    p=inicio;
    do{
        p=remover(cabeca,p,M);

    }while( p != NULL );
}

void continuar(void){
    char continuar;

    printf("\nContinuar ? S/N: ");
    do{
        scanf("%c", &continuar);
        continuar = toupper(continuar);
    }while( continuar != 'S' && continuar != 'N'); 
    system("clear");

}








