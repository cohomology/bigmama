set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)
find_package(Qt5LinguistTools)

### translation stuff

file(GLOB TRANSLATION_FILES ${CMAKE_CURRENT_LIST_DIR}/*.ts)

qt5_create_translation(BIGMAMA_TS ${FILES_TO_TRANSLATE} ${TRANSLATION_FILES})
qt5_add_translation(BIGMAMA_QM ${TRANSLATION_FILES})
add_custom_target(translations_update DEPENDS ${BIGMAMA_TS})
add_custom_target(translations DEPENDS translations ${BIGMAMA_QM})
