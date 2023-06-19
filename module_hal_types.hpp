/**
 * @file module_hal_types.h
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __MODULE_HAL_LINK_TYPES_H__
#define __MODULE_HAL_LINK_TYPES_H__

#include <cstdint>

typedef uint32_t (*GetTick)(void);
typedef bool (*IsElapsed)(uint32_t timeout, uint32_t tick);
typedef void (*IoCtrl)(bool state);

#endif /* __MODULE_HAL_LINK_TYPES_H__ */
