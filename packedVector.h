// does not store the elements ordered
typedef struct {
   unsigned int* index;
   float* value;

   unsigned int tau; // number of (explicitly stored) entries
   unsigned int n; // size, including zeroes
} PackedVector;


void initPackedVector(PackedVector*, unsigned int);
PackedVector* newPackedVector(unsigned int);
void freePackedVector(PackedVector*);

PackedVector* pack(float*, unsigned int);
void unpack(PackedVector*, float*);
PackedVector* gather(float*, unsigned int);
float* scatter(PackedVector*);

float dot(PackedVector*, PackedVector*, float*); // w is a preallocated unpacked array of zeroes
float innerProduct(PackedVector*, PackedVector*);

float addMultiple(PackedVector*, float, PackedVector*, float*); // x <- x + ay
float lazyAddMultiple(PackedVector* x, float a, PackedVector* y);
