#                                                                                                       hexasm

###                 A Clean Binary File Editor written in C++ / CLI with many feature, which include:

*  disassembly for many architectures (thanks to capstone)
*  complete data-interpreter
*  interactable detailed graph view of the file.
  
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# To-Do's / In Progress

* I am writing a scripting language for hexasm right now which will allow synchronized data bindings to files and processes, this will make user-defined file format diagrams possible, unfortunately requires writing a VM in my case so this may take a month or 2. If you have experience with this sort of thing, feel free to contact me.

* Optimization for the Data Graph loading files and synchronizing with the updated contents within the Hex Editor control

* Optimization for the Clipboard Copy / Paste functions - Copying large amounts of Data will eat CPU usage, and sometimes cause the program to crash

* "wintest.h" is as suggested by the title, a testing environment for another feature being worked on which will allow for the creation of Control-Flow graphs from PE files. The subroutine detections "work" (kind of) but are not quite where i wish them to be and while they are similar to IDA's subroutine breakdown, they do not match, nor do they produce a satisfying result.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Credits

* Thanks to Pkcs11Admin for their old Be.HexEditor project which i extended the functionality of and changed [Be.HexEditor](https://github.com/Pkcs11Admin/Be.HexEditor)

* Thank you to the [Capstone Project](https://github.com/capstone-engine/capstone) for the amazing work

* Credits for many of the icons go directly to [gentleface](http://gentleface.com/), and the remainder were made by myself but heavily inspired by his theme and made to match / fit / extend it
