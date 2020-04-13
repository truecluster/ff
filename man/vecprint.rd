\name{vecprint}
\alias{vecprint}
\alias{print.vecprint}
\title{ Print beginning and end of big vector }
\description{
  Print beginning and end of big vector
}
\usage{
vecprint(x, maxlength = 16, digits = getOption("digits"))
 \method{print}{vecprint}(x, quote = FALSE, \dots)
}
\arguments{
  \item{x}{ a vector }
  \item{maxlength}{ max number of elements for printing }
  \item{digits}{ see \code{\link{format}} }
  \item{quote}{ see \code{\link{print}} }
  \item{\dots}{ see \code{\link{print}} }
}
\value{
  a list of class 'vecprint' with components
  \item{ subscript }{ a list with two vectors of subscripts: vector begin and vector end }
  \item{ example }{ the extracted example vector as.character including seperator }
  \item{ sep }{ the row seperator ":" }
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{matprint}} }
\examples{
  vecprint(10000:1)
}
\keyword{ print }
