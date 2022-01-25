# BOF Template

This repository is meant to host the core files needed to create a Beacon Object File for use with Cobalt Strike.

A Beacon Object File (BOF) is a compiled C program, written to a convention that allows it to execute within a Beacon process and use internal Beacon APIs. BOFs are a way to rapidly extend the Beacon agent with new post-exploitation features.

## beacon.h

beacon.h contains definitions for several internal Beacon APIs. The function go is similar to main in any other C program. It's the function that's called by inline-execute and arguments are passed to it. BeaconOutput is an internal Beacon API to send output to the operator.

## BOF Documentation

- https://www.cobaltstrike.com/help-beacon-object-files

## Community developed BOFs

- https://cobalt-strike.github.io/community_kit/

