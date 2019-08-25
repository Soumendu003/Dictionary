from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
ext_modules=[ Extension("PyWire",
              sources=["PyWire.pyx", "Wire.cpp"], language='c++')]
setup(
  name = "PyWire",
  cmdclass = {"build_ext": build_ext},
  ext_modules = ext_modules)
  