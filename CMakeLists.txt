cmake_minimum_required(VERSION 3.23)
project(mephi_labs)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall)

add_executable(lab1 "Term 3. Object-Oriented Programming/lab1/main.cpp"
        "Term 3. Object-Oriented Programming/lab1/sparse.cpp"
        "Term 3. Object-Oriented Programming/lab1/dialog.cpp")

add_executable(lab2 "Term 3. Object-Oriented Programming/lab2/apptest.cpp"
        "Term 3. Object-Oriented Programming/lab2/ButaLib/buta.cpp")

add_executable(lab3A "Term 3. Object-Oriented Programming/lab3/polynomLib/polynom3A.cpp"
        "Term 3. Object-Oriented Programming/lab3/app3A.cpp")
add_executable(lab3B "Term 3. Object-Oriented Programming/lab3/polynomLib/Polynom3B.cpp"
        "Term 3. Object-Oriented Programming/lab3/app3B.cpp")
add_executable(lab3V "Term 3. Object-Oriented Programming/lab3/polynomLib/Polynom3V.cpp"
        "Term 3. Object-Oriented Programming/lab3/app3V.cpp")

add_executable(lab4 "Term 3. Object-Oriented Programming/lab4/AgentLib/agency.cpp"
        "Term 3. Object-Oriented Programming/lab4/AgentLib/table.cpp"
        "Term 3. Object-Oriented Programming/lab4/app.cpp")


add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(SOURCE_FILES "Term 3. Object-Oriented Programming/lab4/test.cpp"
        "Term 3. Object-Oriented Programming/lab4/AgentLib/agency.cpp"
        "Term 3. Object-Oriented Programming/lab4/AgentLib/table.cpp")
add_executable(GoogleTest ${SOURCE_FILES})
target_link_libraries(GoogleTest gtest)