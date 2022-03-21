# Post
# Payload
chrome F12 查看 post 存在 payload。payload 就是 application/x-www-form-urlencoded。

## how to post
https://stackoverflow.com/questions/35325370/how-do-i-post-a-x-www-form-urlencoded-request-using-fetch

# application/w-www-form-urlencoded 是怎么构建的

塞在body里，然后在body里将待传输的文件进行编码，全部是`kv`形式，我们有uri-encoding。

# multipart/form-data
这个就是分成很多东西来传过去，传过去的相当于多个独立的http请求。

（多路,二进制,是2.0才有的）