#!/usr/bin/env python3

# A script to convert Superpico ROM files to UF2 files in batch.
# Author: zwenergy

import os
import shutil

romFolder = "./ROM/"
uf2Folder = "./uf2/"
headerScript = "../bin2c.py"
projectName = "SUPERPICO"
srcFolder = "../"
headerName = "rom.h"
allowedSuffixes = [ ".sv" , ".bin" ]

# Initialize.
os.system( "cmake " + srcFolder )

# Iterate over all files.
for root, dirs, files in os.walk( romFolder ):
  for f in files:
    curPath = os.path.join( root, f )
    pathQuote = "'" + curPath + "'"
    filename, ext = os.path.splitext( f )
    if ( ext.lower() in allowedSuffixes ):
      print( "Found " + f + ". Converting now." )
      # Found a ROM file. Convert it.
      convCall = headerScript + " " + pathQuote + " " + srcFolder + headerName
      os.system( convCall )
      # Compile.
      os.system( "make" )
      # Move generated uf2 file.
      uf2File = "./" + projectName + ".uf2"
      romUF2 = uf2Folder + filename + ".uf2"
      shutil.copy2( uf2File, romUF2 )
