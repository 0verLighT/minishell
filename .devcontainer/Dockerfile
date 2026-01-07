FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# install env tools
RUN apt update && \
	apt install -y \
	git \
	curl \
	bat \
	vim \
	btop \
	fish

# C tools
RUN apt install -y \
	build-essential \
	clang \
	gdb \
	valgrind

RUN apt install -y \
	python3-pip && \
	python3 -m pip install -U norminette --break-system-packages

# minishell dep
RUN apt-get install -y libreadline-dev

WORKDIR /workspaces/minishell