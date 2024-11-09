#include "src/app/app_main.h"

void setup()
{
    App_Init();
}

/**
 * @brief Loop Task Main Loop(Core1)
 * 
 */
void loop()
{
    WDT_TGL;
    // Kill Own Task
    // vTaskDelete(NULL);
}