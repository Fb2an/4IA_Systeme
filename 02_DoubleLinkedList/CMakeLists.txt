cmake_minimum_required(VERSION 3.20)
project(02_DoubleLinkedList C)
set(CMAKE_C_STANDARD 11)
add_executable(02_DoubleLinkedList
        main.c
        dll.c
        dll.h
        ../01_LinkedList/ll.c
        ../01_LinkedList/ll.h)
