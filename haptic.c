#include "allegro5/allegro.h"
#include "allegro5/allegro_haptic.h"
#include "allegro5/internal/aintern.h"
#include "allegro5/internal/aintern_events.h"
#include "allegro5/internal/aintern_haptic.h"
#include "allegro5/internal/aintern_system.h"



/* the active haptic driver */
static ALLEGRO_HAPTIC_DRIVER * haptic_driver = NULL;
static ALLEGRO_EVENT_SOURCE    es;

/* Function: al_uninstall_haptic
 */
void al_uninstall_haptic(void)
{
  if (haptic_driver) {
    /* perform driver clean up */
    haptic_driver->exit_haptic();
    _al_event_source_free(&es);
    haptic_driver = NULL;
  }
}


/* Function: al_install_haptic
 */
bool al_install_haptic(void)
{
  ALLEGRO_HAPTIC_DRIVER *hapticdrv;
  if (haptic_driver)
    return true;

  hapticdrv = _al_get_haptic_driver();
  _al_event_source_init(&es);
  if (hapticdrv && hapticdrv->init_haptic()) {
    haptic_driver = hapticdrv;
    _al_add_exit_func(al_uninstall_haptic, "al_uninstall_haptic");
    return true;
  }
  _al_event_source_free(&es);
  return false;
}  


/* Function: al_is_haptic_installed
 */
bool al_is_haptic_installed(void)
{
  return (haptic_driver) ? true : false;
}


/* Function: al_reconfigure_haptics
 */
bool al_reconfigure_haptics(void)
{
  if (!haptic_driver)
    return false;
  return haptic_driver->reconfigure_haptics();
}



/* Function: al_get_haptic_event_source
 */
ALLEGRO_EVENT_SOURCE *al_get_haptic_event_source(void)
{
  if (!haptic_driver)
    return NULL;
  return &es;
}


void _al_generate_haptic_event(ALLEGRO_EVENT *event)
{
   ASSERT(haptic_driver);
   _al_event_source_lock(&es);
   if (_al_event_source_needs_to_generate_event(&es)) {
      _al_event_source_emit_event(&es, event);
   }
   _al_event_source_unlock(&es);
}


/* Function: al_get_num_haptics
 */
int al_get_num_haptics(void)
{
   if (haptic_driver)
      return haptic_driver->num_haptics();
   return 0;
}


/* Function: al_get_haptic
 */
ALLEGRO_HAPTIC * al_get_haptic(int num)
{
   ASSERT(haptic_driver);
   ASSERT(num >= 0);
   return haptic_driver->get_haptic(num);
}


/* Function: al_release_haptic
 */
void al_release_haptic(ALLEGRO_HAPTIC *hap)
{
   ASSERT(haptic_driver);
   ASSERT(hap);
   haptic_driver->release_haptic(hap);
}

/* Function: al_get_haptic_active
 */
bool al_get_haptic_active(ALLEGRO_HAPTIC *hap)
{
   ASSERT(hap);
   return haptic_driver->get_active(hap);
}



/* Function: al_get_haptic_name
 */
const char *al_get_haptic_name(ALLEGRO_HAPTIC *hap)
{
   ASSERT(hap);
   return haptic_driver->get_name(hap);
}


/*
 * Local Variables:
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
/* vim: set sts=3 sw=3 et: */
