#! /bin/bash

set -ex

mkdir -p dist


for version in 3.8 3.9 3.10; do
  singularity exec --cleanenv --bind .:/dag-python --pwd /dag-python \
    docker://quay.io/pypa/manylinux2014_x86_64 \
    python${version} -m pip wheel . -w dist --verbose
done

rm -f wheelhouse/*

for wheel in dist/*.whl; do
  singularity exec --cleanenv --bind .:/dag-python --pwd /dag-python \
    docker://quay.io/pypa/manylinux2014_x86_64 \
    auditwheel repair --strip $wheel
done
