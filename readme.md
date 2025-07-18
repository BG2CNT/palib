# PAlib
This fork is a experiment to try to add PA_Makefile on BlocksDS, it was rather successful but it sucks so it's unmaintained now.
## Introduction

PAlib (Programmer's Arsenal library) is a Nintendo DS library used to create
homebrew games. It is designed to be easily used by anyone. However, nowadays
there are better alternatives and PAlib should only be used to build old
projects that depend on it to be built.

This repository contains a port of PAlib to BlocksDS to keep this library alive.

## Installation

You can install PAlib directly with `wf-pacman`:

```sh
wf-pacman -Sy blocksds-palib
```

If you want to build it from source, clone this repository, enter that directory
and run:

```sh
make -j`nproc` install
```

## Directory structure

Templates:
- `template`: Contains a PAlib project template.

Resources:
- `examples`: Contains examples that show you how to use PAlib.
- `docs`: Contains the documentation in two languages (English and French).
- `tools`: Contains tools that will aid you in the development process of your projects.

Library source folders:
- `include`: Contains the library headers.
- `source`: Contains the PAlib source code.
- `sys`: Contains the source code of each PAlib ARM7 binary.

## Credits

This repository is based on PALib 100707. Please, check the
[PAlib archive repository](https://github.com/AntonioND/palib-archive/)
if you want to see the history of the library reconstructed from several
sources.
