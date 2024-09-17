\name{chunk.ffdf}
\Rdversion{1.1}
\alias{chunk.ffdf}
\alias{chunk.ff_vector}
\title{
   Chunk ff_vector and ffdf
}
\description{
   Chunking method for ff_vector and ffdf objects (row-wise) automatically considering RAM requirements from recordsize as calculated from \code{\link{sum}(\link{.rambytes}[\link{vmode}])}
}
\usage{
\method{chunk}{ff_vector}(x
, RECORDBYTES = .rambytes[vmode(x)], BATCHBYTES = getOption("ffbatchbytes"), \dots)
\method{chunk}{ffdf}(x
, RECORDBYTES = sum(.rambytes[vmode(x)]), BATCHBYTES = getOption("ffbatchbytes"), \dots)
}
\arguments{
  \item{x}{\code{\link{ff}} or \code{\link{ffdf}}}
  \item{RECORDBYTES}{ optional integer scalar representing the bytes needed to process an element of the \code{ff_vector} a single row of the \code{ffdf} }
  \item{BATCHBYTES}{ integer scalar limiting the number of bytes to be processed in one chunk, default from \code{getOption("ffbatchbytes")}, see also \code{\link{.rambytes}} }
  \item{\dots}{further arguments passed to \code{\link[bit]{chunk}}}
}
\value{
  A list with \code{\link[bit]{ri}} indexes each representing one chunk
}
\author{
  Jens Oehlschlägel
}
\seealso{ \code{\link[bit]{chunk}}, \code{\link{ffdf}} }
\examples{
  x <- data.frame(x=as.double(1:26), y=factor(letters), z=ordered(LETTERS), stringsAsFactors = TRUE)
  a <- as.ffdf(x)
  ceiling(26 / (300 \%/\% sum(.rambytes[vmode(a)])))
  chunk(a, BATCHBYTES=300)
  ceiling(13 / (100 \%/\% sum(.rambytes[vmode(a)])))
  chunk(a, from=1, to = 13, BATCHBYTES=100)
  rm(a); gc()

  message("dummy example for linear regression with biglm on ffdf")
  library(biglm)

  message("NOTE that . in formula requires calculating terms manually
    because . as a data-dependant term is not allowed in biglm")
  form <- Sepal.Length ~ Sepal.Width + Petal.Length + Petal.Width + Species

  lmfit <- lm(form, data=iris)

  firis <- as.ffdf(iris)
  for (i in chunk(firis, by=50)){
    if (i[1]==1){
      message("first chunk is: ", i[[1]],":",i[[2]])
      biglmfit <- biglm(form, data=firis[i,,drop=FALSE])
    }else{
      message("next chunk is: ", i[[1]],":",i[[2]])
      biglmfit <- update(biglmfit, firis[i,,drop=FALSE])
    }
  }

  summary(lmfit)
  summary(biglmfit)
  stopifnot(all.equal(coef(lmfit), coef(biglmfit)))
}
\keyword{ IO }
\keyword{ data }
