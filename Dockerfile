FROM centos:latest
WORKDIR /demo
ADD socketserver socketserver
ENTRYPOINT ["/demo/socketserver"]
