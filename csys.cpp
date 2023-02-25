#include <python3.11/Python.h>
#include <sys/stat.h>
#include <iostream>
#include <filesystem>
#include <any>


//static PyObject *CSysError;


namespace fs = std::filesystem;


static PyObject *
is_exists(PyObject *self, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    int ex = fs::exists(path);
    return Py_BuildValue("i", ex);
}


static PyObject *
print_str(PyObject *self, PyObject* args) {
    char *str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        return NULL;
    }
    std::cout << str;
    return Py_BuildValue("");
}

static PyObject *
_end_line(PyObject *self, PyObject *args) {
    return Py_BuildValue("s", "\n");
}


static PyObject *
rm_all(PyObject *self, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    fs::remove_all(path);
    return Py_BuildValue("");
}


static PyObject *
make_dir_with_permissions(PyObject *self, PyObject* args) {
    const char *path;
    const char *permission;
    if (!PyArg_ParseTuple(args, "ss", &path, &permission)) {
        return NULL;
    }
    mkdir(path, atoi(permission));
    return Py_BuildValue("");
}


static PyObject *
make_dir(PyObject *self, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    fs::create_directory(path);
    return Py_BuildValue("");
}


static PyObject *
copy_in_fs_from_to(PyObject *self, PyObject* args) {
    const char *from;
    const char *to;
    if (!PyArg_ParseTuple(args, "ss", &from, &to)) {
        return NULL;
    }
    fs::copy(from, to);
    return Py_BuildValue("");
}


static PyObject *
file_size_in_fs(PyObject *self, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    return Py_BuildValue("y", fs::file_size(path));
}



static PyMethodDef CSysMethods[] = {
    {"isexists",  (PyCFunction) is_exists, METH_VARARGS, "Return 'True' if dir exist, else False."},
    {"mkdirwp",  (PyCFunction) make_dir_with_permissions, METH_VARARGS, "Make directory with permissions.\nUsage: mkdir('path', 'linux access codes in the decimal system')"},
    {"mkdir",  (PyCFunction) make_dir, METH_VARARGS, "Make directory."},
    {"remove",  (PyCFunction) rm_all, METH_VARARGS, "Remove file or recursive remove dir."},
    {"copy",  (PyCFunction) copy_in_fs_from_to, METH_VARARGS, "Copy file/dir/.. from ... to ... ."},
    {"filesize",  (PyCFunction) file_size_in_fs, METH_VARARGS, "Get file size in bytes."},
    {"printstr",  (PyCFunction) print_str, METH_VARARGS, "Print string."},
    {"endl",  (PyCFunction) _end_line, METH_VARARGS, "Print end of line (line separator ('\\n') )\nUsage: endl(int_count_of_endl)"},
    // {"method_name_in_python",  c_method, METH_VARARGS, "Description"},
    {NULL}
};


static struct PyModuleDef csys =
{
    PyModuleDef_HEAD_INIT,
    "csys", /* name of module */
    "NULL", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    CSysMethods
};

PyMODINIT_FUNC PyInit_csys(void)
{
    return PyModule_Create(&csys);
}
