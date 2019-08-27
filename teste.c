#include <stdio.h>
#include <stdlib.h>

#include "signatures.h"

int main(void) {
   unsigned int n = 10;
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

   free(v);
   free(w);
   freePackedVector(p);
}
