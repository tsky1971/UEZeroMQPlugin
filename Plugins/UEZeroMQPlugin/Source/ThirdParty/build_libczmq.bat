git clone git://github.com/zeromq/czmq.git
::cd czmq\builds\msvc
::configure.bat --without-zmakecert --disable-drafts --without-zsp --without-czmq_selftest
cd czmq\builds\msvc\vs2015
call build.bat
cd ..\..\..\..
pause