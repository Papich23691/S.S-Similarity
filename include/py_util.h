#pragma once

#include <stdio.h>
#include <memory>
#include <Python.h>

class PyUtils final
{
    private:
        inline static std::shared_ptr<PyUtils> _py_util;
        PyObject* _py_module;

    public:
        static std::shared_ptr<PyUtils> get_py_util();
        virtual ~PyUtils();
        PyUtils(PyUtils const&) = delete;
        void operator=(PyUtils const&) = delete;

        PyObject *nlp_py_function(char * fname,const char * argument,const char * argument2,int argc);

    private:
        PyUtils();
        void py_init();
};