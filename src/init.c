
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP has_openmp_(void);

extern SEXP pdist_c_      (SEXP x_, SEXP y_);
extern SEXP pdist_openmp_ (SEXP x_, SEXP y_, SEXP nthreads_);

extern SEXP sleep_c_(SEXP N_);
extern SEXP sleep_openmp_(SEXP N_, SEXP nthreads_);

static const R_CallMethodDef CEntries[] = {
  
  {"has_openmp_"   , (DL_FUNC) &has_openmp_   , 0},
  
  {"pdist_c_"      , (DL_FUNC) &pdist_c_      , 2},
  {"pdist_openmp_" , (DL_FUNC) &pdist_openmp_ , 3},
  
  {"sleep_c_"      , (DL_FUNC) &sleep_c_      , 1},
  {"sleep_openmp_" , (DL_FUNC) &sleep_openmp_ , 2},
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



