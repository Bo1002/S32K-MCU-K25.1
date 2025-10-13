/*
 * clock.h
 *
 *  Created on: Oct 12, 2025
 *      Author: BO
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "S32K144.h"

void SOSC_init_8MHz(void);
void SPLL_init_160MHz(void);
void NormalRUNmode_80MHz(void);

#endif /* CLOCK_H_ */
