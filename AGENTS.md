# Agent Guidelines for reticula-python

## Build & Test Commands
- **Build**: `python -m pip install .[test] -v` (builds C++ extension with nanobind)
- **Test all**: `python -m pytest .`
- **Test single**: `python -m pytest tests/test_filename.py::test_function_name`
- **Lint**: `flake8` (extends ignore E402 for import order)

## Project Structure
- C++ source in `src/` (uses nanobind, CMake, C++20)
- Python package in `src/reticula/`
- Tests in `tests/` using pytest + hypothesis
- Uses scikit-build-core for building

## Code Style
- **Python**: Follow PEP 8, snake_case naming, type hints preferred
- **C++**: LLVM style (see .clang-format), 2-space indent, left pointer alignment
- **Imports**: Relative imports with underscore prefix for internal modules
- **Generic attributes**: Use `_generic_attribute` pattern for templated functions
- **Error handling**: Raise appropriate exceptions with descriptive messages

## Key Patterns
- Generic templated functions via `generic_attribute` metaclass
- C++ types exposed as Python classes with `__name__` attributes
- Network types parameterized by vertex and time types
- Use `_reticula_ext` for C++ bindings, expose through main module