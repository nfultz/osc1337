
#include <Rcpp.h>
using namespace Rcpp;



pDevDesc osc_driver_new(int bg, double width, double height, double pointsize) {
  
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
  dd->close = NULL;//svg_close;
  dd->clip = NULL;//svg_clip;
  dd->size = NULL;//svg_size;
  dd->newPage = NULL;//svg_new_page;
  dd->line = NULL;//svg_line;
  dd->text = NULL;//svg_text;
  dd->strWidth = NULL;//svg_strwidth;
  dd->rect = NULL;//svg_rect;
  dd->circle = NULL;//svg_circle;
  dd->polygon = NULL;//svg_polygon;
  dd->polyline = NULL;//svg_polyline;
  dd->path = NULL;//svg_path;
  dd->mode = NULL;
  dd->metricInfo = NULL;//svg_metric_info;
  dd->cap = NULL;
  dd->raster = NULL;//svg_raster;
  
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

void makeDevice(std::string bg_, double width, double height,
                double pointsize) {
  
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
bool osc1337_(std::string file, std::string bg, double width, double height,
              double pointsize, bool standalone, Rcpp::List aliases) {
  
  makeDevice(bg, width, height, pointsize);
  
  return true;
}