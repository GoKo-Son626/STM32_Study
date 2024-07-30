#ifndef __BTIM_H_
#define __BTIM_H_

#include "./SYSTEM/sys/sys.h"

extern TIM_HandleTypeDef g_btime_time6;
void btim_time6_init(uint16_t pre, uint16_t arr);


#endif
