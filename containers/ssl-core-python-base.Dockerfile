FROM mcr.microsoft.com/devcontainers/python:3

SHELL ["/bin/bash", "-c"]

ARG PROTOC_VERSION='25.3'

COPY containers/scripts /tmp/scripts
WORKDIR /tmp/scripts

RUN apt update && apt upgrade -y && \
  bash protoc.sh ${PROTOC_VERSION} '/usr/local' && \
  \
  rm -rf /tmp/scripts
