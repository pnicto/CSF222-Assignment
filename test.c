#include <stdio.h>
#include <stdlib.h>

void nextListPermutation(int* startPtr, int* endPtr, int* ACTUALSTARTPTR) {
  if (startPtr == endPtr) {
    for (int* i = ACTUALSTARTPTR; i != endPtr; i++) {
      printf("%d ", *i);
    }
    printf("\n");
    return;
  }

  for (int* i = startPtr; i != endPtr; i++) {
    int temp = *startPtr;
    *startPtr = *i;
    *i = temp;
    nextListPermutation(startPtr + 1, endPtr, ACTUALSTARTPTR);
    *i = *startPtr;
    *startPtr = temp;
  }
}

int main() {
  printf("Enter the number of numbers\n");
  int n;
  scanf("%d", &n);
  int* seq = (int*)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    seq[i] = i;
  }

  nextListPermutation(&(seq[0]), &(seq[n]), &(seq[0]));
}

// SOME LEFTOVER TEST CODE FROM THE MAIN FILE I DIDN'T WANNA DELETE
// for (int i = 0; i < nodeCount1; i++) {
//   printf("%d ", degreeSequence1[i]);
// }
// printf("\n");

// for (int i = 0; i < nodeCount2; i++) {
//   printf("%d ", degreeSequence2[i]);
// }
// printf("\n");