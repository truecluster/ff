\name{unsort}
\alias{unsort}
\alias{unsort.hi}
\alias{unsort.ahi}
\alias{subscript2integer}
\title{ Hybrid Index, internal utilities }
\description{
  Non-documented internal utilities that might change
}
\usage{
unsort(x, ix)
unsort.hi(x, index)
unsort.ahi(x, index, ixre = any(sapply(index, function(i) {
    if (is.null(i$ix)) {
        if (i$re) TRUE else FALSE
    } else {
        TRUE
    }
})), ix = lapply(index, function(i) {
    if (is.null(i$ix)) {
        if (i$re)
            orig <- rev(seq_len(poslength(i)))
        else orig <- seq_len(poslength(i))
    }
    else {
        orig <- i$ix
    }
    orig
}))
subscript2integer(x, maxindex = NULL, names = NULL)
}
\arguments{
  \item{x}{ \code{x} }
  \item{ix}{ \code{ix} }
  \item{ixre}{ \code{ixre} }
  \item{index}{ \code{index} }
  \item{maxindex}{ \code{maxindex} }
  \item{names}{ \code{names} }
}
\details{
  These are utility functions for restoring original order after sorting.
  For now we 'mimic' the intuitive but wrong argument order of match()
  which should rather have the 'table' argument as its first argument,
  then one could properly method-dispatch on the type of table.
  xx We might change to proper 'unsort' generic, but then we have to change argument order.
}
\value{
 undefined
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{hi}}, \code{\link{as.hi}} }
\keyword{ IO }
\keyword{ data }
