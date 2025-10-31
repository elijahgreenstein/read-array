# `read_array`

The C code in `src` provides two functions to read data from simple CSV or TSV files into C arrays:

- `read_darray`: Load data into an array of `double` values.
- `read_iarray`: Load data into an array of `int` values.

Note that the 2D data is stored as a 1D array in memory.
Use index `i * p + j`, where `p` is the number of columns, to access zero-indexed row `i`, column `j`.

## Parameters

Both functions take the following parameters:

| Parameter  | Description                                                     |
| ---------- | ----------------------------------------------------------------|
| `file`     | File stream (the data).                                         |
| `delim`    | Field delimiter, separating values on each line.                |
| `array`    | Address of array of `double`/`int` values (modified in place).  |
| `n`        | Number of rows (modified in place).                             |
| `p`        | Number of columns (modified in place).                          |

Note that `array`, `n`, and `p` are modified in place;
hence, pass the addresses of the variables to the relevant function.

## Return values

If the load succeeds, then the function returns the number of rows of data, `n` (an `int` greater than `0`).
If the load fails, then the function returns an error code (an `int` less than `1`).

### Error codes

| Error    | Description                                                |
| -------- | -----------------------------------------------------------|
| `0`      | The file stream points to `NULL`.                          |
| `-1`     | Found inconsistent number of fields after the first line.  |
| `-2`     | Last line does not end with a newline character (`\n`).    |
| `-3`     | Failed to allocate memory for the array with `malloc`.     |
| `-4`     | Failed to load a value or encountered invalid character.   |

## Example usage

- Load array
- Access value in second row, third column (i.e. `a[1][2]` of zero-indexed array)
- Free memory

```c
FILE *file = fopen("data.csv", "r");
char delim = ',';
double *array = NULL;
int n, p;
double val;
int res;

res = read_darray(file, delim, &array, &n, &p);
/* Check that return value is positive (not an error code). */
if (res > 0 && n > 1 && p > 2) {
  /* Check that index `a[1][2]` exists. */
  if (n > 1 && p > 2) {
    val = *(array + (1 * p + 2));
    free(array);
    darray = NULL;
  }
}
```

## Tests

The C code in `test` tests the functions on the data in `test/data`.
Use the `Makefile` to compile the test code and run the tests:

```
make tests
make runtests
```

Use `make cleantests` to remove the compiled test code.

