Dearchive the freeimage distribution into a directory called freeimage, such that you have the following:

grit.sln
grit.vcproj
freeimage\FreeImage.dll
freeimage\FreeImage.h
freeimage\FreeImage.lib

Then, sprinkle the dll around as necessary. Building should be straightforward.

Be sure to update grit_version.h to change the version number for MSVC builds, although we anticipate building with mingw in perpetuity.
