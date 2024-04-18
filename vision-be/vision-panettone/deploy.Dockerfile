ARG SERVICE_DIRECTORY=vision-be/vision-panettone
ARG BINARY_DIRECTORY=${SERVICE_DIRECTORY}/bin
ARG BINARY_NAME=microservice_main

FROM robocin/ssl-core-cpp-mongo:latest AS devcontainer

COPY .cmake /tmp/.cmake
COPY common /tmp/common
COPY protocols /tmp/protocols

RUN \
  pushd /tmp/common/cpp && rm -rf build && \
  cmake -B build -S . -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ && \
  cmake --build build && cmake --install build && popd && \
  \
  pushd /tmp/protocols && rm -rf build && \
  cmake -B build -S . -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ && \
  cmake --build build && cmake --install build && popd && \
  \
  rm -rf /tmp/.cmake /tmp/common /tmp/protocols

FROM devcontainer AS before-deploy

ARG SERVICE_DIRECTORY
ARG BINARY_DIRECTORY
ARG BINARY_NAME

COPY . /

RUN \
  pushd /${SERVICE_DIRECTORY} && \
  rm -rf build bin && \
  cmake -B build -S . -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ && \
  cmake --build build && \
  popd

RUN mkdir /deploy && \
  ldd /${BINARY_DIRECTORY}/${BINARY_NAME} | awk 'NF == 4 {print $3}; NF == 2 {print $1}' | grep '^/' | xargs -I {} cp --parents {} /deploy

FROM scratch AS deploy

ARG BINARY_DIRECTORY

COPY --from=before-deploy /bin/sh /bin/sh

COPY --from=before-deploy /deploy /
COPY --from=before-deploy /${BINARY_DIRECTORY} /${BINARY_DIRECTORY}

# WORKDIR /${BINARY_DIRECTORY}
# ENTRYPOINT [ "./microservice_main" ]
