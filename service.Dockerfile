FROM robocin/clang-cpp23-ubuntu-latest:manual-experimental-v5

RUN mkdir /app

WORKDIR /app

COPY . .

RUN cd common/cpp && rm -rf build && mkdir build && cd build && cmake .. && make -j$(nproc) && make install -j$(nproc)

WORKDIR /app/vision-be/mock_impl

RUN rm -rf build && mkdir build && cd build && cmake .. && make -j6