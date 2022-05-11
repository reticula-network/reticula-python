Installation
============

Python binding
--------------

Pre-compiled binding "Wheel"s are available for 64-bit Linux systems with glibc
version 2.17 or above. You can install the most recent stable release from the
PyPi index using pip:

.. code-block:: console

   $ pip install --upgrade pip
   $ pip install --upgrade reticula

The first command makes sure your pip installation is up-to-date, the second
command installs the most recent version of Reticula from the repository.

The binding currently supports Python versions 3.8, 3.9 and 3.10, with an
experimental support for PyPy versions 3.8 and 3.9.

If you need to install the library on a system with no pre-compiled Wheels, you
can also build and install the binding from scrach. Chack out the
:ref:`Development` section for more information.


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
approximatly infinite RAM ( > 30GB) and time.

.. code-block:: console

   $ git clone https://github.com/reticula-network/reticula-python.git
   $ cd reticula-python
   $ mkdir dist
   $ python -m pip install --upgrade pip
   $ python -m pip wheel . -w dist/
   $ python -m auditwheel dist/*.whl
   $ python -m pip install wheelhouse/*.whl

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
