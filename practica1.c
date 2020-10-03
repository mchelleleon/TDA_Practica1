#include <stdio.h>
#include <stdlib.h>
struct Puntos {
  float x;
  float y;
  struct Puntos *sig;
};
typedef struct Puntos coorde;
void insertar (coorde **Inicio, float valx, float valy);
void Imprimir (coorde *Inicio);
void borrar (coorde *Inicio);
void graficar();
void generar (int masa, int k, float g, int xi, int xf, coorde **Inicio);
int main ()
{
  coorde *Inicio = NULL;
  //valores iniciales
  int masa=60, k=500, xi=10, xf=10;
  float g=9.81;
  generar(masa,k,g,xi,xf,&Inicio);
  Imprimir(Inicio);
  borrar(Inicio);
  graficar();
  return 0;
}
void generar(int masa, int k, float g, int xi, int xf, coorde **Inicio)
{
  int observaciones=10, i;
  float resultado, delta, anterior, corchetes,segundo,tercero;
  anterior = xi;
  insertar(Inicio, 0, xi);
  for (i=1; i<observaciones;i++)
  {
    delta = i*0.1;
    corchetes = 1 + ((k*delta*delta)/masa);
    segundo= 2*anterior;
    tercero= delta*delta*g;
    resultado = (-xi*corchetes)+segundo+tercero;
    anterior = resultado;
    insertar(Inicio, delta, resultado);
  }
  insertar(Inicio, 1, xf);
}
void insertar (coorde **Inicio, float valx, float valy)
{
  coorde *temp, *temp2;
  temp= (coorde*)malloc(sizeof(coorde));
  temp->x= valx;
  temp->y= valy;
  temp->sig=NULL;
  if (*Inicio!=NULL)
    {
      temp2=*Inicio;
      while (temp2->sig !=NULL)
  {
    temp2=temp2->sig;
  }
      temp2->sig=temp;
    }
  else
  *Inicio=temp;
}
void Imprimir (coorde *Inicio)
{
  coorde *temp;
  temp = Inicio;
  int i;
  FILE* arch = fopen("coordenadas.txt", "wt");
  while (temp != NULL)
    {
      fprintf(arch, "%f, %f\n", temp->x, temp->y);
      temp= temp -> sig;
    }
  fclose(arch);


}
void borrar (coorde *Inicio)
{
  coorde *temp;
  temp= Inicio;
  while (temp!=NULL)
  {
    Inicio = temp->sig;
    free (temp);
    temp=Inicio;
  }
}
void graficar()
{
  char title[100];
  sprintf(title, "set title \"Trayectoria\"");
  char * configGnuplot[] = {title,
                                "set ylabel \"x(t)\"",
                                "set xlabel \"x\"",
                                "plot \"coordenadas.txt\" with lines",
                                "set autoscale",
                                "replot"
                               };
  FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
  for (int i=0; i < 4; i++){
    fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
  }
}
