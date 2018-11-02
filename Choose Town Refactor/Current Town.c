#include "TspAcoSequential.h"
#include <stdlib.h>
#include <math.h>


extern int * allowedArray;
extern int * antPathArray;
extern double * probabilityArray;


int currentTown;

void CurrenTTown(int antIndex, int tabuListIndex)

{
  currentTown = * (antPathArray + ((antIndex * CITYCOUNT) + (tabuListIndex - 1)));
  printf("Current town %d\n", currentTown);

  int i;
  for(i = 0; i < CITYCOUNT; i++){
    * (probabilityArray + i) = 0;
}
