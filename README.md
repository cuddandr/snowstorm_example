## Snowstorm Example(s)

This repository contains example code and environment initialization scripts for performing Snowstorm analysis for the 2x2.

The current example `snowstorm_skeleton.cxx` is a ROOT macro that expects the pathname of a structured CAF to process.
It requires access to `duneanaobj` and StandardRecord and can be loaded via UPS. The `setup_cafs.sh` script will load the neccessary
software for reading CAFs, but requires the FNAL SL7 environment. The `nersc_load_fnal_sl7.sh` script will load a container
to provide the correct SL7 environment on NERSC.
