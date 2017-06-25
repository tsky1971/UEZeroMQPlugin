:: if libsodium is on disk, the Windows build of libzmq will automatically use it
git clone git://github.com/zeromq/libzmq.git
cd libzmq\builds\msvc
cd build
CALL buildbase.bat ..\vs2017\libzmq.sln 15
CALL buildbase.bat ..\vs2015\libzmq.sln 14
::buildall.bat
cd ..\..\..\..