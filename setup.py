from distutils.core import setup, Extension

module1 = Extension('hello',
                    sources = ['aesWrapper.c', 'aes.c'])

setup (name = 'myDemo',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
