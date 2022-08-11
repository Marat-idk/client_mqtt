cmake_minimum_required(VERSION 3.10)

project(client_mqtt VERSION 1.0.0)

# Переменная для одиковых названий экспортруемого таргетов
set(EXPORT_TARGETS_NAME ${PROJECT_NAME}Targets)

# Определяем стандарт С++
set(CMAKE_CXX_STANDARD 14)

# Определяем суфикс для версии Debug
set(CMAKE_DEBUG_POSTFIX _g)

# Определяем флаги для компиляции файлов C (если таковые имеются)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -D_DEBUG")

# Определяем флаги для компиляции файлов C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -D_DEBUG")
set(CMAKE_C_FLAGS "-m32")
# set(CMAKE_CXX_FLAGS "-m32")

# Определяем список исходных файлов
file(GLOB SOURCES src/*.cpp src/*.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Mosquitto IMPORTED_TARGET libmosquittopp REQUIRED)

# Определяем имя цели (проекта)
add_executable(${PROJECT_NAME} ${SOURCES})

# Подключаем библиотеки
# target_link_libraries(${PROJECT_NAME} PRIVATE mosquitto)
target_link_libraries(${PROJECT_NAME} PkgConfig::Mosquitto)

#Постфикс для Debug
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

# Задаем версию для имени файла. Используется для формирования soname.
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
