#include <python3.11/Python.h>
#include <sys/stat.h>
#include <iostream>
#include <filesystem>
#include <string.h>


#define pyobj static PyObject*
#define pyself PyObject *self

//static PyObject *CSysError;


namespace fs = std::filesystem;


/* BACK METHODS */
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
make_dir_with_permissions(PyObject *self, PyObject* args);

static PyObject *
std_system(PyObject *self, PyObject* args);


static PyObject *
make_dir(PyObject *self, PyObject* args);


static PyObject *
copy_in_fs_from_to(PyObject *self, PyObject* args);


static PyObject *
file_size_in_fs(PyObject *self, PyObject* args);


static PyObject *
get_perms(PyObject *self, PyObject* args);


