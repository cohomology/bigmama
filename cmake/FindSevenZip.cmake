include(FindPackageHandleStandardArgs)

if (win32)
  set(progfilesx86 "ProgramFiles(x86)")
  find_program(SEVENZIP_BIN
    NAMES 7z 7za
    HINTS "${MINGWDIR}" "${MINGWLIBS}/bin" "$ENV{${progfilesx86}}/7-zip" "$ENV{ProgramFiles}/7-zip" "$ENV{ProgramW6432}/7-zip"
    PATH_SUFFIXES bin
    DOC "7zip executable"
    )
  unset(progfilesx86)
else()
  find_program(SEVENZIP_BIN
    NAMES 7z 7za
    HINTS /usr/bin /usr/local/bin
    PATH_SUFFIXES bin
    DOC "7zip executable"
    ) 
endif()

find_package_handle_standard_args(SevenZip DEFAULT_MSG SEVENZIP_BIN)

mark_as_advanced(SEVENZIP_BIN)
