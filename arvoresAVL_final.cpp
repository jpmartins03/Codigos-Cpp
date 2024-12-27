/**************************************************
 *
 * João Pedro Martins Montera, Lucas Rocha Liz
 * Trabalho 2
 * Professor(a): Fábio Henrique Viduani Martinez
 *
 */

//****************************************************TO-DO LIST***********************************************************/

// FEITO
/*1. União de Árvores AVL: desenvolva um algoritmo que, dadas duas árvores AVL T1 e T2,
realize a união de ambas, devolvendo uma nova árvore AVL T3 que contenha todos os elementos de T1 e T2, sem repetições.

//FEITO
2. Interseção de Árvores AVL: implemente um algoritmo que, dadas duas árvores AVL T1 e
T2, devolva uma nova árvore AVL T3 que contenha apenas os elementos presentes em ambas
as árvores T1 e T2.*/

// FEITO
/*3. Busca em Intervalo: Implemente um algoritmo que, dada uma árvore AVL T, devolva todo
os elementos cujos valores estejam dentro de um intervalo definido por dois valores A e B.*/

//************************************************************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
using std::string;

int MAX = 100;

int *chaves_intersec(int *chaves1, int *chaves2, int n1, int n2, int &count);

// Definição da classe Nó
//===========================================================================================================================================//
class No
{
  friend class AVL;

public:
  No(const int chave);

  void escreve(const char *sep = "");
  inline bool eh_raiz();         // retorna true se nó é raiz
  inline bool eh_direito();      // retorna true se nó é filho direito
  inline bool eh_esquerdo();     // retorn true se nó é filho esquerdo
  inline int bal();              // calcula e retorna o fator de balanceamento
  inline void atualiza_altura(); // recalcula a altura com base nas alturas dos filhos

  // Getters
  int getChave() const { return chave; }
  No *getEsq() const { return esq; }
  No *getDir() const { return dir; }

  // Setters (opcional, se precisar alterar os atributos)
  void setEsq(No *novoEsq) { esq = novoEsq; }
  void setDir(No *novoDir) { dir = novoDir; }

private:
  int chave;
  int altura; // consideramos altura das folhas co mo 0
  No *pai;
  No *esq;
  No *dir;
};
//===========================================================================================================================================//

// Definição da classe AVL
//===========================================================================================================================================//
class AVL
{
public:
  // funções que escrevem a arvore e constutores
  //-------------------------------------------------------------------------------------------------------------------------------------------//
  AVL();                            // construtor vazio
  AVL(const AVL &outro);            // construtor de cópia (cria uma cópia de uma arvore AVL)
  ~AVL();                           // destrutor (libera a memória alocada pela arvore)
  AVL &operator=(const AVL &outro); // operador de atribuição (atribui o estado de uma arvore AVL à outra)

  // funções de construção
  //-------------------------------------------------------------------------------------------------------------------------------------------//
  void escreve_ordenado(No *x); // escreve em percurso em-ordem
  void escreve_ordenado();
  void escreve(const string &prefixo, No *x); // desenha a arvore
  void escreve();

  // funções de busca
  //-------------------------------------------------------------------------------------------------------------------------------------------//
  No *get_raiz();                                               // devolve a raiz
  No *busca(int k);                                             // devolve o ponteiro para um elemento, se achar, ou NULL
  No *minimo();                                                 // devolve o menor elemento da árvore
  No *maximo();                                                 // devolve o maior elemento da árvore
  No *sucessor(No *x);                                          // devolve o sucessor de um elemento
  No *predecessor(No *x);                                       // devolve o predecessor de um elemento
  int *coleta_chaves(int &tamanho);                             // Retorna todas as chaves em um array
  void coleta_chaves_recursivo(No *no, int *array, int &index); // Método auxiliar para coleta de chaves
  int conta_nos(No *no);
  int *busca_intervalo(No *raiz, int min, int max, int &size);

  // funções de manipulação de dados
  //-------------------------------------------------------------------------------------------------------------------------------------------//
  void insere(int chave); // insere uma chave
  bool remove(int chave); // remove uma árvore
  void limpa();           // remove todos elementos da árvore

private:
  No *raiz;

  // funções de busca
  //-------------------------------------------------------------------------------------------------------------------------------------------//
  No *busca(No *x, int k); // chamada recursiva inicial para a raiz
  No *minimo(No *x);       // devolve o mínimo a partir de um nó
  No *maximo(No *x);       // devolve o máximo a partir de um nó

  // funções de manipulação de dados
  //-------------------------------------------------------------------------------------------------------------------------------------------//
  void transplante(No *u, No *v); // transplante de um nó v para um nó u, não altera filhos
  void insere(No *z);             // insere um nó z na árvore
  void remove(No *z);             // remove um nó z da árvore
  void limpa(No *x);              // remove recursivamente todos elementos abaixo do nó e deleta x
  void copia(const AVL &T);       // copia uma árvore T para a atual a partir da raiz, usada no construtor de cópia e no operador de atribuição
  void copia(No *dest, No *orig); // copia um nó e os descendentes recursivamente

  // funções de balanceamento
  //-------------------------------------------------------------------------------------------------------------------------------------------//
  //  recalcula balanceamento e rotaciona, se necessário, devolvendo o
  //  ponteiro para o nó que ocupou a posição de p na árvore (caso uma
  //  rotação tenha sido realizada)
  No *ajusta_balanceamento(No *p, bool ins);

  void rotacao_dir(No *p);       // Rotação à direita: p e p->esq
  void rotacao_esq(No *p);       // Rotação à esquerda: p e p->dir
  void rotacao_dupla_dir(No *p); // Rotação dupla à direita: p->esq e p->esq->dir à esquerda, então p e p->esq à direita
  void rotacao_dupla_esq(No *p); // Rotação dupla à esquerda: p->dir e p->dir->esq à direita, então p e p->dir à esquerda
};
//===========================================================================================================================================//

// MAIN
//===========================================================================================================================================//

int main()
{

  char arvore_buscada[3] = {0};
  char opcao;
  AVL arvore1;
  AVL arvore2;
  AVL arvore3;
  AVL arvore4;
  int tamanho = 0;
  int n1 = 0, n2 = 0, n3 = 0, n4 = 0, valor = 0;
  int max = 0, min = 0;
  int *chaves1 = nullptr;
  int *chaves2 = nullptr;
  int *chaves3 = nullptr;
  int *chaves4 = nullptr;
  int count = 0;

  bool flag = true;
  while (flag)
  {
    std::cout << "Escolha uma operação:\n";
    std::cout << "(A) - Inserir elementos na arvore T1\n";
    std::cout << "(B) - Inserir elementos na arvore T2\n";
    std::cout << "(C) - Imprimir dados de T1 em forma de arvore\n";
    std::cout << "(D) - Imprimir dados de T2 em forma de arvore\n";
    std::cout << "(E) - Imprimir dados de T1 em ordem\n";
    std::cout << "(F) - Imprimir dados de T2 em ordem\n";
    std::cout << "(G) - Criar arvore Uniao (T3)\n";
    std::cout << "(H) - Imprimir dados de T3 em forma de arvore\n";
    std::cout << "(I) - Imprimir dados de T3 em ordem\n";
    std::cout << "(J) - Criar arvore Intersecção (T4)\n";
    std::cout << "(K) - Imprimir dados de T4 em forma de arvore\n";
    std::cout << "(L) - Imprimir dados de T4 em ordem\n";
    std::cout << "(M) - Buscar em Intervalo\n";
    std::cout << "(X) - Encerrar programa\n";
    std::cin >> opcao;
    std::cout << "===============================================================================\n";
    switch (opcao)
    {
    case 'A':
      cout << "Digite a quantidade de elementos que deseja inserir na arvore 1: ";
      cin >> n1;

      for (int i = 0; i < n1; i++)
      {
        cout << "Digite o valor " << i << " a ser inserido na arvore T1: ";
        cin >> valor;
        if (!arvore1.busca(valor))
        {
          arvore1.insere(valor);
        }
        else
        {
          std::cout << "------------------------------------------------------------------------\n";
          cout << "Ja existe um produto com este código, tente outro\n";
          std::cout << "------------------------------------------------------------------------\n";

          i--;
        }
      };
      break;

    case 'B':
      cout << "Digite a quantidade de elementos que deseja inserir na arvore 2: ";
      cin >> n2;

      for (int i = 0; i < n2; i++)
      {
        cout << "Digite o valor " << i << " a ser inserido na arvore T2: ";
        cin >> valor;
        if (!arvore2.busca(valor))
        {
          arvore2.insere(valor);
        }
        else
        {
          std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------\n";
          cout << "Ja existe um produto com este código, tente outro\n";
          std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------\n";

          i--;
        }
      }
      break;

    case 'C':
      cout << "Elementos de T1 em forma de arvore: \n";
      arvore1.escreve();
      cout << endl;
      break;

    case 'D':
      cout << "Elementos da T2 em forma de arvore: \n";
      arvore2.escreve();
      cout << endl;
      break;

    case 'E':
      cout << "Elementos da arvore T1 em ordem: ";
      arvore1.escreve_ordenado();
      cout << endl;
      break;

    case 'F':
      cout << "Elementos da arvore T2 em ordem: ";
      arvore2.escreve_ordenado();
      cout << endl;
      break;

    case 'G': // União de árvores
      chaves1 = arvore1.coleta_chaves(n1);
      chaves2 = arvore2.coleta_chaves(n2);
      for (int i = 0; i < n1; i++)
      {
        if (!arvore3.busca(chaves1[i]))
        {
          arvore3.insere(chaves1[i]);
          n3++;
        }
      }
      for (int i = 0; i < n2; i++)
      {
        if (!arvore3.busca(chaves2[i]))
        {
          arvore3.insere(chaves2[i]);
          n3++;
        }
      }
      delete[] chaves1;  // Libera memória
      chaves1 = nullptr; // Zera ponteiro
      delete[] chaves2;  // Libera memória
      chaves2 = nullptr; // Zera ponteiro
      cout << "Arvore Uniao criada com sucesso! ";
      break;

    case 'H':
      cout << "Elementos da T3 em forma de arvore: \n";
      arvore3.escreve();
      cout << endl;
      break;

    case 'I':
      cout << "Elementos da arvore T3 em ordem: ";
      arvore3.escreve_ordenado();
      cout << endl;
      break;

    case 'J': // Interseção de árvores
      chaves1 = arvore1.coleta_chaves(n1);
      chaves2 = arvore2.coleta_chaves(n2);
      chaves3 = chaves_intersec(chaves1, chaves2, n1, n2, count);
      for (int i = 0; i < count; i++)
      {
        if (!arvore4.busca(chaves3[i]))
        {
          arvore4.insere(chaves3[i]);
          n4++;
        }
      }
      delete[] chaves1;  // Libera memória
      chaves1 = nullptr; // Zera ponteiro
      delete[] chaves2;  // Libera memória
      chaves2 = nullptr; // Zera ponteiro
      delete[] chaves3;  // Libera memória
      chaves3 = nullptr; // Zera ponteiro
      cout << "Arvore Intersecção criada com sucesso! ";
      break;

    case 'K':
      cout << "Elementos da T4 em forma de arvore: \n";
      arvore4.escreve();
      cout << endl;
      break;

    case 'L':
      cout << "Elementos da arvore T4 em ordem: ";
      arvore4.escreve_ordenado();
      cout << endl;
      break;

    case 'M':
      cout << "Selecione a arvore em que você quer realizar a busca (T1, T2, T3 ou T4): ";
      std::cin >> arvore_buscada;
      cout << "Digite o primeiro valor do intervalo: ";
      std::cin >> min;
      cout << "Digite o segundo valor do intervalo: ";
      std::cin >> max;

      if (strcmp(arvore_buscada, "T1") == 0)
      {
        chaves4 = arvore1.busca_intervalo(arvore1.get_raiz(), min, max, n1);
        tamanho = n1;
      }
      else if (strcmp(arvore_buscada, "T2") == 0)
      {
        chaves4 = arvore2.busca_intervalo(arvore2.get_raiz(), min, max, n2);
        tamanho = n2;
      }
      else if (strcmp(arvore_buscada, "T3") == 0)
      {
        chaves4 = arvore3.busca_intervalo(arvore3.get_raiz(), min, max, n3);
        tamanho = n3;
      }
      else
      {
        chaves4 = arvore4.busca_intervalo(arvore4.get_raiz(), min, max, n4);
        tamanho = n4;
      }

      std::cout << "-------------------------------------------------------------------------------\n";
      cout << "Chaves encontradas na arvore " << arvore_buscada << ": ";
      for (int i = 0; i < tamanho; i++)
      {
        if (chaves4[i] != -1)
        {
          cout << chaves4[i] << " ";
        }
      }
      cout << endl;
      std::cout << "-------------------------------------------------------------------------------\n";

      delete[] chaves4;  // Liberação da memória alocada
      chaves4 = nullptr; // Prevenir reutilização do ponteiro
      break;

    case 'X':
      if (chaves1)
      {
        delete[] chaves1;
        chaves1 = nullptr;
      }
      if (chaves2)
      {
        delete[] chaves2;
        chaves2 = nullptr;
      }
      if (chaves3)
      {
        delete[] chaves3;
        chaves3 = nullptr;
      }
      if (chaves4)
      {
        delete[] chaves4;
        chaves4 = nullptr;
      }
      std::cout << "Good Bye!\n";
      flag = false;
      break;
    default:
      std::cout << "Opção inválida!" << std::endl;
    }
  }

  return 0;
}

//===========================================================================================================================================//

//************************************************//
//>>>>>>>> implementações da classe nó <<<<<<<<<<<//
//************************************************//

// construtor da classe nó
//-------------------------------------------------------------------------------------------------------------------------------------------//
No::No(const int chave) : chave(chave),
                          altura(0),
                          pai(NULL),
                          esq(NULL),
                          dir(NULL)
{
}

// este metodo escreve a chave de um nó e seu fator de balanceamento
//-------------------------------------------------------------------------------------------------------------------------------------------//
void No::escreve(const char *sep)
{
  printf("%2d(%d)%s", chave, bal(), sep);
}

// este metodo retorna true se o nó for a raiz (se o pai do nó em questão for NULL)
//-------------------------------------------------------------------------------------------------------------------------------------------//
bool No::eh_raiz()
{
  return pai == NULL;
}

// este metodo retorna true se o nó nao for a raiz e se o nó for o filho direito de seu pai
//-------------------------------------------------------------------------------------------------------------------------------------------//
bool No::eh_direito()
{
  return !eh_raiz() and pai->dir == this;
}

// este metodo retorna true se o nó nao for a raiz e se o nó for o filho esquerdo de seu pai
//-------------------------------------------------------------------------------------------------------------------------------------------//
bool No::eh_esquerdo()
{
  return !eh_raiz() and pai->esq == this;
}

// este metodo retorna o fator de balanceamento do nó atual com base nas alturas dos seus filhos
//-------------------------------------------------------------------------------------------------------------------------------------------//
int No::bal()
{
  int alt_esq = esq ? esq->altura : -1;
  int alt_dir = dir ? dir->altura : -1;
  return alt_esq - alt_dir;
}

// este metodo recalcula a altura de um nó com base na altura de seu filho mais alto
//-------------------------------------------------------------------------------------------------------------------------------------------//
void No::atualiza_altura()
{
  int alt_esq = esq ? esq->altura : -1;
  int alt_dir = dir ? dir->altura : -1;
  altura = 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}
//-------------------------------------------------------------------------------------------------------------------------------------------//

//***********************************************//
//>>>>>>>> implementações da classe AVL <<<<<<<<<//
//***********************************************//

// construtor da classe AVL
//-------------------------------------------------------------------------------------------------------------------------------------------//
AVL::AVL()
{
  raiz = NULL;
}

// construtor de cópia
//-------------------------------------------------------------------------------------------------------------------------------------------//
AVL::AVL(const AVL &outro)
{
  copia(outro);
}

// destrutor
//-------------------------------------------------------------------------------------------------------------------------------------------//
AVL::~AVL()
{
  limpa();
}

// este metodo copia o conteudo de uma arvore para outra
// 1 - A arvore destino é limpa
// 2 - Os dados são copiados para a nova arvore
// 3 - Um ponteiro referência da nova arvore é retornado
//-------------------------------------------------------------------------------------------------------------------------------------------//
AVL &AVL::operator=(const AVL &outro)
{
  limpa();
  copia(outro);
  return *this;
}

// este metodo faz o percurso em ordem da arvore passando a raiz como argumento para outra função
// este outro método irá imprimir os valores
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::escreve_ordenado()
{
  escreve_ordenado(raiz);
  putchar('\n');
}

// este metodo é a segunda parte do anterior
// 1 - se o nó passado for nulo nao imprime nada
// 2 - se nao for, chamamos a função recursivamente para a subarvore da esquerda antes de visitar o nó atual
// 2.1 - isso garante que mantenhamos a condição de percurso em ordem
// 3 - chamamos a função escreve passando uma string separadora para printar o valor do nó
// 4 - fazemos a chamada recursiva do filho direito para visitar a subarvore direita
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::escreve_ordenado(No *x)
{
  // percurso em-ordem
  if (x == NULL)
    return;

  escreve_ordenado(x->esq);
  x->escreve(" ");
  escreve_ordenado(x->dir);
}

// este metodo é a terceira parte do metodo de escrever, sendo a versão do método que nao recebe nenhum parametro
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::escreve()
{
  escreve("", raiz);
}

// este é o metodo que recebe uma string (caractere separador) e um nó para printar, com formato correto, o conteúdo da arvore
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::escreve(const string &prefixo, No *x)
{
  if (x == NULL)
    return;

  bool ehDireito = x->pai and x->pai->dir == x;
  bool temIrmaoEsq = x->pai and x->pai->esq;

  std::cout << prefixo;
  printf(ehDireito and temIrmaoEsq ? "├──" : "└──");

  if (x->pai == NULL) // raiz
    x->escreve("\n");
  else
    x->escreve(ehDireito ? "d\n" : "e\n");

  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->dir);
  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->esq);
}

// retorna a raiz da arvore
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::get_raiz()
{
  return raiz;
}

// metodo de busca que recebe um inteiro k para ser procurado na arvore e chama outra função de busca para de fato percorrer a arvore
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::busca(int k)
{
  return busca(raiz, k);
}

// metodo que recebe um ponteiro x de um nó e um valor k
// 1 - se o nó é nulo ou k é a chave de x retorna x
// 2 - se k é menor que a chave de x retorna uma chamada recursiva da busca mas passando
// 2.1 - o filho esquerdo de x em vez do proprio x
// 3 - se k é maior que a chave de x retorna a chamada recursiva, mas sobre o filho direito
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::busca(No *x, int k)
{
  if (x == NULL or k == x->chave)
    return x;

  if (k < x->chave)
    return busca(x->esq, k);
  else
    return busca(x->dir, k);
}

// este metodo retorna o metodo sobrecarregado 'minimo' se a raiz nao for nula e null caso seja
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::minimo()
{
  return raiz ? minimo(raiz) : NULL;
}

// este metodo recebe um ponteiro para um nó para buscar o menor valor da subarvore deste nó
// 1 - executamos um loop enquanto o valor mais a esquerda nao seja nulo
// 2 - a cada iteração fazemos com que o valor de x seja substituido pelo seu filho esquerdo
//  3 - quando o loop acaba retornamos o filho mais a esquerda da subarvore
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::minimo(No *x)
{
  while (x->esq != NULL)
    x = x->esq;
  return x;
}

// este metodo retorna o metodo sobrecarregado 'maximo' se a raiz nao for nula e NULL caso seja
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::maximo()
{
  return raiz ? maximo(raiz) : NULL;
}

// este metodo recebe um ponteiro para um nó e busca o maior valor de sua subarvore
// 1 - executamos um loop enquanto o valor mais a direita não é nulo
// 2 - a cada iteração substituimos o valor de x pelo seu filho direito
// 3 - quando o loop acaba retornamos o valor do filho mais a direita da subarvore
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::maximo(No *x)
{
  while (x->dir != NULL)
    x = x->dir;
  return x;
}

// este metodo recebe um ponteiro para um nó e retorna seu sucessor
// 1 - se o filho direito de x nao for nulo retornamos a chamada da função minimo para esse filho
// 2 - se nao, criamos um ponteiro y que recebe o pai de x
// 3 - criamos um loop que roda enquanto y não é NULL e x é filho direito de y
// 4 - a cada iteração desse loop atualizamos x com o valor de y e y com o pai de y
// 5 - ao final do loop retornamos y que será o sucessor.
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::sucessor(No *x)
{
  if (x->dir != NULL)
    return minimo(x->dir);

  No *y = x->pai;
  while (y != NULL and x == y->dir)
  {
    x = y;
    y = y->pai;
  }
  return y;
}

// este metodo recebe um ponteiro para um nó e tetorna seu predecessor
// 1 - se o filho esquerdo nao for NULO retorna a chamada da funcao 'maximo' passando o filho esquerdo como argumento
// 2 - se nao, criamos um ponteiro y para o nó pai de x
// 3 - criamos um loop que roda enquando y nao for NULL e x é filho esquerdo de y
// 4 - a cada iteração atualizamos x com o valor de y e y com o valor de seu pai
// 5 - retornamos o valor de y e esse será o predecessor de x
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::predecessor(No *x)
{
  if (x->esq != NULL)
    return maximo(x->esq);

  No *y = x->pai;
  while (y != NULL and x == y->esq)
  {
    x = y;
    y = y->pai;
  }
  return y;
}

// este metodo é um pouco complexo, mas tem como objetivo balancear a arvore caso nao esteja balanceada
// ele recebe um ponteiro p para um nó e uma variavel booleana que indica se o balanceamento esta sendo
// feito após uma inserção (true) ou nao (false)
// 1 - atualizamos a altura de p para garantir que não façamos operações com calculos errados
// 2 - agora verificamos o fator de balanceamento do nó p em dois casos:
//     - caso 1: fator de balanceamento de p é 2 (subarvore esquerda mais alta)
//       - caso 1.1: se o fator de balanceamento do filho esq de p é >= 0, realizamos rotação simples a direita.
//          - se ins for true imprime o caso da rotação
//       - caso 1.2: se o fator de balanceamento do filho esquerdo de p é < 0 fazemos uma rotação dupla a direita
//          - se ins for true imprime o caso da rotação
//     - caso 2: se o fator de balanceamento de p é -2 (subarvore direita mais alta)
//       - caso 2.1: se o fator de balanceamento do filho direito de p é <= 0 realizamos uma rotação simples a esquerda
//          - se ins for true imprime o caso da rotação
//       - caso 2.2: se o fator de balanceamento do filho direito de p é > 0 realizamos uma rotação dupla a esquerda
//          - se ins for true imprime o caso da rotação
// 3 - após qualquer rotação, p desce um nível
// 4 - Retorna p agora atualizado
//-------------------------------------------------------------------------------------------------------------------------------------------//
No *AVL::ajusta_balanceamento(No *p, bool ins)
{

  p->atualiza_altura();

  if (p->bal() == 2)
  { // Caso 1
    if (p->esq->bal() >= 0)
    { // Caso 1.1
      if (ins)
        printf(">> Rotação direita (Caso 1.1)\n");
      rotacao_dir(p);
    }
    else
    { // Caso 1.2
      if (ins)
        printf(">> Rotação dupla direita (Caso 1.2)\n");
      rotacao_dupla_dir(p);
    }
    p = p->pai; // após a rotação p desceu 1 nível, precisamos subir de volta
  }
  else if (p->bal() == -2)
  { // Caso 2
    if (p->dir->bal() <= 0)
    { // Caso 2.1
      if (ins)
        printf(">> Rotação esquerda (Caso 2.1)\n");
      rotacao_esq(p);
    }
    else
    { // Caso 2.2
      if (ins)
        printf(">> Rotação dupla esquerda (Caso 2.2)\n");
      rotacao_dupla_esq(p);
    }
    p = p->pai; // após a rotação p desceu 1 nível, precisamos subir de volta
  }

  return p;
}

// este metodo recebe uma chave inteira, cria um ponteiro para um novo nó z
// chama o metodo insere sobrecarregado passando z como argumento
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::insere(int chave)
{
  No *z = new No(chave);
  insere(z);
}

// este metodo recebe um nó z e o insere na arvore
// 1 - inicializa 2 ponteiros do tipo No, um com NULL e um apontando para a raiz
// 2 - criamos um loop que roda atualizando o valor de x e y
//     - se a chave de z for menor que a do nó atual apontamos para a subarvore esq
//     - se não, apontamos para a subarvore dir
//     - quando esse loop acaba y aponta para o pai do nó onde z será inserido
//     - e x aponta para NULL indicando onde z deve ser inserido
// 3 - Define o pai de z como y, e se for null tornamos z a raiz da arvore
//     - se não, define z como filho esquerdo ou direito de y dependendo do valor da chave de z
// 4 - Verifica se z é raiz, se nao for inicia o balanceamento.
// 5 - Iniciamos um loop do-while para percorrer a arvore a partir do pai do nó inserido
//     - esse loop vai corrigindo os possiveis desequilibrios causados pela inserção
//     - o loop para de subir a arvore quando encontra um nó com fator de balanceamento 0
//     - ou alcançar a raiz
//     - ao fim desse loop, a arvore estará com o novo nó e devidamente balanceada
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::insere(No *z)
{
  No *y = NULL;
  No *x = raiz;

  while (x != NULL)
  {
    y = x;
    x = z->chave < x->chave ? x->esq : x->dir;
  }
  z->pai = y;
  if (y == NULL)
    raiz = z;
  else if (z->chave < y->chave)
    y->esq = z;
  else
    y->dir = z;

  // Atualização dos fatores de balanceamento
  if (z->eh_raiz())
    return;

  do
  { // o laço inicia subindo imediatamente para o pai do nó inserido
    z = z->pai;
    z = ajusta_balanceamento(z, true);
  } while (!z->eh_raiz() and z->bal() != 0);
}
// este metodo recebe dois ponteiros para nós u é v e substitui um pelo outro na arvore
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::transplante(No *u, No *v)
{
  if (u->eh_raiz())
    raiz = v;
  else if (u->eh_esquerdo())
    u->pai->esq = v;
  else
    u->pai->dir = v;

  if (v != NULL)
    v->pai = u->pai;
}

// este metodo recebe um valor inteiro, busca um nó com essa chave e o remove da arvore
//-------------------------------------------------------------------------------------------------------------------------------------------//
bool AVL::remove(int chave)
{
  No *z = busca(raiz, chave);
  if (z == NULL)
    return false;

  remove(z);
  delete z;
  return true;
}

// este metodo recebe o nó que deve ser removido da arvore, remove e ajusta os fatores de balanceamento
// 1 - criamos um ponteiro p do tipo No para representar onde a a estrutura
//     foi alterada para começar a atualização
// 2 - determina caso de remoção com base nos filhos de z:
//     - caso 1: z nao tem filho esquerdo. Filho direito substitui z. p agora é pai de z
//     - caso 2: z nao tem filho direito. Filho esquerdo substitui z. p agora é pai de z
//     - caso 3: z tem ambos os filhos. Define y como o menor nó na subarvore direita de z e executa o seguinte:
//       - subcaso (a): Se y é o filho direito de z, y substitui z diretamente. y recebe o filho esquerdo de z
//       - subcaso (b): Se y não é o filho direto de z, y é substituído por seu próprio filho direito e depois substitui z
// 3 - Atualização de Alturas/Fatores de Balanceamento
//     - Se p é NULL, a função termina, pois a raiz foi substituída sem alteração significativa
//     - Caso contrário, chama ajusta_balanceamento(p, false) para balancear a partir de p.
//     - Laço de ajuste: Enquanto p não for a raiz e o balanceamento de p não for ±1, sobe na árvore e ajusta o balanceamento.
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::remove(No *z)
{

  // Precisamos salvar a posição na qual a árvore foi efetivamente
  // modificada e onde devemos começar a atualização de
  // alturas/fatores de balanceamento.
  No *p = NULL;

  if (z->esq == NULL)
  { // 1o caso

    p = z->pai; // a altura de z->dir (que substituirá z) não será alterada, e z->dir pode ser nulo
    transplante(z, z->dir);
  }
  else
  {
    if (z->dir == NULL)
    { // 2o caso
      printf("<< Remoção 2o caso\n");
      p = z->pai; // a altura de z->esq (que substituirá z) não será alterada
      transplante(z, z->esq);
    }
    else
    { // 3o caso
      No *y = minimo(z->dir);

      printf("<< Remoção 3o caso (a) ");
      if (y->pai != z)
      { // (b)
        printf("+ (b)\n");
        p = y->pai; // a altura de y->dir (que substituirá y) não será alterada, e y->dir pode ser nulo
        transplante(y, y->dir);
        y->dir = z->dir;
        y->dir->pai = y;
      }
      printf("\n");

      transplante(z, y); // (a)
      y->esq = z->esq;
      y->esq->pai = y;

      // Se não entramos no caso 3(b), a atualização de "p" é um
      // pouco diferente dos outros casos. Se entramos diretamente no
      // caso 3(a), o nó "z" removido tem filhos esquerdo E direito,
      // mas o sucessor "y" que o substituirá é seu filho direito. A
      // altura de "y" *PODE* ser modificada, já que "y" terá um filho
      // esquerdo que não tinha antes (o antigo filho esquerdo de "z").
      if (p == NULL) // se fomos direto pro caso 3(a) sem entrar no caso 3(b)
        p = y;
    }
  }

  // Atualização das alturas/fatores de balanceamento

  // Se p é nulo, significa que a raiz foi removida e substituída por
  // seu único filho, então nada muda.
  if (p == NULL)
    return;

  // Não podemos subir imediatamente para o pai de p (como na
  // inserção), pois p é o próprio nó que precisa atualização.
  p = ajusta_balanceamento(p, false);

  while (!p->eh_raiz() and p->bal() != 1 and p->bal() != -1)
  {
    p = p->pai;
    p = ajusta_balanceamento(p, false);
  }
}

// este metodo não recebe parametros e chama o metodo sobrecarregado 'limpa' passando a raiz como argumento
// a raiz se torna NULL após isso, mostrando que a arvore foi devidamente limpa
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::limpa()
{
  limpa(raiz);
  raiz = NULL;
}

// este metodo recebe um ponteiro para o nó raiz 'x' e enquanto x nao for NULL ele se chama recursivamente para
// seus filhos esquerdo e direito
// ao final da execução, a arvore deve estar limpa e deletamos o ponteiro x.
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::limpa(No *x)
{
  if (x == NULL)
    return;

  limpa(x->esq);
  limpa(x->dir);
  delete x;
}

// este metodo recebe uma referencia constante para outra arvore AVL T
// se T nao tem raiz, define a raiz da arvore atual como NULL
// caso contrario, cria um novo nó com a chave da raiz de Te chama o metodo sobrecarregado copia
// que irá recplicar recursivamente os nós da arvore T
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::copia(const AVL &T)
{
  if (T.raiz == NULL)
    raiz = NULL;
  else
  {
    raiz = new No(T.raiz->chave);
    copia(raiz, T.raiz);
  }
}

// este metodo sobrecarregado recebe um ponteiro para a raiz da subarvore destino e um para a da
// subarvore de origem
// 1 - testa se a raiz da subarvore original tem filho direito esquerdo
//     1.1: se sim, cria um nó a esquerda da raiz da arvore destino com a chave no nó a esquerda da raiz da origem
//           - define o pai do nó recem criado e chama recursivamente 'copia' para copiar o restante da subarvore esquerda
// 2 - testa se a raiz da subarvore original tem filho direito
//     2.1: se sim cria um nó a direita da raiz da arvore destino com a chave do nó a direita da raiz da origem
//           - define o pai do no recem criado e chama recursivamente 'copia' para copiar o restante da subarvore direita
// 3 - Apos a execução, todos os nos da subarvore origem estarao devidamente copiados na destino.
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::copia(No *dest, No *orig)
{
  if (orig->esq)
  {
    dest->esq = new No(orig->esq->chave);
    dest->esq->pai = dest;
    copia(dest->esq, orig->esq);
  }

  if (orig->dir)
  {
    dest->dir = new No(orig->dir->chave);
    dest->dir->pai = dest;
    copia(dest->dir, orig->dir);
  }
}

// este método ajusta a estrutura da árvore para corrigir desequilíbrios, movendo o nó à esquerda de 'p' (u) para
//   a posição de 'p' e fazendo as mudanças necessárias nos ponteiros para preservar a estrutura da árvore
// 1 - Armazena o filho esquerdo de 'p' em 'u'
// 2 - Usa o método transplante para substituir 'p' por 'u' na árvore
// 3 - Coloca 'p' à direita de 'u' e move o filho direito de 'u' (se existir) para a esquerda de 'p'
// 4 - Ajusta o ponteiro pai de 'p' e o ponteiro pai do novo filho esquerdo de 'p' (se existir)
// 5 - Atualiza as alturas de 'p' e 'u' após a rotação para manter os valores corretos de altura
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::rotacao_dir(No *p)
{
  No *u = p->esq;
  // arruma u e seu pai (o pai de p)
  transplante(p, u);
  // move p para a direita de u, e o filho direito de u para a esquerda de p
  p->pai = u;
  p->esq = u->dir;
  u->dir = p;
  if (p->esq)
    p->esq->pai = p;
  // atualiza alturas
  p->atualiza_altura();
  u->atualiza_altura();
}

// este método ajusta a árvore ao mover o nó à direita de 'p' (u) para a posição de 'p', corrigindo desequilíbrios
// 1 - Armazena o filho direito de 'p' em 'u'
// 2 - Usa o método transplante para substituir 'p' por 'u' na árvore
// 3 - Coloca 'p' à esquerda de 'u' e move o filho esquerdo de 'u' (se existir) para a direita de 'p'
// 4 - Ajusta o ponteiro pai de 'p' e o ponteiro pai do novo filho direito de 'p' (se existir)
// 5 - Atualiza as alturas de 'p' e 'u' para refletir as mudanças na árvore
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::rotacao_esq(No *p)
{
  No *u = p->dir;
  // arruma u e seu pai (o pai de p)
  transplante(p, u);
  // move p para a esquerda de u, e o filho esquerdo de u para a direita de p
  p->pai = u;
  p->dir = u->esq;
  u->esq = p;
  if (p->dir)
    p->dir->pai = p;
  // atualiza alturas
  p->atualiza_altura();
  u->atualiza_altura();
}

// este método é aplicado quando o filho esquerdo de 'p' está desbalanceado à direita, causando a necessidade de duas rotações:
// uma rotação simples à esquerda no filho esquerdo de 'p' seguida de uma rotação simples à direita em 'p'
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::rotacao_dupla_dir(No *p)
{
  rotacao_esq(p->esq);
  rotacao_dir(p);
}

// este método é aplicado quando o filho direito de 'p' está desbalanceado à esquerda, requerendo duas rotações:
// uma rotação simples à direita no filho direito de 'p' seguida de uma rotação simples à esquerda em 'p'
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::rotacao_dupla_esq(No *p)
{
  rotacao_dir(p->dir);
  rotacao_esq(p);
}

// Este método coleta todas as chaves presentes na árvore AVL e as armazena em um array.
// Ele primeiro conta o número de nós na árvore e aloca memória suficiente para armazenar as chaves.
// 1 - Chama o método `conta_nos` para contar o número de nós na árvore.
// 2 - Se a árvore estiver vazia (tamanho == 0), retorna um ponteiro nulo.
// 3 - Aloca dinamicamente memória para armazenar as chaves.
// 4 - Chama o método recursivo `coleta_chaves_recursivo` para percorrer a árvore e armazenar as chaves no array.
// 5 - Retorna o array contendo as chaves coletadas.
//-------------------------------------------------------------------------------------------------------------------------------------------//

int *AVL::coleta_chaves(int &tamanho)
{
  tamanho = conta_nos(raiz);
  if (tamanho == 0)
  {
    return nullptr;
  }

  int *chaves = new int[tamanho];
  int index = 0;
  coleta_chaves_recursivo(raiz, chaves, index);
  return chaves;
}

// Este método percorre a árvore AVL de forma recursiva para coletar as chaves de todos os nós,
// armazenando as chaves no array passado como parâmetro.
// Passos executados:
// 1 - Verifica se o nó atual é nulo, caso em que a função retorna sem fazer nada.
// 2 - Chama recursivamente o método para o filho esquerdo do nó.
// 3 - Armazena a chave do nó no array.
// 4 - Chama recursivamente o método para o filho direito do nó.
// 5 - O processo é repetido até que todos os nós sejam visitados e suas chaves armazenadas.
//-------------------------------------------------------------------------------------------------------------------------------------------//
void AVL::coleta_chaves_recursivo(No *no, int *array, int &index)
{
  if (no != nullptr)
  {
    coleta_chaves_recursivo(no->esq, array, index);
    array[index++] = no->chave;
    coleta_chaves_recursivo(no->dir, array, index);
  }
}

// Este método conta o número de nós na árvore AVL, percorrendo recursivamente todas as subárvores.
// 1 - Se o nó for nulo, retorna 0, indicando que não há nós nessa subárvore.
// 2 - Caso contrário, retorna 1 (para o nó atual) somado à quantidade de nós da subárvore esquerda e direita.
// 3 - A função é chamada recursivamente para os filhos esquerdo e direito de cada nó, até que todos os nós sejam contados.
//-------------------------------------------------------------------------------------------------------------------------------------------//
int AVL::conta_nos(No *no)
{
  if (no == nullptr)
  {
    return 0;
  }
  return 1 + conta_nos(no->esq) + conta_nos(no->dir);
}

// Este método calcula a interseção entre dois arrays de chaves, retornando um novo array contendo
// os elementos comuns entre as duas listas, sem duplicatas.
// 1 - Calcula o tamanho do array de saída, que é o menor entre os tamanhos de `chaves1` e `chaves2`.
// 2 - Aloca dinamicamente um array para armazenar as chaves da interseção.
// 3 - Preenche o array com um valor sentinela (-1) para indicar que os elementos ainda não foram preenchidos.
// 4 - Percorre ambas as listas (`chaves1` e `chaves2`) e compara os elementos. Quando encontra um elemento comum,
//    verifica se ele já foi adicionado à lista de interseção.
// 5 - Se o elemento não estiver na lista de interseção, ele é adicionado.
// 6 - Retorna o array contendo as chaves de interseção, após a remoção de duplicatas.
//-------------------------------------------------------------------------------------------------------------------------------------------//
int *chaves_intersec(int *chaves1, int *chaves2, int n1, int n2, int &count)
{
  int size = n1 > n2 ? n2 : n1;
  int *chaves3 = new int[size];
  for (int i = 0; i < size; i++)
  {
    chaves3[i] = -1;
  }
  count = 0;

  for (int i = 0; i < n1; i++)
  {
    for (int j = 0; j < n2; j++)
    {
      if (chaves1[i] == chaves2[j])
      {
        bool ja_existe = false;
        for (int k = 0; k < count; k++)
        {
          if (chaves3[k] == chaves1[i])
          {
            ja_existe = true;
            break;
          }
        }
        if (!ja_existe)
        {
          chaves3[count] = chaves1[i];
          count++;
        }
      }
    }
  }
  return chaves3;
}

// Este método percorre a árvore AVL de forma recursiva para buscar chaves dentro de um intervalo [min, max],
// armazenando as chaves encontradas em um array.
// 1 - Verifica se o nó atual é nulo, caso em que a função retorna sem fazer nada.
// 2 - Se a chave do nó for maior que o valor mínimo do intervalo, percorre a subárvore esquerda.
// 3 - Se a chave do nó estiver dentro do intervalo [min, max], adiciona a chave no array de resultados.
// 4 - Se a chave do nó for menor que o valor máximo do intervalo, percorre a subárvore direita.
// 5 - A função continua até que todos os nós dentro do intervalo sejam encontrados.
//-------------------------------------------------------------------------------------------------------------------------------------------//
void busca_intervalo_rec(No *raiz, int min, int max, int *&lista, int &index, int &size)
{
  if (raiz == nullptr)
    return;

  // Visitar subárvore esquerda
  if (raiz->getChave() > min)
  {
    busca_intervalo_rec(raiz->getEsq(), min, max, lista, index, size);
  }

  // Processar nó atual
  if (raiz->getChave() >= min && raiz->getChave() <= max)
  {
    if (index >= size)
    {
      // Realoca array se necessário
      int novo_tamanho = size * 2;
      int *novo_lista = new int[novo_tamanho];
      for (int i = 0; i < size; i++)
      {
        novo_lista[i] = lista[i];
      }
      delete[] lista;
      lista = novo_lista;
      size = novo_tamanho;
    }

    lista[index] = raiz->getChave();
    index++;
  }

  // Visitar subárvore direita
  if (raiz->getChave() < max)
  {
    busca_intervalo_rec(raiz->getDir(), min, max, lista, index, size);
  }
}

// Este método realiza a busca de chaves dentro de um intervalo [min, max] e retorna um array contendo
// as chaves encontradas. A quantidade de elementos encontrados é atualizada na variável 'size'.
// 1 - Aloca um array para armazenar as chaves encontradas no intervalo. O tamanho do array é especificado por 'size'.
// 2 - Inicializa o array com valores sentinela (-1) para indicar que as posições ainda não foram preenchidas.
// 3 - Chama a função recursiva `busca_intervalo_rec` para percorrer a árvore e preencher o array com as chaves no intervalo.
// 4 - Atualiza a variável 'size' com o número de chaves encontradas.
// 5 - Retorna o array contendo as chaves encontradas no intervalo.
//-------------------------------------------------------------------------------------------------------------------------------------------//
int *AVL::busca_intervalo(No *raiz, int min, int max, int &size)
{
  // Garantir que size seja um valor válido antes da alocação
  if (size <= 0)
  {
    size = 10; // Ou um valor adequado, ou talvez baseado em alguma lógica de tamanho mínimo
  }
  int *lista = new int[size];
  for (int i = 0; i < size; i++)
  {
    lista[i] = -1;
  }
  int index = 0;

  busca_intervalo_rec(raiz, min, max, lista, index, size);

  size = index;
  for (int i = 0; i < size; i++)
  {
  }
  return lista;
}