# Burgerhash 🍔

## About
Burgerhash is a Merkle–Damgård-based hashing algorithm. This python implementation makes use of the CPython API and outputs 256 bits of ciphertext.

```python
>>> from burgerhash import Burgerhash
>>> 
>>> Burgerhash.to_string("bar")
'5f16c4c801387af4c198fb4f82e1feb1b8ecd96e052623d90bf9f202adfc72fb'
>>> 
>>> Burgerhash.to_string("baz")
'a9a880fa2ffbee000155ec133a997ca5480212e811b311261101f7ae3beae90c'
```

##  🚨 Disclaimer
This software is provided solely for educational and learning purposes. It is not suitable for production use.

## Features
- Variable length input
- Relatively small message schedule size
- Single sigma function, no initial "H-value" words
- Novel compression function
- Minimal, fast CPython implementation