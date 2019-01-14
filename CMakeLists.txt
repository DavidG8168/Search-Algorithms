cmake_minimum_required(VERSION 3.12)
project(ProblemSolver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pthread")
add_executable(ProblemSolver main.cpp Server.h MySerialServer.cpp ClientHandler.h MyClientHandler.cpp Solver.h CacheManager.h FileCacheManager.cpp ClientThread.h Main.cpp BFS.cpp Searcher.h Searchable.h)