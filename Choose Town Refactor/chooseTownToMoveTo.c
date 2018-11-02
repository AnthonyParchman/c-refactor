#include "TspAcoSequential.h"
#include <stdlib.h>
#include <math.h>

extern int * allowedArray;
extern int * antPathArray;
extern double * probabilityArray;
extern int * tabuArray;
extern double * trailArray;
extern double * visibilityArray;

int currentTown;

void chooseTownToMoveTo(int antIndex, int tabuListIndex)
{


  currentTown = * (antPathArray + ((antIndex * CITYCOUNT) + (tabuListIndex - 1)));
  printf("Current town %d\n", currentTown);

  int i;
  for(i = 0; i < CITYCOUNT; i++){
    * (probabilityArray + i) = 0;
}

  double trailComponent;
  double visibilityComponent;
  double transitionProbabilityDenominator = 0;
  double transitionRoll = 0.0;
  double probabilitySum;
  double randomNumber;
  int rerollCount = 0;
  int nextCity=0;


  // use the allowed list to make the probability array
  for(int cityMinusOne = 0; cityMinusOne < CITYCOUNT; cityMinusOne ++) {
    if(1 == * ( allowedArray + (antIndex * CITYCOUNT) + cityMinusOne )) {
      trailComponent = pow( * (trailArray + ((currentTown-1) * CITYCOUNT) +cityMinusOne), ALPHA);
      visibilityComponent = pow( * (visibilityArray + ((currentTown-1) * CITYCOUNT) + cityMinusOne) , BETA);
      * ( probabilityArray + cityMinusOne ) = trailComponent * visibilityComponent;
      transitionProbabilityDenominator = transitionProbabilityDenominator +
      * ( probabilityArray + cityMinusOne );
    }
  }
  while(0.0 == transitionRoll) {
    randomNumber = (double)rand() / ((double)RAND_MAX + 1);
    printf("Our random number was %f\n", randomNumber);
    transitionRoll = transitionProbabilityDenominator * randomNumber;
    rerollCount= rerollCount +1;

    if(100 == rerollCount) {
      break;
    }
  }
  probabilitySum = 0;
  for (i = 0; i < CITYCOUNT; i++) {
    probabilitySum = probabilitySum + * ( probabilityArray + i );
    if(probabilitySum > transitionRoll) {
      nextCity = i+1;
      break;
    }

  }

  if ( 0 == nextCity ) {
    for (i = 0; i < CITYCOUNT; i++) {
      if(1 == * ( allowedArray + ( antIndex * CITYCOUNT) + i)) {
        nextCity =  i + 1;
        break;
      }
    }
  }


  * ( antPathArray + (tabuListIndex + (antIndex * CITYCOUNT))) = nextCity;
}
