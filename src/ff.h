/*/////////////////////////////////////////////////////////////////////////////

 Copyright (c) 2007,2008 Daniel Adler <dadler@uni-goettingen.de>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

/////////////////////////////////////////////////////////////////////////////*/

#ifndef FF_H
#define FF_H

#ifdef __cplusplus
extern "C" {
#endif

/* === ff C Interface ====================================================== */

/** opaque handle type */
typedef void* FF;

/* --- COMMON INTERFACE ---------------------------------------------------- */

/** get system page size */
int    ff_getpagesize(void);


/** get error code */
int    ff_geterror(FF handle);

/** get error message */
const char*  ff_geterrstr(FF handle);


/** close */
void   ff_close(FF handle);

/** destruction */
void   ff_delete(FF handle);


/** return length of ff object in units of double */
int    ff_len(FF handle);

/** --- TYPE-SPECIFIC INTERFACE MACROS ------------------------------------- */

#define FF_DECL_TYPE2(NAME,TYPE,INDEX,SIZE) \
FF   ff_##NAME##_new(const char* filepath, TYPE initval, SIZE size, SIZE pagesize, int readonly, int autoflush \
, int createNew /* Martijn Schuemie for zero row ff */ \
); \
TYPE ff_##NAME##_get(       FF handle, INDEX index); \
void ff_##NAME##_set(       FF handle, INDEX index, TYPE x); \
TYPE ff_##NAME##_getset(    FF handle, INDEX index, TYPE x); \
void ff_##NAME##_addset(    FF handle, INDEX index, TYPE x); \
TYPE ff_##NAME##_addgetset( FF handle, INDEX index, TYPE x); \
void ff_##NAME##_getset_contiguous(   FF handle, INDEX index, SIZE size, TYPE* ret, TYPE* value); \
void ff_##NAME##_get_contiguous(      FF handle, INDEX index, SIZE size, TYPE* ret               ); \
void ff_##NAME##_set_contiguous(      FF handle, INDEX index, SIZE size             , TYPE* value); \
void ff_##NAME##_addgetset_contiguous(FF handle, INDEX index, SIZE size, TYPE* ret, TYPE* value); \
void ff_##NAME##_addset_contiguous(   FF handle, INDEX index, SIZE size             , TYPE* value);

#define FF_DECL_TYPE(NAME,TYPE) \
  FF_DECL_TYPE2(NAME,TYPE,int,int) \
  FF_DECL_TYPE2(NAME##_d,TYPE,double,int)


/* --- TYPE-SPECIFIC FUNCTIONS INTERFACE DECLARATIONS ---------------------- */

/** format:
 **   FF_DECL_TYPE( <name>, <interface value type> )
 **
 **/


FF_DECL_TYPE(boolean,int)
FF_DECL_TYPE(quad,int)
FF_DECL_TYPE(logical,int)
FF_DECL_TYPE(nibble,int)
FF_DECL_TYPE(byte,int)
FF_DECL_TYPE(ubyte,int)
FF_DECL_TYPE(short,int)
FF_DECL_TYPE(ushort,int)
FF_DECL_TYPE(integer,int)
FF_DECL_TYPE(single,double)
FF_DECL_TYPE(double,double)
FF_DECL_TYPE(raw,unsigned char)


#ifdef __cplusplus
}
#endif

#endif /* FF_H */

