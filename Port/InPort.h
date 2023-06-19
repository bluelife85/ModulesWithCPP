/**
 * @file InPort.h
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __MODULE_IN_PORT_H__
#define __MODULE_IN_PORT_H__

#include "../module_hal_types.hpp"

struct InPortInit
{
   IoRead read;
   uint32_t timeout;
   GetTick getTick;
   IsElapsed isElapsed;
   InPort::PullState pull;
   bool hasLongState;
};

class InPort
{
public:
   enum State
   {
      NONE = 0,
      SHORT,
      LONG,
      ON_PUSH
   };

   enum PullState
   {
      DOWN,
      UP
   };

   InPort(struct InPortInit& init)
   {
      read = init.read;
      pull = init.pull;
      if(init.hasLongState)
      {
         timeout = init.timeout;
         getTick = init.getTick;
         isElapsed = init.isElapsed;
      }
      hasLongState = init.hasLongState;
   }

   State readState() const
   {
      bool io = read();
      bool comp = (pull == UP) ? (false) : (true);
      State ret = State::NONE;
      if(io == comp)
      {
         if(hasLongState)
         {
            if(!isPushed)
            {
               isPushed = true;
               tick = getTick();
            }

            ret = State::ON_PUSH;
         }
         else
         {
            ret = State::SHORT;
         }
      }
      else
      {
         if(hasLongState)
         {
            if(isPushed)
            {
               if(isElapsed(timeout, tick))
               {
                  ret = State::LONG;
               }
               else
               {
                  ret = State::SHORT;
               }

               isPushed = false;
            }
         }
         else
         {
            ret = State::NONE;
         }
      }

      return ret;
   }
private:
   IoRead read;
   GetTick getTick;
   IsElapsed isElapsed;
   PullState pull;
   uint32_t timeout;
   uint32_t tick;
   bool hasLongState;
   bool isPushed;
};

#endif /* __MODULE_IN_PORT_H__ */
