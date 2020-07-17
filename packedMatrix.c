#include <stdlib.h>
#include <stdio.h>

#include "packedMatrix.h"

void initPackedMatrix(PackedMatrix* m, unsigned int n, unsigned int maxEntries) {
   m->n = n;
   m->maxEntries = maxEntries;

   m->value = malloc(maxEntries*sizeof(float));
   m->colIndex = malloc(maxEntries*sizeof(unsigned int));

   m->rowStart = malloc(n*sizeof(unsigned int));
   m->rowLength = malloc(n*sizeof(unsigned int));
}

PackedMatrix* newPackedMatrix(unsigned int n, unsigned int maxEntries) {
   PackedMatrix* m = malloc(sizeof(PackedMatrix));

   initPackedMatrix(m, n, maxEntries);

   return m;
}

void freePackedMatrix(PackedMatrix* m) {
   free(m->colIndex);
   free(m->rowStart);
   free(m->rowLength);
   free(m->value);
   free(m);
}

PackedMatrix* packMatrix(float* unpacked, unsigned int n, unsigned int maxEntries) {
   PackedMatrix* packed = newPackedMatrix(n, maxEntries);
   char first; // bool
   unsigned int pos = 0;
   unsigned int tau = 0;

   for (int i = 0; i < n; i++) {
      first = 1;
      packed->rowLength[i] = 0;

      for (int j = 0; j < n; j++) {
         if (unpacked[pos] != 0) {
            if (first) {
               packed->rowStart[i] = tau;
               first = 0;
            }

            packed->rowLength[i]++;

            packed->value[tau] = unpacked[pos];
            packed->colIndex[tau] = j;
            tau++;
         }

         pos++;
      }
   }

   return packed;
}

float* unpackMatrix(PackedMatrix* m) {
   float* unpacked = malloc(m->n*m->n*sizeof(float));

   for (unsigned int i = 0; i < m->n*m->n; i++)
      unpacked[i] = 0;

   for (unsigned int i = 0; i < m->n; i++) {
      for (unsigned int pos = m->rowStart[i]; pos < m->rowStart[i] + m->rowLength[i]; pos++) {
         int j = m->colIndex[pos];
         unpacked[i*m->n + j] = m->value[pos];
      }
   }

   return unpacked;
}

void printPackedMatrix(PackedMatrix* m) {
   int tau = 0;

   printf("n = %d, maxEntries = %d\n", m->n, m->maxEntries);

   printf("rowStart:\t");
   for (int i = 0; i < m->n; i++)
      printf("%2d ", m->rowStart[i]);

   printf("\nrowLength:\t");
   for (int i = 0; i < m->n; i++) {
      printf("%2d ", m->rowLength[i]);
      tau += m->rowLength[i];
   }

   printf("\ncolIndex:\t");
   for (int i = 0; i < tau; i++)
      printf("%2d ", m->colIndex[i]);

   printf("\nvalue:\t\t");
   for (int i = 0; i < tau; i++)
      printf("%2.0f ", m->value[i]);

   printf("\n");
}

// esse algoritmo é uma porcaria, por preguiça
void printPackedMatrixAsUnpacked(PackedMatrix* m) {
   float* unpacked = unpackMatrix(m);
   unsigned int pos = 0;

   for (unsigned int i = 0; i < m->n; i++) {
      for (unsigned int j = 0; j < m->n; j++) {
         if (unpacked[pos])
            printf("X ");
         else
            printf("_ ");
         pos++;
      }
      printf("\n");
   }

   free(unpacked);
}

void printPackedMatrixAsUnpackedPermuted(PackedMatrix* m, int* perm) {
   int* p = malloc(m->n*sizeof(int));

   float* unpacked = unpackMatrix(m);
   float* translated = malloc(m->n*m->n*sizeof(float));
   unsigned int pos;

   for (unsigned int i = 0; i < m->n; i++) {
      p[i] = perm[i];
   }

   int max = -1;
   for (unsigned int i = 0; i < m->n; i++)
      if (p[i] > max) max = p[i];
   
   max++;
   for (unsigned int i = 0; i < m->n; i++)
      if (p[i] == -1) {
         p[i] = max;
         max++;
      }

   for (unsigned int i = 0; i < m->n*m->n; i++)
      translated[i] = 0;

   for (unsigned int i = 0; i < m->n; i++) {
      for (unsigned int j = 0; j < m->n; j++) {
         if (unpacked[i*m->n + j] != 0)
            translated[p[i]*m->n + p[j]] = unpacked[i*m->n + j];
      }
   }

   printf("permutação parcial:\t");
   for (unsigned int i = 0; i < m->n; i++)
      printf("%d ", p[i]);
   printf("\n");
   printf("ordem das linhas:\t");
   for (unsigned int i = 0; i < m->n; i++) {
      unsigned int j;
      for (j = 0; p[j] != i; j++);
      printf("%d ", j);
   }
   printf("\n\n");

   for (unsigned int i = 0; i < m->n; i++) {
      for (unsigned int j = 0; j < m->n; j++) {
         pos = i*m->n + j;

         if (translated[pos])
            printf("X ");
         else
            printf("_ ");
      }
      printf("\n");
   }
   printf("\n");

   free(unpacked);
   free(translated);
   free(p);
}
