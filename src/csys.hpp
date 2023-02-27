/*
@Copyright 2023 MRX

license: XOSL - X Open Source License ('unknown')

You are granted free permission to work with the Software without restrictions, including not
limited to, the rights to use, copy, modify, merge, publish, distribute.
Changed files should be marked.
The right to apply another license is NOT granted.
All your developments using this software must also be open source and in the public domain.
You may not, however, sell copies of this software.
*/

#include <python3.11/Python.h>
#include <sys/stat.h>
#include <iostream>
#include <filesystem>
#include <string.h>


#define pyobj static PyObject*
#define pyself PyObject *self
#define pyargs PyObject *args


using std::cout;


namespace fs = std::filesystem;


class CSysException : public std::exception {
    private:
        std::string error;
    public:
        CSysException(std::string _error) {
            error = "\n    CSysException:\n         " + _error;
        }
        const char * what () const throw () {
            return error.c_str();
        }
};


/* BACK METHODS */
inline void flush_outstream() {
    flush(cout.put(cout.widen('\0'))); 
}

int
length(const char *cstr);

char *
str_join(const char *cstr1, const char *cstr2);

char *
get_permissions_c(fs::perms p);

static bool 
is_exists_c(const char *path);
/* BACK METHODS */


static PyObject *
is_exists(PyObject *self, PyObject* args);


static PyObject *
print_str(PyObject *self, PyObject* args);


static PyObject *
_end_line(PyObject *self, PyObject* args);


static PyObject *
rm_all(PyObject *self, PyObject* args);


static PyObject *
std_system(PyObject *self, PyObject* args);


static PyObject *
make_dir_with_permissions(PyObject *self, PyObject* args);


static PyObject *
make_dir(PyObject *self, PyObject* args);


static PyObject *
copy_in_fs_from_to(PyObject *self, PyObject* args);


static PyObject *
file_size_in_fs(PyObject *self, PyObject* args);


static PyObject *
get_perms(PyObject *self, PyObject* args);



