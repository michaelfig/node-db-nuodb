TESTS=$(shell find test -name "*.js")

all:
	make deps
	make build
	make install

deps:
	# install global packages
	sudo npm install -g nodeunit
	sudo npm install -g node-gyp

	# install local packages
	npm install nodeunit
	npm install underscore

	# sync submodule
	git submodule update --init

build:
	# configure and build npm module
	node-gyp configure
	node-gyp build

install:
	# install npm module
	node-gyp install

rebuild:
	# rebuild npm module
	node-gyp rebuild

clean:
	# remove module dependencies
	node-gyp clean
	rm -rf build

test:
	nodeunit $(TESTS)

.PHONY: all deps build install rebuild clean test
