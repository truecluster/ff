\name{bigsample}
\alias{bigsample}
\alias{bigsample.default}
\alias{bigsample.ff}
\title{ Sampling from large pools }
\description{
   \command{bigsample} samples quicker from large pools than \command{\link{sample}} does.
}
\usage{
bigsample(x, ...)
\method{bigsample}{default}(x, size, replace = FALSE, prob = NULL, negative = FALSE, ...)
\method{bigsample}{ff}(x, size, replace = FALSE, prob = NULL, ...)
}
\arguments{
  \item{x}{ the pool to sample from }
  \item{size}{ the number of elements to sample }
  \item{replace}{ TRUE to use sampling with replacement }
  \item{prob}{ optional vector of sampling probabilities (recyled to pool length) }
  \item{negative}{ \code{negative} }
  \item{\dots}{ \code{\dots} }
}
\details{
   For small pools \command{\link{sample}} is called.
}
\note{
  Note that \command{bigsample} and \command{sample} do not necessarily return the same sequence of elements when \command{set.seed} is set before.
}
\value{
  a vector of elements sampled from the pool (argument 'x')
}
\author{ Daniel Adler, Jens Oehlschlägel, Walter Zucchini}
\seealso{ \code{\link{sample}}, \code{\link{ff}} }
\examples{
message("Specify pool size")
bigsample(1e8, 10)
message("Sample ff elements (same as x[bigsample(length(ff(1:100 / 10)), 10)])")
bigsample(ff(1:100 / 10), 10)
 \dontrun{
   message("Speed factor")
     (system.time(for(i in 1:10)sample(1e8, 10))[3]/10) 
   / (system.time(for(i in 1:1000)bigsample(1e8, 10))[3]/1000)
 }
}
\keyword{ distribution }
\keyword{ data }
