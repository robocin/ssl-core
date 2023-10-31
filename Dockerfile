FROM gcc:4.9
WORKDIR /src
RUN gcc -o service_c/main .\service_c/main.c

FROM python:3
RUN python .\service_python/main.py
