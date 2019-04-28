# socketdemo
实现了一个socketserver 默认监听端口6000
可使用 -p参数指定监听端口
例如：socketserver -p 20001  
# 使用方法
已将代码编译为二进制文件socketserver，亲测centos、ubuntu latest镜像直接可用。

在dockerfile 中指定socketserver 作为ENTRYPOINT即可。
