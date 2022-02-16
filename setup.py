from Cython.Build import cythonize
from setuptools import Extension, setup

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name="pygfc",
    version="1.0.5",
    author="Maxime Mouchet",
    author_email="max@maxmouchet.com",
    description="Implementation of a Generalized-Feistel Cipher for generating random permutations.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/maxmouchet/gfc",
    ext_modules=cythonize(
        [
            Extension("pygfc", ["python/pygfc.pyx"]),
        ]
    ),
    classifiers=[
        "License :: OSI Approved :: MIT License",
        "Operating System :: MacOS :: MacOS X",
        "Operating System :: POSIX :: Linux",
        "Programming Language :: Cython",
        "Programming Language :: Python :: 3",
    ],
    python_requires=">=3.6",
)
