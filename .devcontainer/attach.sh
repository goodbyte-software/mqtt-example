#!/bin/bash

# Get name of repository
REPO_NAME=$(basename $(realpath $(dirname "$0")/..))

docker exec -it $(docker ps -alqf "name=$REPO_NAME") bash
