library("testthat")
library("ff")

context("ff-zero-rows")

# options('fftempdir' = '/var/tmp')
# options('fftempdir' = 's:/fftemp')

test_that("Can create zero length ff objects from empty call", {
  y <- ff()
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "logical")
  
  delete(y)
})


test_that("Can create zero length ff objects from length= specification", {
  y <- ff(length=0)
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "logical")
  
  z <- as.ram(y)
  expect_equal(length(z), 0)
  expect_equal(class(z), "logical")
  
  y <- ff(length=0, vmode = "integer")
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "integer")
  
  z <- as.ram(y, vmode="integer")
  expect_equal(length(z), 0)
  expect_equal(vmode(z), "integer")
  
  delete(y)
})


test_that("Can create zero length ff objects from NULL", {
  x <- NULL
  
  y <- ff(x)
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "logical")
  
  y <- ff(x, vmode = "integer")
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "integer")
  
  y <- as.ff(x)
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "logical")

  y <- as.ff(x, vmode = "integer")
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "integer")

  delete(y)
})


test_that("Can create zero length ff objects from zero-length ram-objects", {
  x <- logical()
  
  y <- ff(x)
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "logical")
  
  y <- ff(x, vmode = "integer")
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "integer")
  
  y <- as.ff(x)
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "logical")
  
  y <- as.ff(x, vmode = "integer")
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "integer")
  
  delete(y)
})


test_that("Can clone zero length ff objects", {
  x <- ff(NULL)
  y <- clone(x)

  px <- physical(x)
  py <- physical(y)
  # do not compare filenames as they differ by definition
  px$filename <- NULL
  py$filename <- NULL
  expect_equal(px, py)
  expect_equal(virtual(x), virtual(y))
  
  delete(x)
  delete(y)
})

# the rhub and cran docker container lack the zip uitility
#test_that("Can ffsave zero length ff objects", {
#  x <- ff()
#  ffsave(x, file = "ffTest")
#  delete(x)
#  rm(x)
#  ffload("ffTest")
#  expect_equal(length(x), 0)
#  expect_equal(vmode(x), "logical")
#  delete(x)
#})

test_that("Can create zero row ffdf objects", {
  x <- data.frame(i = integer(), d = double(), q=quad())
  y <- as.ffdf(x)
  expect_equal(x,y[,])
  expect_equal(nrow(y), 0)
  expect_equal(vmode(y)[["i"]], "integer")
  expect_equal(vmode(y)[["d"]], "double")
  expect_equal(vmode(y)[["q"]], "quad")
  delete(y)
})

test_that("Can clone zero row ffdf objects", {
  x <- data.frame(i = integer(), d = double(), q=quad())
  y <- as.ffdf(x)
  z <- clone(y)

  # do not compare filenames as they differ by definition
  py <- lapply(physical(y), function(x){x <- physical(x); x$filename <- NULL; x})
  pz <- lapply(physical(z), function(x){x <- physical(x); x$filename <- NULL; x})
  expect_equal(pz, py)
  expect_equal(virtual(z), virtual(y))
  
  delete(y)
  delete(z)
})


# the rhub and cran docker container lack the zip uitility
#test_that("Can save zero row ffdf objects", {
#  x <- data.frame(i = integer(), d = double(), q=quad())
#  y <- as.ffdf(x)
#
#  ffsave(y, file = "ffTest")
#  delete(y)
#  rm(y)
#  ffload("ffTest")
#  expect_equal(x, y[,])
#
#  delete(y)
#})


test_that("Can read zero row csv into ffdf object", {
  f <- file.path(options('fftempdir'), "test.csv")
  # note that empty csv don't now any data type => hence default logical
  x <- data.frame(l1 = logical(), l2 = logical())
  write.csv(x, f, row.names = FALSE)
  y <- read.csv.ffdf(file = f)
  expect_equal(x,y[,])
  
  file.remove(f)
  delete(y)
})



test_that("Can write zero row ffdf object into csv", {
  f <- file.path(options('fftempdir'), "test.csv")
  # note that empty csv don't now any data type => hence default logical
  x <- data.frame(l1 = logical(), l2 = logical())
  y <- as.ffdf(x)
  write.csv.ffdf(y, f)
  z <- read.csv(file = f, stringsAsFactors = TRUE)
  expect_equal(x,z)
  
  file.remove(f)
  delete(y)
})



test_that("Indexing functions can handle zero rows", {
  
  b <- integer()
  expect_equal(b, as.integer(bit()))
  expect_equal(b, as.integer(as.hi(b)))
  x <- as.ff(b)
  expect_equal(length(x), 0)
  expect_equal(vmode(x), "integer")
  y <- as.ram(x)
  expect_equal(length(x), 0)
  expect_equal(vmode(x), "integer")
  
  
  byte()
  b <- as.byte(c())
  expect_equal(length(b), 0)
  expect_equal(class(b), "integer")
  x <- as.ff(b)
  expect_equal(length(x), 0)
  expect_equal(vmode(x), "byte")
  y <- as.ram(x)
  expect_equal(length(y), 0)
  expect_equal(vmode(y), "byte")
  
  b <- bitwhich()
  expect_equal(length(b), 0)
  expect_equal(class(b), c("booltype","bitwhich"))
  expect_equal(b, as.bitwhich(NULL))
  expect_equal(b, as.bitwhich(logical()))
  expect_equal(as.hi(b), as.hi(NULL))
  expect_equal(b, as.bitwhich(as.hi(b)))
  
  b <- bit()
  expect_equal(length(b), 0)
  expect_equal(class(b), c("booltype","bit"))
  expect_equal(b, as.bit(NULL))
  expect_equal(b, as.bit(logical()))
  expect_equal(as.hi(b), as.hi(NULL))
  expect_equal(b, as.bit(as.hi(b)))

  x <- as.ff(b)
  expect_equal(length(x), 0)
  expect_equal(vmode(x), "boolean")
      
  b <- logical()
  expect_equal(b, as.logical(NULL))
  expect_equal(b, as.logical(bit()))
  expect_equal(length(b), 0)
  expect_equal(as.hi(b), as.hi(NULL))
  expect_equal(b, as.logical(as.hi(b)))
  
  x <- as.ff(b)
  expect_equal(length(x), 0)
  expect_equal(vmode(x), "logical")
  
  b <- as.which(integer(), maxindex=0)
  expect_equal(length(b), 0)
  expect_equal(class(b), c("booltype","which"))
  expect_equal(b, as.which(bit()))
  expect_equal(b, as.which(logical()))
  expect_equal(as.hi(b), as.hi(NULL))
  expect_equal(b, as.which(as.hi(b)))
  x <- as.ff(b)
  expect_equal(length(x), 0)
  expect_equal(vmode(x), "integer")


  h <- as.hi(NULL)
  expect_equal(h, as.hi(as.which(integer(), maxindex=0)))
  expect_equal(h, as.hi(logical()))
  expect_equal(h, as.hi(bit()))
  expect_equal(h, as.hi(bitwhich()))
  h$maxindex <- NA_integer_
  expect_equal(h, as.hi(as.which(integer())))
  expect_equal(h, as.hi(integer()))
  expect_equal(h, as.hi(double()))
  
  x <- as.ff(1:10)
  y <- x[as.hi(NULL)]
  expect_equal(vmode(x), vmode(y))
  
  x <- as.integer(as.hi(c()))
  expect_equal(length(x), 0)
  expect_equal(class(x), "integer")
  
  x <- as.vmode(c(),"double")
  expect_equal(length(x), 0)
  
  x <- as.vmode(c(),"logical")
  expect_equal(length(x), 0)
  
  x <- as.vmode(c(),"byte")
  expect_equal(length(x), 0)
  
  chunks <- chunk(ff(c()))
  expect_equal(length(chunks), 0)

  x <- data.frame(a = c(1,2), b = c(2,3))
  x <- as.ffdf(x)
  chunks <- chunk(x)
  expect_equal(length(chunks), 1)
  expect_equal(dimnames(x)[[2]], c("a","b"))
  ffdfsort(x)
  
  x <- data.frame(a = c(1,2), b = c(2,3))
  x <- x[x$a == 3,]
  x <- as.ffdf(x)
  chunks <- chunk(x)
  expect_equal(length(chunks), 0)
  expect_equal(dimnames(x)[[2]], c("a","b"))
  ffdfsort(x)
  expect_equal(nrow(x), 0)
  
  x <- ff(c())
  y <- ff(c())
  x <- x[fforder(x,y)]
  expect_equal(length(x), 0)
  
  x <- ff(c())
  x <- ffsort(x)  
  expect_equal(length(x), 0)
  
  
})

test_that("Extract functions can handle zero rows", {
  x <- ff(c())
  expect_equal(length(x[]), 0)
  expect_equal(length(as.vector(x[])), 0)

  x <- ff(factor(letters))
  y <- ff(1:26)
  d <- ffdf(x,y)
  e <- clone(d)
  i <- ff(c(), vmode="integer")
  di <- d[i,]
  expect_equal(nrow(di), 0)

  di <- ffdfindexget(d, i, FF_RETURN=di)
  expect_equal(nrow(di), 0)
  
  d2 <- ffdfindexset(d, i, di)
  expect_equal(d[,], d2[,])
  expect_equal(d[,], e[,])

  x <- ff(factor(letters))
  i <- ff(c(), vmode="integer")
  xi <- x[i]
  expect_equal(xi, ff(factor(letters)[0]))
  expect_equal(xi[], factor(letters)[0])
  
  expect_equal(length(xi), 0)
  ff()
  xi <- ffindexget(x, i, FF_RETURN=xi)
  expect_equal(length(xi), 0)
  
  x2 <- ffindexset(x, i, xi)
  expect_equal(x, x2)
})

test_that("Can convert to bit and back", {
  l <- c(T,F,T,T,F)
  b <- as.bit(l)
  f <- as.ff(b)
  l2 <- f[]
  vmode(l2) <- "logical"
  expect_equal(l, l2)
  b2 <- as.bit(f)
  close(f)
  finalizer(f) <- "close"
  f2 <- as.ff(b2)
  expect_equal(filename(f), filename(f2))
  l2 <- f2[]
  vmode(l2) <- "logical"
  expect_equal(l, l2)
  physical(b2) <- physical(b2)["vmode"]
  expect_equal(b, b2)
  rm(f,f2)
  gc()
  
  l <- logical()
  b <- as.bit(l)
  f <- as.ff(b)
  l2 <- f[]
  vmode(l2) <- "logical"
  expect_equal(l, l2)
  b2 <- as.bit(f)
  close(f)
  finalizer(f) <- "close"
  f2 <- as.ff(b2)
  expect_equal(filename(f), filename(f2))
  l2 <- f2[]
  vmode(l2) <- "logical"
  expect_equal(l, l2)
  physical(b2) <- physical(b2)["vmode"]
  expect_equal(b, b2)
  rm(f,f2)
  gc()
})

test_that("test names", {
  n <- 0
  x <- integer(n)
  y <- ff(x)
  expect_silent(x[] <- 1:26)
  expect_silent(y[] <- 1:26)
  
  length(x) <- 1
  length(y) <- 1
  expect_warning(x[] <- 1:26)
  expect_warning(y[] <- 1:26)
  
  length(x) <- 26
  x[] <- 1:26
  names(x) <- letters
  length(y) <- 26
  y[] <- 1:26
  names(y) <- letters
  
  expect_equal(length(x), 26)
  expect_equal(length(names(x)), 26)
  expect_equal(length(y), 26)
  expect_equal(length(names(y)), 26)
  expect_equal(names(x), names(y))
  
  length(x) <- 3
  length(y) <- 3
  expect_equal(length(x), 3)
  expect_equal(length(names(x)), 3)
  expect_equal(length(y), 3)
  expect_equal(length(names(y)), 3)
  expect_equal(names(x), names(y))
  
  length(x) <- 0
  length(y) <- 0
  expect_equal(length(x), 0)
  expect_equal(length(names(x)), 0)
  expect_equal(length(y), 0)
  expect_equal(length(names(y)), 0)
  expect_equal(names(x), names(y))
  
  length(x) <- 7
  length(y) <- 7
  expect_equal(length(names(x)), 7)
  expect_equal(length(names(y)), 7)
  #not expect_equal(names(x), names(y))
})

