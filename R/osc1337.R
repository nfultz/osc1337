

osc1337 <- function(filename=NA,
                    width=320, height=320, 
                    units= "px", pointsize=12, 
                    bg="transparent", ...) {

  if(is.na(filename))   
    filename <- tempfile(fileext = "png")

    
  png(filename = filename, width = width, height = height, units = units, pointsize = pointsize, bg=bg, ...)
  dev.control("enable")
  i <- dev.current()
  
}


.onload <- function(...) {
  if(!interactive()) warning("Using osc1337 non-interactively")
}


dev2osc <- function() {
  me <- dev.current()
  on.exit(dev.set(me))
  
  i <- 1
  
  dev.copy(png)
  dev.off()
  
}