set(HAPTIC_INCLUDE_FILES allegro5/allegro_haptic.h)

set_our_header_properties(${HAPTIC_INCLUDE_FILES})

set(HAPTIC_SOURCES
    haptic.c
    )

if(APPLE AND NOT IPHONE)
   list(APPEND HAPTIC_SOURCES osx_haptic.c)
   set(ALLEGRO_CFG_HAPTIC_OSX 1)
   set(SUPPORT_HAPTIC 1)
endif(APPLE AND NOT IPHONE)

if(APPLE AND IPHONE)
   list(APPEND HAPTIC_SOURCES iphone_haptic.c)
   set(ALLEGRO_CFG_HAPTIC_IPHONE 1)
   set(SUPPORT_HAPTIC 1)
endif(APPLE AND IPHONE)

if(WIN32)
   list(APPEND HAPTIC_SOURCES win_haptic.c)
   set(ALLEGRO_CFG_HAPTIC_WINDOWS 1)
   set(SUPPORT_HAPTIC 1)
endif(WIN32)

if(LINUX) 
  list(APPEND HAPTIC_SOURCES linux_haptic.c)
endif(LINUX)

if(SUPPORT_HAPTIC)
   configure_file(
       allegro5/internal/aintern_haptic_cfg.h.cmake
       ${CMAKE_BINARY_DIR}/include/allegro5/internal/aintern_haptic_cfg.h
       )

   add_our_library(allegro_haptic
       "${HAPTIC_SOURCES};${HAPTIC_INCLUDE_FILES}"
       "-DALLEGRO_HAPTIC_SRC"
       "${HAPTIC_LIBRARIES};${ALLEGRO_LINK_WITH}"
       )

   set_our_framework_properties(allegro_haptic AllegroHaptic-${ALLEGRO_SOVERSION})

   install_our_library(allegro_haptic)
   install_our_headers(${HAPTIC_INCLUDE_FILES})

   set(SUPPORT_HAPTIC 1 PARENT_SCOPE)
   set(HAPTIC_LINK_WITH allegro_haptic PARENT_SCOPE)
endif(SUPPORT_HAPTIC)

# vim: set sts=4 sw=4 et:
