project(playbak)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES}  src/ui/widgets)

add_subdirectory( doc )
add_subdirectory( src )
add_subdirectory( icons )
