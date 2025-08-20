#!/bin/sh

(cd core && make) &&
(cd src/duke && make gui && make cli) &&
(cd tests && make)
