

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


dev2osc <- function(i, filename=tempfile(fileext = ".png")) {
  me <- dev.cur()
  on.exit(dev.set(me))
  
  dev.set(i)
  
  dev.copy(png, filename=filename)
  dev.off()
  
  cat(filename)
  cat(length(readBin(filename, "raw", file.size(filename))))
  
}
