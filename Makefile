boost-version = 1.75.0
_version = 1_75_0

build: installdeps
	g++ -o build/dirpeek src/dirpeek.cpp \
		-lcpr \
		-lboost_program_options \
		-pthread

installdeps: clean install-boost install-cpr

install-boost:
	wget 'https://dl.bintray.com/boostorg/release/${boost-version}/source/boost_${_version}.tar.gz' -O build/boost.tar.gz
	tar -zxpf build/boost.tar.gz -C build
	(cd build/boost_${_version} && ./bootstrap.sh --with-libraries=program_options && ./b2 install)

install-cpr:
	rm -drf build/cpr
	git clone https://github.com/whoshuu/cpr build/cpr
	(mkdir build/cpr/build && cd build/cpr/build && cmake .. -DUSE_SYSTEM_CURL=OFF && make && make install)

clean:
	rm -drf build/*
	mkdir build
