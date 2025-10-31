#include <stdio.h>
#include <stdlib.h>
#include "read-array.h"


/**
 * Return EOF or number of fields separated by `d` on line `n` of file `f`.
 */
int count_fields(FILE *f, char d, int n) {
  char c;
  int dc; /* Delimiter count */

  dc = 0;
  while ( (c = getc(f)) != EOF && c != '\n') {
    if (c == d)
      dc++;
  }
  if (c == EOF)
    return EOF;
  return dc + 1; /* Return fields (number of delimiters + 1). */
}


/**
 * Count number of lines `n` and fields `p` (separated by `d`) in file `f`.
 */
int get_dim(FILE *f, char d, int *n, int *p){
  
  *p = count_fields(f, d, 1); /* Number of fields in first row. */
  int p2; /* Number of fields in subsequent rows. */

  for (*n = 1; (p2 = count_fields(f, d, *n)) != EOF; (*n)++) {
    if (*p != p2)
      return 0; /* Inconsistent number of fields. */
  }
  return *p; /* Must be greater than or equal to 1. */
}


/**
 * Load n x p double data in `f` into `a`; return `n` rows on success.
 */
int scan_ddata(FILE *f, char d, double *a, int *n, int *p) {
  int i;
  int j;
  char c;
  double val;

  for (i = 0; i < *n; i++) {
    for (j = 0; j < *p; j++) {
      if (
          (fscanf(f, "%lf%c", &val, &c) != 2) ||
          (j < *p - 1 && c != d) ||
          (j == *p - 1 && c != '\n')
         ) {
        *n = i;
        *p = j;
        return 0;
      }
      else
        a[i * *p + j] = val;
    }
  }

  return *n;
}


/**
 * Load n x p int data in `f` into `a`; return `n` rows on success.
 */
int scan_idata(FILE *f, char d, int *a, int *n, int *p) {
  int i;
  int j;
  char c;
  int val;

  for (i = 0; i < *n; i++) {
    for (j = 0; j < *p; j++) {
      if (
          (fscanf(f, "%d%c", &val, &c) != 2) ||
          (j < *p - 1 && c != d) ||
          (j == *p - 1 && c != '\n')
         ) {
        *n = i;
        *p = j;
        return 0;
      }
      else
        a[i * *p + j] = val;
    }
  }

  return *n;
}


int read_darray(FILE *f, char d, double **a, int *n, int *p) {
  *a = NULL;

  if (f == NULL)
    return *n = *p = 0;

  if (get_dim(f, d, n, p) < 1)
    return -1; /* Inconsistent number of fields. */

  fseek(f, -1, SEEK_CUR);
  if (getc(f) != '\n')
    return -2; /* Last line does not end with newline. */

  rewind(f);

  *a = (double *) malloc(sizeof(double) * *n * *p);
  if (a == NULL)
    return -3; /* Failed to allocate memory. */

  if (scan_ddata(f, d, *a, n, p) < 1) {
    free(*a);
    return -4; /* Error loading value. */
  }

  return *n;
}


int read_iarray(FILE *f, char d, int **a, int *n, int *p) {
  *a = NULL;

  if (f == NULL) {
    return *n = *p = 0;
  }

  if (get_dim(f, d, n, p) < 1)
    return -1; /* Inconsistent number of fields. */

  fseek(f, -1, SEEK_CUR);
  if (getc(f) != '\n')
    return -2; /* Last line does not end with newline. */

  rewind(f);

  *a = (int *) malloc(sizeof(int) * *n * *p);
  if (a == NULL)
    return -3; /* Failed to allocate memory. */

  if (scan_idata(f, d, *a, n, p) < 1) {
    free(*a);
    return -4; /* Error loading value. */
  }

  return *n;
}
