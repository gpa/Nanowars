SET DEP_PATH=%USERPROFILE%\Desktop\Development\Dependencies
SET SCRIPT_PATH=%~dp0
SET MSBUILD=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\msbuild.exe
mkdir %DEP_PATH%
cd %DEP_PATH%
git clone https://github.com/google/liquidfun.git
git clone https://github.com/Tencent/rapidjson.git
git clone https://github.com/catchorg/Catch2.git
git clone https://github.com/TankOs/SFGUI.git
git clone https://github.com/SFML/SFML.git
git clone --recurse-submodules -j8 https://github.com/boostorg/boost.git
cd liquidfun/liquidfun/Box2D
mkdir build
cd build
cmake -DBOX2D_BUILD_EXAMPLES=OFF -DBOX2D_BUILD_UNITTESTS=OFF -DBOX2D_BUILD_SHARED=ON -DBOX2D_BUILD_STATIC=OFF -DCMAKE_BUILD_TYPE=$1 ..
cd Box2D
powershell -Command "(gc Box2D_shared.vcxproj) -replace '<TreatWarningAsError>true</TreatWarningAsError>', '<TreatWarningAsError>false</TreatWarningAsError>' | Out-File -encoding ASCII Box2D_shared.vcxproj"
cd ..
"%MSBUILD%" -target:Box2D_shared /p:Configuration=Release Box2D.sln
"%MSBUILD%" -target:Box2D_shared /p:Configuration=Debug Box2D.sln
cd %DEP_PATH%
cd SFML
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
"%MSBUILD%" -target:CMake\ALL_BUILD /p:Configuration=Release SFML.sln
cmake -DCMAKE_BUILD_TYPE=Debug ..
"%MSBUILD%" -target:CMake\ALL_BUILD /p:Configuration=Debug SFML.sln
cd %DEP_PATH%
cd SFGUI
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DSFML_DIR=%DEP_PATH%\SFML\build ..
"%MSBUILD%" -target:ALL_BUILD /p:Configuration=Release SFGUI.sln
cmake -DCMAKE_BUILD_TYPE=Debug -DSFML_DIR=%DEP_PATH%\SFML\build ..
"%MSBUILD%" -target:ALL_BUILD /p:Configuration=Debug SFGUI.sln
cd %SCRIPT_PATH%
cd ..
mkdir build
cd build
cmake -DSFML_INCLUDE_DIR=%DEP_PATH%/SFML/include -DSFML_ROOT=%DEP_PATH%/SFML/build/lib/Release -DBOX2D_INCLUDE_DIR=%DEP_PATH%/liquidfun/liquidfun/Box2D -DBOX2DDIR=%DEP_PATH%/liquidfun/liquidfun/Box2D/build/Box2D/Release -DCATCH2_INCLUDE_DIR=%DEP_PATH%/Catch2/single_include -DRAPIDJSON_INCLUDEDIR=%DEP_PATH%/rapidjson/include -DSFGUI_ROOT=%DEP_PATH%/SFGUI/build/lib/Release -DSFGUI_INCLUDE_DIR=%DEP_PATH%/SFGUI/include -DBUILD_TESTS=OFF ..
