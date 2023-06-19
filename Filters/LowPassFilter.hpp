/**
 * @file LowPassFilter.hpp
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * @see https://pinkwink.kr/741
 */
#ifndef __MODULE_LOWER_PASS_FILTER_H__
#define __MODULE_LOWER_PASS_FILTER_H__

#include "../module_hal_types.hpp"

class LowerPassFilter
{
public:
   LowPassFilter()
   {
      tau = 0.0;
      ts = 0.0;
      out = 0.0;
   }
   LowPassFilter(float tau, float ts)
   {
      this.tau = tau;
      this.ts = ts;
      out = 0.0f;
   }
   void reset()
   {
      out = 0.0f;
   }
   float lpf(float in)
   {
      out = (tau * out + ts * in) / (tau + ts);
      return out;
   }
   void set(float tau, float ts)
   {
      this.tau = tau;
      this.ts = ts;
   }
private:
   float tau;
   float ts;
   float out;
};

#endif /* __MODULE_LOWER_PASS_FILTER_H__ */
