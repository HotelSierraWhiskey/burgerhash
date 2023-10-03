PACKAGE_NAME = _burgerhash

build:
	python setup.py build && mv build/lib.linux-x86_64-cpython-311/$(PACKAGE_NAME).cpython-311-x86_64-linux-gnu.so src/$(PACKAGE_NAME).so && make clean

clean:
	rm -r build && rm -r src/*.egg-info

test:
	pytest src/tests/