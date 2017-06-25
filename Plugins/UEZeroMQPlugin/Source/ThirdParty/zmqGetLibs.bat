::git clone --depth 1 -b stable https://github.com/jedisct1/libsodium.git
::cd libsodium\builds\msvc\build
::rem buildall.bat
::CALL buildbase.bat ..\vs2017\libsodium.sln 15
::CALL buildbase.bat ..\vs2015\libsodium.sln 14
::cd ..\..\..\..

:: if libsodium is on disk, the Windows build of libzmq will automatically use it
git clone git://github.com/zeromq/libzmq.git
cd libzmq\builds\msvc
cd build
CALL buildbase.bat ..\vs2017\libzmq.sln 15 clean
::CALL buildbase.bat ..\vs2015\libzmq.sln 14
::buildall.bat
cd ..\..\..\..

git clone git://github.com/zeromq/czmq.git
cd czmq\builds\msvc
configure.bat
::cd build
call vs2015\build.bat
cd ..\..\..\..
