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
 )

SET(playbak_UIS
    ui/mainwindow.ui
)

add_subdirectory( ui )

kde4_add_ui_files(playbak_SRCS ${playbak_UIS})

kde4_add_kcfg_files(playbak_SRCS settings.kcfgc )

kde4_add_executable(playbak ${playbak_SRCS})
# 
target_link_libraries(playbak ${KDE4_KDEUI_LIBS})

install(TARGETS playbak ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES playbak.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES playbak.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES playbakui.rc  DESTINATION  ${DATA_INSTALL_DIR}/playbak )
