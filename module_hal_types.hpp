/**
 * @file module_hal_types.h
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief This file describes the type of function pointer to link
 *        hardware-dependent and fragmentary functions with modules.
 * @version 0.1
 * @date 2023-06-19
 * 
 */
#ifndef __MODULE_HAL_LINK_TYPES_H__
#define __MODULE_HAL_LINK_TYPES_H__

#include <cstdint>

/**
 * @brief A callback that connects to a hardware timer that counts ticks in ms.
 * @return ms tick.
 */
typedef uint32_t (*GetTick)(void);
/**
 * @brief This is a function callback that determines whether [timeout] time
 *        has passed from [tick].
 * @param[in] timeout Timeout value in ms.
 * @param[in] tick Starting tick value in ms.
 * @return true when the [timeout] value is exceeded,
 *         If not passed, return false.
 */
typedef bool (*IsElapsed)(uint32_t timeout, uint32_t tick);
/**
 * @brief A callback function connected to a function that controls
 *        GPIO for one pin.
 * @param[in] state true : IO should be in set state.
 *                  false : IO should be reset.
 */
typedef void (*IoCtrl)(bool state);
/**
 * @brief A callback function connected to a function that reads
 *        GPIO for one pin.
 * @return true : IO should be in set state.
 *         false : IO should be reset.
 * @note The handling of chattering should be handled by the hardware.
 */
typedef bool (*IoRead)(void);
/**
 * @brief Callback function for the function of transmitting data
 *        through the CAN bus.
 * @param[in] word 64-bit payload data bundle.
 * @param[in] dlc data length code.
 * @return error codes. This error code should be implemented in hardware
 *         and provided to middleware.
 * @note data alignment should be little-endian.
 */
typedef uint32_t (*CanTx)(uint32_t* word, uint8_t dlc);
/**
 * @brief Hardware callback function to receive data from CAN bus.
 * @param[out] bytes received from CAN bus in bytes.
 * @param[out] dlc data length code.
 * @return true : data is received from CAN bus.
 *         false : data is not received.
 * @note data alignment should be little-endian.
 */
typedef bool (*CanRx)(uint8_t* bytes, uint8_t* dlc);

#endif /* __MODULE_HAL_LINK_TYPES_H__ */
