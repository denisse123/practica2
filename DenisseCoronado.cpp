#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct nodo{
     int nro;
     struct nodo *izq, *der;
}*ABB;

int numNodos = 0;
int numK = 0, k;

struct nodoCola{
    ABB ptr;
    struct nodoCola *sgte;
};
struct cola{
    struct nodoCola *delante;
    struct nodoCola *atras;
};

void inicializaCola(struct cola &q)
{
    q.delante = NULL;
    q.atras = NULL;
}

void encola(struct cola &q, ABB n)
{
     struct nodoCola *p;
     p = new(struct nodoCola);
     p->ptr = n;
     p->sgte = NULL;
     if(q.delante==NULL)
         q.delante = p;
     else
         (q.atras)->sgte = p;
     q.atras = p;
}

ABB desencola(struct cola &q)
{
    struct nodoCola *p;
    p = q.delante;
    ABB n = p->ptr;
    q.delante = (q.delante)->sgte;
    delete(p);
    return n;
}

ABB crearNodo(int x)
{
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
void insertar(ABB &arbol, int x)
{
     if(arbol==NULL)
     {
           arbol = crearNodo(x);
           cout<<"\n\t  Insertado..!"<<endl<<endl;
     }
     else if(x < arbol->nro)
          insertar(arbol->izq, x);
     else if(x > arbol->nro)
          insertar(arbol->der, x);
}

void preOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          cout << arbol->nro <<" ";
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}

void inOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          inOrden(arbol->izq);
          cout << arbol->nro << " ";
          inOrden(arbol->der);
     }
}

void postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          postOrden(arbol->izq);
          postOrden(arbol->der);
          cout << arbol->nro << " ";
     }
}

void verArbol(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->der, n+1);

     for(int i=0; i<n; i++)
         cout<<"   ";

     numNodos++;
     cout<< arbol->nro <<endl;

     verArbol(arbol->izq, n+1);
}
ABB unirABB(ABB izq, ABB der)
{
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    ABB centro = unirABB(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;
    return der;
}

void elimina(ABB &arbol, int x)
{
    int izq;
     if(izq==NULL) return;

     if(x<arbol->nro)
         elimina(arbol->izq, x);
     else if(x>arbol->nro)
         elimina(arbol->der, x);

     else
     {
         ABB p = arbol;
         arbol = unirABB(arbol->izq, arbol->der);
         delete p;
     }
}

int alturaAB(ABB arbol)
{
    int AltIzq, AltDer;

    if(arbol==NULL)
        return -1;
    else
    {
        AltIzq = alturaAB(arbol->izq);
        AltDer = alturaAB(arbol->der);

        if(AltIzq>AltDer)
            return AltIzq+1;
        else
            return AltDer+1;
    }
}
void menu()
{
     cout << "\n\t\t   ARBOL                             \n\n";
     cout << "\t 1)  Insertar elemento                    \n";
     cout << "\t 2)  Mostrar arbol                        \n";
     cout << "\t 3)  InOrden                              \n";
     cout << "\t 4)  PreOrden                             \n";
     cout << "\t 5)  PostOrden                            \n";
     cout << "\t 6)  Eliminar elemento                    \n";
     cout << "\t 7)  SALIR                                \n";
     cout << "\n\t Ingrese opcion : ";
}

int main()
{
    ABB arbol = NULL;
    int x;
    int op;

    do
    {
          menu();  cin>> op;
          cout << endl;

          switch(op)
          {
               case 1:
                    cout << " Ingrese valor : ";  cin>> x;
                    insertar( arbol, x);
                    break;

               case 2:
                    verArbol(arbol, 0);
                    break;

               case 3:
                    inOrden(arbol); break;

               case 4:
                    preOrden(arbol); break;

               case 5:
                    postOrden(arbol); break;

               case 6:
                    cout<<" Valor a eliminar: "; cin>> x;
                    elimina(arbol, x);
                    cout << "\n\tEliminado..!";
                    break;
                case 7:
                    exit(0);
          }
          cout<<"\n\n\n";
    }while(op!=9);
}
