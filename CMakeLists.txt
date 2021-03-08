cmake_minimum_required(VERSION 3.5)
project(pubtime_gui)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

find_package(Qt5Core)
find_package(Qt5Widgets)

set(QT_LIBRARIES Qt5::Widgets)
#------------------------------------------------

include_directories(time_pub
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

add_executable(time_pub
  src/qt_talker.cpp
  src/qt_talker_class.cpp
)

ament_target_dependencies(time_pub
  rclcpp
  std_msgs
)

target_link_libraries(time_pub
  ${QT_LIBRARIES}
)

install(TARGETS
  time_pub
  DESTINATION lib/${PROJECT_NAME}
)
#--------------------------------------------------
ament_package()
