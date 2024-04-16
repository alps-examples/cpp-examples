FROM ubuntu:22.04

RUN apt-get update --fix-missing

RUN DEBIAN_FRONTEND=noninteractive TZ=Europa/Berlin apt-get -y install tzdata

RUN apt-get install --fix-missing -y \
	cmake \
	doxygen \
	g++ \
	git \
	libgtest-dev \
	libtbb-dev \
	ninja-build
