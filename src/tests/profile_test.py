from src.burgerhash import hash
import time


def test():
    plaintext = "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG" * 10000000

    s = time.time()
    hash(plaintext)
    e = time.time()

    assert (e - s) < 5
