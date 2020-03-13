\name{put52}
\alias{put52}
\title{Put to OSC-52 clipboard}
\usage{
put52(...)
}
\arguments{
  \item{...}{A sequence of objects}
}
\value{
  NULL
}
\description{
  Paste together the elements of \code{...} and emit
  them with OSC-52 control codes. With the right
  terminal, they will be added to the system clipboard.
}
\examples{
  put52(1, 1)
  put52(10, 1)
}
