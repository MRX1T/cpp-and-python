from setuptools import setup, Extension
from os import system

module_name = 'csys'

setup(
    name=module_name,
    version='0.0.1',
    description='Python API for calling system functions',
    author='MRX',
    #author_email='',
    ext_modules=[Extension('csys', ['csys.cpp'])],
    #py_modules=['csys.py']
)

system(f'mv -v build/lib.linux-x86_64-cpython-311/{module_name}.cpython-311-x86_64-linux-gnu.so .')
system('rm -rf build')
