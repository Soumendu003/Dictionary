from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
ext_modules=[ Extension("PyMap",
              sources=["PyMap.pyx", "Map.cpp"], language='c++')]
setup(
  name = "PyMap",
  cmdclass = {"build_ext": build_ext},
  ext_modules = ext_modules)
  