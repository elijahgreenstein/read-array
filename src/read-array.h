#ifndef LOAD_ARRAY_H_
#define LOAD_ARRAY_H_


/**
 * Load 2D `double` data from file stream.
 *
 * This function determines the dimensions (n x p) of the data in `file` (values
 * separated by `delim`), allocates sufficient memory, points `array` to the
 * memory block, and loads the data into the array.
 * 
 * Note that the 2D data is stored as a 1D array. Use index `i * p + j` to
 * access row `i`, column `j` (zero-indexed).
 * 
 * If successful, the function modifies `n`, `p`, and `a` in place and returns
 * the number of rows `n` (>= 1). If unsuccessful, the function returns an error
 * code (< 1), points `a` to `NULL`, and modifies `n` and `p` as follows:
 * 
 * - Error code `0`: The file stream points to `NULL`.
 *     - `n` and `p` both set to `0`.
 * - Error code `-1`: Found inconsistent number of fields after the first line.
 *     - `n` set to the zero-indexed line where the error was encountered.
 *     - `p` set to the number of fields found on the first line.
 * - Error code `-2`: Last line does not end with a newline character (`\n`).
 *     - `n` set to one less than the number of rows.
 *     - `p` set to the number of fields found on the first line.
 * - Error code `-3`: Failed to allocate memory for the array with `malloc`.
 *     - `n` and `p` set to the number of rows and columns found.
 * - Error code `-4`: Failed to load a value or encountered invalid character.
 *     - `n` and `p` set to zero-indexed row and column of problem field.
 * 
 * @param file File stream.
 * @param delim Field delimiter.
 * @param array Array address (modified in place).
 * @param n Number of rows (modified in place).
 * @param p Number of columns (modified in place).
 * @return Number of rows (n) if successful; otherwise error code.
 *
 * Example usage: Load array; access value in second row, third column (i.e.
 * `a[1][2]`, for zero-indexed array); free memory.
 * 
 * ```
 * FILE *dfile = fopen("test/data/double.csv", "r");
 * char delim = ',';
 * double *darray = NULL;
 * int n, p;
 * double dval;
 * int res;
 * 
 * res = read_darray(dfile, delim, &darray, &n, &p);
 * if (res > 0 && n > 1 && p > 2) {
 *   dval = *(darray + (1 * p + 2));
 *   free(darray);
 *   darray = NULL;
 * }
 * ```
 */
int read_darray(FILE *file, char delim, double **array, int *n, int *p);


/**
 * Load 2D `int` data from file stream.
 *
 * This function determines the dimensions (n x p) of the data in `file` (values
 * separated by `delim`), allocates sufficient memory, points `array` to the
 * memory block, and loads the data into the array.
 * 
 * Note that the 2D data is stored as a 1D array. Use index `i * p + j` to
 * access row `i`, column `j` (zero-indexed).
 * 
 * If successful, the function modifies `n`, `p`, and `a` in place and returns
 * the number of rows `n` (>= 1). If unsuccessful, the function returns an error
 * code (< 1), points `a` to `NULL`, and modifies `n` and `p` as follows:
 * 
 * - Error code `0`: The file stream points to `NULL`.
 *     - `n` and `p` both set to `0`.
 * - Error code `-1`: Found inconsistent number of fields after the first line.
 *     - `n` set to the zero-indexed line where the error was encountered.
 *     - `p` set to the number of fields found on the first line.
 * - Error code `-2`: Last line does not end with a newline character (`\n`).
 *     - `n` set to one less than the number of rows.
 *     - `p` set to the number of fields found on the first line.
 * - Error code `-3`: Failed to allocate memory for the array with `malloc`.
 *     - `n` and `p` set to the number of rows and columns found.
 * - Error code `-4`: Failed to load a value or encountered invalid character.
 *     - `n` and `p` set to zero-indexed row and column of problem field.
 * 
 * @param file File stream.
 * @param delim Field delimiter.
 * @param array Array address (modified in place).
 * @param n Number of rows (modified in place).
 * @param p Number of columns (modified in place).
 * @return Number of rows (n) if successful; otherwise error code.
 *
 * Example usage: Load array; access value in second row, third column (i.e.
 * `a[1][2]`, for zero-indexed array); free memory.
 * 
 * ```
 * FILE *ifile = fopen("test/data/int.csv", "r");
 * char delim = ',';
 * int *iarray = NULL;
 * int n, p;
 * int ival;
 * int res;
 * 
 * res = read_iarray(ifile, delim, &iarray, &n, &p);
 * if (res > 0 && n > 1 && p > 2) {
 *   ival = *(iarray + (1 * p + 2));
 *   (ival == 6) ? printf("- int success\n") : printf("- int fail\n");
 *   free(iarray);
 *   iarray = NULL;
 * }
 * ```
 */
int read_iarray(FILE *file, char delim, int **array, int *n, int *p);


#endif
