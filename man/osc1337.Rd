\name{osc1337}
\alias{osc1337}
\alias{show1337}
\title{Put to OSC-52 clipboard}
\usage{
osc1337(filename, ...)
show1337(filename, size=c('auto', 'auto'))
}
\arguments{
  \item{filename}{File to use}
  \item{size}{Width and height tuple as string. }
  \item{...}{Key-value pairs of file attributes}
}
\value{
  NULL
}
\description{
  In the right terminal, download a file or show an image.

  \code{size} may be \code{auto}, or number of character cells, Npx or N\%.
}
\examples{
  \dontrun{
  osc1337("data.csv")
  show1337("Rplot.png")
  }
}
