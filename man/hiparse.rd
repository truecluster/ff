\name{hiparse}
\alias{hiparse}
\title{ Hybrid Index, parsing }
\description{
  \command{hiparse} implements the parsing done in Hybrid Index Preprocessing in order to avoid RAM for expanding index expressions.
  \emph{Not to be called directly}
}
\usage{
hiparse(x, envir, first = NA_integer_, last = NA_integer_)
}
\arguments{
  \item{x}{ an index expression, precisely: \code{\link{call}} }
  \item{envir}{ the environemtn in which to evaluate components of the index expression }
  \item{first}{ first index position found so far }
  \item{last}{ last index position found so far }
}
\details{
  This primitive parser recognises the following tokens: numbers like 1, symbols like x, the colon sequence operator \code{\link{:}} and the concat operator \code{\link{c}}.
  \code{hiparse} will \code{\link{Recall}} until the index expression is parsed or an unknown token is found.
  If an unknown token is found, \code{hiparse} evluates it, inspects it and either accepts it or throws an error, catched by \code{\link{as.hi.call}},
  which falls back to evaluating the index expression and dispatching (again) an appropriate \code{\link{as.hi}} method.
  Reasons for suspending the parsing: if the inspected token is of class 'hi', 'ri', 'bit', 'bitwhich', 'is.logical', 'is.character', 'is.matrix' or has length>16.
}
\value{
  undefined (and redefined as needed by \code{\link{as.hi.call}})
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{hi}}, \code{\link{as.hi.call}} }
\keyword{ IO }
\keyword{ data }
