\name{levels.ff}
\alias{levels.ff}
\alias{levels<-.ff}
\alias{is.factor}
\alias{is.factor.default}
\alias{is.factor.ff}
\alias{is.ordered}
\alias{is.ordered.default}
\alias{is.ordered.ff}
\title{ Getting and setting factor levels }
\description{
  \code{levels.ff<-} sets factor levels, \code{levels.ff} gets factor levels
}
\usage{
\method{levels}{ff}(x)
\method{levels}{ff}(x) <- value
 is.factor(x)
 is.ordered(x)
\method{is.factor}{ff}(x)
\method{is.ordered}{ff}(x)
\method{is.factor}{default}(x)
\method{is.ordered}{default}(x)
}
\arguments{
  \item{x}{ an ff object }
  \item{value}{ the new factor levels, if NA is an allowed level it needs to be given explicitely, nothing is excluded }
}
\details{
  The ff object must have an integer vmode, see \code{\link{.rammode}}.
  If the mode is unsigned -- see \code{\link{.vunsigned}} -- the first factor level is coded with 0L instead of 1L in order to maximize the number of codable levels.
  Usually the internal ff coding -- see \code{\link{ram2ffcode}} -- is invisible to the user: when subscripting from an ff factor, unsigend codings are automatically converted to R's standard factor codes starting at 1L.
  However, you need to be aware of the internal ff coding in two situtations. \cr
  1. If you convert an ff integer object to an ff factor object and vice versa by assigning levels and \code{is.null(oldlevels)!=is.null(newlevels)}.  \cr
  2. Assigning data that does not match any level usually results in NA, however, in unsigned types there is no NA and all unknown data are mapped to the first level.
}
\value{
  \command{levels} returns a character vector of levels (possibly including \code{as.cha racter(NA)}).
}
\author{ Jens Oehlschlägel }
\note{ When levels as assigned to an ff object that formerly had not levels, we assign automatically \code{\link{ramclass}} == "factor". If you want to change to an ordered factor, use \code{\link[=Extract.ff]{virtual}$ramclass <- c("ordered", "factor")} }
\seealso{ \code{\link{ramclass}}, \code{\link{factor}}, \code{\link[=Extract.ff]{virtual}} }
\examples{
  message("--- create an ff factor including NA as last level")
  x <- ff("a", levels=c(letters, NA), length=99)
  message('    we expect a warning because "A" is an unknown level')
  x[] <- c("a", NA,"A")
  x
  levels(x)

  message("--- create an ff ordered factor")
  x <- ff(letters, levels=letters, ramclass=c("ordered","factor"), length=260)
  x
  levels(x)

  message("    make it a non-ordered factor")
  virtual(x)$ramclass <- "factor"
  x
  rm(x); gc()

 \dontrun{
  message("--- create an unsigned quad factor")
  x <- ff(c("A","T","G","C"), levels=c("A","T","G","C"), vmode="quad", length=100)
  x
  message("  0:3 coding usually invisible to the user")
  unclass(x[1:4])
  message("    after removing levels, the 0:3 coding becomes visible to the user")
  message("    we expect a warning here")
  levels(x) <- NULL
  x[1:4]
  rm(x); gc()
 }

}
\keyword{ IO }
\keyword{ data }
\keyword{ attribute }
