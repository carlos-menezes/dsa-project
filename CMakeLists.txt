cmake_minimum_required(VERSION 3.17)
project(super_eda)

set(CMAKE_CXX_STANDARD 20)

add_executable(super_eda main.cpp supermarket/supermarket.cpp supermarket/supermarket.h supermarket/product.cpp supermarket/product.h supermarket/sector.cpp supermarket/sector.h supermarket/sale.cpp supermarket/sale.h utils/navigation.cpp utils/navigation.h utils/runtime.cpp utils/runtime.h utils/metadata.cpp utils/metadata.h utils/files.cpp utils/files.h utils/random.cpp utils/random.h  utils/array.cpp utils/array.h utils/io.cpp utils/io.h)