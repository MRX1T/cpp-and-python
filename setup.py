from setuptools import setup, Extension
from os import system

module_name = 'csys'

setup(
    name=module_name,
    version='0.0.2',
    description='Low-level Python API by wrote on C++',
    author='MRX',
    #author_email='',
    ext_modules=[ Extension( 'csys', ['csys.cpp'], include_dirs=['src'] ) ],
    #py_modules=['csys.py']
)

system(f'mv -v build/lib.linux-x86_64-cpython-311/{module_name}.cpython-311-x86_64-linux-gnu.so .')
system('rm -rf build')
