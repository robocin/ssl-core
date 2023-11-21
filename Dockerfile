FROM python:3 AS server2
RUN mkdir /test
WORKDIR /test

COPY . /test

WORKDIR /test/src/service_python
RUN pip install -r requirements.txt
RUN python3 main.py

FROM gcc:latest AS client2
WORKDIR /test

COPY . /test
WORKDIR /test/src/service_c
RUN gcc -o main main.c
CMD ["./main"]