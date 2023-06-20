/**
 * @file Hysteresis.h
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief software hysteresis  module.
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __MODULE_HYSTERESIS_H__
#define __MODULE_HYSTERESIS_H__

#include "../module_hal_types.hpp"

/**
 * @brief A structure that connects HAL implementations.
 */
struct HysteresisHAL
{
   GetTick getTick; /**< @see GetTick */
   IsElapsed isElapsed; /**< @see IsElapsed */
};

/**
 * @brief A structure to configure the hysteresis object.
 */
struct HysteresisInit_t
{
   uint32_t upperTimeout; /**< upper area timeout */
   uint32_t lowerTimeout; /**< lower area timeout */
   struct HysteresisHAL hal; /**< HAL layer */
};

enum class HysState
{
   STABLE,
   OVER,
   UNDER
};

template <typename T>
class Hysteresis
{
public:
   Hysteresis(T _upper, T _lower, struct HysteresisInit_t& init) : upper(_upper), lower(_lower)
   {
      upperTimeout = init.upperTimeout;
      lowerTimeout = init.lowerTimeout;
      getTick = init.hal.getTick;
      isElapsed = init.hal.isElapsed;
      tick = 0;
      isUpperHit = false;
      isLowerHit = false;
   }
   HysState check(T value)
   {
      HysState ret;
      
      if(isLowerHit)
      {
         if(isElapsed(lowerTimeout, tick))
         {
            ret = HysState::UNDER;
            if(value > lower)
            {
               ret = HysState::STABLE;
               isLowerHit = false;
            }
         }
         else
         {
            if(value > lower)
            {
               isLowerHit = false;
            }
            
            ret = HysState::STABLE;
         }
      }
      else if(isUpperHit)
      {
         if(isElapsed(upperTimeout, tick))
         {
            ret = HysState::OVER;
            if(value < upper)
            {
               ret = HysState::STABLE;
               isUpperHit = false;
            }
         }
         else
         {
            if(value < upper)
            {
               isUpperHit = false;
            }
            
            ret = HysState::STABLE;
         }
      }
      else
      {
         if(value > upper)
         {
            isUpperHit = true;
            tick = getTick();
         }
         else if(value < lower)
         {
            isLowerHit = true;
            tick = getTick();
         }
         
         ret = HysState::STABLE;
      }
      
      return ret;
   }
private:
   T upper;
   T lower;
   bool isUpperHit;
   bool isLowerHit;
   uint32_t upperTimeout;
   uint32_t lowerTimeout;
   uint32_t tick;
   uint32_t (*getTick)(void);
   bool (*isElapsed)(uint32_t timeout, uint32_t tick);
};

#endif /* __MODULE_HYSTERESIS_H__ */


