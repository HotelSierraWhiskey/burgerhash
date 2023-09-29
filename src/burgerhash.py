import importlib
import os
import sys


try:
    parent_directory = os.path.abspath(os.path.dirname(__file__))
    sys.path.append(parent_directory)
    _burgerhash = importlib.import_module("_burgerhash")
except ModuleNotFoundError as e:
    print(f"Burgerhash module not found.\n{e}")
    sys.exit()


def hash(plaintext: str) -> str:
    return _burgerhash.hash(plaintext)
