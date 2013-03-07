cmake_minimum_required (VERSION 2.6)
project (cse5542lab3)
add_executable (lab3 lab3.cpp GlGlut.cpp mesh.cpp MY_MATH.cpp MY_GLSL.cpp)
target_link_libraries (lab3 glut GL GLU GLEW)
