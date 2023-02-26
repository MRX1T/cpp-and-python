#include "csys.hpp"



/* BACK METHODS */
char *
get_permissions_c(fs::perms p)
{
    using fs::perms;
    char *result_permissions = (char*) malloc( sizeof(char) * 9 );
    if (result_permissions != NULL) {
        result_permissions[0] = (perms::none == (perms::owner_read & p) ? '-' : 'r');
        result_permissions[1] = (perms::none == (perms::owner_write & p) ? '-' : 'w');
        result_permissions[2] = (perms::none == (perms::owner_exec & p) ? '-' : 'x');
        result_permissions[3] = (perms::none == (perms::group_read & p) ? '-' : 'r');
        result_permissions[4] = (perms::none == (perms::group_write & p) ? '-' : 'w');
        result_permissions[5] = (perms::none == (perms::group_exec & p) ? '-' : 'x');
        result_permissions[6] = (perms::none == (perms::others_read & p) ? '-' : 'r');
        result_permissions[7] = (perms::none == (perms::others_write & p) ? '-' : 'w');
        result_permissions[8] = (perms::none == (perms::others_exec & p) ? '-' : 'x');
        // std::cout << "{" << result_permissions << "}";
        return result_permissions;  
    }
    return NULL;
}


static bool
is_exists_c(const char *path) {
    int ex = fs::exists(path);
    if (ex == 1)
        return true;
    return false;
}
/* BACK METHODS */


pyobj
is_exists(pyself, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    if (!is_exists_c(path))
        return Py_False;
    return Py_True;
}


pyobj
print_str(pyself, PyObject* args) {
    char *str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        return NULL;
    }
    std::cout << str;
    return Py_None;
}


pyobj
_end_line(pyself, PyObject* args) {
    int count;
    if (!PyArg_ParseTuple(args, "i", &count)) {
        return NULL;
    }
    char endls[count];
    for (int i = 0; i < count; i++) {
        endls[i] = '\n';
    }
    return Py_BuildValue("s", endls);
}


pyobj
rm_all(pyself, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    fs::remove_all(path);
    return Py_None;
}


pyobj
make_dir_with_permissions(pyself, PyObject* args) {
    const char *path;
    const char *permission;
    if (!PyArg_ParseTuple(args, "ss", &path, &permission)) {
        return NULL;
    }
    mkdir(path, atoi(permission));
    return Py_None;
}


pyobj
std_system(pyself, PyObject* args) {
    const char *to_exec;
    if (!PyArg_ParseTuple(args, "s", &to_exec)) {
        return NULL;
    }
    long status = std::system(to_exec);
    return PyLong_FromLong(status);
}


pyobj
make_dir(pyself, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    fs::create_directory(path);
    return Py_None;
}


pyobj
copy_in_fs_from_to(pyself, PyObject* args) {
    const char *from;
    const char *to;
    if (!PyArg_ParseTuple(args, "ss", &from, &to)) {
        return NULL;
    }
    fs::copy(from, to);
    return Py_None;
}


pyobj
file_size_in_fs(pyself, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    unsigned long int size_of_file = fs::file_size(path);
    return Py_BuildValue("K", size_of_file);
}


pyobj
get_perms(pyself, PyObject* args) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    if (!is_exists_c(path)) {
        PyErr_SetString( PyExc_FileExistsError, "csys: path '' does not exists.");
        return NULL;
    }
    char *perms = get_permissions_c(fs::status(path).permissions());
    if (perms == NULL) {
        PyErr_SetString(PyExc_MemoryError, "csys: memory allocation error");
        return NULL;
    }
    return Py_BuildValue("s", perms);
}



static PyMethodDef CSysMethods[] = {
    {"isexists",  (PyCFunction) is_exists, METH_VARARGS, "Return 'True' if dir exist, else False."},
    {"mkdirwp",  (PyCFunction) make_dir_with_permissions, METH_VARARGS, "Make directory with permissions.\nUsage: mkdir('path', 'linux access codes in the decimal system')"},
    {"mkdir",  (PyCFunction) make_dir, METH_VARARGS, "Make directory."},
    {"system",  (PyCFunction) std_system, METH_VARARGS, "Execute system/shell command."},
    {"remove",  (PyCFunction) rm_all, METH_VARARGS, "Remove file or recursive remove dir."},
    {"copy",  (PyCFunction) copy_in_fs_from_to, METH_VARARGS, "Copy file/dir from ... to ... ."},
    {"filesize",  (PyCFunction) file_size_in_fs, METH_VARARGS, "Get file size in bytes as an integer."},
    {"printstr",  (PyCFunction) print_str, METH_VARARGS, "Print string."},
    {"endl",  (PyCFunction) _end_line, METH_VARARGS, "Print end of line (line separator ('\\n') )\nUsage: endl(int_count_of_endl)"},
    {"getperms",  (PyCFunction) get_perms, METH_VARARGS, "Get permissions of file/dir"},
    // {"method_name_in_python",  c_method, METH_VARARGS, "Description"},
    {NULL}
};


static struct PyModuleDef csys =
{
    PyModuleDef_HEAD_INIT,
    "csys", /* name of module */
    "Low-level Python API by wrote on C++", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    CSysMethods
};

PyMODINIT_FUNC PyInit_csys(void)
{
    return PyModule_Create(&csys);
}