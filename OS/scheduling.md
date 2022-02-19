# Topics
进程切换的开销有多大？
进程切换的策略是什么？
用户态的scheduler是什么？
有没有scheduler的design pattern
tradeoffs ?

# Questions
- Why thread switching similar to process switching in Linux?

- What is fancy pants?


# Kernel Scheduler

## Cost of switching?
### How to estimate switching cost?
Thread A: read / write

Thread B: read / write

**Use perf**

## Hints


# User Scheduler
## Go
twice as fast as 