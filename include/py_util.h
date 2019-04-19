#ifndef UTIL    
#define UTIL

#include <stdio.h>
#include <Python.h>

void Py_Init();
PyObject *py_function(char * fname,const char * argument,const char * argument2,int argc);

#endif