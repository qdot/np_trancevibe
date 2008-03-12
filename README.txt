==================================
np_trancevibe Max/MSP External
==================================

by Kyle Machulis <kyle@nonpolynomial.com>
Nonpolynomial Labs - http://www.nonpolynomial.com

===========
Description
===========

np_trancevibe is an external for either Max/MSP or Puredata to control the Rez Trancevibrator. It is based on libtrancevibe:

http://sourceforge.net/projects/libtrancevibe

nplabs.trancevibe works with both the original ASCII Rez Trancevibrator, as well as the Drmn Trance Vibrator (http://tim.cexx.org/projects/vibe/)

Portability of source between Max and Pd is available thanks to flext

Max: http://www.cycling74.com
Pd: http://www.puredata.info
Flext: http://www.parasitaere-kapazitaeten.net/ext/flext/

=========
Licensing
=========

libtrancevibe is covered under the MIT License.

flext and np_trancevibe source code are covered under the GPL v2 License.

===========================
Trance Vibrator Information
===========================

More information about the TranceVibrator can be found at 

http://wiki.opendildonics.org/Rez_TranceVibrator

==================
Installation - Max
==================

- Put the .mxo(Mac)/.mxe(Windows) or .pd_[platform] file in a directory that Max/Pd will search for externals (Max: Options -> File Preferences -> Other Folders, Pd: Options -> Paths)
- Max: Put the .help file in the max-help directory of your Max/MSP installation

=========================
Platform Specifics Issues
=========================

-------
Windows
-------

- Windows will require the libusb-win32 filter driver to use the trancevibe external. This filter driver is available through the libtrancevibe sourceforge site.
- If the write timeout on windows is set to 0, writes will be quite flakey and will fail often. Always set it to at least 5. (The patch defaults it to 10)

-----
Linux
-----

- No Max/MSP build is available for linux as Max/MSP is not available for linux
- libusb requires either root access (i.e. running pd under sudo) or correct udev based USB permissions to run as non-root.

---
Mac
---

- Pd: libusb and libtrancevibe are required to be in /usr/local/lib since I can't get static builds working. These are included with the .dmg installer
