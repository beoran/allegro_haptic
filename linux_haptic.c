#include "allegro5/allegro.h"
#include "allegro5/allegro_haptic.h"
#include "allegro5/internal/aintern_haptic.h"

#include <stdio.h>

#define BUFSIZE 1024

#define ALLEGRO_HAPTIC_LINUX_NAME_SIZE 100



/* Linux specific haptic object. */
typedef struct ALLEGRO_HAPTIC_LINUX
{
   ALLEGRO_HAPTIC parent;
   bool is_haptic;
   bool is_mouse;
   bool is_joystick;
   int fd;
   char device_name[ALLEGRO_HAPTIC_LINUX_NAME_SIZE];
   char event_name[ALLEGRO_HAPTIC_LINUX_NAME_SIZE];
   char name[ALLEGRO_HAPTIC_LINUX_NAME_SIZE];
   int bus, vendor, product, version;
   int hok, hflags1, hflags2, hflags3;
} ALLEGRO_HAPTIC_LINUX;

#define ALLEGRO_HAPTIC_DEVICES 32 // at most 32 haptic devices.
static ALLEGRO_HAPTIC_LINUX haptic_devices[ALLEGRO_HAPTIC_DEVICES];
static int num_haptics;   /* number of haptic devices known to the user */


static int linux_find_haptic(void)  {
  FILE * fin = NULL;
  char buffer[BUFSIZE];
  ALLEGRO_HAPTIC_LINUX * device = haptic_devices;
  num_haptics = 0;
  fin = fopen("/proc/bus/input/devices", "r");
  if(!fin) return -1;
  device->fd = -1;
  while(!feof(fin)) {
    if(!fgets(buffer, BUFSIZE, fin)) break;

    /* now use scanf repeatedly until sucessful to get the info we need
The following is an example: 
     I: Bus=0003 Vendor=0e8f Product=0012 Version=0110
N: Name="GreenAsia Inc.      USB  Joystick  "
P: Phys=usb-0000:00:13.3-1/input0
S: Sysfs=/devices/pci0000:00/0000:00:13.3/usb5/5-1/5-1:1.0/input/input7
U: Uniq=
H: Handlers=event4 js0 
B: EV=20001b
B: KEY=fff 0 0 0 0 0 0 0 0 0
B: ABS=30027
B: MSC=10
B: FF=1 7030000 0 0
*/
    if(sscanf(buffer, "N: Bus=%d Vendor=%d Product=%d Version=%d",
    &device->bus, &device->vendor, &device->product, &device->version) == 4) {
      /* A new device is mentioned. The previous one was haptic only if it's is_haptic flag was set. */
      if (device->is_haptic) {
        device->parent.number = num_haptics;
        num_haptics++ ;
        device = haptic_devices + num_haptics;
        device->fd = -1;
        /* don't increase amount if not haptic, let previous device be overwritten if it's not haptic. */
      }
    } else if (
      sscanf(buffer, "N: Name=\"%99c", device->name) == 1
      ) {
      device->name[strlen(device->name)] = '\0';
      /* get rid of trailing " */
    } else if (
      sscanf(buffer, "H: Handlers=%99s %99s",
             device->event_name, device->device_name) == 2
      ) {
      /* Nothing to do here, hevent and device name copied OK */
    } else if (
      sscanf(buffer, "B: FF=%d %d %d %d",
             &device->hok, &device->hflags1, &device->hflags2,
             &device->hflags3)  == 4
      ) {
      device->is_haptic = true;
      /* If we find this, the current device is haptic. */
    }
  }
  fclose(fin);
  return num_haptics;
}

static void linux_release_haptic(ALLEGRO_HAPTIC *haptic) {
ALLEGRO_HAPTIC_LINUX * lhaptic = (ALLEGRO_HAPTIC_LINUX *) haptic;
  if(lhaptic->fd >= 0) {
    close(lhaptic->fd);
    lhaptic->fd = -1;
  }
}


static bool linux_init_haptic(void) {
  if(linux_find_haptic() >= 0) return true;
  return false;
}

static void linux_exit_haptic(void) {
  int index;
  for(index = 0; index < num_haptics; index++) {
    linux_release_haptic((ALLEGRO_HAPTIC *)(haptic_devices + index));
    // release the active devices. 
  }
  num_haptics = 0; // reset the amount of active haptics.
}

static bool linux_reconfigure_haptics(void) {
  /* just exit and init again for now. */
  linux_exit_haptic();
  return linux_init_haptic();
}


static int linux_num_haptics(void) {
  return num_haptics;
}

static ALLEGRO_HAPTIC * linux_open_haptic(ALLEGRO_HAPTIC_LINUX * lhaptic) {
  char filename[200];
  if(lhaptic->fd >= 0)
    return (ALLEGRO_HAPTIC *) lhaptic;
  /* already open, just return */
  snprintf(filename, 200, "/dev/input/%s", lhaptic->event_name);
  lhaptic->fd = open(filename, O_RDWR);
  if(lhaptic->fd >= 0) {
    return (ALLEGRO_HAPTIC *) lhaptic;
  }
  return NULL;
}


static ALLEGRO_HAPTIC * linux_get_haptic(int index) {
  if (index < 0) return NULL;
  if (index >= num_haptics) return NULL;
  return linux_open_haptic(haptic_devices + index);
}

static const char * linux_get_name(ALLEGRO_HAPTIC *haptic) {
  ALLEGRO_HAPTIC_LINUX * lhaptic = (ALLEGRO_HAPTIC_LINUX *) haptic;
  return (const char *) lhaptic->name;
}

static bool linux_get_active(ALLEGRO_HAPTIC *haptic) {
  ALLEGRO_HAPTIC_LINUX * lhaptic = (ALLEGRO_HAPTIC_LINUX *) haptic;
  return (lhaptic->fd >= 0 ? true : false);
}

/* XXX: what should this be??? */
#define _ALLEGRO_HAPTICDRV_LINUX 0xbad

/* The haptic driver vtable */
static ALLEGRO_HAPTIC_DRIVER _al_hapticdrv_linux =
{
   _ALLEGRO_HAPTICDRV_LINUX,
   "",
   "",
   "Linux haptic(s)",
   linux_init_haptic,
   linux_exit_haptic,
   linux_reconfigure_haptics,
   linux_num_haptics,
   linux_get_haptic,
   linux_release_haptic,
   linux_get_name,
   linux_get_active
};


ALLEGRO_HAPTIC_DRIVER * _al_get_haptic_driver()  {
  return &_al_hapticdrv_linux;
}

