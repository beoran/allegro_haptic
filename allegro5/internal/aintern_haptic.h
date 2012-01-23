#ifndef __al_included_allegro_aintern_haptic_h
#define __al_included_allegro_aintern_haptic_h

#ifdef __cplusplus
   extern "C" {
#endif

typedef struct ALLEGRO_HAPTIC_DRIVER
{
   int  hapticdrv_id;
   const char *hapticdrv_name;
   const char *hapticdrv_desc;
   const char *hapticdrv_ascii_name;
   AL_METHOD(bool, init_haptic, (void));
   AL_METHOD(void, exit_haptic, (void));
   AL_METHOD(bool, reconfigure_haptics, (void));
   AL_METHOD(int, num_haptics, (void));
   AL_METHOD(ALLEGRO_HAPTIC *, get_haptic, (int index));
   AL_METHOD(void, release_haptic, (ALLEGRO_HAPTIC *haptic));
   AL_METHOD(const char *, get_name, (ALLEGRO_HAPTIC *haptic));
   AL_METHOD(bool, get_active, (ALLEGRO_HAPTIC *haptic));
} ALLEGRO_HAPTIC_DRIVER;

struct ALLEGRO_HAPTIC
{
  int number; 
};


/* Returns the haptic driver vtable. */
ALLEGRO_HAPTIC_DRIVER * _al_get_haptic_driver(void);

#ifdef __cplusplus
   }
#endif

#endif
