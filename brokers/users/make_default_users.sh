#!/bin/bash

SCRIPT_DIR=$(dirname "$(realpath "$0")")
PASSWD_FILE="${SCRIPT_DIR}/passwd"

# Create passwd file with root access to read and write
touch  "${PASSWD_FILE}"
chmod 0700 "${PASSWD_FILE}"
mosquitto_passwd -b "${PASSWD_FILE}" John Doe
mosquitto_passwd -b "${PASSWD_FILE}" Alex Pass123
