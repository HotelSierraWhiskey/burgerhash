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
    f("")
    f("a")
    f("aa")
    f("aaa")
    f("aaaa")
    f("aaaaa")



    # f("b")
    # f("c")
    # f("d")
