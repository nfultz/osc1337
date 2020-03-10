

oldopts <- new.env(parent = emptyenv())

.onAttach <- function(libname, pkgname) {
  oldopts$i   <- nullpng()
  oldopts$pal <- palette()
  oldopts$par <- par(fg='grey50', col='grey50', col.axis='grey50', col.lab='grey50', col.main='grey50', col.sub='grey50')
  
  newpal <- adjustcolor(col=seq_along(palette()), 1, .7, .7, .7, offset=.6*c(1,1,1,1))
  
  palette(newpal)
}

.onDetach <- function(libpath) {
  dev.off(oldopts$i)
  palette(oldopts$pal)
  par(oldopts$par)
}


nullpng <- function(filename = nullfile(),
                    width = getOption("osc1337.width", 400),
                    height = getOption("osc1337.height", 300), 
                    units = "px", 
                    pointsize = getOption("osc1337.pointsize", 12), 
                    bg = getOption("osc1337.bg", "transparent"), 
                    ...) {

  if(!interactive()) warning("Using `osc1337`` non-interactively")
    
  png(filename = filename, width = width, height = height, units = units, pointsize = pointsize, bg=bg, ...)
  dev.control("enable")
  dev.cur()
}



osc1337 <- function(filename=tempfile(fileext = ".png")) {

  i <- dev.copy(png, filename=filename)
  size <- dev.size("px")
  dev.off(i)
  
  cat(filename, "\n", size, "\n")
  cat(length(readBin(filename, "raw", file.size(filename))), "\n")
  
  escaper(
    '\033]1337;',
    'File=name=', base64enc::base64encode(charToRaw(basename(filename))), ';',
    'width=', size[1], ';',
    'height=', size[2], ';',
    'inline=1:',
    base64enc::base64encode(filename),
    '\a'
  )
  
  
  # local name="$1"
  # local opts="inline=1;$2"
  # print_seq "$(printf '\033]1337;File=name=%s;%s%s:%s\a' \
  #   "$(echo "$(basename "${name}")" | b64enc)" \
  #   "$(dimensions "${name}")" \
  #   "${opts}" \
  #   "$(b64enc <"${name}")")"
}


notify <- function(title, body) {
  escaper('\033]777;notify;', title, ';', body, '\a\n')
}


escaper <- function(...) {
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

