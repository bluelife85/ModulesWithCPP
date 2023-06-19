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
typedef bool (*IoRead)(void);
typedef uint32_t (*CanTx)(uint32_t* word, uint8_t dlc);
typedef bool (*CanRx)(uint8_t* bytes, uint8_t* dlc);

#endif /* __MODULE_HAL_LINK_TYPES_H__ */
