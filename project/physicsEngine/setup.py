from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "physicsEngine",
        ["calculation.cpp"],
        include_dirs=[pybind11.get_include()],
        language="c++",
        extra_compile_args=["-O3"],
    ),
]

setup(
    name="physicsEngine",
    version="0.1",
    ext_modules=ext_modules,
)