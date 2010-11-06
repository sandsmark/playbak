set(playbak_SRCS
   main.cpp
   mainwidow.cpp
   ui/widgets/MediaInfoPage.cpp
   ui/widgets/MediaInfoInteractivePage.cpp
   ui/widgets/PlaybakSliderWidget.cpp
   ui/widgets/PlaybaKFadingButton.cpp
   ui/widgets/PlaybaKGlowTextButton.cpp
   ui/widgets/PlaybaKAnimatedSliderWidget.cpp
   ui/widgets/PlaybaKFrameWidget.cpp
   src/MediaItem.cpp
   src/AlbumMediaItemData.cpp
   src/AudioMediaItem.cpp
   src/CollectionItem.cpp
   src/PlaybakSettings.cpp
   src/VisualMediaItemData.cpp
   src/ArtisticalMediaItemData.cpp
   src/Collection.cpp
   src/ComposedMediaItemData.cpp
   src/MediaPlaylist.cpp
   src/VideoMediaItem.cpp
 )

SET(playbak_UIS
    ui/mainwindow.ui
    ui/prefs_base.ui
)

find_package(Nepomuk REQUIRED)
find_package(Taglib REQUIRED)

add_subdirectory( ui )

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} ${NEPOMUK_INCLUDES} ui/widgets include)

kde4_add_ui_files(playbak_SRCS ${playbak_UIS})

kde4_add_kcfg_files(playbak_SRCS settings.kcfgc)

kde4_add_executable(playbak ${playbak_SRCS})
# 
target_link_libraries(playbak ${KDE4_KDEUI_LIBS} ${NEPOMUK_LIBRARIES} ${TAGLIB_LIBRARIES} phonon)

install(TARGETS playbak ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES playbak.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES playbak.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES playbakui.rc  DESTINATION  ${DATA_INSTALL_DIR}/playbak )
