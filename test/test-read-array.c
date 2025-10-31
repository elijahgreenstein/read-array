#include <stdio.h>
#include "../src/read-array.h"


struct testValidInt {
  char *f; /* file path */
  char d; /* delimiter */
  int n;
  int p;
  int sum;
} ivalid[] = {
  { "./test/data/data-int.csv", ',', 10, 3, -42 },
  { "./test/data/data-int.tsv", '\t', 10, 3, -42 },
};


struct testValidDouble {
  char *f; /* file path */
  char d; /* delimiter */
  int n;
  int p;
  double sum;
} dvalid[] = {
  { "./test/data/data-dbl.csv", ',', 10, 3, -1.0902907342491428 },
  { "./test/data/data-dbl.tsv", '\t', 10, 3, -1.0902907342491428 },
};


struct testInvalid {
  char *f; /* file path */
  char d; /* delimiter */
  int is_int;
  int err; /* error code */
  int line; /* error line */
  int field; /* error field */
} invalid[] = {
  { "./test/data/data-nonexistent.csv", ',', 0, 0, 0, 0 },
  { "./test/data/data-dbl-no-newline.csv", ',', 0, -2, 9, 3 },
  { "./test/data/data-dbl-unk-char-eol.csv", ',', 0, -4, 6, 2 },
  { "./test/data/data-dbl-unk-char.csv", ',', 0, -4, 7, 1 },
  { "./test/data/data-dbl-wrong-field.csv", ',', 0, -1, 8, 3 }
};


int isum(int *a, int n, int p) {
  int i;
  int j;
  int sum;

  sum = 0;

  for (i = 0; i < n; i++) {
    for (j = 0; j < p; j++) {
      sum += *(a + (i * p + j));
    }
  }

  return sum;
}


double dsum(double *a, int n, int p) {
  int i;
  int j;
  double sum;

  sum = 0.0;

  for (i = 0; i < n; i++) {
    for (j = 0; j < p; j++) {
      sum += *(a + (i * p + j));
    }
  }

  return sum;
}


int main() {
  printf("Testing `read_array` (`test-read-array`):\n");

  /* Number of tests and index */
  int t;
  int i;
  /* Arrays */
  int *a_i;
  double *a_d;
  /* Dimensions */
  int n;
  int p;
  /* File */
  FILE *f;
  /* Return value */
  int res;
  /* Check sum diff (double array), with allowed error 'eps'. */
  double diff;
  double eps = 1e-10;
  /* Print '.' for successful test, 'X' otherwise. */
  char s;

  /* Check valid integer data. */
  t = sizeof(ivalid) / sizeof(struct testValidInt);

  for (i = 0; i < t; i++) {
    s = '.';
    printf("- testing on '%s': ", ivalid[i].f);
    f = fopen(ivalid[i].f, "r");
    res = read_iarray(f, ivalid[i].d, &a_i, &n, &p);
    (res == n) ? printf(".") : printf("%c", s = 'X');
    (ivalid[i].n == n) ? printf(".") : printf("%c", s = 'X');
    (ivalid[i].p == p) ? printf(".") : printf("%c", s = 'X');
    (ivalid[i].sum == isum(a_i, n, p)) ? printf(".") : printf("%c", s = 'X');
    s == '.' ? printf(" success\n") : printf(" failed\n");
  }

  /* Check valid double data. */
  t = sizeof(dvalid) / sizeof(struct testValidDouble);

  for (i = 0; i < t; i++) {
    s = '.';
    printf("- testing on '%s': ", dvalid[i].f);
    f = fopen(dvalid[i].f, "r");
    res = read_darray(f, dvalid[i].d, &a_d, &n, &p);
    (res == n) ? printf(".") : printf("%c", s = 'X');
    (dvalid[i].n == n) ? printf(".") : printf("%c", s = 'X');
    (dvalid[i].p == p) ? printf(".") : printf("%c", s = 'X');
    /* Allow for minor error (< `eps`) in sum. */
    diff = dsum(a_d, n, p) - dvalid[i].sum;
    if (diff > 0.0)
      (diff < eps) ? printf(".") : printf("%c", s = 'X');
    else
      (-diff < eps) ? printf(".") : printf("%c", s = 'X');
    printf(" (sum diff: %.16f)", diff);
    s == '.' ? printf(" success\n") : printf(" failed\n");
  }


  /* Check invalid data. */
  t = sizeof(invalid) / sizeof(struct testInvalid);

  for (i = 0; i < t; i++) {
    s = '.';
    printf("- testing on '%s': ", invalid[i].f);
    f = fopen(invalid[i].f, "r");
    if (invalid[i].is_int) {
      res = read_iarray(f, invalid[i].d, &a_i, &n, &p);
    }
    else {
      res = read_darray(f, invalid[i].d, &a_d, &n, &p);
    }
    (res == invalid[i].err) ? printf(".") : printf("%c", s = 'X');
    (n == invalid[i].line) ? printf(".") : printf("%c", s = 'X');
    (p == invalid[i].field) ? printf(".") : printf("%c", s = 'X');
    s == '.' ? printf(" success\n") : printf(" failed\n");
  }

  return 0;
}
