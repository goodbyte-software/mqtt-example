FROM ubuntu:20.04

ARG USER_NAME=dev
ARG USER_PASSWORD=1234
ARG USER_UID=1000
ARG USER_GID=1000

# Create the user
RUN groupadd --gid $USER_GID $USER_NAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USER_NAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USER_NAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USER_NAME \
    && chmod 0440 /etc/sudoers.d/$USER_NAME

# Install common utils
RUN apt-get update && apt-get install -y \
    software-properties-common

# Install mosquitto
RUN apt-add-repository ppa:mosquitto-dev/mosquitto-ppa && \
    apt-get update && \
    apt-get install -y mosquitto

USER ${USER_NAME}
