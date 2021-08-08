# StaticHook

StaticHook is a static library written in C++ that provides functionality in form of functions and classes used for efficently creating hooks for DLL injections.

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Features](#features)
* [Code Examples](#code-examples)

## General info

This statically-linked library provides functionality for creating DLL injections in a simple manner.

## Technologies
* C++ 17

## Setup


## Features
* Write and read bytes internally or externally
* Basic data types including `BYTE`, `WORD`, `DWORD`, `QWORD`
* Data structures such as `Vector2`, `Vector3`, `Vector4`
#### To Do:
* Allow for memory allocation in the virtual address space of the hijacked process, in order to eliminate 14-byte jumps in 64-bit applications
* Add matrix data structure 
* Add a DLL Injector
## Code Examples
