#pragma once
#include <Windows.h>
#include<iostream>

#ifndef LOG_ERROR(x, stop)
#define LOG_ERROR(x, stop) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED); std::cout << "ERROR: " << x << "\n"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); if(stop == true){std::cout << "\n\nPress anything to close ..."; std::cin.get();}
#endif
#ifndef LOG_WARNING(x)
#define LOG_WARNING(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN); std::cout << "WARNING: " << x << "\n"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#endif
#ifndef LOG_INFO(x)
#define LOG_INFO(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); std::cout << "INFO: " << x << "\n"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#endif
#ifndef GL_CALL_DEBUG(x)
#define GL_CALL_DEBUG(x) x; auto err = glGetError(); if(err!=0){LOG_ERROR(err, false);}
#endif
#ifndef GL_CALL_DEBUG_STOPPING(x)
#define GL_CALL_DEBUG_STOPPING(x) x; if(glGetError()!=0){LOG_ERROR(glGetError(), true);}
#endif
