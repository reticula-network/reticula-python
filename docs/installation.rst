Installation
============

Python binding
--------------

Pre-compiled binding "Wheel"s are available for x64 Windows, x64 or ARM
MacOS 10.15 or newer and x64 Linux systems with glibc version 2.17 or above.
You can install the most recent stable release from the PyPi index using pip:

.. code-block:: console

   $ python -m pip install --upgrade pip
   $ python -m pip install --upgrade reticula

The first command makes sure your pip installation is up-to-date, the second
command installs the most recent version of Reticula from the repository.

The binding currently supports Python versions 3.8, 3.9, 3.10 and 3.11.

If you need to install the library on a system with no pre-compiled Wheels, you
can also build and install the binding from scrach. Chack out the
:ref:`Development <installation:Development>` section for more information.


The C++ library
---------------

You can include the C++ library in your code using CMake `FetchContent`_ module.
To do this, you need to specify how to fetch Reticula in your
:file:`CMakeLists.txt` file:

.. code-block:: cmake

   include(FetchContent)

   FetchContent_Declare(
   reticula
   GIT_REPOSITORY https://github.com/reticula-network/reticula.git
   GIT_TAG ${COMMIT_HASH})

   FetchContent_MakeAvailable(reticula)


You can use a git tag or branch name or the hash of a specific commit. We
recommand that you use the most recent release branch v#.# for a new project.

You can then link to the :code:`reticula` target:

.. code-block:: cmake

   add_executable(my_program main.cpp)
   target_link_libraries(my_program PRIVATE reticula)


.. _FetchContent: https://cmake.org/cmake/help/latest/module/FetchContent.html

Development
-----------

Building the Python binding from scratch
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In order to build the Python binding on a development machine, you need to make
sure Python development headers are installed and accessible, a modern version
of GCC ( >= 10.2) is installed and accessible and that you have access to
approximatly infinite RAM (> 40GB) and time.

.. code-block:: console

   $ git clone https://github.com/reticula-network/reticula-python.git
   $ cd reticula-python
   $ mkdir dist
   $ python -m pip install --upgrade pip
   $ python -m pip wheel . -w dist/
   $ python -m pip install dist/*.whl

If you actively developing the Python binding (perhaps to send a pull request?
Thank you very much!) you might want to avoid re-building everything from
scratch every single time. In this scenario, I recommand disabling build
isolation and cleaning steps of :command:`pip wheel` by using this command
instead:

.. code-block:: console

   $ python -m pip wheel . -w dist/ --verbose --no-build-isolation --no-clean

This needs you to manually have the required python packages installed. You can
find a list of these packages and acceptable version in the
:file:`pyproject.toml` file under the :code:`[build-system]` table.

You might also need to re-install the created wheel without bumping the version
every time. Consider adding the flag :option:`--force-reinstall` to the
:command:`pip install` command.

When building a wheel you intend to distribute, you might want to copy the
external shared libraries using the `auditwheel` tool to ensure compatibility
across different Linux distributions. Refer to the `auditwheel` documentation
for more details.

.. code-block:: console

   $  python -m auditwheel repair --plat manylinux_2_39_x86_64 dist/*.whl

You can use the most recent platform compatible with all the computers that
will be using the wheel instead of :code:`manylinux_2_39_x86_64`. A better
option is to use `cibuildwheel`_ for building wheels across different platforms.

.. _cibuildwheel: https://cibuildwheel.readthedocs.io/en/stable/

Building C++ library tests
^^^^^^^^^^^^^^^^^^^^^^^^^^

To build the tests for the C++ library, make sure you have CMake version 3.14 or
newer installed on your system. All you need to do then, is to clone the
library, make a build directory and build the tests:

.. code-block:: console

   $ git clone https://github.com/reticula-network/reticula.git
   $ cd reticula
   $ mkdir build
   $ cd build
   $ cmake ..
   $ cmake --build . --target reticula_tests -j 10

This creates an executable titled :code:`reticula_tests`, which you can execute
to run the runtime tests, including address, memory leak and undefined behaviour
sanitizer by default.

.. code-block:: console

   $ ./reticula_tests

After you made some modifications to the code, to re-compile the tests just
re-run the build command.

.. code-block:: console

   $ cmake --build . --target reticula_tests -j 10
   $ ./reticula_tests
