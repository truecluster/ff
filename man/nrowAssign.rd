\name{nrowAssign}
\Rdversion{1.1}
\alias{nrow<-}
\alias{ncol<-}
\title{
  Assigning the number of rows or columns
}
\description{
  Function \code{nrow<-} assigns \code{\link{dim}} with a new number of rows. \cr
  Function \code{ncol<-} assigns \code{\link{dim}} with a new number of columns.
}
\usage{
nrow(x) <- value
ncol(x) <- value
}
\arguments{
  \item{x}{ a object that has \code{\link{dim}} AND can be assigned ONE new dimension }
  \item{value}{ the new size of the assigned dimension }
}
\details{
  Currently only asssigning new rows to \code{\link{ffdf}} is supported.
  The new ffdf rows are not initialized (usually become zero).
  NOTE that
}
\value{
  The object with a modified dimension
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{ffdf}}, \code{\link{dim.ffdf}}
}
\examples{
  a <- as.ff(1:26)
  b <- as.ff(factor(letters)) # vmode="integer"
  c <- as.ff(factor(letters), vmode="ubyte")
  df <- ffdf(a,b,c)
  nrow(df) <- 2*26
  df
  message("NOTE that the new rows have silently the first level 'a' for UNSIGNED vmodes")
  message("NOTE that the new rows have an illegal factor level <0> for SIGNED vmodes")
  message("It is your responsibility to put meaningful content here")
  message("As an example we replace the illegal zeros by NA")
  df$b[27:52] <- NA
  df

  rm(a,b,c,df); gc()
}
\keyword{ array }
