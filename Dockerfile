FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    gdb \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /taskforge
COPY . .

RUN make

CMD ["./taskforge"]
