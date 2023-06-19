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

/**
 * @brief data type to initialize InPort class.
 */
struct InPortInit
{
   IoRead read; /**< @see IoCtrl */
   uint32_t timeout; /**< the time (ms) for distinguishing between long button and short button among input functions.*/
   GetTick getTick; /**< @see GetTick */
   IsElapsed isElapsed; /**< @see IsElapsed */
   InPort::PullState pull; /**< When there is no input, it determines whether it is high-state or low-state. */
   bool hasLongState; /**< Depending on the input time, it determines whether long and short need to be distinguished. */
};

/**
 * @brief A class that creates an object that is only input 
 *        among the functions of GPIO.
 */
class InPort
{
public:
   /**
    * @brief the input result. 
    */
   enum State
   {
      NONE = 0,
      SHORT,
      LONG,
      ON_PUSH
   };
   /**
    * @brief When there is no input, it determines whether
    *        it is high-state or low-state.
    */
   enum PullState
   {
      DOWN,
      UP
   };
   /**
    * @brief Construct a new InPort object
    * @param init @see InPortInit
    */
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
   /**
    * @brief read the pin state.
    * @return State @see InPort::State
    * @note 
    */
   State readState()
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
