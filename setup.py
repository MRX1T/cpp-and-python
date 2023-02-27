"""
@Copyright 2023 MRX

license: XOSL - X Open Source License ('unknown')

You are granted free permission to work with the Software without restrictions, including not
limited to, the rights to use, copy, modify, merge, publish, distribute.
Changed files should be marked.
The right to apply another license is NOT granted.
All your developments using this software must also be open source and in the public domain.
You may not, however, sell copies of this software.
"""

from setuptools import setup, Extension
from os import system


module_name = 'csys'


setup(
    name=module_name,
    version='0.0.4',
    description='Low-level Python API by wrote on C++',
    author='MRX',
    #author_email='',
    ext_modules=[ Extension( 'csys', ['src/csys.cpp'], include_dirs=['src'] ) ],
    #py_modules=['csys.py']
)

system(f'mv -v build/lib.linux-x86_64-cpython-311/{module_name}.cpython-311-x86_64-linux-gnu.so .')
system('rm -rf build')
