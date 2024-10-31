#!/bin/bash

export ARCUBE_RUNTIME=SHIFTER
export ARCUBE_CONTAINER=fermilab/fnal-wn-sl7:latest
shifter --image=$ARCUBE_CONTAINER --module=cvmfs,gpu /bin/bash
