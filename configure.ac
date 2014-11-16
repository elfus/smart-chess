#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([smart-chess], [0.1], [adrianog.sw@gmail.com])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AM_INIT_AUTOMAKE()

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AX_CXX_COMPILE_STDCXX_11(,mandatory)

# Checks for libraries.
PKG_CHECK_MODULES([libgtkmm], [gtkmm-3.0 >= 3.10])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
