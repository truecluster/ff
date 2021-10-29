library("testthat")
library("ff")

# expect_identical <- function(x, y, ...){
#   stopifnot(identical(x,y))
# }

is_not_macos <- function(){Sys.info()["sysname"] != 'Darwin'}

context("ff-zero-lengths")

test_that("file size is correct  when creating ff integer from scratch", {
  a0 <- ff(length=0, vmode="integer")
  f0 <- filename(a0)
  expect_true(file.exists(f0))
  expect_null(names(a0))
  names(a0) <- character(0)
  expect_identical(names(a0), character(0))
  a1 <- ff(length=1, vmode="integer")
  f1 <- filename(a1)
  expect_true(file.exists(f1))
  names(a1) <- "1"
  expect_equal(file.size(filename(a0)), 0)
  expect_equal(file.size(filename(a1)), 4)
  length(a0) <- 1
  length(a1) <- 0
  expect_equal(file.size(filename(a0)), 4)
  expect_equal(file.size(filename(a1)), 0)
  expect_identical(names(a0), "1")
  expect_identical(names(a1), character(0))
  rm(a0)
  rm(a1)
  expect_true(file.exists(f0))
  expect_true(file.exists(f1))
  gc()
  if (is_not_macos()){
    expect_false(file.exists(f0))
    expect_false(file.exists(f1))
  }
  rm(f0,f1)
})

test_that("file size is correct  when creating ff quad from scratch", {
  a0 <- ff(length=0, vmode="quad")
  f0 <- filename(a0)
  expect_true(file.exists(f0))
  expect_null(names(a0))
  names(a0) <- character(0)
  expect_identical(names(a0), character(0))
  a1 <- ff(length=1, vmode="quad")
  f1 <- filename(a1)
  expect_true(file.exists(f1))
  names(a1) <- "1"
  expect_equal(file.size(filename(a0)), 0)
  expect_equal(file.size(filename(a1)), 4)
  length(a0) <- 1
  length(a1) <- 0
  expect_equal(file.size(filename(a0)), 4)
  expect_equal(file.size(filename(a1)), 0)
  expect_identical(names(a0), "1")
  expect_identical(names(a1), character(0))
  rm(a0)
  rm(a1)
  expect_true(file.exists(f0))
  expect_true(file.exists(f1))
  gc()
  if (is_not_macos()){
    expect_false(file.exists(f0))
    expect_false(file.exists(f1))
  }
  rm(f0,f1)
})


test_that("file size is correct when creating ff integer from existing file", {
  a0 <- ff(length=0, vmode="integer", pattern="ff", finalizer="close")
  b0 <- ff(vmode="integer", filename=filename(a0), pattern="ff", finalizer="close")
  expect_identical(physical(a0),physical(b0))
  expect_identical(virtual(a0),virtual(b0))
  a1 <- ff(length=1, vmode="integer", pattern="ff", finalizer="close")
  b1 <- ff(vmode="integer", filename=filename(a1), pattern="ff", finalizer="close")
  expect_identical(physical(a1),physical(b1))
  expect_identical(virtual(a1),virtual(b1))
  f0 <- filename(a0)
  f1 <- filename(a1)
  expect_equal(file.size(f1), 4)
  close(b0)
  close(b1)
  delete(a0)
  delete(a1)
  rm(a0,b0,a1,b1)
  expect_false(file.exists(f0))
  expect_false(file.exists(f1))
  gc()
  if (is_not_macos()){
    expect_false(file.exists(f0))
    expect_false(file.exists(f1))
  }
  rm(f0,f1)
})


test_that("file size is correct when creating ff quad from existing file", {
  a0 <- ff(length=0, vmode="quad", pattern="ff", finalizer="close")
  b0 <- ff(vmode="quad", filename=filename(a0), pattern="ff", finalizer="close")
  expect_identical(physical(a0),physical(b0))
  expect_identical(virtual(a0),virtual(b0))
  a1 <- ff(length=1, vmode="quad", pattern="ff", finalizer="close")
  b1 <- ff(vmode="quad", filename=filename(a1), pattern="ff", finalizer="close")
  # note that quads are internally 32-bit-integers 
  # and hence quad-files are multiples of 32-bits 
  # and hence reading quad files reads multiples of 16 quads
  expect_identical(length(b1), 16L)
  # only after correcting the length to 1 we a1 and b1 are identical ff objects
  length(b1) <- 1
  expect_identical(physical(a1),physical(b1))
  expect_identical(virtual(a1),virtual(b1))
  f0 <- filename(a0)
  f1 <- filename(a1)
  expect_equal(file.size(f1), 4)
  close(b0)
  close(b1)
  delete(a0)
  delete(a1)
  rm(a0,b0,a1,b1)
  expect_false(file.exists(f0))
  expect_false(file.exists(f1))
  gc()
  if (is_not_macos()){
    expect_false(file.exists(f0))
    expect_false(file.exists(f1))
  }
  rm(f0,f1)
})


test_that("length changes are correct for ff integer", {
  a1 <- ff(length=1, vmode="integer", pattern="ff", finalizer="close")
  a0 <- ff(length=0, vmode="integer", pattern="ff", finalizer="close")
  f0 <- filename(a0)
  f1 <- filename(a1)
  r1 <- a1[]
  r0 <- a0[]
  a1[1] <- 1L
  r1[1] <- 1L
  n <- 64
  length(a1) <- n
  length(a0) <- n
  length(r1) <- n
  length(r0) <- n
  r1[is.na(r1)] <- 0L
  r0[is.na(r0)] <- 0L
  expect_equal(file.size(f1), n*4)
  expect_equal(file.size(f0), n*4)
  expect_equal(a1[], r1)
  expect_equal(a0[], r0)
  
  a1[] <- n:1
  a0[] <- n:1
  r1[] <- n:1
  r0[] <- n:1
  n <- 3
  length(a1) <- n
  length(a0) <- 0
  length(r1) <- n
  length(r0) <- 0
  expect_equal(file.size(f1), n*4)
  expect_equal(file.size(f0), 0)
  expect_equal(a1[], r1)
  expect_equal(a0[], r0)
  
  rm(n)
  rm(a0,a1)
  rm(r0,r1)
  rm(f0,f1)
  gc()
})


test_that("length changes are correct for ff quad", {
  a1 <- ff(length=1, vmode="quad", pattern="ff", finalizer="close")
  a0 <- ff(length=0, vmode="quad", pattern="ff", finalizer="close")
  f0 <- filename(a0)
  f1 <- filename(a1)
  r1 <- a1[]
  r0 <- a0[]
  a1[1] <- 1L
  r1[1] <- 1L
  n <- 63
  length(a1) <- n
  length(a0) <- n
  r1 <- as.quad(c(1, rep(0, n-1)))
  r0 <- quad(n)
  expect_equal(file.size(f1), ceiling(n/16)*4)
  expect_equal(file.size(f0), ceiling(n/16)*4)
  expect_equal(a1[], r1)
  expect_equal(a0[], r0)
  a1[] <- 1L  # we write hidden values beyond the future vector size
  a0[] <- 1L  # we write hidden values beyond the future vector size
  length(a1) <- 1 # hopefully the hidden values are removed
  length(a0) <- 0 # hopefully the hidden values are removed
  r1 <- as.quad(1)
  r0 <- quad(0)
  expect_equal(file.size(f1), 4)
  expect_equal(file.size(f0), 0)
  expect_equal(a1[], r1)
  expect_equal(a0[], r0)

  n <- 16
  length(a1) <- n
  length(a0) <- n
  r1 <- as.quad(c(1, rep(0, n-1)))
  r0 <- quad(n)
  expect_equal(file.size(f1), ceiling(n/16)*4) 
  expect_equal(file.size(f0), ceiling(n/16)*4)
  expect_equal(a1[], r1) # hopefully the hidden values are removed
  expect_equal(a0[], r0) # hopefully the hidden values are removed
  
  rm(n)
  rm(a0,a1)
  rm(r0,r1)
  rm(f0,f1)
  gc()
})



test_that("length changes are correct for named ff integer", {
  a1 <- ff(length=1, vmode="integer", pattern="ff", finalizer="close")
  a0 <- ff(length=0, vmode="integer", pattern="ff", finalizer="close")
  f0 <- filename(a0)
  f1 <- filename(a1)
  names(a1) <- "a"
  names(a0) <- character()
  expect_equal(names(a1), "a")
  expect_equal(names(a0), character())
  
  r1 <- a1[]
  r0 <- a0[]
  expect_equal(names(a1), names(r1))
  expect_equal(names(a0), names(r0))

  n <- 64  
  a1[1] <- 1L
  r1[1] <- 1L
  length(a1) <- n
  length(a0) <- n
  length(r1) <- n
  length(r0) <- n
  names(r1)[2:n] <- 2:n
  names(r0)[1:n] <- 1:n
  expect_equal(file.size(f1), n*4)
  expect_equal(file.size(f0), n*4)
  expect_equal(a1[], r1)
  expect_equal(a0[], r0)
  
  a1[] <- n:1
  a0[] <- n:1
  r1[] <- n:1
  r0[] <- n:1
  n <- 3
  length(a1) <- n
  length(a0) <- 0
  length(r1) <- n
  length(r0) <- 0
  expect_equal(file.size(f1), n*4)
  expect_equal(file.size(f0), 0)
  
  rm(n)
  rm(a0,a1)
  rm(r0,r1)
  rm(f0,f1)
  gc()
})


test_that("length changes are correct for named ff quad", {
  a1 <- ff(length=1, vmode="quad", pattern="ff", finalizer="close")
  a0 <- ff(length=0, vmode="quad", pattern="ff", finalizer="close")
  f0 <- filename(a0)
  f1 <- filename(a1)
  
  names(a1) <- "a"
  names(a0) <- character()
  expect_equal(names(a1), "a")
  expect_equal(names(a0), character())
  
  r1 <- a1[]
  r0 <- a0[]
  expect_equal(names(a1), names(r1))
  expect_equal(names(a0), names(r0))
  
  a1[1] <- 1L
  n <- 63
  length(a1) <- n
  length(a0) <- n
  r1 <- as.quad(c(1, rep(0, n-1)))
  r0 <- quad(n)
  names(r1) <- c("a",2:n)
  names(r0) <- 1:n
  expect_equal(file.size(f1), ceiling(n/16)*4)
  expect_equal(file.size(f0), ceiling(n/16)*4)
  expect_equal(a1[], r1)
  expect_equal(a0[], r0)
  a1[] <- 1L  # we write hidden values beyond the future vector size
  a0[] <- 1L  # we write hidden values beyond the future vector size
  length(a1) <- 1 # hopefully the hidden values are removed
  length(a0) <- 0 # hopefully the hidden values are removed
  r1 <- as.quad(1)
  r0 <- quad(0)
  names(r1) <- c("a")
  names(r0) <- character()
  expect_equal(file.size(f1), 4)
  expect_equal(file.size(f0), 0)
  expect_equal(a1[], r1)
  expect_equal(a0[], r0)
  
  n <- 16
  length(a1) <- n
  length(a0) <- n
  r1 <- as.quad(c(1, rep(0, n-1)))
  r0 <- quad(n)
  names(r1) <- c("a", 2:n)
  names(r0) <- 1:n
  expect_equal(file.size(f1), ceiling(n/16)*4) 
  expect_equal(file.size(f0), ceiling(n/16)*4)
  expect_equal(a1[], r1) # hopefully the hidden values are removed
  expect_equal(a0[], r0) # hopefully the hidden values are removed
  
  rm(n)
  rm(a0,a1)
  rm(r0,r1)
  rm(f0,f1)
  gc()
})




test_that("get, set and getset are correct when accessing zero and one file length", {
  a1 <- ff(length=1, vmode="quad", pattern="ff", finalizer="close")
  a0 <- ff(length=0, vmode="quad", pattern="ff", finalizer="close")
  
  expect_identical(get.ff(a1, integer()), quad(0))
  expect_identical(get.ff(a0, integer()), quad(0))
  
  expect_identical(get.ff(a1, 1), quad(1))
  expect_error(get.ff(a1, 2), "illegal index")
  expect_error(get.ff(a0, 1), "illegal index")
  
  expect_silent(set.ff(a1, 1, 2))
  expect_identical(get.ff(a1, 1), as.quad(2))
  expect_silent(set.ff(a1, 1, 2, add=TRUE))
  expect_identical(get.ff(a1, 1), as.quad(0))
  expect_identical(getset.ff(a1, 1, 2), as.quad(0))
  expect_identical(get.ff(a1, 1), as.quad(2))
  expect_identical(getset.ff(a1, 1, 2, add=2), as.quad(0))
  expect_identical(get.ff(a1, 1), as.quad(0))
  
  expect_error(set.ff(a0, 1, 2), "illegal index")
  expect_error(set.ff(a0, 1, 2, add=TRUE), "illegal index")
  expect_error(getset.ff(a0, 1, 2), "illegal index")
  expect_error(getset.ff(a0, 1, 2, add=TRUE), "illegal index")

  rm(a1,a0)
  gc()
})

test_that("read, write and readwrite are correct when accessing zero and one file length", {
  a1 <- ff(length=1, vmode="quad", pattern="ff", finalizer="close")
  a0 <- ff(length=0, vmode="quad", pattern="ff", finalizer="close")

  expect_identical(read.ff(a1,1,0), quad(0))
  expect_identical(read.ff(a0,1,0), quad(0))

  expect_error(read.ff(a1,0,0), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  expect_error(read.ff(a0,0,0), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  
  expect_error(read.ff(a1,0,1), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  expect_error(read.ff(a0,0,1), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  
  expect_error(read.ff(a1,0,2), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  expect_error(read.ff(a0,0,2), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  
  expect_error(read.ff(a1,2,2), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  expect_error(read.ff(a0,1,2), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  
  expect_error(read.ff(a1,3,0), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  expect_error(read.ff(a0,2,0), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  
  expect_silent(write.ff(a1, 1, 2))
  expect_identical(read.ff(a1, 1, 1), as.quad(2))
  expect_silent(write.ff(a1, 1, 2, add=TRUE))
  expect_identical(read.ff(a1, 1, 1), as.quad(0))
  expect_identical(readwrite.ff(a1, 1, 2), as.quad(0))
  expect_identical(read.ff(a1, 1, 1), as.quad(2))
  expect_identical(readwrite.ff(a1, 1, 2, add=TRUE), as.quad(0))
  expect_identical(read.ff(a1, 1, 1), as.quad(0))

  expect_error(write.ff(a0, 1, 2), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  expect_error(write.ff(a0, 1, 2, add=TRUE), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  expect_error(readwrite.ff(a0, 1, 2), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  expect_error(readwrite.ff(a0, 1, 2, add=TRUE), "0 < i && i [+] n [-] 1 [<][=] length[(]x[)] is not TRUE")
  
  rm(a1,a0)
  gc()
})


test_that("[[, [[<-, add and swap are correct when accessing zero and one file length", {
  r1 <- quad(1)
  r0 <- quad(0)
  names(r1) <- "a"
  names(r0) <- character()
  
  f1 <- ff(r1, pattern="ff", finalizer="close")
  f0 <- ff(r0, pattern="ff", finalizer="close")
  
  expect_error(f1[[]], 'argument "i" is missing, with no default')
  expect_error(f0[[]], 'argument "i" is missing, with no default')
  expect_error(f1[[]]<-1, 'argument "i" is missing, with no default')
  expect_error(f0[[]]<-1, 'argument "i" is missing, with no default')
  
  expect_error(f1[[integer()]], "i must have length 1")
  expect_error(f0[[integer()]], "i must have length 1")
  expect_error(f1[[integer()]]<-1, "i must have length 1")
  expect_error(f0[[integer()]]<-1, "i must have length 1")
  
  expect_error(f1[[2]], "illegal index")
  expect_identical(f1[[1]], quad(1))
  expect_error(f1[[0]], "illegal index")
  expect_error(f1[[NA]], "illegal index")
  expect_error(f1[[-1]], "illegal index")
  expect_error(f1[[-2]], "illegal index")

  expect_error(f1[[2]]<-1, "illegal index")
  expect_silent(f1[[1]]<-1)
  expect_identical(f1[[1]], as.quad(1))
  expect_silent(f1[[1]]<-4)
  expect_identical(f1[[1]], as.quad(0))
  expect_silent(f1[[1,add=TRUE]]<-2)
  expect_identical(f1[[1]], as.quad(2))
  expect_silent(f1[[1,add=TRUE]]<-2)
  expect_identical(f1[[1]], as.quad(0))
  expect_error(f1[[0]]<-1, "illegal index")
  expect_error(f1[[NA]]<-1, "illegal index")
  expect_error(f1[[-1]]<-1, "illegal index")
  expect_error(f1[[-2]]<-1, "illegal index")
  
  expect_error(f0[[2]], "illegal index")
  expect_error(f0[[1]], "illegal index")
  expect_error(f0[[0]], "illegal index")
  expect_error(f0[[NA]], "illegal index")
  expect_error(f0[[-1]], "illegal index")
  expect_error(f0[[-2]], "illegal index")

  expect_error(f0[[2]]<-1, "illegal index")
  expect_error(f0[[1]]<-1, "illegal index")
  expect_error(f0[[0]]<-1, "illegal index")
  expect_error(f0[[NA]]<-1, "illegal index")
  expect_error(f0[[-1]]<-1, "illegal index")
  expect_error(f0[[-2]]<-1, "illegal index")
    
  rm(r1,r0)
  rm(f1,f0)
  gc()
})



test_that("[ and [<- are correct when accessing zero and one file length", {
  r1 <- quad(1)
  r0 <- quad(0)
  names(r1) <- "a"
  names(r0) <- character()
  f1 <- as.ff(r1, pattern="ff", finalizer="close")
  f0 <- as.ff(r0, pattern="ff", finalizer="close")
  expect_identical(names(f1[]), names(r1))
  expect_identical(names(f0[]), names(r0))
  expect_identical(pattern(f1), "ff")
  expect_identical(pattern(f0), "ff")
  expect_identical(finalizer(f1), "close")
  expect_identical(finalizer(f0), "close")
  expect_identical(f1[], r1)
  expect_identical(f0[], r0)

  expect_identical(f1[,pack=TRUE], r1)
  expect_identical(f0[,pack=TRUE], r0)

  expect_identical(f1[integer()], r0)
  expect_identical(f0[integer()], r0)
  expect_identical(f1[integer(),pack=TRUE], r0)
  expect_identical(f0[integer(),pack=TRUE], r0)
  expect_silent(f1[integer()]<-1)
  expect_silent(f0[integer()]<-1)
  expect_identical(f1[], r1)
  expect_identical(f0[], r0)
  expect_silent(f1[integer()]<-1)
  expect_silent(f0[integer()]<-1)
  expect_identical(f1[], r1)
  expect_identical(f0[], r0)
  expect_silent(f1[integer(), add=TRUE]<-1)
  expect_silent(f0[integer(), add=TRUE]<-1)
  expect_identical(f1[], r1)
  expect_identical(f0[], r0)

  expect_error(f1[2], "positive subscripts out of range")
  expect_identical(f1[1], r1)
  expect_identical(f1[1,pack=TRUE], r1)
  expect_error(f1[0], "0s and mixed positive/negative subscripts not allowed")
  expect_identical(f1[-1], r0)
  expect_identical(f1[-1, pack=TRUE], r0)
  expect_error(f1[-2], "negative subscripts out of range")
  expect_error(f1[-2, pack=TRUE], "negative subscripts out of range")

  expect_error(f1[2]<-1, "positive subscripts out of range")
  expect_silent(f1[1]<-2)
  expect_identical(f1[1], r1+2L)
  expect_silent(f1[1]<-4)
  expect_identical(f1[1], r1)
  expect_silent(f1[1, add=TRUE]<-2)
  expect_identical(f1[1], r1+2L)
  expect_silent(f1[1, add=TRUE]<-2)
  expect_identical(f1[1], r1)
  expect_error(f1[0]<-1, "0s and mixed positive/negative subscripts not allowed")
  expect_silent(f1[-1]<-1)
  expect_identical(f1[], r1)
  expect_error(f1[-2]<-1, "negative subscripts out of range")
  
  expect_error(f0[2], "positive subscripts out of range")
  expect_error(f0[1], "positive subscripts out of range")
  expect_error(f0[0], "0s and mixed positive/negative subscripts not allowed")
  expect_error(f0[-1], "negative subscripts out of range")
  expect_error(f0[-2], "negative subscripts out of range")

  expect_error(f0[2,pack=TRUE], "positive subscripts out of range")
  expect_error(f0[1,pack=TRUE], "positive subscripts out of range")
  expect_error(f0[0,pack=TRUE], "0s and mixed positive/negative subscripts not allowed")
  expect_error(f0[-1,pack=TRUE], "negative subscripts out of range")
  expect_error(f0[-2,pack=TRUE], "negative subscripts out of range")

  expect_error(f0[2]<-1, "positive subscripts out of range")
  expect_error(f0[1]<-1, "positive subscripts out of range")
  expect_error(f0[0]<-1, "0s and mixed positive/negative subscripts not allowed")
  expect_error(f0[-1]<-1, "negative subscripts out of range")
  expect_error(f0[-2]<-1, "negative subscripts out of range")

  expect_error(f0[2,add=TRUE]<-1, "positive subscripts out of range")
  expect_error(f0[1,add=TRUE]<-1, "positive subscripts out of range")
  expect_error(f0[0,add=TRUE]<-1, "0s and mixed positive/negative subscripts not allowed")
  expect_error(f0[-1,add=TRUE]<-1, "negative subscripts out of range")
  expect_error(f0[-2,add=TRUE]<-1, "negative subscripts out of range")

  rm(r1,r0)
  rm(f1,f0)
  gc()
})


test_that("swap are correct when accessing zero and four file length", {
  r4 <- quad(4)
  r3 <- quad(3)
  r2 <- quad(2)
  r1 <- quad(1)
  r0 <- quad(0)
  names(r4)<- letters[1:4]
  names(r3) <- letters[1:3]
  names(r2) <- letters[1:2]
  names(r1) <- letters[1]
  names(r0) <- character()
  f4 <- as.ff(r4, pattern="ff", finalizer="close")
  f0 <- as.ff(r0, pattern="ff", finalizer="close")
  expect_identical(names(f4[]), names(r4))
  expect_identical(names(f0[]), names(r0))
  expect_identical(pattern(f4), "ff")
  expect_identical(pattern(f0), "ff")
  expect_identical(finalizer(f4), "close")
  expect_identical(finalizer(f0), "close")
  expect_identical(f4[], r4)
  expect_identical(f0[], r0)
  
  # -- first we do some checks for 4 elements
  expect_silent(ram <- f4[])
  expect_identical(swap(ram, 2L), r4)
  expect_identical(ram, r4+2L)
  expect_identical(swap(f4, 2L), r4)
  expect_identical(f4[], r4+2L)
  
  expect_identical(swap(ram, 4L, 1), r4[1]+2L)
  expect_identical(ram, r4+c(4L,2L,2L,2L))
  expect_identical(swap(f4, 4L, 1), r1+2L)
  expect_identical(f4[], r4+c(0L,2L,2L,2L))
  
  expect_identical(swap(ram, 1L, integer()), r4[integer()])
  expect_identical(ram, r4+c(4L,2L,2L,2L))
  expect_identical(swap(f4, 1L, integer()), r0)
  
  expect_identical(swap(ram, 1L, 0), r4[integer()])
  expect_identical(ram, r4+c(4L,2L,2L,2L))
  expect_error(swap(f4, 1L, 0), "0s and mixed positive/negative subscripts not allowed")
  expect_error(swap(f4, 1L, -5), "negative subscripts out of range")
  expect_error(swap(f4, 1L, 5), "positive subscripts out of range")
  
  f4[] <- 0L
  ram <- f4[]
  expect_identical(swap(ram, 1L, -(3:4)), r4[-(3:4)])
  expect_identical(ram, r4+c(1L,1L,0L,0L))
  expect_identical(swap(f4, 1L, -(3:4)), r2)
  expect_identical(f4[], r4+c(1L,1L,0L,0L))

  f4[] <- 0L
  expect_silent(swap(f4,5L))
  expect_identical(f4[], r4+1L)
  expect_silent(swap(f4,-1L))
  expect_identical(f4[], r4+3L)
  
  f4[] <- 0:3
  expect_identical(swap(f4,1L,add=TRUE), r4+c(1:3,0L))
  expect_identical(f4[], r4+c(1:3,0L))
  expect_identical(swap(f4,-1L,add=TRUE), r4+0:3)
  expect_identical(f4[], r4+0:3)
  

  # -- now we do similar for 0 elements
  expect_silent(ram <- f0[])
  expect_identical(swap(ram, 2L), r0)
  expect_identical(ram, r0)
  expect_identical(swap(f0, 2L), r0)
  expect_identical(f0[], r0)
  
  expect_true(is.na(swap(ram, 4L, 1)))  # assigns to new position
  expect_identical(ram, structure(4L, .Names = "", vmode = "quad"))  # now ram is longer than before
  ram <- f0[]
  expect_error(swap(f0, 4L, 1), "positive subscripts out of range")
  expect_identical(f0[], r0)
  
  expect_identical(swap(ram, 1L, integer()), r0[integer()])
  expect_identical(ram, r0)
  expect_identical(swap(f0, 1L, integer()), r0)
  
  expect_identical(swap(ram, 1L, 0), r0[integer()])
  expect_identical(ram, r0)
  expect_error(swap(f0, 1L, 0), "0s and mixed positive/negative subscripts not allowed")
  expect_error(swap(f0, 1L, -5), "negative subscripts out of range")
  expect_error(swap(f0, 1L, 5), "positive subscripts out of range")
  
  f0[] <- 0L
  ram <- f0[]
  expect_identical(swap(ram, 1L, -(3:4)), r0[-(3:4)])
  expect_identical(ram, r0)
  expect_error(swap(f0, 1L, -(3:4)), "negative subscripts out of range")
  expect_identical(f0[], r0)
  
  f0[] <- 0L
  expect_silent(swap(f0,5L))
  expect_identical(f0[], r0)
  expect_silent(swap(f0,-1L))
  expect_identical(f0[], r0)
  
  f0[] <- 0L
  expect_identical(swap(f0,1L,add=TRUE), r0)
  expect_identical(f0[], r0)
  expect_identical(swap(f0,-1L,add=TRUE), r0)
  expect_identical(f0[], r0)
    
  rm(r0,r1,r2,r3,r4)
  rm(f4)
  gc()
})



test_that("add is correct when accessing zero and four file length", {
  r4 <- quad(4)
  r3 <- quad(3)
  r2 <- quad(2)
  r1 <- quad(1)
  r0 <- quad(0)
  names(r4)<- letters[1:4]
  names(r3) <- letters[1:3]
  names(r2) <- letters[1:2]
  names(r1) <- letters[1]
  names(r0) <- character()
  f4 <- as.ff(r4, pattern="ff", finalizer="close")
  f0 <- as.ff(r0, pattern="ff", finalizer="close")
  expect_identical(names(f4[]), names(r4))
  expect_identical(names(f0[]), names(r0))
  expect_identical(pattern(f4), "ff")
  expect_identical(pattern(f0), "ff")
  expect_identical(finalizer(f4), "close")
  expect_identical(finalizer(f0), "close")
  expect_identical(f4[], r4)
  expect_identical(f0[], r0)
  
  # -- first we do some checks for 4 elements
  expect_silent(f4[] <- 0)
  expect_silent(ram <- f4[])
  expect_silent(add(ram, 1L))
  expect_identical(ram, r4+1L)
  expect_silent(add(f4, 1))
  expect_identical(f4[], r4+1L)
  
  expect_silent(f4[] <- 0)
  expect_silent(ram <- f4[])
  expect_silent(add(ram, 1:2))
  expect_identical(ram, r4+1:2)
  expect_silent(add(f4, 1:2))
  expect_identical(f4[], r4+1:2)
  
  expect_silent(f4[] <- 0)
  expect_silent(ram <- f4[])
  expect_warning(add(ram, 1:3), "longer object length is not a multiple of shorter object length")
  expect_identical(ram, r4+c(1:3,1L))
  expect_warning(add(f4, 1:3), "number of elements to replace is not multiple of values for replacement")
  expect_identical(f4[], r4+c(1:3,1L))
  
  expect_silent(f4[] <- 0)
  expect_silent(ram <- f4[])
  expect_warning(add(ram, 0:7), "number of items to replace is not a multiple of replacement length")
  expect_identical(ram, r4+0:3)
  expect_warning(add(f4, 0:7), "number of elements to replace is not multiple of values for replacement")
  expect_identical(f4[], r4+0:3)
  
  expect_warning(add(ram, -(0:7)), "number of items to replace is not a multiple of replacement length")
  expect_identical(ram, r4)
  expect_silent(add(f4, -(4:7))) # wrap-sround maps to -(0:3)
  expect_identical(f4[], r4)
  
  # -- now we do similar for 0 elements
  expect_silent(ram <- f0[])
  expect_silent(add(ram, 1L))
  expect_identical(ram, r0)
  expect_silent(add(f0, 1))
  expect_identical(f0[], r0)
  
  expect_silent(ram <- f0[])
  expect_silent(add(ram, 1:2))
  expect_identical(ram, r0)
  expect_silent(add(f0, 1:2))
  expect_identical(f0[], r0)
  

  rm(r0,r1,r2,r3,r4)
  rm(f4)
  gc()
})



test_that("zero length ff can be cloned", {
  expect_silent(a1 <- ff(length=1, vmode="integer", pattern="ff"))
  expect_silent(a0 <- ff(length=0, vmode="integer", pattern="ff"))
  
  expect_silent(b1 <- ff(a1))
  expect_silent(b0 <- ff(a0))
  
  expect_silent(c1 <- clone(a1))
  expect_silent(c0 <- clone(a0))
  
  expect_identical(a1[], b1[])
  expect_identical(a0[], b0[])
  
  expect_identical(a1[], c1[])
  expect_identical(a0[], c0[])
  
  rm(a0,a1)
  rm(b0,b1)
  rm(c0,c1)
  gc()
})




test_that("lots of stuff related to dims work", {
  
  vm <- "quad"
  
  expect_silent(r <- as.vmode(integer(), vmode=vm))
  
  expect_silent(r0 <- as.vmode(integer(0), vmode=vm))
  expect_silent(r1 <- as.vmode(integer(1), vmode=vm))
  
  expect_silent(r00 <- as.vmode(integer( 0), vmode=vm))
  expect_silent(r01 <- as.vmode(integer( 0), vmode=vm))
  expect_silent(r10 <- as.vmode(integer( 0), vmode=vm))
  expect_silent(r11 <- as.vmode(integer( 1), vmode=vm))
  expect_silent(r09 <- as.vmode(integer( 0), vmode=vm))
  expect_silent(r19 <- as.vmode(integer( 9), vmode=vm))
  expect_silent(r90 <- as.vmode(integer( 0), vmode=vm))
  expect_silent(r91 <- as.vmode(integer( 9), vmode=vm))
  expect_silent(r99 <- as.vmode(integer(81), vmode=vm))
  
  expect_error(dim(r) <- integer())
  
  expect_silent(dim(r) <- NULL)
  
  expect_silent(dim(r0) <- 0L)
  expect_silent(dim(r1) <- 1L)
  
  expect_silent(dim(r00) <- c(0L,0L))
  expect_silent(dim(r01) <- c(0L,1L))
  expect_silent(dim(r10) <- c(1L,0L))
  expect_silent(dim(r11) <- c(1L,1L))
  expect_silent(dim(r09) <- c(0L,9L))
  expect_silent(dim(r19) <- c(1L,9L))
  expect_silent(dim(r90) <- c(9L,0L))
  expect_silent(dim(r91) <- c(9L,1L))
  expect_silent(dim(r99) <- c(9L,9L))
  
  expect_silent(d <- NULL)

  expect_silent(d0 <- list(character()))
  expect_silent(d1 <- list(LETTERS[1]))
  
  expect_silent(d00 <- list(character(), character()))
  expect_silent(d01 <- list(character(), letters[1]))
  expect_silent(d10 <- list(LETTERS[1], character()))
  expect_silent(d11 <- list(LETTERS[1], letters[1]))
  expect_silent(d09 <- list(character(), letters[1:9]))
  expect_silent(d19 <- list(LETTERS[1], letters[1:9]))
  expect_silent(d90 <- list(LETTERS[1:9], character()))
  expect_silent(d91 <- list(LETTERS[1:9], letters[1]))
  expect_silent(d99 <- list(LETTERS[1:9], letters[1:9]))
  
  
  expect_silent(dimnames(r) <- d)
  
  expect_silent(dimnames(r0) <- d0)
  expect_silent(dimnames(r1) <- d1)
  
  expect_silent(dimnames(r00) <- d00)
  expect_silent(dimnames(r01) <- d01)
  expect_silent(dimnames(r10) <- d10)
  expect_silent(dimnames(r11) <- d11)
  expect_silent(dimnames(r09) <- d09)
  expect_silent(dimnames(r19) <- d19)
  expect_silent(dimnames(r90) <- d90)
  expect_silent(dimnames(r91) <- d91)
  expect_silent(dimnames(r99) <- d99)
  
  expect_silent(a <- as.ff(r))
  expect_silent(a0 <- as.ff(r0))
  expect_silent(a1 <- as.ff(r1))
  expect_silent(a00 <- as.ff(r00))
  expect_silent(a01 <- as.ff(r01))
  expect_silent(a10 <- as.ff(r10))
  expect_silent(a11 <- as.ff(r11))
  expect_silent(a09 <- as.ff(r09))
  expect_silent(a19 <- as.ff(r19))
  expect_silent(a90 <- as.ff(r90))
  expect_silent(a91 <- as.ff(r91))
  expect_silent(a99 <- as.ff(r99))
  
  expect_equal(a[], r[])
  expect_equal(a0[], r0[])
  expect_equal(a1[], r1[])
  expect_equal(a00[], r00[])
  expect_equal(a01[], r01[])
  expect_equal(a10[], r10[])
  expect_equal(a11[], r11[])
  expect_equal(a09[], r09[])
  expect_equal(a19[], r19[])
  expect_equal(a90[], r90[])
  expect_equal(a91[], r91[])
  expect_equal(a99[], r99[])

  expect_silent(c <- clone(a))
  expect_silent(c0 <- clone(a0))
  expect_silent(c1 <- clone(a1))
  expect_silent(c00 <- clone(a00))
  expect_silent(c01 <- clone(a01))
  expect_silent(c10 <- clone(a10))
  expect_silent(c11 <- clone(a11))
  expect_silent(c09 <- clone(a09))
  expect_silent(c19 <- clone(a19))
  expect_silent(c90 <- clone(a90))
  expect_silent(c91 <- clone(a91))
  expect_silent(c99 <- clone(a99))
  
  expect_equal(a[], c[])
  expect_equal(a0[], c0[])
  expect_equal(a1[], c1[])
  expect_equal(a00[], c00[])
  expect_equal(a01[], c01[])
  expect_equal(a10[], c10[])
  expect_equal(a11[], c11[])
  expect_equal(a09[], c09[])
  expect_equal(a19[], c19[])
  expect_equal(a90[], c90[])
  expect_equal(a91[], c91[])
  expect_equal(a99[], c99[])
  
  
  expect_error(f <- ff(0, vmode=vm, dim=integer()), "'dims' cannot be of length 0")
  expect_silent(f <- ff(0, vmode=vm))
  
  expect_silent(f0 <- ff(0, vmode=vm, dim=0L))
  expect_silent(f1 <- ff(0, vmode=vm, dim=1L))
  
  expect_silent(f00 <- ff(0, vmode=vm, dim=c(0L,0L)))
  expect_silent(f01 <- ff(0, vmode=vm, dim=c(0L,1L)))
  expect_silent(f10 <- ff(0, vmode=vm, dim=c(1L,0L)))
  expect_silent(f11 <- ff(0, vmode=vm, dim=c(1L,1L)))
  expect_silent(f09 <- ff(0, vmode=vm, dim=c(0L,9L)))
  expect_silent(f19 <- ff(0, vmode=vm, dim=c(1L,9L)))
  expect_silent(f90 <- ff(0, vmode=vm, dim=c(9L,0L)))
  expect_silent(f91 <- ff(0, vmode=vm, dim=c(9L,1L)))
  expect_silent(f99 <- ff(0, vmode=vm, dim=c(9L,9L)))
  

  expect_silent(dimnames(f) <- d)
  
  expect_silent(dimnames(f0) <- d0)
  expect_silent(dimnames(f1) <- d1)
  
  expect_silent(dimnames(f00) <- d00)
  expect_silent(dimnames(f01) <- d01)
  expect_silent(dimnames(f10) <- d10)
  expect_silent(dimnames(f11) <- d11)
  expect_silent(dimnames(f09) <- d09)
  expect_silent(dimnames(f19) <- d19)
  expect_silent(dimnames(f90) <- d90)
  expect_silent(dimnames(f91) <- d91)
  expect_silent(dimnames(f99) <- d99)
  
  expect_equal(dimnames(r), dimnames(f))
  #expect_equal(dimnames(r0), dimnames(f0))
  expect_equal(dimnames(r1), dimnames(f1))
  #expect_equal(dimnames(r00), dimnames(f00))
  #expect_equal(dimnames(r01), dimnames(f01))
  #expect_equal(dimnames(r10), dimnames(f10))
  expect_equal(dimnames(r11), dimnames(f11))
  #expect_equal(dimnames(r09), dimnames(f09))
  #expect_equal(dimnames(r90), dimnames(f90))
  expect_equal(dimnames(r19), dimnames(f19))
  expect_equal(dimnames(r91), dimnames(f91))
  expect_equal(dimnames(r99), dimnames(f99))
    
  expect_equal(a0[], f0[])
  expect_equal(a1[], f1[])
  expect_equal(a00[], f00[])
  expect_equal(a01[], f01[])
  expect_equal(a10[], f10[])
  expect_equal(a11[], f11[])
  expect_equal(a09[], f09[])
  expect_equal(a19[], f19[])
  expect_equal(a90[], f90[])
  expect_equal(a91[], f91[])
  expect_equal(a99[], f99[])
  
  for (frc in list(f00, f01, f10, f11, f09, f19, f90, f91, f99)){
    d <- dim(frc)
    i <- seq_len(d[[1]])
    j <- seq_len(d[[2]])
    k <- seq_len(prod(d))
    ftmp <- clone(frc)
    rtmp <- ftmp[]
    rtmp[] <- rtmp[] + 1L
    ftmp[] <- rtmp[]
    expect_equal(ftmp[], rtmp[])
    rtmp[,] <- rtmp[,] + 1L
    ftmp[,] <- rtmp[,]
    expect_equal(ftmp[], rtmp[])
    rtmp[k] <- rtmp[k] + 1L
    ftmp[k] <- rtmp[k]
    expect_equal(ftmp[], rtmp[])
    rtmp[i,] <- rtmp[i,] - 1L
    ftmp[i,] <- rtmp[i,]
    expect_equal(ftmp[], rtmp[])
    rtmp[,j] <- rtmp[,j] - 1L
    ftmp[,j] <- rtmp[,j]
    expect_equal(ftmp[], rtmp[])
    rtmp[i,j] <- rtmp[i,j] - 1L
    ftmp[i,j] <- rtmp[i,j]
    expect_equal(ftmp[], rtmp[])
    close(ftmp)
    delete(ftmp)
  }
    
  for (frc in list(f00, f01, f10, f11, f09, f19, f90, f91, f99)){
    d <- dim(frc)
    i <- seq_len(d[[1]])
    j <- seq_len(d[[2]])
    k <- seq_len(prod(d))
    ftmp <- clone(frc)
    rtmp <- ftmp[]
    expect_equal(swap(ftmp, 1L), {ret <- swap(rtmp, 1L); vmode(ret) <- vm; ret})
    expect_equal(ftmp[], rtmp[])
    expect_equal(swap(ftmp, 1L,,), {ret <- swap(rtmp, 1L,,); vmode(ret) <- vm; ret})
    expect_equal(ftmp[], rtmp[])
    expect_equal(swap(ftmp, 1L,k), {ret <- swap(rtmp, 1L,k); vmode(ret) <- vm; ret})
    expect_equal(ftmp[], rtmp[])
    expect_equal(swap(ftmp, 1L,i,), {ret <- swap(rtmp, 1L,i,); vmode(ret) <- vm; ret})
    expect_equal(ftmp[], rtmp[])
    expect_equal(swap(ftmp, 1L,,j), {ret <- swap(rtmp, 1L,,j); vmode(ret) <- vm; ret})
    expect_equal(ftmp[], rtmp[])
    expect_equal(swap(ftmp, 1L,i,j), {ret <- swap(rtmp, 1L,i,j); vmode(ret) <- vm; ret})
    expect_equal(ftmp[], rtmp[])
    close(ftmp)
    delete(ftmp)
  }

  for (frc in list(f00, f01, f10, f11, f09, f19, f90, f91, f99)){
    d <- dim(frc)
    i <- seq_len(d[[1]])
    j <- seq_len(d[[2]])
    k <- seq_len(prod(d))
    ftmp <- clone(frc)
    rtmp <- ftmp[]
    expect_silent(rtmp[] <- 1L)
    expect_silent(ftmp[] <- 1L)
    expect_equal(ftmp[], rtmp[])
    expect_silent(rtmp[,] <- 2L)
    expect_silent(ftmp[,] <- 2L)
    expect_equal(ftmp[], rtmp[])
    expect_silent(rtmp[k] <- 3L)
    expect_silent(ftmp[k] <- 3L)
    expect_equal(ftmp[], rtmp[])
    expect_silent(rtmp[i,] <- 0L)
    expect_silent(ftmp[i,] <- 0L)
    expect_equal(ftmp[], rtmp[])
    expect_silent(rtmp[,j] <- 1L)
    expect_silent(ftmp[,j] <- 1L)
    expect_equal(ftmp[], rtmp[])
    expect_silent(rtmp[i,j] <- 2L)
    expect_silent(ftmp[i,j] <- 2L)
    expect_equal(ftmp[], rtmp[])
    close(ftmp)
    delete(ftmp)
  }

  dims <- list(f00, f01, f10, f11, f09, f19, f90, f91, f99)
  nams <- sapply(dims, function(x)paste(dim(x), sep="", collapse=""))
  dres <- array(list(NULL), dim=c(length(nams), length(nams)), dimnames = list(obj=nams, dim=nams))
  fres <- array(list(NULL), dim=c(length(nams), length(nams)), dimnames = list(obj=nams, dim=nams))
  for (frc in dims){
    for (drc in dims){
      dtmp <- dim(drc)
      dnam <- paste(dim(drc), sep="", collapse="")
      fnam <- paste(dim(frc), sep="", collapse="")
      ftmp <- clone(frc)
      rtmp <- ftmp[]
      etmp <- try(dim(rtmp) <- dtmp, silent = TRUE)
      if (inherits(etmp, 'try-error')){
        dres[[fnam,dnam]] <- as.character(etmp)
      }
      etmp <- try(dim(ftmp) <- dtmp, silent = TRUE)
      if (inherits(etmp, 'try-error')){
        fres[[fnam,dnam]] <- as.character(etmp)
      }
      close(ftmp)
      delete(ftmp)
    }
  }
  
  dok <- apply(dres, 1:2, function(x){is.null(x[[1]])})
  fok <- apply(fres, 1:2, function(x){is.null(x[[1]])})
  #check whether differences are plausible ...
  #b <- bok <- dok == fok
  #b[] <- ''
  #b[!bok] <- paste(dok[!bok], fok[!bok], sep="-")
  #b
  # ... and freeze results for regression-test
  expect_equal(dok, structure(c(
    TRUE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, 
    FALSE, TRUE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, 
    TRUE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, 
    FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
    TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
    FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, TRUE, 
    FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
    FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
    FALSE, FALSE, FALSE, FALSE, FALSE, TRUE), .Dim = c(9L, 9L), .Dimnames = list(
      obj = c("00", "01", "10", "11", "09", "19", "90", "91", "99"
      ), dim = c("00", "01", "10", "11", "09", "19", "90", "91", 
                 "99"))))
  
  expect_equal(fok, structure(c(
    TRUE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, 
    FALSE, TRUE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, 
    TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, 
    FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, 
    TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, 
    TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, TRUE, FALSE, 
    TRUE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
    TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
    TRUE, TRUE, TRUE), .Dim = c(9L, 9L), .Dimnames = list(obj = c("00", 
    "01", "10", "11", "09", "19", "90", "91", "99"), dim = c("00", 
    "01", "10", "11", "09", "19", "90", "91", "99"))))
  
  rm(rtmp, ftmp, dtmp, etmp, dnam, fnam, dims, nams, dres, fres, dok, fok); gc()
  rm(i,j,k,vm,ret)
  rm(frc, drc)
  
  rm(d, d0, d1, d00, d01, d10, d11, d09, d19, d90, d91, d99)
  rm(r, r0, r1, r00, r01, r10, r11, r09, r19, r90, r91, r99)
  rm(a, a0, a1, a00, a01, a10, a11, a09, a19, a90, a91, a99)
  rm(c, c0, c1, c00, c01, c10, c11, c09, c19, c90, c91, c99)
  rm(f, f0, f1, f00, f01, f10, f11, f09, f19, f90, f91, f99)
  
})


