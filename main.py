import src.burgerhash as burgerhash
import binascii


def f(x):
    result = burgerhash.hash(x)
    # print(result)
    hex_string = binascii.hexlify(result).decode("utf-8")
    # print("\n")
    print(f"Hash: {hex_string}")
    # print("\n")


if __name__ == "__main__":
    # f("")
    f("abc")
    f("def")
    # f("aaa")
    # f("aaaa")
    # f("bsdcascvujbwneovfibweoibbobuirwbvwoeirubvjdhfbvsodijfbvwoipeurybvlidsojfbvsldkjfb")

    # f("b")
    # f("c")
    # f("d")
