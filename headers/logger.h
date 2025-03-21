#pragma once
#include<string>
#include<iostream>
#include<stdio.h>
#define LOG_INFO  0
#define LOG_WARN  1
#define LOG_ERROR  3
void Hlog(unsigned int LOG, const char* v);
void Hlog(unsigned int LOG, std::string v);

 