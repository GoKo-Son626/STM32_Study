#ifndef _WDG_H
#define _WDG_H

#include "./SYSTEM/sys/sys.h"

void iwdg_init(uint8_t prer, uint16_t rel);
void iwdg_feed(void);


#endif
