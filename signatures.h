// does not store the elements ordered
typedef struct {
   unsigned int* index;
   float* value;

   unsigned int tau; // number of (explicitly stored) entries
   unsigned int n; // size, including zeroes
} PackedVector;


void init(PackedVector* p, unsigned int n);
PackedVector* newPackedVector(unsigned int n);
void freePackedVector(PackedVector* p);

PackedVector* pack(float* unpacked, unsigned int n);
void unpack(PackedVector* packed, float* aux);
PackedVector* gather(float* unpacked, unsigned int n);
float* scatter(PackedVector* packed);

float dot(PackedVector* p, PackedVector* q, float* w); // w is a preallocated unpacked array of zeroes

float innerProduct(PackedVector* p, PackedVector* q);
