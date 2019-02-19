#!/bin/sh

lupdate -target-language en src/*.cpp include/*.h -ts translations/bigmama_en.ts  
lupdate -target-language de src/*.cpp include/*.h -ts translations/bigmama_de.ts

