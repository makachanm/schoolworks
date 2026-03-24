# CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(banking)
 
add_executable(banking 
    Account.cpp 
    AccountArray.cpp 
    AccountHandler.cpp
    BankingSystemMain.cpp
)