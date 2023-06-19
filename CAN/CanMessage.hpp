/**
 * @file CanMessage.hpp
 * @author Kyungwoo Min (bluelife85@naver.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MODULE_CAN_MESSAGE_H__
#define __MODULE_CAN_MESSAGE_H__

#include "../module_hal_types.hpp"

struct CanMessageInit
{
   CanTx tx;
   CanRx rx;
   uint8_t dlc;
};

template <typename Message>
class CanMessage
{
public:
   CanMessage(CanMessageInit& init) : tx(init.tx), rx(init.rx), dlc(init.dlc)
   {
      frame.word[0] = 0;
      frame.word[1] = 0;
   }

   ~CanMessage() { }

   void setPayload(Message _payload) { frame.payload = _payload; }

   Message getPayload() { return frame.payload; }

   void clearPayload()
   {
      frame.word[0] = 0;
      frame.word[1] = 0;
   }

   inline uint32_t send()
   {
      return tx(frame.word, 8);
   }

   inline bool receive()
   {
      return rx(&frame.word[0], &dlc);
   }
private:
   union 
   {
      uint32_t word[2];
      uint8_t bytes[8];
      Message payload;
   } frame;
   CanTx tx;
   CanRx rx;
   uint8_t dlc;
};

#endif /* __MODULE_CAN_MESSAGE_H__ */
