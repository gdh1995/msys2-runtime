/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2004-2005 David Schultz <das@FreeBSD.ORG>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _SYS_FENV_H_
#define _SYS_FENV_H_ 1

#include <sys/_types.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	__fenv_static
#define	__fenv_static static
#endif

typedef int fenv_t;
typedef int fexcept_t;

/* Exception flags */
#define	FE_INVALID	0x0001
#define	FE_DIVBYZERO	0x0002
#define	FE_OVERFLOW	0x0004
#define	FE_UNDERFLOW	0x0008
#define	FE_INEXACT	0x0010
#ifdef __ARM_PCS_VFP
#define	FE_DENORMAL	0x0080
#define	FE_ALL_EXCEPT	(FE_DIVBYZERO | FE_INEXACT | \
			 FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW | FE_DENORMAL)
#else
#define	FE_ALL_EXCEPT	(FE_DIVBYZERO | FE_INEXACT | \
			 FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)
#endif



/* Rounding modes */
#define	VFP_FE_TONEAREST	0x00000000
#define	VFP_FE_UPWARD		0x00400000
#define	VFP_FE_DOWNWARD		0x00800000
#define	VFP_FE_TOWARDZERO	0x00c00000

#ifdef __ARM_PCS_VFP
#define	FE_TONEAREST	VFP_FE_TONEAREST
#define	FE_UPWARD	VFP_FE_UPWARD
#define	FE_DOWNWARD	VFP_FE_DOWNWARD
#define	FE_TOWARDZERO	VFP_FE_TOWARDZERO
#else
#define	FE_TONEAREST	0x0000
#define	FE_TOWARDZERO	0x0001
#define	FE_UPWARD	0x0002
#define	FE_DOWNWARD	0x0003
#endif
#define	_ROUND_MASK	(FE_TONEAREST | FE_DOWNWARD | \
			 FE_UPWARD | FE_TOWARDZERO)


/* Default floating-point environment */

extern const fenv_t	*_fe_dfl_env;
#define	FE_DFL_ENV	(_fe_dfl_env)

/* We need to be able to map status flag positions to mask flag positions */
#ifndef __ARM_PCS_VFP
#define	_FPUSW_SHIFT	16
#define	_ENABLE_MASK	(FE_ALL_EXCEPT << _FPUSW_SHIFT)
#endif



int feclearexcept(int excepts);
int fegetexceptflag(fexcept_t *flagp, int excepts);
int fesetexceptflag(const fexcept_t *flagp, int excepts);
int feraiseexcept(int excepts);
int fetestexcept(int excepts);
int fegetround(void);
int fesetround(int round);
int fegetenv(fenv_t *envp);
int feholdexcept(fenv_t *envp);
int fesetenv(const fenv_t *envp);
int feupdateenv(const fenv_t *envp);
#if __BSD_VISIBLE
int feenableexcept(int __mask);
int fedisableexcept(int __mask);
int fegetexcept(void);
#endif /* __BSD_VISIBLE */



#ifdef __cplusplus
}
#endif

#endif	/* _SYS_FENV_H_ */ 
