#include <R.h>
#include <Rinternals.h>
#include <R_ext/GraphicsEngine.h>


void save_mode(int mode, pDevDesc dd) {
  if(mode != 0) dd->canChangeGamma = TRUE;
}

SEXP reset_mode(SEXP deviceIndex) {

  int i = INTEGER(deviceIndex)[0];
  
  pGEDevDesc gedd = GEgetDevice(i);
  
  
  SEXP out;
  PROTECT(out = allocVector(LGLSXP, 1)); 
  LOGICAL(out)[0] = gedd->dev->canChangeGamma;

  gedd->dev->canChangeGamma = FALSE;
  
  UNPROTECT(1);
  return out;
  
}

SEXP shim(SEXP deviceIndex) {

  int i = INTEGER(deviceIndex)[0];
  pGEDevDesc gedd = GEgetDevice(i);
  gedd->dev->mode = &save_mode;

  return R_NilValue;
}

