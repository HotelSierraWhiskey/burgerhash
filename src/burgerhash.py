import importlib
import os
import sys
import binascii


try:
    parent_directory = os.path.abspath(os.path.dirname(__file__))
    sys.path.append(parent_directory)
    _burgerhash = importlib.import_module("_burgerhash")
except ModuleNotFoundError as e:
    print(f"Burgerhash module not found.\n{e}")
    sys.exit()


class Burgerhash:
    def to_bytes(plaintext):
        return _burgerhash.hash(plaintext)

    def to_string(plaintext):
        ciphertext = _burgerhash.hash(plaintext)
        return binascii.hexlify(ciphertext).decode("utf-8")
