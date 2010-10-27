project(playbak)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES}  src/ui/widgets)

include(NepomukMacros)

add_subdirectory( doc )
add_subdirectory( src )
add_subdirectory( po )
add_subdirectory( icons )

# Package management
set(CPACK_PACKAGE_DESCRIPTION "KDE video player")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.6), libgcc1 (>= 1:4.1)")
set(CPACK_SET_DESTDIR ON)

set(CPACK_PACKAGE_CONTACT "Rémy Greinhofer ")
set(CPACK_PACKAGE_VERSION_MAJOR ${MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${PATCH_LEVEL})
set(VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(CPACK_GENERATOR "DEB;RPM;TGZ;")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${VERSION}-${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)