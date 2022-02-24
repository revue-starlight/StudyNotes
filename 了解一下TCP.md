本文全部来源于 `RFC文档`
TCP 假设下层是完全可靠的。

# section 1
协议规范，与高层和其他 TCP 的交互
# section 2
设计哲学
# section 3 
忘记了

# 协议规范
host-to-host communications?
端到端协议，可靠，多种网络

接口：
异步通知上层。
TCP和底层协议之间的接口本质上是未指明的，但假设存在一种机制两个级别可以异步地相互传递信息。

(这不可能吧？)

## basic data transfer
TCP decide when to block and forward data at their own convenience.

## Reliability
数据在互联网中可能被损坏，丢失，复制，乱序到达，什么的。利用了ACK。

# 设计哲学

# Why need socket?
`Hosts` are computers attached to a network, and from the communication network’s point of view, are the sources and destinations of packets.

`Processes` are viewed as the active elements in host computers.Even terminals and files or other I/O devices are viewed as communicating with each other through the use of processes. Thus, all communication is viewed as inter-process communication.

Since a process may need to distinguish among several communication streams between itself and another process (or processes), we imagine that **each process may have a number of ports through which it communicates with the ports of other processes.**

# how do process transfer datas?
1. calling on the TCP
2. passing buffers of data as arguments
3. 


