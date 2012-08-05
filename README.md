Pintos
=====

Pintos describes itself as a simple operating system
framework for the 80x86 architecture.  It originated
as a replacement for Nachos at Stanford for the cs140
class, and has achieved widespread usage in undergraduate
Operating Systems classes.  The canonical version of
the project is at http://www.stanford.edu/class/cs140/projects/pintos

This version of pintos documents a set of modifications
to both the code and assigments for use at the University
of Washington.  These modifications are designed to
make the projects more ammenable to a Quarter-length
class, and to build upon the prerequisites expected
of students in the CSE451 course.

Modifications
-----

* Network support

    This version of pintos is equipped with a PCI
    driver, drivers for the emulated network
    devices provided by both Bochs and Qemu, and a
    sockets library modeled after what is found in
    a traditional *nix OS.

    The Filesystems assignment has been modified to
    require less detailed implementation of file system
    System calls in exchange for development of a
    basic network driver in order to allow students
    to run and communicate with a web server in their
    OS.
