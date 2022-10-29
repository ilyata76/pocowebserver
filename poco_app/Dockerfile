FROM ubuntu:22.04

WORKDIR /poco_app

COPY . .

ENV POCO_SERVER_PORT=80

EXPOSE ${POCO_SERVER_PORT}

RUN apt-get -y update && apt-get -y install gcc && apt-get -y install g++ && apt-get -y install cmake

RUN mkdir build && cmake -S . -B build && cmake --build build

CMD ["build/bin/pocowebserver"]