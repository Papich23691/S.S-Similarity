#pragma once

#include <stdio.h>
#include <memory>
#include <Python.h>


#define XDECREF_RESOURCE(resource) \
    do                             \
    {                              \
        if (nullptr != resource)   \
        {                          \
            Py_XDECREF(resource);  \
        }                          \
    } while(0)

class NLPPyUtils final
{
    private:
        inline static std::shared_ptr<NLPPyUtils> _py_util;
        PyObject* _py_module;
        PyObject* _py_compare;
        PyObject* _py_tokenize;

    public:
        static std::shared_ptr<NLPPyUtils> get_py_util();
        virtual ~NLPPyUtils();
        NLPPyUtils(NLPPyUtils const&) = delete;
        void operator=(NLPPyUtils const&) = delete;

        PyObject* py_compare(const char* first_word, const char* second_word);
        PyObject* py_tokenize(const char* sentence);

    private:
        NLPPyUtils();
        void clear_resources();
        void py_init();
};