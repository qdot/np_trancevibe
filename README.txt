==================================
nplabs.trancevibe Max/MSP External
==================================

by Kyle Machulis <kyle@nonpolynomial.com>
Nonpolynomial Labs - http://www.nonpolynomial.com

===========
Description
===========

nplabs.trancevibe is a Max/MSP external to control the Rez Trancevibrator. It is based on libtrancevibe:

http://sourceforge.net/projects/libtrancevibe

nplabs.trancevibe works with both the original ASCII Rez Trancevibrator, as well as the Drmn Trance Vibrator (http://tim.cexx.org/projects/vibe/)

===========================
Trance Vibrator Information
===========================

More information about the TranceVibrator can be found at 

http://wiki.opendildonics.org/Rez_TranceVibrator

============
Installation
============

- Put the .mxo(Mac)/.mxe(Windows) file in a directory that Max will search for externals (Settable in Max at Options -> File Preferences -> Other Folders)
- Put the .help file in the max-help directory of your Max/MSP installation

=========================
Platform Specifics Issues
=========================

-------
Windows
-------

- Windows will require the libusb-win32 filter driver to use the trancevibe external. This filter driver is available through the libtrancevibe sourceforge site.
- If the write timeout on windows is set to 0, writes will be quite flakey and will fail often. Always set it to at least 5. (The patch defaults it to 10)

