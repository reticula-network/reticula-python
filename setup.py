import sys

try:
    from skbuild import setup
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml"
        " yourself",
        file=sys.stderr,
    )
    raise

from skbuild.cmaker import get_cmake_version
from setuptools import find_packages

setup(
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    cmake_install_dir="src/reticula",
    include_package_data=True,
)
