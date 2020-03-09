
#include <Rcpp.h>
using namespace Rcpp;

void pngDumpCallback(...){
  
}


pDevDesc osc_driver_new(int bg, int height, int width, int pointsize) {
  
  pDevDesc dd = (DevDesc*) calloc(1, sizeof(DevDesc));
  if (dd == NULL)
    return dd;
  
  dd->startfill = bg;
  dd->startcol = R_RGB(80, 80, 80);
  dd->startps = pointsize;
  dd->startlty = 0;
  dd->startfont = 1;
  dd->startgamma = 1;
  
  // Callbacks
  dd->activate = NULL;
  dd->deactivate = NULL;
  dd->close = (void (*)(pDevDesc)) pngDumpCallback;
  dd->clip = (void (*)(double, double, double, double, pDevDesc)) pngDumpCallback;
  dd->size = (void (*)(double*, double*, double*, double*, pDevDesc)) pngDumpCallback;
  dd->newPage = (void (*)(pGEcontext, pDevDesc)) pngDumpCallback;
  dd->line = (void (*)(double, double, double, double, pGEcontext, pDevDesc)) pngDumpCallback;
  dd->text = (void (*)(double, double, const char*, double, double, pGEcontext, pDevDesc)) pngDumpCallback;
  dd->strWidth = (double (*)(const char*, pGEcontext, pDevDesc)) pngDumpCallback;
  dd->rect = (void (*)(double, double, double, double, pGEcontext, pDevDesc)) pngDumpCallback;
  dd->circle = (void (*)(double, double, double, pGEcontext, pDevDesc)) pngDumpCallback;
  dd->polygon = (void (*)(int, double*, double*, pGEcontext, pDevDesc)) pngDumpCallback;
  dd->polyline = (void (*)(int, double*, double*, pGEcontext, pDevDesc)) pngDumpCallback;
  dd->path = (void (*)(double*, double*, int, int*, Rboolean, pGEcontext, pDevDesc)) pngDumpCallback;
  dd->mode = NULL;
  dd->metricInfo = (void (*)(int, pGEcontext, double*, double*, double*, pDevDesc)) pngDumpCallback;
  dd->cap = NULL;
  dd->raster = NULL;
  
  // UTF-8 support
  dd->wantSymbolUTF8 = (Rboolean) 1;
  dd->hasTextUTF8 = (Rboolean) 1;
  dd->textUTF8 = NULL;//svg_text;
  dd->strWidthUTF8 = NULL;//svg_strwidth;
  
  // Screen Dimensions in pts
  dd->left = 0;
  dd->top = 0;
  dd->right = width * 72;
  dd->bottom = height * 72;
  
  // Magic constants copied from other graphics devices
  // nominal character sizes in pts
  dd->cra[0] = 0.9 * pointsize;
  dd->cra[1] = 1.2 * pointsize;
  // character alignment offsets
  dd->xCharOffset = 0.4900;
  dd->yCharOffset = 0.3333;
  dd->yLineBias = 0.2;
  // inches per pt
  dd->ipr[0] = 1.0 / 72.0;
  dd->ipr[1] = 1.0 / 72.0;
  
  // Capabilities
  dd->canClip = TRUE;
  dd->canHAdj = 0;
  dd->canChangeGamma = FALSE;
  dd->displayListOn = FALSE;
  dd->haveTransparency = 2;
  dd->haveTransparentBg = 2;
  
  dd->deviceSpecific = NULL;
  return dd;
}

void makeDevice(std::string bg_, double width, double height, double pointsize) {
  
  int bg = R_GE_str2col(bg_.c_str());
  
  R_GE_checkVersionOrDie(R_GE_version);
  R_CheckDeviceAvailable();
  BEGIN_SUSPEND_INTERRUPTS {
    pDevDesc dev = osc_driver_new(bg, width, height, pointsize);
    if (dev == NULL)
      Rcpp::stop("Failed to start OSC proxy device");
    
    pGEDevDesc dd = GEcreateDevDesc(dev);
    GEaddDevice2(dd, "devOSC");
    GEinitDisplayList(dd);
    dd->displayListOn = TRUE;
    
  } END_SUSPEND_INTERRUPTS;
}

// [[Rcpp::export]]
bool osc1337_(std::string bg="transparent", double width=400, double height=300, double pointsize=12) {

  makeDevice(bg, width, height, pointsize);

  return true;
}

