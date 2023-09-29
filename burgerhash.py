import importlib
import sys

try:
    _burgerhash = importlib.import_module("_burgerhash")
except ModuleNotFoundError as e:
    print(f"Burgerhash module not found.\n{e}")
    sys.exit()


def hash(plaintext: str) -> str:
    return _burgerhash.hash(plaintext)
