#! /bin/bash

set -ex

mkdir -p dist
rm -f wheelhouse/*

for version in python3.8 python3.9 python3.10 python3.11 pypy3.9; do
  rm -f dist/*
  rm -rf _skbuild
  singularity exec --cleanenv --bind .:/reticula-python --pwd /reticula-python \
    docker://quay.io/pypa/manylinux2014_x86_64 \
    ${version} -m pip wheel . -w dist --verbose
  singularity exec --cleanenv --bind .:/reticula-python --pwd /reticula-python \
    docker://quay.io/pypa/manylinux2014_x86_64 \
    auditwheel repair --strip dist/*.whl
done
