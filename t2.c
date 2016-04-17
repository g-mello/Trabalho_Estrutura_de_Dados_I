
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct no{
    char nome[20];
    struct no *prox;
};

typedef struct no lista_c;

void inserir( lista_c *, char []);
lista_c *buscar( lista_c *, char[]);
void mostrar( lista_c *);
lista_c *remover( lista_c *, lista_c *, int );
void sorteio(lista_c *, int );

int main(void){

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
    while( p->prox != cabeca ){
        printf("%s ", p->nome);
    }
    printf("\n");
}

lista_c *remover( lista_c *cabeca, lista_c *inicio, int M){

   lista_c *p, *r;

   p=inicio;
   for( int i=0; i < M; i++){
        p = p->prox;
   } 

   if( p == cabeca)
       p = p->prox;

   if( p->prox == cabeca ){
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

void sorteio(lista_c *cabeca, int M){

    lista_c *p;

    p = cabeca->prox;
    do{
        p=remover(cabeca,p,M);

    }while( p != NULL );
}












