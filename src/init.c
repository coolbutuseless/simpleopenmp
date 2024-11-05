
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP pdist_c_      (SEXP x_, SEXP y_);
extern SEXP pdist_openmp_ (SEXP x_, SEXP y_, SEXP nthreads_);
extern SEXP has_openmp_(void);

static const R_CallMethodDef CEntries[] = {
  
  {"pdist_c_"      , (DL_FUNC) &pdist_c_      , 2},
  {"pdist_openmp_" , (DL_FUNC) &pdist_openmp_ , 3},
  {"has_openmp_"   , (DL_FUNC) &has_openmp_   , 0},
  {NULL , NULL, 0}
};


void R_init_simpleopenmp(DllInfo *info) {
  R_registerRoutines(
    info,      // DllInfo
    NULL,      // .C
    CEntries,  // .Call
    NULL,      // Fortran
    NULL       // External
  );
  R_useDynamicSymbols(info, FALSE);
}



