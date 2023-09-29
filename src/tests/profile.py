from src.burgerhash import hash
import time


def test():
    plaintext = "THIS IS A TEST"

    s = time.time()
    result = hash(plaintext)
    e = time.time()

    print(f"plaintext length: {len(plaintext)}")
    print(f"Time elapsed: {round(e - s, 3)}s")
    print(result)
