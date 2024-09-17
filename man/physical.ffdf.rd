\name{physical.ffdf}
\Rdversion{1.1}
\alias{physical.ffdf}
\alias{virtual.ffdf}
\title{
Getting physical and virtual attributes of ffdf objects
}
\description{
Functions for getting physical and virtual attributes of ffdf objects.
}
\usage{
\method{physical}{ffdf}(x)
\method{virtual}{ffdf}(x)
}
\arguments{
  \item{x}{an \code{\link{ffdf}} object}
}
\details{
\code{\link{ffdf}} objects enjoy a complete decoupling of virtual behaviour from physical storage.
The physical component is simply a (potentially named) list where each element represents an atomic ff vector or matrix.
The virtual component is itself a dataframe, each row of which defines a column of the ffdf through a mapping to the physical component.
}
\value{
'physical.ffdf' returns a \code{\link{list}} with atomic ff objects. \cr
'virtual.ffdf' returns a \code{\link{data.frame}} with the following columns \cr
  \item{VirtualVmode}{the \code{\link{vmode}} of this row (=ffdf column)}
  \item{AsIs}{logical defining the \code{\link{AsIs}} status of this row (=ffdf column)}
  \item{VirtualIsMatrix}{logical defining whether this row (=ffdf column) represents a matrix}
  \item{PhysicalIsMatrix}{logical reporting whether the corresponding physical element is a matrix}
  \item{PhysicalElementNo}{integer identifying the corresponding physical element}
  \item{PhysicalFirstCol}{integer identifying the first column of the corresponding physical element (1 if it is not a matrix)}
  \item{PhysicalLastCol}{integer identifying the last column of the corresponding physical element (1 if it is not a matrix)}
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{ffdf}}, \code{\link[=Extract.ff]{physical}}, \code{\link[=Extract.ff]{virtual}}, \code{\link[=vmode.ffdf]{vmode}}
}
\examples{
  x <- 1:2
  y <- matrix(1:4, 2, 2)
  z <- matrix(1:4, 2, 2)

  message("Here the y matrix is first converted to single columns by data.frame, 
then those columns become ff")
  d <- as.ffdf(data.frame(x=x, y=y, z=I(z)))
  physical(d)
  virtual(d)

  message("Here the y matrix is first converted to ff, and then stored still as matrix 
in the ffdf object (although virtually treated as columns of ffdf)")
  d <- ffdf(x=as.ff(x), y=as.ff(y), z=I(as.ff(z)))
  physical(d)
  virtual(d)

  message("Apply the usual methods extracting physical attributes")
  lapply(physical(d), filename)
  lapply(physical(d), vmode)
  message("And don't confuse with virtual vmode")
  vmode(d)

  rm(d); gc()
}
\keyword{ IO }
\keyword{ data }
