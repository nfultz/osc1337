

oldopts <- new.env(parent = emptyenv())

.onAttach <- function(libname, pkgname) {

  if(Sys.getenv("RSTUDIO") == 1) {
    return(message("Not compatible with RStudio console or terminal."))
  }

  oldopts$i   <- nullpng()

  .Call("shim", as.integer(oldopts$i - 1), PACKAGE="osc1337")

  oldopts$pal <- palette()
  oldopts$par <- par(fg='grey50', col='grey50', col.axis='grey50', col.lab='grey50', col.main='grey50', col.sub='grey50')

  newpal <- adjustcolor(col=seq_along(palette()), 1, .7, .7, .7, offset=.6*c(1,1,1,1))

  palette(newpal)


  addTaskCallback(name="osc1337", function(expr, value, ok, visible) {

    if(dev.cur() != oldopts$i) return(invisible());


    dirty <- .Call("reset_mode", as.integer(oldopts$i - 1), PACKAGE="osc1337")

    if(dirty && ok && !visible) {
      osc1337()
    }

    TRUE
  })
}

.onDetach <- function(libpath) {
  if(Sys.getenv("RSTUDIO") == 1) {
    return(invisible())
  }
  dev.off(oldopts$i)
  palette(oldopts$pal)
  par(oldopts$par)
  removeTaskCallback("osc1337")
}


nullpng <- function(filename = nullfile(),
                    width = getOption("osc1337.width", 400),
                    height = getOption("osc1337.height", 300),
                    units = "px",
                    pointsize = getOption("osc1337.pointsize", 12),
                    bg = getOption("osc1337.bg", "transparent"),
                    ...) {

  if(!interactive()) message("Using `osc1337`` non-interactively. Logs may contain encoded image data.")

  png(filename = filename, width = width, height = height, units = units, pointsize = pointsize, bg=bg, ...)
  dev.control("enable")
  dev.cur()
}



osc1337 <- function(filename=tempfile(fileext = ".png"), inline=TRUE) {

  inline <- if(inline) "inline=1:" else ""
  size <- dev.size("px")

  i <- dev.copy(png, filename=filename, width=size[1], height=size[2])
  dev.off(i)

  if(getOption("osc1337.debug", FALSE)) {
      cat(filename, "\n", size, "\n")
      cat(length(readBin(filename, "raw", file.size(filename))), "\n")
  }

  escaper(
    '\033]1337;',
    'File=name=', base64enc::base64encode(charToRaw(basename(filename))), ';',
    'width=', size[1], ';',
    'height=', size[2], ';',
    inline,
    base64enc::base64encode(filename),
    '\a'
  )

}

notify <- function(title, body='') {
  escaper('\033]777;notify;', title, ';', body, '\a\n')
}

put52 <- function(...) {
  payload <- base64enc::base64encode(charToRaw(paste(..., collapse='\n')))
  escaper('\033]52;c;', payload, '\a')
}

escaper <- function(...) {
  if(requireNamespace("colorout")) try({
      if(colorout::isColorOut())
        on.exit(colorout::ColorOut())
      colorout::noColorOut()
  })

  if (nzchar(Sys.getenv("TMUX"))) escaper.tmux(...)
  else if (grepl("^screen", Sys.getenv("TERM"))) escaper.screen(...)
  else cat(..., sep='')
}

escaper.tmux <- function(...) cat('\033Ptmux;\033',...,'\033\\', sep='')


escaper.screen <- function(...) {
  limit <- 255 - 4
  s <- paste0(...)

  for(i in seq(0, nchar(s), by = limit))
    cat('\x1bP', substring(s, i+1, i+limit),  '\x1b\\', sep='')
}

