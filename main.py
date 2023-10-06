import src.burgerhash as burgerhash
import binascii


if __name__ == "__main__":
    result = burgerhash.hash("")
    print("\n")
    print(result)
    print("\n")
    hex_string = binascii.hexlify(result).decode("utf-8")
    print(hex_string)
    print("\n")
