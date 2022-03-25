#include "co.h"
#include <stdlib.h>

int co_tot;
const int reg_type_sum = 24;
enum status
{
  waiting,
  running
};
enum reg_type
{
  rax,
  rbx,
  rcx,
  rdx,
  rsi,
  rdi,
  rbp,
  rsp,
  r8,
  r9,
  r10,
  r11,
  r12,
  r13,
  r14,
  r15,
  rip,
  eflags,
  cs,
  ss,
  ds,
  es,
  fs,
  gs
};

struct co
{
  char *name;
  int co_id;

  enum status stat;
  u_int64_t waitlist[16];
  u_int64_t reg[reg_type_sum];
};

void co_init(const char *name)
{
  struct co *co = (struct co *)name;
  co->co_id = ++co_tot;
  co->stat = waiting;
  memset(co->waitlist, 0, sizeof(co->waitlist));
  for (int i = 0; i < reg_type_sum; ++i)
    co->reg[i] = 0;
}

struct co *co_start(const char *name, void (*func)(void *), void *arg)
{
  struct co *ret = (struct co *)malloc(sizeof(struct co));
  co_init(ret);
  asm volatile("");
  
  func(arg);
  return ret;
}

void co_wait(struct co *co)
{

}

void co_yield()
{

}
