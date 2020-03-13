\name{notify}
\alias{notify}
\title{OSC-777 notifications}
\usage{
notify(title, body="")
}
\arguments{
  \item{title}{A string}
  \item{body}{A string}
}
\value{
  NULL
}
\description{
  With the right terminal, displays a notification.
}
\details{
  From the original script:
  \enumerate{

  \item The title should not have a semi-colon in it.
  \item Neither field should have escape sequences in them.
  \item Best to stick to plain text.
  }
}
\examples{
  notify("Here I Am", "Rock You Like A Hurricane")
}
