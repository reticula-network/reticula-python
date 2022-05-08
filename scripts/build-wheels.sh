#! /bin/bash

set -ex

mkdir -p dist


for version in python3.8 python3.9 python3.10 pypy3.8 pypy3.9; do
  singularity exec --cleanenv --bind .:/reticula-python --pwd /reticula-python \
    docker://quay.io/pypa/manylinux2014_x86_64 \
    ${version} -m pip wheel . -w dist --verbose
done

rm -f wheelhouse/*

for wheel in dist/*.whl; do
  singularity exec --cleanenv --bind .:/reticula-python --pwd /reticula-python \
    docker://quay.io/pypa/manylinux2014_x86_64 \
    auditwheel repair --strip $wheel
done
