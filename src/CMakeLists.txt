set(playbak_SRCS  
   main.cpp
   mainwindow.cpp
   ui/widgets/MediaInfoPage.cpp
   ui/widgets/MediaInfoInteractivePage.cpp
   ui/widgets/PlaybakSliderWidget.cpp
   ui/widgets/PlaybaKFadingButton.cpp
   ui/widgets/PlaybaKGlowTextButton.cpp
   ui/widgets/PlaybaKAnimatedSliderWidget.cpp
   ui/widgets/PlaybaKFrameWidget.cpp
   ui/widgets/PlaylistAbstractMediaItem.cpp
   ui/widgets/PlaylistAudioItemExtra.cpp
   ui/widgets/PlaylistAudioItemWidget.cpp
   ui/widgets/PlaylistItemWidget.cpp
   ui/widgets/PlaylistWidget.cpp
   MediaItem.cpp
   AlbumMediaItemData.cpp
   AudioMediaItem.cpp
   CollectionItem.cpp
   PlayableMediaItemData.cpp
   PlaybakSettings.cpp
   VisualMediaItemData.cpp
   ArtisticalMediaItemData.cpp
   Collection.cpp
   ComposedMediaItemData.cpp
   MediaPlaylist.cpp
   VideoMediaItem.cpp
   NetworkManager.cpp
   YoutubeManager.cpp
 )

SET(playbak_UIS
   ui/mainwindow.ui
   ui/prefs_base.ui
   ui/widgets/PlaylistAbstractMediaItem.ui
   ui/widgets/PlaylistAudioItemExtra.ui
   ui/widgets/PlaylistAudioItemWidget.ui
   ui/widgets/PlaylistWidget.ui
)

find_package(Nepomuk REQUIRED)
find_package(Taglib REQUIRED)

find_package(Qt4 REQUIRED)
# Is not obligatory, is recomended
# This read the C and CXX flags (are diferents in diferents compilers)
find_package(OpenMP)
# fopenmp: OpenMP pragma directives
# If OpenMP exist, we use it
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")

add_subdirectory( ui )

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} ${NEPOMUK_INCLUDES} ui/widgets include)

kde4_add_ui_files(playbak_SRCS ${playbak_UIS})

kde4_add_kcfg_files(playbak_SRCS settings.kcfgc)

qt4_automoc(${playbak_SRCS})

kde4_add_executable(playbak ${playbak_SRCS})
# gomp: OpenMP library
target_link_libraries(playbak ${KDE4_KDEUI_LIBS} ${NEPOMUK_LIBRARIES} ${TAGLIB_LIBRARIES} phonon gomp kio)

install(TARGETS playbak ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES playbak.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES playbak.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES playbakui.rc  DESTINATION  ${DATA_INSTALL_DIR}/playbak )
