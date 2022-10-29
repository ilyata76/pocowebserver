FROM ubuntu:22.04

WORKDIR /poco_app

COPY . .

ARG ARG_USE_FIND_POSTGRES_CMAKE
ENV USE_FIND_POSTGRES_CMAKE=${ARG_USE_FIND_POSTGRES_CMAKE}

RUN apt-get -y update && apt-get -y install gcc g++ cmake
RUN apt-get -y install libpq-dev postgresql-server-dev-all
RUN mkdir build && cmake -E env USE_FIND_POSTGRES_CMAKE=${USE_FIND_POSTGRES_CMAKE} cmake -S . -B build && cmake --build build

CMD ["build/bin/pocowebserver"]