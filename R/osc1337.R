

osc1337 <- function(filename='/dev/null',
                    width=320, height=320, 
                    units= "px", pointsize=12, 
                    bg="transparent", ...) {

    
  png(filename = filename, width = width, height = height, units = units, pointsize = pointsize, bg=bg, ...)
  dev.control("enable")
  i <- dev.current()
  
}


.onload <- function(...) {
  if(!interactive()) warning("Using osc1337 non-interactively")
}


dev2osc <- function(filename=tempfile(fileext = ".png")) {

  message(1)
  dev.copy(png, filename=filename)
  message(2)
  dev.off()
  
  message(3)
  cat(filename)
  message(4)
  cat(length(readBin(filename, "raw", file.size(filename))))
  
}
