#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int Valor;
  struct No *prox;
} t_no;

typedef struct {
  t_no *topo;
  int size;
} t_pilha;

void desenharBloco(int i) {
  printf("  _______\n");
  printf(" /      /|\n");
  printf("/______/ |\n");
  printf("|      | |\n");
  printf("|  [%d] | /\n", i);
  printf("|______|/ ");

  printf("\n");
}

int menu() {
    int escolha;
  
    printf("\nMenu:\n");
    printf("1. Jogar\n");
    printf("2. Regras\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    return escolha;
}

t_no *criarNo(int num) {
  t_no *novo_no = malloc(sizeof(t_no));
  if(novo_no) {
    novo_no->Valor = num;
    novo_no->prox = NULL;
  }
  return novo_no;
}

// a) Escreva uma função push para inserir um novo nó no topo da pilha.
void push(t_pilha *pilha, int num) {
  if(!pilha) { // pilha == NULL
    fprintf(stderr, "Pilha inválida!\n");
    return;
  }
  t_no *novo_no = criarNo(num);
  if(!novo_no) {
    fprintf(stderr, "Erro ao criar novo nó!\n");
    return;
  }
  t_no *topo = pilha->topo;
  pilha->topo = novo_no;
  novo_no->prox = topo;
  pilha->size++;
}

// b) Escreva uma função pop para remover um nó do topo da pilha, devendo liberá-lo da memória e, posteriormente, retornar o valor do nó removido.
int pop(t_pilha *pilha) {
  if(!pilha) { // pilha == NULL
    fprintf(stderr, "Pilha inválida!\n");
    return 0;
  }
  if(pilha->size == 0) {
    fprintf(stdout, "Pilha vazia!\n");
    return 0;
  }

  int topo = pilha->topo->Valor;
  t_no *no_topo = pilha->topo;
  pilha->topo = no_topo->prox;
  free(no_topo);
  pilha->size--;
  return topo;
}

void imprimirpilha(t_pilha *pilha) {
  t_no *aux = pilha->topo;
  while(aux) {
    desenharBloco(aux->Valor);

    aux = aux->prox;
    }
}

int isEmpty(t_pilha *stack) {
    return stack->topo == 0;
}

void movedisco(t_pilha *pilhaorigem, t_pilha *pilhadestino) {
   if (isEmpty(pilhaorigem)) {
      printf("Movimento invalido, tente novamente\n");
      return;
    }

    if (!isEmpty(pilhadestino) && pilhaorigem->topo->Valor > pilhadestino->topo->Valor) {
      printf("Movimento invalido, tente novamente\n");
      return;
    }

    int disco = pop(pilhaorigem);
    push(pilhadestino, disco);
  }

void limparTela() {
    for (int i = 0; i < 100; i++) {
        printf("\n");
    }
}

int main(void) {

  int opcao, numDiscos;

  do {
      opcao = menu();
       limparTela();

      switch (opcao) {
          case 1:
              printf("Digite o número de discos (máx. 10): ");
              scanf("%d", &numDiscos);
              if (numDiscos < 1 || numDiscos > 10) {
                  printf("Número de discos inválido.\n");
              } else {
                  // Inicialização das pilhas
                  t_pilha pilha1 = {NULL, 0};
                  t_pilha pilha2 = {NULL, 0};
                  t_pilha pilha3 = {NULL, 0};

                  // Preencher a primeira pilha com discos
                  for(int i = numDiscos; i > 0; i--) {
                      push(&pilha1, i);
                  }

                  int origem, destino;
                  // Lógica do jogo
                  while(1) {

                      printf("Pilha 1: ");
                      printf("\n");
                      imprimirpilha(&pilha1);
                      printf("\n");
                      printf("\n");
                       printf("Pilha 2: ");
                      printf("\n");
                      imprimirpilha(&pilha2);
                       printf("\n");
                      printf("\n");
                       printf("Pilha 3: ");
                      printf("\n");
                      imprimirpilha(&pilha3);
                       printf("\n");
                      printf("\n");
                          printf("Digite a haste de origem e destino (1, 2 ou 3, 0 para sair): ");
                    scanf("%d %d", &origem, &destino);
                      if (origem == 0 || destino == 0) {
                        printf("Saindo do programa...");
                        break;
                      }

                     if(origem == destino) {
                       printf("Movimento invalido");
                       break;
                     }
                      else{

                        if(origem == 1 && destino == 2)
                          movedisco(&pilha1, &pilha2);
                        if(origem == 1 && destino == 3)
                          movedisco(&pilha1, &pilha3);
                        if(origem == 2 && destino == 1)
                             movedisco(&pilha2, &pilha1);
                        if(origem == 2 && destino == 3)
                             movedisco(&pilha2, &pilha3);
                        if(origem == 3 && destino == 1)
                           movedisco(&pilha3, &pilha1);
                        if(origem == 3 && destino == 2)
                           movedisco(&pilha3, &pilha2);
                      } 

                    }
                  }

              break;
          case 2:
              printf("\n\nA torre de Hanoi e um jogo onde existem tres torres e n discos.\n");
              printf("O objetivo do jogo e mover todos os discos da primeira para a\n");
              printf("ultima torre, utilizando a restante como torre auxiliar, seguindo\n");
              printf("as seguintes regras:\n");
              printf("   1. Apenas um disco pode ser movido de cada vez.\n");
              printf("   2. Cada movimento consiste de tirar o disco do topo\n");
              printf("      de uma das torres e posiciona-lo no topo de outra\n");
              printf("   3. Nenhum disco pode ser posicionado acima de um disco menor.\n\n");

              break;
          case 3:
              printf("Saindo do programa...\n");
              break;
          default:
              printf("Opção inválida. Por favor, tente novamente.\n");
      }
  } while (opcao != 3);


  // adicionar elementos


  return 0;
} 

