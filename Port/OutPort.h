/**
 * @file OutPort.h
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __MODULE_OUT_PORT_H__
#define __MODULE_OUT_PORT_H__

#include "../module_hal_types.hpp"

class OutPort
{
public:
   OutPort(IoCtrl _io, GetTick _getTick, IsElapsed _isElapsed)
   {
      io = _io;
      getTick = _getTick;
      isElapsed = _isElapsed;
   }
   
   OutPort(IoCtrl _io, GetTick _getTick, IsElapsed _isElapsed, uint32_t _timeout)
   {
      io = _io;
      getTick = _getTick;
      isElapsed = _isElapsed;
      timeout = _timeout;
      mode(true);
   }

   void setTimeout(uint32_t _timeout) const
   {
      timeout = _timeout;
   }

   void control(bool _state) const
   {
      io(_state);
      state = _state;
   }

   void mode(bool _toggle) const
   {
      tick = getTick();
      toggle = _toggle;
   }

   void toggle() const
   {
      if(toggle && (timeout != 0))
      {
         if(isElapsed(timeout, tick))
         {
            state = !state;
            Io(state);
            tick = getTick();
         }
      }
   }
private:
   IoCtrl io;
   GetTick getTick;
   IsElapsed isElapsed;
   uint32_t timeout;
   uint32_t tick;
   bool state;
   bool toggle;
};

#endif /* __MODULE_OUT_PORT_H__ */
