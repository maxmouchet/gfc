from Cython.Build import cythonize
from setuptools import Extension, setup

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name="pygfc",
    version="0.1.0",
    author="Maxime Mouchet",
    author_email="max@maxmouchet.com",
    description="(Partial) implementation of a Generalized-Feistel Cipher for generating random permutations.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/maxmouchet/gfc",
    ext_modules=cythonize(
        [
            Extension("pygfc", ["python/pygfc.pyx"]),
        ]
    ),
    classifiers=[
        "Programming Language :: Cython",
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
    ],
    python_requires=">=3.6",
)
