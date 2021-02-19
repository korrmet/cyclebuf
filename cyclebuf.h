/** \file      cyclebuf.h
 *  \brief     contains interface of cycle buffer 
 *  \details   this is a simple cycle buffer implementation. i wrote it many 
 *             times before and i decide what it's enough. this implementation 
 *             use pointer arithmetics and use minimum of storage so it's more
 *             stable than another ones in my practice.
 *
 *             so today i write some code for interview and i decide to use
 *             this kind of buffer. but i have no implementation of it. again...
 *  \copyright if you use this code without telling your buddies what you got it
 *             on github.com/Korrmet - you're an asshole. */

#ifndef CYCLEBUF_H
#define CYCLEBUF_H

/** \brief   descriptor of cycle buffer
 *  \details used as argument of functions. you should not use it as is */
typedef struct //cyclebuf_desc_t
{ char* mem_start;        ///< start of buf memory
  char* mem_end;          ///< end of buf memory
  unsigned int item_size; ///< size of each item of buffer
  char* head;             ///< points to first FREE data
  char* tail;             ///< points to place before last USED data
} cyclebuf_desc_t;

#ifndef CYCLEBUF_PROTECT_START_MACRO
/** \brief this macro must guarantee, what after it context will not be broken
 *         and data operation will be secure */
#define CYCLEBUF_PROTECT_START_MACRO()
#endif

#ifndef CYCLEBUF_PROTECT_END_MACRO
/** \brief canceles CYCLEBUF_PROTECT_START_MACRO() */
#define CYCLEBUF_PROTECT_END_MACRO()
#endif

/** \brief   creates cycle buffer statically and tune it
 *  \details creates cycle buffer descriptor, memory array which will be called
 *           name#_mem. you can use it for create global or local area.
 *  \arg     name name of cycle buffer
 *  \arg     type type of elementof cycle buffer
 *  \arg     num  number of maximum elements inside it */
#define CYCLEBUF_CREATE_STATIC(name, type, num)                            \
  type name##_mem[num + 2] = {};                                           \
  cyclebuf_desc_t name = { .mem_start = (char*)name##_mem,                 \
                           .mem_end   = (char*)(&name##_mem[num + 2 - 1]), \
                           .item_size = sizeof(type),                      \
                           .head      = (char*)name##_mem + sizeof(type),  \
                           .tail      = (char*)name##_mem } 

/** \brief   write data to head of buffer
 *  \details wrapper of real push function
 *  \arg     cb   pointer to a cycle buffer descriptor
 *  \arg     num  number of items to push
 *  \arg     data pointer of data source
 *  \return  actually written number of items */
unsigned int cyclebuf_push_head 
(cyclebuf_desc_t* cb, unsigned int num, void* data);

/** \brief   get data from head
 *  \details wrapper of real pop function
 *  \arg     cb   pointer to a cycle buffer descriptor
 *  \arg     num  number of items to pop
 *  \arg     data pointer to place where to copy
 *  \return  actually readen number of items */
unsigned int cyclebuf_pop_head  
(cyclebuf_desc_t* cb, unsigned int num, void* data);

/** \brief   write data to tail of buffer
 *  \details wrapper of real push function
 *  \arg     cb   pointer to a cycle buffer descriptor
 *  \arg     num  number of items to push
 *  \arg     data pointer of data source
 *  \return  actually written number of items */
unsigned int cyclebuf_push_tail
(cyclebuf_desc_t* cb, unsigned int num, void* data);

/** \brief   get data from tail
 *  \details wrapper of real pop function
 *  \arg     cb   pointer to a cycle buffer descriptor
 *  \arg     num  number of items to pop
 *  \arg     data pointer to place where to copy
 *  \return  actually readen number of items */
unsigned int cyclebuf_pop_tail 
(cyclebuf_desc_t* cb, unsigned int num, void* data);

#endif//CYCLEBUF_H
