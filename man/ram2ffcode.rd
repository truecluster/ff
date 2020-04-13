\name{ram2ffcode}
\alias{ram2ffcode}
\alias{ram2ramcode}
\title{ Factor codings }
\description{
  Function \command{ram2ffcode} creates the \emph{internal} factor codes used by ff to store factor levels. Function \code{ram2ramcode} is a compatibility function used instead if \code{RETURN_FF==FALSE}.
}
\usage{
ram2ffcode(value, levels, vmode)
ram2ramcode(value, levels)
}
\arguments{
  \item{value}{ factor or character vector of values }
  \item{levels}{ character vector of factor levels }
  \item{vmode}{ one of the integer vmodes in \code{\link{.rammode}} }
}
\details{
  Factors stored in unsigned vmodes \code{\link{.vunsigned}} have their first level represented as 0L instead of 1L.
}
\value{
  A vector of integer values representing the correspnding factor levels.
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{factor}}, \code{\link{levels.ff}}, \code{\link{vmode}} }
\examples{
 ram2ffcode(letters, letters, vmode="byte")
 ram2ffcode(letters, letters, vmode="ubyte")
 ram2ffcode(letters, letters, vmode="nibble")
 message('note that ram2ffcode() does NOT warn that vmode="nibble" cannot store 26 levels')
}
\keyword{ IO }
\keyword{ data }
