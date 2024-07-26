/*	$OpenBSD: stdint.h,v 1.11 2019/01/25 00:19:26 millert Exp $	*/

/*
 * Copyright (c) 1997, 2005 Todd C. Miller <millert@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef	_SYS_STDINT_H_
#define _SYS_STDINT_H_

#ifndef	__BIT_TYPES_DEFINED__
#define	__BIT_TYPES_DEFINED__
#endif

/* 7.18.1.1 Exact-width integer types (also in sys/types.h) */
#ifndef	_INT8_T_DEFINED_
#define	_INT8_T_DEFINED_
typedef	char		xint8_t;
#endif

#ifndef	_INT16_T_DEFINED_
#define	_INT16_T_DEFINED_
typedef	short		xint16_t;
#endif

#ifndef	_INT32_T_DEFINED_
#define	_INT32_T_DEFINED_
typedef	int		xint32_t;
#endif

#ifndef	_INT64_T_DEFINED_
#define	_INT64_T_DEFINED_
typedef	long		xint64_t;
#endif

#ifndef	_UINT8_T_DEFINED_
#define	_UINT8_T_DEFINED_
typedef	char		xuint8_t;
#endif

#ifndef	_UINT16_T_DEFINED_
#define	_UINT16_T_DEFINED_
typedef	unsigned short		xuint16_t;
#endif

#ifndef	_UINT32_T_DEFINED_
#define	_UINT32_T_DEFINED_
typedef	unsigned int		xuint32_t;
#endif

#ifndef	_UINT64_T_DEFINED_
#define	_UINT64_T_DEFINED_
typedef	unsigned long		xuint64_t;
#endif

/* 7.18.1.4 Integer types capable of holding object pointers */
#ifndef	_INTPTR_T_DEFINED_
#define	_INTPTR_T_DEFINED_
typedef	xint64_t		xintptr_t;
#endif

typedef	xuint64_t		xuintptr_t;

/*
 * 7.18.4 Macros for integer constants.
 *
 * The following function-like macros expand to integer constants
 * suitable for initializing objects that have integer types corresponding
 * to types defined in <stdint.h>.  The argument in any instance of
 * these macros shall be a decimal, octal, or hexadecimal constant with
 * a value that does not exceed the limits for the corresponding type.
 */

/* 7.18.4.1 Macros for minimum-width integer constants. */
#define	INT8_C(_c)		(_c)
#define	INT16_C(_c)		(_c)
#define	INT32_C(_c)		(_c)
#define	INT64_C(_c)		__CONCAT(_c, LL)

#define	UINT8_C(_c)		(_c)
#define	UINT16_C(_c)		(_c)
#define	UINT32_C(_c)		__CONCAT(_c, U)
#define	UINT64_C(_c)		__CONCAT(_c, ULL)

/* 7.18.4.2 Macros for greatest-width integer constants. */
#define	INTMAX_C(_c)		__CONCAT(_c, LL)
#define	UINTMAX_C(_c)		__CONCAT(_c, ULL)

#endif /* _SYS_STDINT_H_ */