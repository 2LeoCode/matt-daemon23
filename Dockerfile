FROM debian:bookworm


# INSTALL DEPENDENCIES #

WORKDIR /tmp
RUN apt-get update && apt-get upgrade && apt-get install -y apt install -y wget gnupg lsb-release software-properties-common
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 18 all

WORKDIR /usr/bin
RUN ln -s clang++-18 clang++

########################


#    BUILD SOURCES     #

WORKDIR /usr/src/matt-daemon
COPY . .
RUN make && cp matt-daemon /usr/bin/matt-daemon

########################


CMD ["matt-daemon"]
