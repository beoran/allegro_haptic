#include "allegro5/allegro.h"
#include "allegro5/allegro_haptic.h"
#include "allegro5/internal/aintern_haptic.h"

#define BUFSIZE 1024

#define ALLEGRO_HAPTIC_DEVICES 32 # at most 32 haptic devices. 
ALLEGRO_HAPTIC haptic_devices[ALLEGRO_HAPTIC_DEVICES]

int linux_haptic_find_devices(void)  {
  FILE * fin = NULL;
  char buffer[BUFSIZE];
  int amount = 0;
  fin = fopen ("/proc/bus/input/devices", 'r');
  if(!fin) return -1;
  while(!feof(fin)) {
    if(!fgets(fin, BUFSIZE, buffer)) break;
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
    if(sscanf(buffer, "N: Bus=%d Vendor=%d Product=%d Version=%d", &bus, &vendor, &product, &version) == 4) {
      amount ++;
    } else if (sscanf(buffer, "") == 1) {
    }


    switch(buffer[0]) {
      case 'I': amount++; /* Found an input device. */   break;
      case 'N':  break; /*Name of device. */
      

      default: break;
    }
    
  }
  fclose(fin);
  

