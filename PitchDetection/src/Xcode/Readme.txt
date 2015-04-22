how to setup environment
install fftw3
./configure --enable-float
make
make install

then headers are in /usr/local/include and libs are
in /usr/local/lib

download boost
./bootstrap.sh
./b2 install -j2 --prefix=/Users/MYUSERNAME/src/boost

sudo gem update --system
sudo gem install cocoapods

go to project directory
pod install
