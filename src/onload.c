#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>



extern SEXP reset_mode(SEXP deviceIndex);
extern SEXP shim(SEXP deviceIndex);


static const R_CallMethodDef CallEntries[] = {
  {"reset_mode", (DL_FUNC) &reset_mode, 1},
  {"shim", (DL_FUNC) &shim, 1},
  {NULL, NULL, 0}
};

void R_init_osc1337(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}