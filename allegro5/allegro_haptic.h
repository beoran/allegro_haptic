#ifndef __al_included_allegro5_allegro_haptic_h
#define __al_included_allegro5_allegro_haptic_h

#include "allegro5/allegro.h"

#ifdef __cplusplus
   extern "C" {
#endif

#if (defined ALLEGRO_MINGW32) || (defined ALLEGRO_MSVC) || (defined ALLEGRO_BCC32)
   #ifndef ALLEGRO_STATICLINK
      #ifdef ALLEGRO_HAPTIC_SRC
         #define _ALLEGRO_HAPTIC_DLL __declspec(dllexport)
      #else
         #define _ALLEGRO_HAPTIC_DLL __declspec(dllimport)
      #endif
   #else
      #define _ALLEGRO_HAPTIC_DLL
   #endif
#endif

#if defined ALLEGRO_MSVC
   #define ALLEGRO_HAPTIC_FUNC(type, name, args)      _ALLEGRO_HAPTIC_DLL type __cdecl name args
#elif defined ALLEGRO_MINGW32
   #define ALLEGRO_HAPTIC_FUNC(type, name, args)      extern type name args
#elif defined ALLEGRO_BCC32
   #define ALLEGRO_HAPTIC_FUNC(type, name, args)      extern _ALLEGRO_HAPTIC_DLL type name args
#else
   #define ALLEGRO_HAPTIC_FUNC      AL_FUNC
#endif

/* Type: ALLEGRO_HAPTIC
 */
typedef struct ALLEGRO_HAPTIC ALLEGRO_HAPTIC;

/* Type: ALLEGRO_HAPTIC_EFFECT
 */
typedef struct ALLEGRO_HAPTIC_EFFECT ALLEGRO_HAPTIC_EFFECT;


ALLEGRO_HAPTIC_FUNC(bool, al_init_haptic_addon, (void));
ALLEGRO_HAPTIC_FUNC(bool, al_install_hapic, (void));
ALLEGRO_HAPTIC_FUNC(bool, al_uninstall_hapic, (void));
ALLEGRO_HAPTIC_FUNC(bool, al_is_haptic_installed, (void));
ALLEGRO_HAPTIC_FUNC(int , al_get_num_haptic, (void));
ALLEGRO_HAPTIC_FUNC(ALLEGRO_HAPTIC *, al_get_haptic, (int index));
ALLEGRO_HAPTIC_FUNC(void, al_release_haptic, (ALLEGRO_HAPTIC * haptic));
ALLEGRO_HAPTIC_FUNC(bool, al_get_haptic_active, (ALLEGRO_HAPTIC * haptic));
ALLEGRO_HAPTIC_FUNC(const char *, al_get_haptic_name, (ALLEGRO_HAPTIC * haptic));
ALLEGRO_HAPTIC_FUNC(bool, al_is_haptic_joystick, (void));
ALLEGRO_HAPTIC_FUNC(bool, al_is_haptic_mouse, (void));
ALLEGRO_HAPTIC_FUNC(int,  al_get_joystick_index_for_haptic, 
                              (ALLEGRO_HAPTIC * haptic));
ALLEGRO_HAPTIC_FUNC(ALLEGRO_JOYSTICK *, al_get_joystick_for_haptic, 
                              (ALLEGRO_HAPTIC * haptic));
                              /* Simple rumble effects for the given amount of seconds with 
the given intensity (0.0 to 1.0. */
ALLEGRO_HAPTIC_FUNC(bool, al_rumble_haptic, 
                          (ALLEGRO_HAPTIC * haptic, 
                           double duration, double intensity)
                       );
ALLEGRO_HAPTIC_FUNC(bool, al_start_haptic_effect,
                          (ALLEGRO_HAPTIC * haptic, 
                           ALLEGRO_HAPTIC_EFFECT * effect)
                        ); 
/* There will also functions to set up ALLEGRO_HAPTIC_EFFECT, etc. */
ALLEGRO_HAPTIC_FUNC(ALLEGRO_HAPTIC_EFFECT *, al_create_haptic_effect,
                          (int type, double duration, double intensity));
ALLEGRO_HAPTIC_FUNC(void, al_destroy_haptic_effect, 
                          (ALLEGRO_HAPTIC_EFFECT * effect));
ALLEGRO_HAPTIC_FUNC(ALLEGRO_EVENT_SOURCE *, al_get_hatic_event_source, 
                          (void));


enum {
   ALLEGRO_HAPTIC_EFFECT_SINE           = 1<<0,
   ALLEGRO_HAPTIC_EFFECT_SQUARE         = 1<<1,
   ALLEGRO_HAPTIC_EFFECT_TRIANGLE       = 1<<2,
};

enum {
   ALLEGRO_EVENT_HAPTIC_CLOSE          = 7900, // XXX these are wrong.
   ALLEGRO_EVENT_HAPTIC_DONE           = 7901
};


#ifdef __cplusplus
   }
#endif

#endif

/* vim: set sts=3 sw=3 et: */
