#!/bin/bash

pushd "$(dirname "$0")"
devtools/bin/vpc /open +game /mksln openmod
popd
