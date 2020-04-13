\name{matprint}
\alias{matprint}
\alias{print.matprint}
\title{ Print beginning and end of big matrix }
\description{
  Print beginning and end of big matrix
}
\usage{
matprint(x, maxdim = c(16, 16), digits = getOption("digits"))
\method{print}{matprint}(x, quote = FALSE, right = TRUE, \dots)
}
\arguments{
  \item{x}{ a \code{\link{matrix}} }
  \item{maxdim}{ max number of rows and columns for printing }
  \item{digits}{ see \code{\link{format}} }
  \item{quote}{ see \code{\link{print}} }
  \item{right}{ see \code{\link{print}} }
  \item{\dots}{ see \code{\link{print}} }
}
\value{
  a list of class 'matprint' with components
  \item{ subscript }{ a list with four vectors of subscripts: row begin, column begin, row end, column end  }
  \item{ example }{ the extracted example matrix as.characer including seperators }
  \item{ rsep }{ logical scalar indicating whether row seperator is included }
  \item{ csep }{ logical scalar indicating whether column seperator is included }
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{vecprint}} }
\examples{
  matprint(matrix(1:(300*400), 300, 400))
}
\keyword{ array }
\keyword{ print }
