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

int main(int argc, char* argv[]) {
  // Checks if input filename was given as commandline argument
  if (argc < 2) {
    printf("The input filename must be given as an argument\n");
    return 1;
  }

  FILE* inputFile;
  inputFile = fopen(argv[1], "r");

  // Checks if the file opened successfully
  if (!inputFile) {
    printf("The file couldn't be opened, please check the file name\n");
    return 1;
  }

  int nodeCount, edgeCount;
  fscanf(inputFile, "%d", &nodeCount);
  fscanf(inputFile, "%d", &edgeCount);

  int** adjacencyMatrix = getAdjacencyMatrix(nodeCount);

  // Adds each edge to the Adjacency Matrix one by one
  for (int edge = 0; edge < edgeCount; edge++) {
    int node1, node2;
    fscanf(inputFile, "%d", &node1);
    fscanf(inputFile, "%d", &node2);
    // Check to make sure node number inputted is valid
    if (node1 > nodeCount || node2 > nodeCount || node1 < 1 || node2 < 1) {
      printf("Invalid value entered; node number must be between 1 and %d\n",
             nodeCount);
      for (int row = 0; row < nodeCount; row++) {
        free(adjacencyMatrix[row]);
      }
      free(adjacencyMatrix);
      fclose(inputFile);
      return 1;
    }
    adjacencyMatrix[node1 - 1][node2 - 1] = 1;
    adjacencyMatrix[node2 - 1][node1 - 1] = 1;
  }

  int* degreeSequence = getDegreeSequence(nodeCount, adjacencyMatrix);
  for (int i = 0; i < nodeCount; i++) {
    printf("%d ", degreeSequence[i]);
  }
  printf("\n");

  // Frees the allocated memory
  for (int row = 0; row < nodeCount; row++) {
    free(adjacencyMatrix[row]);
  }
  free(adjacencyMatrix);
  free(degreeSequence);

  fclose(inputFile);

  return 0;
}
