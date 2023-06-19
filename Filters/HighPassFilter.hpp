/**
 * @file HighPassFilter.hpp
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * @see https://coding-robot.tistory.com/15
 */
#ifndef __MODULE_HIGH_PASS_FILTER_H__
#define __MODULE_HIGH_PASS_FILTER_H__

#include "../module_hal_types.hpp"

class HighPassFilter
{
public:
   HighPassFilter()
   {
      tau = 0.0;
      ts = 0.0;
      out = 0.0;
      in = 0.0;
   }
   HighPassFilter(float tau, float ts)
   {
      this->tau = tau;
      this->ts = ts;
      out = 0.0f;
      in = 0.0f;
   }
   void reset()
   {
      out = 0.0f;
      in = 0.0f;
   }
   void set(float tau, float ts)
   {
      this->tau = tau;
      this->ts = ts;
      reset();
   }
   float hpf(float in)
   {
      out = (tau / (tau + ts)) * (out + in - this->in);
      this->in = in;
      return out;
   }
private:
   float tau;
   float ts;
   float out;
   float in;
};

#endif /* __MODULE_HIGH_PASS_FILTER_H__ */
