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

/**
 * @brief Among the functions of GPIO, a class for creating an object 
 *        that serves only as an output.
 */
class OutPort
{
public:
   /**
    * @brief Constructor for using only general output.
    * @param _io @see IoCtrl
    * @note When creating an object using this constructor,
    *       toggle by interval is not supported.
    */
   OutPort(IoCtrl _io)
   {
      io = _io;
   }
   /**
    * @brief A constructor that supports toggle mode.
    * 
    * @param _io @see IoCtrl
    * @param _getTick @see GetTick
    * @param _isElapsed @see IsElapsed
    * @param _timeout interval timeout in ms.
    */
   OutPort(IoCtrl _io, GetTick _getTick, IsElapsed _isElapsed, uint32_t _timeout)
   {
      io = _io;
      getTick = _getTick;
      isElapsed = _isElapsed;
      timeout = _timeout;
      mode(true);
   }
   /**
    * @brief Set the Timeout object
    * @param _timeout interval timeout in ms.
    */
   void setTimeout(uint32_t _timeout)
   {
      timeout = _timeout;
   }
   /**
    * @brief controls the hardware GPIO.
    * @param _state @see IoCtrl
    */
   void control(bool _state)
   {
      io(_state);
      state = _state;
   }
   /**
    * @brief decides whether enable toggle mode or not.
    * @param _toggle true or false.
    */
   void mode(bool _toggle)
   {
      tick = getTick();
      toggle = _toggle;
   }
   /**
    * @brief execute the toggle mode.
    */
   void toggle()
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
