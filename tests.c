/** \file      tests.c
 *  \brief     shitty tests. normal tests not for today
 *  \copyright if you use this code without telling your buddies what you got it
 *             on github.com/Korrmet - you're an asshole. */

#include <stdio.h>
#include <stdint.h>
#include "cyclebuf.h"

CYCLEBUF_CREATE_STATIC(u32_b, uint32_t, 5);

void print_buf_state(void)
{ int bsize = sizeof(u32_b_mem) / sizeof(uint32_t);
  for (int i = 0; i < bsize; i++) { printf("%d", u32_b_mem[i]); }
  printf("\n");
  for (int i = 0; i < (u32_b.head - u32_b.mem_start) / u32_b.item_size; i++)
  { printf(" "); }
  printf("h\n");
  for (int i = 0; i < (u32_b.tail - u32_b.mem_start) / u32_b.item_size; i++)
  { printf(" "); }
  printf("t\n"); }

int main(int argc, char** argv)
{ printf("cyclubuf testing:\n");
  print_buf_state();
  
  for (int i = 0; i < 9; i++)
  { uint32_t num = i + 1;
    printf("trying to push head %2d: %d\n", 
           num, cyclebuf_push_head(&u32_b, 1, &num)); 
    print_buf_state(); }

  for (int i = 0; i < 9; i++)
  { uint32_t num = 0;
    printf("trying to pop head %2d: %d\n", 
           num, cyclebuf_pop_head(&u32_b, 1, &num));
  print_buf_state(); }

  for (int i = 0; i < sizeof(u32_b_mem)/sizeof(uint32_t); i++) 
  { u32_b_mem[i] = 0; }

  for (int i = 0; i < 9; i++)
  { uint32_t num = i + 1;
    printf("trying to push tail %2d: %d\n", 
           num, cyclebuf_push_tail(&u32_b, 1, &num));
  print_buf_state(); }

  for (int i = 0; i < 9; i++)
  { uint32_t num = 0;
    printf("trying to pop tail %2d: %d\n", 
           num, cyclebuf_pop_tail(&u32_b, 1, &num));
  print_buf_state(); }

  return 0; }
