#include <nvs_flash.h>

void setup() {
  nvs_flash_erase();
  nvs_flash_init();
  while(true);
}

void loop() {
  // put your main code here, to run repeatedly:

}
