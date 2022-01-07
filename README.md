# Python bindings for DAG

## Getting started

Clone the library:
```bash
$ git clone https://github.com/arashbm/dag-python.git
```

Compile the shared objects:
```bash
$ cd dag-python
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

In the same build directory, load the extension and enjoy:
```
$ python
>>> import dag_ext
>>> dag_ext.__version__
'dev'
```
