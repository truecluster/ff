\name{CFUN}
\alias{CFUN}
\alias{ccbind}
\alias{crbind}
\alias{cfun}
\alias{cquantile}
\alias{csummary}
\alias{cmedian}
\alias{clength}
\alias{csum}
\alias{cmean}
\title{ Collapsing functions for batch processing }
\description{
  These are used in aggregating the chunks resulting from batch processing. They are usually called via \command{\link{do.call}}
}
\usage{
ccbind(\dots)
crbind(\dots)
cfun(\dots, FUN, FUNARGS = list())
cquantile(\dots, probs = seq(0, 1, 0.25), na.rm = FALSE, names = TRUE, type = 7)
csummary(\dots, na.rm = "ignored")
cmedian(\dots, na.rm = FALSE)
clength(\dots, na.rm = FALSE)
csum(\dots, na.rm = FALSE)
cmean(\dots, na.rm = FALSE)
}
\arguments{
  \item{\dots}{ \code{\dots} }
  \item{FUN}{ a aggregating function }
  \item{FUNARGS}{ further arguments to the aggregating function }
  \item{na.rm}{ TRUE to remove NAs }
  \item{probs}{ see \code{\link{quantile}} }
  \item{names}{ see \code{\link{quantile}} }
  \item{type}{ see \code{\link{quantile}} }
}
\details{
 \tabular{lll}{
  \strong{CFUN}        \tab \strong{FUN}              \tab \strong{comment} \cr
  \command{ccbind}     \tab \command{\link{cbind}}    \tab like \command{cbind} but respecting names \cr
  \command{crbind}     \tab \command{\link{rbind}}    \tab like \command{rbind} but respecting names \cr
  \command{cfun}       \tab                           \tab \command{crbind} the input chunks and then apply 'FUN' to each column \cr
  \command{cquantile}  \tab \command{\link{quantile}} \tab \command{crbind} the input chunks and then apply 'quantile' to each column \cr
  \command{csummary}   \tab \command{\link{summary}}  \tab \command{crbind} the input chunks and then apply 'summary' to each column \cr
  \command{cmedian}    \tab \command{\link{median}}   \tab \command{crbind} the input chunks and then apply 'median' to each column \cr
  \command{clength}    \tab \command{\link{length}}   \tab \command{crbind} the input chunks and then determine the number of values in each column\cr
  \command{csum}       \tab \command{\link{sum}}      \tab \command{crbind} the input chunks and then determine the sum values in each column\cr
  \command{cmean}      \tab \command{\link{mean}}     \tab \command{crbind} the input chunks and then determine the (unweighted) mean in each column\cr
  }
  In order to use CFUNs on the result of \code{\link{lapply}} or \code{\link{ffapply}} use \code{\link{do.call}}.
}
\note{
 Currently - for command line convenience - we map the elements of a single list argument to \dots, but this may change in the future.
}
\section{ff options}{
  xx TODO: extend this for weighted means, weighted median etc., \cr
  google "Re: [R] Weighted median"
}
\value{
  depends on the CFUN used
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ffapply}}, \code{\link{do.call}}, \code{\link[bit]{na.count}} }
\examples{
   X <- lapply(split(rnorm(1000), 1:10), summary)
   do.call("crbind", X)
   do.call("csummary", X)
   do.call("cmean", X)
   do.call("cfun", c(X, list(FUN=mean, FUNARGS=list(na.rm=TRUE))))
   rm(X)
}
\keyword{ manip }
\keyword{ list }
