typedef struct {
   float* value;
   unsigned int* colIndex;

   unsigned int* rowStart;
   unsigned int* rowLength;

   unsigned int n;
   unsigned int maxEntries;
} PackedMatrix;

void initPackedMatrix(PackedMatrix*, unsigned int, unsigned int);
PackedMatrix* newPackedMatrix(unsigned int, unsigned int);
void freePackedMatrix(PackedMatrix*);

PackedMatrix* packMatrix(float*, unsigned int, unsigned int);
float* unpackMatrix(PackedMatrix*);

void printPackedMatrix(PackedMatrix*);
void printPackedMatrixAsUnpacked(PackedMatrix*);
void printPackedMatrixAsUnpackedPermuted(PackedMatrix*, int*);
