PAlib documentation folder
==========================

This directory contains Doxygen configuration files to generate PAlib
documentation in two languages, English and French.

Each language subfolder has two versions of the documentation:
  - PAlib.pdf      - The printable PDF version.
  - html subfolder - The browsable HTML version.

To generate the documentation you need the following installed:
  - Doxygen
  - MikTeX on Windows or pdfTeX on other OSes

Just run the appropiate batch file on Windows or follow these steps:
  - From the root of this repository, run "doxygen docs/Doxyfile_[Language]"
    where Language is the language you want to generate the documentation for.
  - Run make on the docs/[Language]/latex folder.
