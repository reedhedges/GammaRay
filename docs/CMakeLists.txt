# This file is part of GammaRay, the Qt application inspection and manipulation tool.
#
# SPDX-FileCopyrightText: 2014-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-or-later
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

# qdoc toolchain
# TODO: some of this probably should be upstreamed to Qt's cmake files...
# TODO replace with Qt::qhelpgenerator for Qt >= 5.7.1
find_program(QHELPGEN_EXECUTABLE qhelpgenerator HINTS ${QT_INSTALL_BINS})
find_program(QDOC_EXECUTABLE qdoc HINTS ${QT_INSTALL_BINS})
find_program(QTATTRIBUTIONSSCANNER_EXECUTABLE qtattributionsscanner HINTS ${QT_INSTALL_BINS})

if(NOT DEFINED QDOC_TEMPLATE_DIR)
    find_file(QDOC_TEMPLATE global/qt-html-templates-offline.qdocconf HINTS ${QT_INSTALL_DOCS} ${QT_INSTALL_DATA}
                                                                            ${QT_INSTALL_DATA}/doc
    )
    if(QDOC_TEMPLATE)
        #compute the qdoc template dir from where the qt-html-templates-offline.qdocconf was found
        get_filename_component(QDOC_TEMPLATE_DIR ${QDOC_TEMPLATE} DIRECTORY)
        get_filename_component(QDOC_TEMPLATE_DIR ${QDOC_TEMPLATE_DIR} DIRECTORY)
    endif()
endif()

if(NOT DEFINED QDOC_INDEX_DIR)
    find_file(QDOC_QTCORE_INDEX qtcore.index HINTS ${QT_INSTALL_DOCS}/qtcore ${QT_INSTALL_DATA}/doc/qtcore)
    if(QDOC_QTCORE_INDEX)
        #compute the qdoc index dir from where the qtcore.index was found
        get_filename_component(QDOC_INDEX_DIR ${QDOC_QTCORE_INDEX} DIRECTORY)
        get_filename_component(QDOC_INDEX_DIR ${QDOC_INDEX_DIR} DIRECTORY)
    endif()
endif()

if(NOT QDOC_EXECUTABLE
   OR NOT QHELPGEN_EXECUTABLE
   OR NOT QDOC_TEMPLATE_DIR
   OR NOT QDOC_INDEX_DIR
   OR NOT QTATTRIBUTIONSSCANNER_EXECUTABLE
)
    message(STATUS "Unable to build user manual in qch format.")
    message(STATUS "qdoc executable: ${QDOC_EXECUTABLE}")
    message(STATUS "qhelpgenerator executable: ${QHELPGEN_EXECUTABLE}")
    message(STATUS "qtattributionsscanner executable: ${QTATTRIBUTIONSSCANNER_EXECUTABLE}")
    message(STATUS "qdoc template dir: ${QDOC_TEMPLATE_DIR}")
    message(STATUS "qdoc index dir: ${QDOC_INDEX_DIR}")
    set(GAMMARAY_USER_MANUAL_BUILD False)
else()
    set(GAMMARAY_USER_MANUAL_BUILD True)
endif()

add_feature_info(
    "User Manual creation in qch format" GAMMARAY_USER_MANUAL_BUILD
    "Requires qdoc, qhelpgenerator, qtattributionsscanner, the qdoc templates and index files"
)

# Doxygen
find_package(Doxygen)
set_package_properties(
    Doxygen PROPERTIES
    TYPE OPTIONAL
    DESCRIPTION "API Documentation system"
    URL "https://www.doxygen.org"
    PURPOSE "Needed to build the API documentation."
)
if(DOXYGEN_DOT_EXECUTABLE)
    set(HAVE_DOT "YES")
else()
    set(HAVE_DOT "NO")
    message(STATUS "Unable to provide inheritance diagrams for the API documentation. "
                   "To fix, install the graphviz project from https://www.graphviz.org"
    )
endif()

if(DOXYGEN_FOUND AND QHELPGEN_EXECUTABLE)
    set(GAMMARAY_API_DOCS_BUILD True)
else()
    set(GAMMARAY_API_DOCS_BUILD False)
endif()

#
# generate docs
#

if(GAMMARAY_API_DOCS_BUILD)
    add_subdirectory(api)
endif()
if(GAMMARAY_USER_MANUAL_BUILD)
    add_subdirectory(manual)
    add_subdirectory(collection)
endif()
add_subdirectory(man)
