#include "signatures.h"
#include <stdlib.h>

void init(PackedVector* p, unsigned int n) {
   p->n = n;
   p->tau = 0;
   p->index = malloc(n*sizeof(unsigned int));
   p->value = malloc(n*sizeof(float));
}

PackedVector* newPackedVector(unsigned int n) {
   PackedVector* p = malloc(sizeof(PackedVector));

   init(p, n);

   return p;
}

void freePackedVector(PackedVector* p) {
   free(p->index);
   free(p->value);
   free(p);
}

PackedVector* pack(float* unpacked, unsigned int n) {
   PackedVector* packed = newPackedVector(n);

   for (int i = 0; i < n; i++) {
      if (unpacked[i] != 0) {
         packed->index[packed->tau] = i;
         packed->value[packed->tau] = unpacked[i];
         packed->tau++;
      }
   }

   return packed;
}

PackedVector* gather(float* unpacked, unsigned int n) {
   return pack(unpacked, n);
}

void unpack(PackedVector* packed, float* aux) {
   for (int i = 0; i < packed->tau; i++) {
      aux[packed->index[i]] = packed->value[i];
   }
}

float* arrayOfZeroes(int n) {
   float* aux = malloc(n * sizeof(float));

   for (int i = 0; i < n; i++)
      aux[i] = 0;

   return aux;
}

float* lazyUnpack(PackedVector* packed) {
   float* aux = arrayOfZeroes(packed->n);

   unpack(packed, aux);

   return aux;
}

float* scatter(PackedVector* packed) {
   return lazyUnpack(packed);
}

float dot(PackedVector* p, PackedVector* q, float* aux) {
   float sum = 0;

   unpack(q, aux);

   for (int i = 0; i < p->tau; i++) {
      sum += p->value[i]*aux[p->index[i]];
   }

   return sum;
}

float lazyDot(PackedVector* p, PackedVector* q) {
   float* aux = arrayOfZeroes(p->n);
   float r = dot(p, q, aux);

   free(aux);
   return r;
}

float innerProduct(PackedVector* p, PackedVector* q) {
   return lazyDot(p, q);
}
