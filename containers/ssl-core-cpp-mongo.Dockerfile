FROM robocin/ssl-core-cpp-base:manual-protobuf-3.21.10

ARG MONGOCXX_VERSION='3.10.0'

COPY containers/scripts /tmp/scripts
WORKDIR /tmp/scripts

RUN \
  bash mongocxx.sh ${MONGOCXX_VERSION} '/usr/local' && \
  \
  rm -rf /tmp/scripts
