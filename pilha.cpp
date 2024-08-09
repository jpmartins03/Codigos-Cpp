#include <stdio.h>
#include <iostream>

class Celula 
{
  friend class Pilha;

public:
  void escrever (const char *sep =", ");
  Celula(int chave);
  Celula();

private:
  int chave;
  Celula *prox;

};

class Pilha
{
public:
  void empilhar(int chave);
  int desempilhar (void);
  void escrever ();
  bool vazia (void);
  Pilha ();
  ~Pilha();

private:
  Celula *topo;
};

int main (void)
{
  Pilha p;

  for(int i = 0; i < 10; i++)
  {
    printf("Digite o valor a ser empilhado: ");
    int x;
    std::cin >> x;
    p.empilhar(x);
  }

  printf("-----------------------------------------------------------------\n");
  p.escrever();
  printf("-----------------------------------------------------------------\n");

  bool y;
  while(y)
  {
    printf("Pressione D para desempilhar e S para sair: ");

    std::string z;
    std::cin >> z;
    printf(Z);
    if(z == "D")
    {
      p.desempilhar();
    }
    else
    {
      y != y;
    }
  }

  printf("A chave desempilhada foi: %d.\n", p.desempilhar());
  p.escrever();

  return 0;
}

void Celula::escrever (const char *sep)
{
  printf("%d%s", this->chave, sep);
}

Celula::Celula(int chave)
{
  this->chave = chave;
  this->prox = NULL;
}

/* // Posso fazer o construtor dessa forma...
   Celula::Celula(int chave) :
   chave(chave);
   prox(NULL);
   {
   //posso fazer outras coisas aqui, outros comandos.
   }
*/

//para a cabeça
Celula::Celula()
{
  this->prox = NULL;
}

void Pilha::empilhar (int chave)
{
  Celula *c = new Celula(chave);

  c->prox = topo->prox;
  topo->prox = c;
}

int Pilha::desempilhar (void)
{
  int chave;
  Celula *p;

  p = topo->prox;

  topo->prox = p->prox;

  chave = p->chave;
  delete p;

  return chave;
}

Pilha::Pilha ()
{
  topo = new Celula();
}

void Pilha::escrever (void)
{
  Celula *p;

  for (p = topo->prox; p!= NULL; p = p->prox)
    if (p->prox == NULL)
      p->escrever("\n");
    else
      p->escrever();
}

Pilha::~Pilha ()
{
  /*
    Celula *p = topo->prox;

    while (p != NULL)
    {
    delete topo;
    topo = p;
    p = p->prox;
    }
    delete topo;
  */

  while(!vazia())
    desempilhar();
  delete topo;

}

bool Pilha::vazia (void)
{
  return topo->prox == NULL ? true : false;
}