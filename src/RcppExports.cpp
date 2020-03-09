// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// osc1337_
bool osc1337_(std::string file, std::string bg, double width, double height, double pointsize, bool standalone, Rcpp::List aliases);
RcppExport SEXP _osc1337_osc1337_(SEXP fileSEXP, SEXP bgSEXP, SEXP widthSEXP, SEXP heightSEXP, SEXP pointsizeSEXP, SEXP standaloneSEXP, SEXP aliasesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type file(fileSEXP);
    Rcpp::traits::input_parameter< std::string >::type bg(bgSEXP);
    Rcpp::traits::input_parameter< double >::type width(widthSEXP);
    Rcpp::traits::input_parameter< double >::type height(heightSEXP);
    Rcpp::traits::input_parameter< double >::type pointsize(pointsizeSEXP);
    Rcpp::traits::input_parameter< bool >::type standalone(standaloneSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type aliases(aliasesSEXP);
    rcpp_result_gen = Rcpp::wrap(osc1337_(file, bg, width, height, pointsize, standalone, aliases));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_osc1337_osc1337_", (DL_FUNC) &_osc1337_osc1337_, 7},
    {NULL, NULL, 0}
};

RcppExport void R_init_osc1337(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
