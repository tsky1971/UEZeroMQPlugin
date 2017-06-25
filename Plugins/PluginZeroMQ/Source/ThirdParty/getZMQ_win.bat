echo off
echo "https://github.com/zeromq/czmq#building-on-windows"
pause
echo "Visual Studio search"
rem call "C:\Programme\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"
rem call "C:\Program Files\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"
rem call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"

call "C:\Programme\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64_x86
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64_x86
echo "Visual Studio search END"

echo "libsodium"
if not exist libsodium (
	git clone git://github.com/jedisct1/libsodium.git
	pushd libsodium
	msbuild builds\msvc\vs2015\libsodium.sln /p:Configuration=DynRelease /p:Platform="x64" /m:4
	msbuild builds\msvc\vs2015\libsodium.sln /p:Configuration=StaticRelease /p:Platform="x64" /m:4
	msbuild builds\msvc\vs2015\libsodium.sln /p:Configuration=StaticRelease /p:Platform="win32" /m:4
	msbuild builds\msvc\vs2015\libsodium.sln /p:Configuration=LtcgRelease /p:Platform="x64" /m:4
	xcopy /Y bin\x64\Release\v140\static\* ..\..\..\Binaries\ThirdParty\libsodium\Win64\
	xcopy /Y bin\Win32\Release\v140\static\* ..\..\..\Binaries\ThirdParty\libsodium\Win32\
	rem xcopy /V/S/E/Y src\libsodium\include ..\..\cglabdepends_win\include\
	popd
) else (
	echo "libsodium exists already"
	pushd libsodium
	git pull
	msbuild builds\msvc\vs2015\libsodium.sln /p:Configuration=DynRelease /p:Platform="x64" /m:4
	msbuild builds\msvc\vs2015\libsodium.sln /p:Configuration=StaticRelease /p:Platform="x64" /m:4
	msbuild builds\msvc\vs2015\libsodium.sln /p:Configuration=StaticRelease /p:Platform="win32" /m:4
	msbuild builds\msvc\vs2015\libsodium.sln /p:Configuration=LtcgRelease /p:Platform="x64" /m:4
	xcopy /Y bin\x64\Release\v140\static\* ..\..\..\Binaries\ThirdParty\libsodium\Win64\
	xcopy /Y bin\Win32\Release\v140\static\* ..\..\..\Binaries\ThirdParty\libsodium\Win32\
	rem xcopy /V/S/E/Y src\libsodium\include ..\..\cglabdepends_win\include\
	popd
)

pause

echo "libzmq"
if not exist libzmq (
	echo "libzmq NOT exist checkout..."
	git clone https://github.com/zeromq/libzmq.git
	pushd libzmq
	mkdir build32 & pushd build32
	cmake -G "Visual Studio 14 2015" ..
	popd
	mkdir build64 & pushd build64
	cmake -G "Visual Studio 14 2015 Win64" ..
	popd
	cmake --build build32 --config Release
	xcopy /Y build32\bin\Release\*.dll ..\..\..\Binaries\ThirdParty\libzmq\Win32\
	xcopy /Y build32\lib\Release\* ..\..\..\Binaries\ThirdParty\libzmq\Win32\
	cmake --build build64 --config Release
	xcopy /Y build64\bin\Release\*.dll ..\..\..\Binaries\ThirdParty\libzmq\Win64\
	xcopy /Y build64\lib\Release\* ..\..\..\Binaries\ThirdParty\libzmq\Win64\
	
	popd
) else (
	echo "libzmq exists already"
	pushd libzmq
	git pull	
	mkdir build32 & pushd build32
	cmake -G "Visual Studio 14 2015" ..
	popd
	mkdir build64 & pushd build64
	cmake -G "Visual Studio 14 2015 Win64" ..
	popd
	cmake --build build32 --config Release
	xcopy /Y build32\bin\Release\*.dll ..\..\..\Binaries\ThirdParty\libzmq\Win32\
	xcopy /Y build32\lib\Release\* ..\..\..\Binaries\ThirdParty\libzmq\Win32\
	cmake --build build64 --config Release
	xcopy /Y build64\bin\Release\*.dll ..\..\..\Binaries\ThirdParty\libzmq\Win64\
	xcopy /Y build64\lib\Release\* ..\..\..\Binaries\ThirdParty\libzmq\Win64\
	popd
)

echo "cppzmq"
if not exist cppzmq (
	git clone https://github.com/zeromq/cppzmq.git
	pushd cppzmq
	rem xcopy *.hpp ..\..\..\Binaries\Win64
	popd
) else (
	echo "cppzmq exists already"
	pushd cppzmq
	git pull
	rem xcopy /y *.hpp ..\..\cglabdepends_win\include\
	popd
)

echo "czmq"
if not exist czmq (
	git clone git://github.com/zeromq/czmq.git
	pushd czmq
	echo "you have to build it manually"
	popd
) else (
	echo "czmq exists already"	
	pushd czmq
	git pull
	echo "you have to build it manually"
	popd
)

echo "ENDE"
