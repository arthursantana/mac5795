#include <stdio.h>
#include <stdlib.h>

#include "packedVector.h"
#include "packedMatrix.h"
#include "tarjan.h"

void testTarjan() {
   float m[5][5];
   PackedMatrix* packed;

   for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
         if (i == j)
            m[i][j] = i+j+1;
         else
            m[i][j] = 0;
      }
   }
   m[1][2] = 1;
   m[0][2] = 2;
   m[2][4] = 3;
   m[4][0] = 10;

   packed = packMatrix((float*) m, 5, 10);

   printf("\n");
   //printPackedMatrix(packed);
   printPackedMatrixAsUnpacked(packed);
   printf("\n");
   getchar();

   free(tarjan(packed));

   //printPackedMatrix(packed);
   //printPackedMatrixExplicitly(packed);

   freePackedMatrix(packed);
}

void testPackedVector() {
   unsigned int n = 10;
   float a = 2;
   float* w;
   float* v = malloc(sizeof(float) * n);
   PackedVector* p, * q;

   for (int i = 0; i < n; i++) {
      if (i % 2 == 0)
         v[i] = 0;
      else
         v[i] = i*i;
   }

   p = gather(v, n);

   for (int i = 0; i < p->tau; i++) {
      printf("(%d, %.0f)\n", p->index[i], p->value[i]);
   }

   w = scatter(p);

   printf("\nP: ");
   for (int i = 0; i < n; i++) {
      printf("%.0f ", w[i]);
   }

   for (int i = 0; i < n; i++) {
      w[i]++;
   }

   printf("\nQ: ");
   for (int i = 0; i < n; i++) {
      printf("%.0f ", w[i]);
   }

   q = gather(w, n);

   printf("\np*q = %0.f\n", innerProduct(p, q));
   printf("\np + aq = %0.f\n", lazyAddMultiple(p, a, q));

   free(v);
   free(w);
   freePackedVector(p);
   freePackedVector(q);
}

int main(void) {
   testTarjan();
}
