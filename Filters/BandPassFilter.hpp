/**
 * @file BandPassFilter.hpp
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __MODULE_BAND_PASS_FILTER_H__
#define __MODULE_BAND_PASS_FILTER_H__

#include "LowPassFilter.hpp"
#include "HighPassFilter.hpp"

class BandPassFilter
{
public:
   BandPassFilter(float tau, float ts)
   {
      hpf.set(tau, ts);
      lpf.set(tau, ts);
   }
   void set(float tau, float ts)
   {
      hpf.set(tau, ts);
      lpf.set(tau, ts);
   }
   void reset()
   {
      hpf.reset();
      lpf.reset();
   }
   float bpf(float in)
   {
      return hpf.hpf(in) - lpf.lpf(in);
   }
private:
   LowerPassFilter lpf;
   HighPassFilter hpf;
};

#endif /* __MODULE_BAND_PASS_FILTER_H__ */
