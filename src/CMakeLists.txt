# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 3.18)

project(AlgoBenchmark)

add_executable(AlgoBenchmark 
				main.cpp
				Test.h Test.cpp
				DataGenerator.h DataGenerator.cpp
				Algorithm.h Algorithm.cpp
				SalesMan.h
				RBTree.h RBNode.h
				MD5.H MD5.c
				2_3tree.h)