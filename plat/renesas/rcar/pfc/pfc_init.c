/*
 * Copyright (c) 2015-2016, Renesas Electronics Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *   - Neither the name of Renesas nor the names of its contributors may be
 *     used to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <debug.h>
#include <mmio.h>
#include "rcar_def.h"
#include "pfc_init.h"
#if RCAR_LSI == RCAR_AUTO
  #include "H3/pfc_init_h3.h"
  #include "M3/pfc_init_m3.h"
#endif
#if RCAR_LSI == RCAR_H3	/* H3 */
  #include "H3/pfc_init_h3.h"
#endif
#if RCAR_LSI == RCAR_M3	/* M3 */
  #include "M3/pfc_init_m3.h"
#endif

#define PRR_PRODUCT_ERR(reg)	do{\
				ERROR("LSI Product ID(PRR=0x%x) PFC "\
				"initialize not supported.\n",reg);\
				panic();\
				}while(0)


void pfc_init(void)
{
#if RCAR_LSI == RCAR_AUTO
	uint32_t reg;

	reg = mmio_read_32(RCAR_PRR);
	switch (reg & RCAR_PRODUCT_MASK) {
	case RCAR_PRODUCT_H3:
		pfc_init_h3();
		break;
	case RCAR_PRODUCT_M3:
		pfc_init_m3();
		break;
	default:
		PRR_PRODUCT_ERR(reg);
		break;
	};

#elif RCAR_LSI == RCAR_H3	/* H3 */
	pfc_init_h3();
#elif RCAR_LSI == RCAR_M3	/* M3 */
	pfc_init_m3();
#endif
}
