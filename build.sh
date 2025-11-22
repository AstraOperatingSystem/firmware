mkdir build
mkdir build/conan
conan install . --profile conan_profiles/stm32f411re.txt -of build/conan --build=missing
cd build
cmake --toolchain conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
