#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>


int main(int argc, char *argv[]) {
        sd_bus_error error = SD_BUS_ERROR_NULL;
        char* msg = NULL;
        sd_bus *bus = NULL;
        int r;

        // units are like org.freedesktop/systemd1/unit/pacemaker_2eservice
        char* service = "/org/freedesktop/systemd1/unit/postfix_2eservice"; 
        
        /* Connect to the system bus */
        r = sd_bus_default_system(&bus);
        if (r < 0) {
                fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
                goto finish;
        }
	
	// get for given servie the property ActiveState
	// to discover more use busctl 
        r = sd_bus_get_property_string(bus,
        "org.freedesktop.systemd1",          
        service,  
        "org.freedesktop.systemd1.Unit", 
        "ActiveState",
         &error, 
         &msg);

        if (r < 0) {
                fprintf(stderr, "Failed to issue method call: %s\n", error.message);
                goto finish;
        }

        printf("Service name: %s \nStatus: -- %s ---\n", service,  msg);

finish:
        sd_bus_error_free(&error);
        free(msg);
        sd_bus_unref(bus);

        return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
