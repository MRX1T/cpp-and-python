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

#include "csys.hpp"



/* BACK METHODS */
int
length(const char *cstr) {
    int len = 0;
    while (cstr[len]) { 
        len++;
    }
    return len;
}


char *
str_join(const char *cstr1, const char *cstr2) {
    int len1 = length(cstr1), 
        len2 = length(cstr2),
        all_len = len1 + len2;
    char *result_str = (char*) malloc( sizeof(char) * all_len );
    if (result_str == NULL) {
        throw CSysException("str_join(): Memory allocation error");
    }
    for (int i = 0; i < len1; i++) {
        *(result_str + i) = *(cstr1 + i);
    }
    for (int j = 0; j < len2; j++) {
        int k = len1;
        k += j;
        *(result_str + k) = *(cstr2 + j);
    }
    return result_str;
}


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
        return result_permissions;  
    }
    throw CSysException("get_permissions_c(): Memory allocation error");
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
is_exists(pyself, pyargs) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    if (!is_exists_c(path))
        return PyLong_FromLong(0);
    return PyLong_FromLong(1);
}


pyobj
print_str(pyself, pyargs) {
    char *str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        return NULL;
    }
    cout << str;
    return Py_None;
}


pyobj
_end_line(pyself, pyargs) {
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
rm_all(pyself, pyargs) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    fs::remove_all(path);
    return Py_None;
}


pyobj
std_system(pyself, pyargs) {
    const char *to_exec;
    if (!PyArg_ParseTuple(args, "s", &to_exec)) {
        return NULL;
    }
    long status = std::system(to_exec);
    return PyLong_FromLong(status);
}


pyobj
make_dir_with_permissions(pyself, pyargs) {
    const char *path;
    int permission;
    if (!PyArg_ParseTuple(args, "si", &path, &permission)) {
        return NULL;
    }
    mkdir(path, permission);
    return Py_None;
}


pyobj
make_dir(pyself, pyargs) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    fs::create_directory(path);
    return Py_None;
}


pyobj
copy_in_fs_from_to(pyself, pyargs) {
    const char *from;
    const char *to;
    if (!PyArg_ParseTuple(args, "ss", &from, &to)) {
        return NULL;
    }
    fs::copy(from, to);
    return Py_None;
}


pyobj
file_size_in_fs(pyself, pyargs) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    unsigned long int size_of_file = fs::file_size(path);
    return Py_BuildValue("K", size_of_file);
}


pyobj
get_perms(pyself, pyargs) {
    const char *path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }
    if (!is_exists_c(path))
        throw CSysException( str_join( str_join("path '", path), "' does not exists" ) );
    const char *perms = get_permissions_c(fs::status(path).permissions());
    return Py_BuildValue("s", perms);
}


pyobj
__flush_outstream(pyself, pyargs) {
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    flush_outstream();
    return Py_None;
}


static PyMethodDef CSysMethods[] = {
    {"isexists",  (PyCFunction) is_exists, METH_VARARGS, "Return '1' if dir exist, else 0."},
    {"mkdirwp",  (PyCFunction) make_dir_with_permissions, METH_VARARGS, "Make directory with permissions.\nUsage: mkdir('path', int(linux access codes in the decimal system)). rwxrwxrwx = 7sys(777) = deciminal(511) !NEVER USE 551 (777) because this is a huge security risk!"},
    {"mkdir",  (PyCFunction) make_dir, METH_VARARGS, "Make directory."},
    {"system",  (PyCFunction) std_system, METH_VARARGS, "Execute system/shell command."},
    {"remove",  (PyCFunction) rm_all, METH_VARARGS, "Remove file or recursive remove dir."},
    {"copy",  (PyCFunction) copy_in_fs_from_to, METH_VARARGS, "Copy file/dir from ... to ... ."},
    {"filesize",  (PyCFunction) file_size_in_fs, METH_VARARGS, "Get file size in bytes as an integer."},
    {"printstr",  (PyCFunction) print_str, METH_VARARGS, "Print string."},
    {"endl",  (PyCFunction) _end_line, METH_VARARGS, "End of line (line separator ('\\n') )\nUsage: endl(int_count_of_endl)"},
    {"getperms",  (PyCFunction) get_perms, METH_VARARGS, "Get permissions of file/dir"},
    {"__flushostream",  (PyCFunction) __flush_outstream, METH_VARARGS, "NULL"},
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
    flush_outstream();
    return PyModule_Create(&csys);
}
