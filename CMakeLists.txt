cmake_minimum_required(VERSION 3.1)
project(solisp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(solisp ${SOURCE_FILES} utils/CharBuffer.h utils/BufferReader.h utils/BufferUnderflowException.h utils/CharBuffer.h utils/CharBuffer.cpp utils/CharBuffer.h utils/utils.h utils/utils.cpp LispObject.h LispObject.cpp Atom.cpp Atom.h SExpression.cpp SExpression.h Environment.cpp Environment.h Parser.cpp Parser.h Interpreter.cpp Interpreter.h)
