import os
import glob
from setuptools import Extension, setup


basedir = "src/module/"
sources = glob.glob(os.path.join(basedir, "*.c"))

setup(
    ext_modules=[
        Extension(
            name="_burgerhash",
            sources=sources,
        ),
    ]
)
