#include<stdio.h>
#include<stdlib.h>

//Listas 

typedef struct nodo{
    int valor;
    struct nodo *prox;
}Nodo;

typedef struct{
    Nodo *inicio;
    int tam;
}Lista;

void criar_lista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_no_inicio(Lista *lista, int num){
    Nodo *novo = malloc(sizeof(Nodo));

    if(novo){
        novo->valor = num;
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->tam++; //toda vez que fizer uma inserção incrementa esse campo tam em uma unidade
    }else  
        printf("Error ao alocar a memoria\n");
}

void inserir_no_fim(Lista *lista, int num){
    Nodo *aux, *novo = malloc(sizeof(Nodo));

    if(novo){
        novo->prox = num;
        novo->prox = NULL;

        if(lista->inicio==NULL)
            lista->inicio = novo;
        else{
            aux = lista->inicio; 
            while(aux->prox)
                aux = aux->prox;
                aux->prox = novo;
        }
        lista->tam++;
    }else 
        printf("Error ao alocar a memoria\n");
}

void inserir_no_meio(Lista *lista, int num, int ant){
    Nodo *aux, *novo = malloc(sizeof(Nodo));

    if(novo){
        novo->valor = num;

        if(lista->inicio == NULL){
            novo->prox = NULL;
            lista->inicio = novo;
        }else{
            aux = lista->inicio;
            while(aux->valor != ant && aux->prox)
                aux = aux->prox;
            novo->prox = aux->prox;
            aux->prox = novo;
        }
        lista->tam++;
    }else   
        printf("Error ao alocar a memoria\n");
}

/*inserir ordenado
void inserir_ordenado(Lista *lista, int num){
    Nodo *aux, *novo = malloc(sizeof(Nodo));

    if(novo){
        novo->valor = num; 
        if(lista->inicio == NULL){
            novo->prox = NULL;
            lista->inicio = novo;
        }
        else if(novo->valor < lista->inicio->valor){
            novo->prox = lista->inicio;
            lista->inicio = novo;
        }
        else{
            aux = lista->inicio;
            while(aux->prox && novo->valor > aux->prox->valor)
                aux = aux->prox;
            novo->prox = aux->prox;
            aux->prox = novo;
        }
        lista->tam++;
    }
    else
        printf("Error ao alocar a memoria\n");
}*/

Nodo *remover(Lista *lista, int num){
    Nodo *aux, *remover = NULL;

    if(lista->inicio){
        if(lista->inicio->valor == num){
            remover = lista->inicio;
            lista->inicio = remover->prox;
            lista->tam--;
        }
        else{
            aux = lista->inicio;
            while(aux->prox && aux->prox->valor != num)
                aux = aux->prox;
            if(aux->prox){
                remover = aux->prox;
                aux->prox = remover->prox;
                lista->tam--;
            }
        }
    }

    return remover; 
}




void imprimir(Lista lista){ //nao vai receber um ponteiro e sim a lista direto, se nao nao posso alterar na main
    Nodo *nodo = lista.inicio;  // . pois nao eh ponteiro, eh um elemento lista, uma copia. Elemento struct
    printf("\nLista tamanho %d: ",lista.tam);
    while(nodo){
        printf(" %d", nodo->valor);
        nodo = nodo->prox;
    }
    printf("\n\n");
}

int main(){

    int op, v, anterior; 
    Lista lista; 
    Nodo *removido;
    
    criar_lista(&lista);

    do{
        printf("\n\t0 - Sair\n\t1 - InserirI\n\t2 - InserirF\n\t3 - InserirM\n\t4 - InserirO\n\t5 - Remover\n\t6 - Imprimir\n");
        scanf("%d",&op);

        switch(op){
        case 1: 
            printf("Digte um valor: ");
            scanf("%d", &v);
            inserir_no_inicio(&lista, v);
            break;
        case 2:
            printf("Digite um valor: ");
            scanf("%d",&v);
            inserir_no_fim(&lista,v);
            break;
        case 3:
            printf("Digite um valor e o valor de referencia: ");
            scanf("%d, %d",&v,&anterior);
            inserir_no_meio(&lista, v, anterior);
            break;
        case 4:
            printf("Digite um valor: ");
            scanf("%d", &v);
            inserir_ordenado(&lista, v);
            break;
        case 5:
            printf("Digite um valor a ser removido: ");
            scanf("%d", &v);
            removido = remover(&lista, v);
            if(removido){
                printf("Elemento removido: %d\n", removido->valor);
                free(removido);
            }
            else
                printf("Elemento inexistente\n");
            break;
        case 6:
            imprimir(lista);
            break;
        default:
            if(op!=0)
                printf("operacao invalida\n");
        }
    }while(op!=0);

    return 0;
}
