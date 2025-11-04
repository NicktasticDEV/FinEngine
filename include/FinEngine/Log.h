#pragma once
#include <iostream>

#define LOG_INFO(class, message) std::cout << "[" << class << "] " << message << std::endl;
#define LOG_ERROR(class, message) std::cerr << "[" << class << "][ERROR] " << message << std::endl;