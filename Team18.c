// TEAM 18
// Member 1: Anurav Garg, 2021A7PS2782H
// Member 2: Dharanikanth Reddy, 2021A7PS0264H

#include <stdio.h>
#include <stdlib.h>

// Allocates and returns an nxn Adjacency Matrix, given n (the number of nodes)
int** getAdjacencyMatrix(int nodeCount) {
  int** adjacencyMatrix = (int**)malloc(nodeCount * sizeof(int*));
  for (int row = 0; row < nodeCount; row++) {
    adjacencyMatrix[row] = (int*)calloc(nodeCount, sizeof(int));
  }
  return adjacencyMatrix;
}

// Helper function used for Selection Sort
// Returns the index of the largest numerical value in an array, between the
// start and end indices (end index is excluded)
int getLargestValIndex(int startIndex, int endIndex, int* arr) {
  int largestValIndex = startIndex;
  while (++startIndex < endIndex) {
    if (arr[startIndex] > arr[largestValIndex]) {
      largestValIndex = startIndex;
    }
  }
  return largestValIndex;
}

// Uses Selection Sort algorithm to sort given number array in descending order
void selectionSortDescending(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    int largestValIndex = getLargestValIndex(i, size, arr);
    int temp = arr[i];
    arr[i] = arr[largestValIndex];
    arr[largestValIndex] = temp;
  }
}

// Returns the Degree Sequence for a given Adjacency Matrix
int* getDegreeSequence(int nodeCount, int** adjacencyMatrix) {
  int* degreeSequence = (int*)calloc(nodeCount, sizeof(int));
  for (int row = 0; row < nodeCount; row++) {
    for (int col = 0; col < nodeCount; col++) {
      if (adjacencyMatrix[row][col]) {
        degreeSequence[row]++;
      }
    }
  }

  selectionSortDescending(degreeSequence, nodeCount);
  return degreeSequence;
}

int** readGraphFromFile(int* nodeCount, int* edgeCount, FILE* inputFile) {
  fscanf(inputFile, "%d", nodeCount);
  fscanf(inputFile, "%d", edgeCount);

  int** adjacencyMatrix = getAdjacencyMatrix(*nodeCount);

  // Adds each edge to the Adjacency Matrix one by one
  for (int edge = 0; edge < *edgeCount; edge++) {
    int node1, node2;
    fscanf(inputFile, "%d", &node1);
    fscanf(inputFile, "%d", &node2);
    // Check to make sure node number inputted is valid
    if (node1 > *nodeCount || node2 > *nodeCount || node1 < 1 || node2 < 1) {
      printf(
          "Invalid node value entered; node number must be between 1 and the "
          "max number of nodes\n");
      for (int row = 0; row < *nodeCount; row++) {
        free(adjacencyMatrix[row]);
      }
      free(adjacencyMatrix);
      fclose(inputFile);
      // return 1;
    }
    adjacencyMatrix[node1 - 1][node2 - 1] = 1;
    adjacencyMatrix[node2 - 1][node1 - 1] = 1;
  }

  fclose(inputFile);
  return adjacencyMatrix;
}

int main(int argc, char* argv[]) {
  // Checks if input filename was given as commandline argument
  if (argc < 3) {
    printf("The input filenames must be given as an argument\n");
    return 1;
  }

  FILE* inputFile1 = fopen(argv[1], "r");
  FILE* inputFile2 = fopen(argv[2], "r");

  // Checks if the files opened successfully
  if (!inputFile1 || !inputFile2) {
    printf(
        "One of the files couldn't be opened, please check the file names\n");
    return 1;
  }

  int nodeCount1, edgeCount1;
  int nodeCount2, edgeCount2;

  int** adjacencyMatrix1 =
      readGraphFromFile(&nodeCount1, &edgeCount1, inputFile1);
  int** adjacencyMatrix2 =
      readGraphFromFile(&nodeCount2, &edgeCount2, inputFile2);

  int* degreeSequence1 = getDegreeSequence(nodeCount1, adjacencyMatrix1);
  int* degreeSequence2 = getDegreeSequence(nodeCount2, adjacencyMatrix2);

  // for (int i = 0; i < nodeCount1; i++) {
  //   printf("%d ", degreeSequence1[i]);
  // }
  // printf("\n");

  // for (int i = 0; i < nodeCount2; i++) {
  //   printf("%d ", degreeSequence2[i]);
  // }
  // printf("\n");

  // Frees the allocated memory
  for (int row = 0; row < nodeCount1; row++) {
    free(adjacencyMatrix1[row]);
  }
  for (int row = 0; row < nodeCount2; row++) {
    free(adjacencyMatrix2[row]);
  }

  free(adjacencyMatrix1);
  free(degreeSequence1);
  free(adjacencyMatrix2);
  free(degreeSequence2);

  return 0;
}
