/** \file      cyclebuf.h
 *  \brief     contains implementation of cycle buffer toolkit
 *  \copyright if you use this code without telling your buddies what you got it
 *             on github.com/Korrmet - you're an asshole. */

#include <stddef.h>
#include "cyclebuf.h"

/** \brief   as memcpy but dumb
 *  \details was written because not of all have memcpy and some compilers
 *           contains realy HUGE memcpy
 *  \arg     dest  pointer to destination memory
 *  \arg     src   pointer to source memory
 *  \arg     count number of bytes need to copy
 *  \return  pointer to destination in any case */
void* memcpy_dumb(void* dest, const void* src, unsigned int count)
{ if (dest == NULL) { return NULL; }
  if (src  == NULL) { return NULL; }

  char* d = (char*)dest; char* s = (char*)src;
  
  for (unsigned int i = 0; i < count; i++) { *d = *s; d++; s++; }

  return dest; }

/** \brief   write data to head of buffer
 *  \details copy data and move pointer
 *  \arg     cb   pointer to a cycle buffer descriptor
 *  \arg     num  number of items to push
 *  \arg     data pointer of data source
 *  \return  really written data */
unsigned int _cyclebuf_push_head
(cyclebuf_desc_t* cb, unsigned int num, void* data)
{ unsigned int items_written;
  char* data_p = (char*)data;

  for (items_written = 0; items_written < num; items_written++)
  { char* head_prev = cb->head;
    cb->head += cb->item_size;
    
    if (cb->head > cb->mem_end) { cb->head = cb->mem_start; }

    if (cb->head == cb->tail) { cb->head = head_prev; break; } 
    
    memcpy_dumb(head_prev, data_p, cb->item_size);
    data_p += cb->item_size; }

  return items_written; }

unsigned int cyclebuf_push_head 
(cyclebuf_desc_t* cb, unsigned int num, void* data)
{ CYCLEBUF_PROTECT_START_MACRO();
  unsigned int retval = _cyclebuf_push_head(cb, num, data);
  CYCLEBUF_PROTECT_END_MACRO();
  return retval; }

/** \brief   get data from head
 *  \details copy data from buffer and move pointer
 *  \arg     cb   pointer to a cycle buffer descriptor
 *  \arg     num  number of items to pop
 *  \arg     data pointer to place where to copy
 *  \return  actually readen number of items */
unsigned int _cyclebuf_pop_head  
(cyclebuf_desc_t* cb, unsigned int num, void* data)
{ unsigned int items_readen;
  char* data_p = (char*)data;

  for (items_readen = 0; items_readen < num; items_readen++)
  { char* head_prev = cb->head;
    cb->head -= cb->item_size;
    
    if (cb->head < cb->mem_start) { cb->head = cb->mem_end; }
    
    if (cb->head == cb->tail) { cb->head = head_prev; break; }
    
    memcpy_dumb(data_p, cb->head, cb->item_size);
    
    data_p += cb->item_size; }

  return items_readen; }

unsigned int cyclebuf_pop_head  
(cyclebuf_desc_t* cb, unsigned int num, void* data)
{ CYCLEBUF_PROTECT_START_MACRO();
  unsigned int retval = _cyclebuf_pop_head(cb, num, data);
  CYCLEBUF_PROTECT_END_MACRO();
  return retval; }

/** \brief   write data to tail of buffer
 *  \details copy data and move pointer
 *  \arg     cb   pointer to a cycle buffer descriptor
 *  \arg     num  number of items to push
 *  \arg     data pointer of data source
 *  \return  really written data */
unsigned int _cyclebuf_push_tail
(cyclebuf_desc_t* cb, unsigned int num, void* data)
{ unsigned int items_written;
  char* data_p = (char*)data;

  for (items_written = 0; items_written < num; items_written++)
  { char* tail_prev = cb->tail;
    cb->tail -= cb->item_size;
    if (cb->tail < cb->mem_start) { cb->tail = cb->mem_end; }
    if (cb->tail == cb->head) { cb->tail = tail_prev; break; }
    
    memcpy_dumb(tail_prev, data_p, cb->item_size);
    
    data_p++; }

  return items_written; }

unsigned int cyclebuf_push_tail
(cyclebuf_desc_t* cb, unsigned int num, void* data)
{ CYCLEBUF_PROTECT_START_MACRO();
  unsigned int retval = _cyclebuf_push_tail(cb, num, data);
  CYCLEBUF_PROTECT_END_MACRO();
  return retval; }

/** \brief   get data from tail
 *  \details copy data from buffer and move pointer
 *  \arg     cb   pointer to a cycle buffer descriptor
 *  \arg     num  number of items to pop
 *  \arg     data pointer to place where to copy
 *  \return  actually readen number of items */
unsigned int _cyclebuf_pop_tail 
(cyclebuf_desc_t* cb, unsigned int num, void* data)
{ unsigned int items_readen;
  char* data_p = (char*)data;

  for (items_readen = 0; items_readen < num; items_readen++)
  { char* tail_prev = cb->tail;
    cb->tail += cb->item_size;
    if (cb->tail > cb->mem_end) { cb->tail = cb->mem_start; }
    if (cb->tail == cb->head) { cb->tail = tail_prev; break; }

    memcpy_dumb(data_p, cb->tail, cb->item_size);

    data_p++; }

  return items_readen; }

unsigned int cyclebuf_pop_tail 
(cyclebuf_desc_t* cb, unsigned int num, void* data)
{ CYCLEBUF_PROTECT_START_MACRO();
  unsigned int retval = _cyclebuf_pop_tail(cb, num, data);
  CYCLEBUF_PROTECT_END_MACRO();
  return retval; }
