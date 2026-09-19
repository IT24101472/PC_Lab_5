#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NPOINTS 2000
#define MAXITER 2000

struct complex {
    double real;
    double imag;
};

int main() {

    int i, j, iter, numoutside = 0;
    double area, error, ztemp;
    double tstart, tstop, tcalc;

    struct complex z, c;

    /* Start timing */
    tstart = omp_get_wtime();

    for (i = 0; i < NPOINTS; i++) {

        for (j = 0; j < NPOINTS; j++) {

            c.real = -2.0
                   + 2.5 * (double)(i) / (double)(NPOINTS)
                   + 1.0e-7;

            c.imag = 1.125
                   * (double)(j) / (double)(NPOINTS)
                   + 1.0e-7;

            z = c;

            for (iter = 0; iter < MAXITER; iter++) {

                ztemp = (z.real * z.real)
                      - (z.imag * z.imag)
                      + c.real;

                z.imag = z.real * z.imag * 2 + c.imag;
                z.real = ztemp;

                if ((z.real * z.real + z.imag * z.imag) > 4.0e0) {
                    numoutside++;
                    break;
                }
            }
        }
    }

    /* Stop timing */
    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    area = 2.0 * 2.5 * 1.125
         * (double)(NPOINTS * NPOINTS - numoutside)
         / (double)(NPOINTS * NPOINTS);

    error = area / (double)NPOINTS;

    printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",
           area, error);

    printf("Execution time = %f seconds\n", tcalc);

    return 0;
}
