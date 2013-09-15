#!/bin/bash/

find src -regex ".*\.cpp" | sed s/^/CPP_FILES+=/ > inc.mk

find src -type -d -exec mkdir intermediate/\{\} \;

make $@
