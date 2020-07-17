#include <stdlib.h>
#include <stdio.h>

#include "packedMatrix.h"

void push(unsigned int v, char* onStack, unsigned int* stack, unsigned int* stackPos) {
   onStack[v] = 1; // true
   stack[*stackPos] = v;
   (*stackPos)++;
}

int pop(char* onStack, unsigned int* stack, unsigned int* stackPos) {
   //printf("\nPOP(%d, %d)\n", *onStack, *stackPos);
   if ((*stackPos) == 0)
      return -1; // empty

   (*stackPos)--;
   onStack[stack[*stackPos]] = 0; // false

   return stack[*stackPos];
}

void printTarjanStructs(
      PackedMatrix* m,
      int* p,
      int* nodeIndex,
      unsigned int* lowlink,
      unsigned int* stack,
      unsigned int* stackPos) {
   printf("Pilha:\t\t");
   for (unsigned int i = 0; i < *stackPos; i++)
      printf("%d ", stack[i]);
   printf("\n");

   printf("NodeIndex:\t");
   for (unsigned int i = 0; i < m->n; i++) {
      if (nodeIndex[i] != -1)
         printf("%d ", nodeIndex[i]);
      else
         printf("_ ");
   }
   printf("\n");

   printf("Lowlink:\t");
   for (unsigned int i = 0; i < m->n; i++) {
      if (nodeIndex[i] != -1)
         printf("%d ", lowlink[i]);
      else
         printf("_ ");
   }
   printf("\n");

   printf("Permutação:\t");
   for (unsigned int i = 0; i < m->n; i++) {
      if (p[i] != -1)
         printf("%d ", p[i]);
      else
         printf("_ ");
   }
   printf("\n");

   getchar();
}

void strongConnect(unsigned int v,
      PackedMatrix* m,
      int* p,
      unsigned int* firstAvailable,
      int* nodeIndex,
      unsigned int* lowlink,
      char* onStack,
      unsigned int* stack,
      unsigned int* stackPos,
      unsigned int* index) {

   int w;

   nodeIndex[v] = (*index);
   lowlink[v] = (*index);
   (*index)++;

   push(v, onStack, stack, stackPos);

   // impressões para didática
   printf("Avaliando o nó %d\n===\n", v);

   printTarjanStructs(m, p, nodeIndex, lowlink, stack, stackPos);

   for (unsigned int i = m->rowStart[v]; i < m->rowStart[v] + m->rowLength[v]; i++) {
      w = m->colIndex[i];

      if (w == v) // laço, ignoramos
         continue;

      if (nodeIndex[w] == -1) { // novo nó
         strongConnect(w, m, p, firstAvailable, nodeIndex, lowlink, onStack, stack, stackPos, index);

         if (lowlink[w] < lowlink[v])
            lowlink[v] = lowlink[w];
      } else if (onStack[w]) { // ciclo
         printf("Ciclo! (%d aponta para %d)\n", v, w);
         if (nodeIndex[w] < lowlink[v])
            lowlink[v] = nodeIndex[w];
      } // else: cross-edge
   }

   if (lowlink[v] == nodeIndex[v]) {
      printf("Componente fortemente conexa: ");

      while ((w = pop(onStack, stack, stackPos)) != v) {
         printf("%d ", w);
         p[w] = *firstAvailable;
         (*firstAvailable)++;
      }
      printf("%d\n", w);
      p[w] = *firstAvailable;
      (*firstAvailable)++;

      printf("\n");
      printTarjanStructs(m, p, nodeIndex, lowlink, stack, stackPos);
      printf("\n");
      printPackedMatrixAsUnpackedPermuted(m, p);
   }
}

// assumindo que já chega uma matriz com transversal cheio
int* tarjan(PackedMatrix* m) {
   int* p = malloc((m->n)*sizeof(int)); // vetor de permutação
   unsigned int firstAvailable = 0;

   char* onStack = malloc(m->n*sizeof(char));
   unsigned int* stack = malloc(m->n*sizeof(unsigned int)); // pilha
   unsigned int stackPos = 0;

   unsigned int index = 0;

   unsigned int* lowlink = malloc(m->n*sizeof(unsigned int));
   int* nodeIndex = malloc(m->n*sizeof(int));

   // inicializações
   for (unsigned int v = 0; v < m->n; v++)
      nodeIndex[v] = -1;

   for (unsigned int v = 0; v < m->n; v++)
      onStack[v] = 0; // false

   for (int i = 0; i < m->n; i++)
      p[i] = -1;





   for (unsigned int v = 0; v < m->n; v++)
      if (nodeIndex[v] == -1)
         strongConnect(v, m, p, &firstAvailable, nodeIndex, lowlink, onStack, stack, &stackPos, &index);





   //printf("nodeIndex: ");
   //for (unsigned int i = 0; i < m->n; i++) {
   //   printf("%d ", nodeIndex[i]);
   //}
   //printf("\n");

   //printf("stack: ");
   //for (unsigned int i = 0; i < stackPos; i++) {
   //   printf("%d ", stack[i]);
   //}
   //printf("\n");

   //printf("lowlink: ");
   //for (unsigned int i = 0; i < m->n; i++) {
   //   printf("%d ", lowlink[i]);
   //}
   printf("\n");

   free(nodeIndex);
   free(lowlink);
   free(onStack);
   free(stack);

   return p;
}
