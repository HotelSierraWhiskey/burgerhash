from setuptools import Extension, setup

setup(
    ext_modules=[
        Extension(
            name="_burgerhash",
            sources=["src/hash_module.c", "src/hash.c"],
        ),
    ]
)
