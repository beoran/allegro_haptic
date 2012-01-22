#ifndef __al_included_allegro_aintern_native_dialog_h
#define __al_included_allegro_aintern_native_dialog_h

#include "allegro5/internal/aintern_vector.h"

typedef struct ALLEGRO_NATIVE_DIALOG ALLEGRO_NATIVE_DIALOG;

/* We could use different structs for the different dialogs. But why
 * bother.
 */
struct ALLEGRO_HAPTIC
{
   ALLEGRO_USTR * name;
   
   /* Only used by platform implementations. */
   ALLEGRO_PATH * path;
   int            handle;
   int            flags;
};

struct ALLEGRO_HAPTIC_EFFECT
{
   ALLEGRO_HAPTIC *device;
   double duration;
   double intensity;
   int type;
};


#endif
