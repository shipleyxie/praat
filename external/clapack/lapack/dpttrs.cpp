#include "clapack.h"
#include "f2cP.h"

/* Subroutine */ int dpttrs_(integer *n, integer *nrhs, double *d__,
	double *e, double *b, integer *ldb, integer *info)
{
	/* Table of constant values */
	static integer c__1 = 1;
	static integer c_n1 = -1;

    /* System generated locals */
    integer b_dim1, b_offset, i__1, i__2, i__3;

    /* Local variables */
    integer j, jb, nb;


/*  -- LAPACK routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DPTTRS solves a tridiagonal system of the form */
/*     A * X = B */
/*  using the L*D*L' factorization of A computed by DPTTRF.  D is a */
/*  diagonal matrix specified in the vector D, L is a unit bidiagonal */
/*  matrix whose subdiagonal is specified in the vector E, and X and B */
/*  are N by NRHS matrices. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The order of the tridiagonal matrix A.  N >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of right hand sides, i.e., the number of columns */
/*          of the matrix B.  NRHS >= 0. */

/*  D       (input) DOUBLE PRECISION array, dimension (N) */
/*          The n diagonal elements of the diagonal matrix D from the */
/*          L*D*L' factorization of A. */

/*  E       (input) DOUBLE PRECISION array, dimension (N-1) */
/*          The (n-1) subdiagonal elements of the unit bidiagonal factor */
/*          L from the L*D*L' factorization of A.  E can also be regarded */
/*          as the superdiagonal of the unit bidiagonal factor U from the */
/*          factorization A = U'*D*U. */

/*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS) */
/*          On entry, the right hand side vectors B for the system of */
/*          linear equations. */
/*          On exit, the solution vectors, X. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= max(1,N). */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -k, the k-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments. */

    /* Parameter adjustments */
    --d__;
    --e;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -1;
    } else if (*nrhs < 0) {
	*info = -2;
    } else if (*ldb < std::max(1_integer,*n)) {
	*info = -6;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DPTTRS", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
	return 0;
    }

/*     Determine the number of right-hand sides to solve at a time. */

    if (*nrhs == 1) {
	nb = 1;
    } else {
/* Computing MAX */
	i__1 = 1, i__2 = ilaenv_(&c__1, "DPTTRS", " ", n, nrhs, &c_n1, &c_n1);
	nb = std::max(i__1,i__2);
    }

    if (nb >= *nrhs) {
	dptts2_(n, nrhs, &d__[1], &e[1], &b[b_offset], ldb);
    } else {
	i__1 = *nrhs;
	i__2 = nb;
	for (j = 1; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
/* Computing MIN */
	    i__3 = *nrhs - j + 1;
	    jb = std::min(i__3,nb);
	    dptts2_(n, &jb, &d__[1], &e[1], &b[j * b_dim1 + 1], ldb);
/* L10: */
	}
    }

    return 0;

/*     End of DPTTRS */

} /* dpttrs_ */
