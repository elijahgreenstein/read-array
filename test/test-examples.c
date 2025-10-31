#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/read-array.h"


int main(void) {
  printf("Testing comment block examples (`test-examples`):\n");

  FILE *dfile = fopen("test/data/double.csv", "r");
  FILE *ifile = fopen("test/data/int.csv", "r");
  char delim = ',';
  double *darray = NULL;
  int *iarray = NULL;
  int n, p;
  double dval;
  int ival;
  int res;
  
  res = read_darray(dfile, delim, &darray, &n, &p);
  if (res > 0 && n > 1 && p > 2) {
    dval = *(darray + (1 * p + 2));
    printf("- double: ");
    (dval == 14.15) ? printf("success\n") : printf("fail\n");
    free(darray);
    darray = NULL;
  }
  
  res = read_iarray(ifile, delim, &iarray, &n, &p);
  if (res > 0 && n > 1 && p > 2) {
    ival = *(iarray + (1 * p + 2));
    printf("- int   : ");
    (ival == 6) ? printf("success\n") : printf("fail\n");
    free(iarray);
    iarray = NULL;
  }

  return 0;
}
