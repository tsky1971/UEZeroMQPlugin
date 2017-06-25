git clone --depth 1 -b stable https://github.com/jedisct1/libsodium.git
pushd libsodium\builds\msvc\build
rem buildall.bat
CALL buildbase.bat ..\vs2017\libsodium.sln 15
CALL buildbase.bat ..\vs2015\libsodium.sln 14
::cd ..\..\..\..
popd