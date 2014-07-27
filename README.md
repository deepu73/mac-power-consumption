This repo contains utilities for working with Apple SMC power sensors. To build the code, simply
run `make`. Then try running `./smcstat`, which will print the current value of all power sensors
each second. When you tire of that game, try something like `./power_meter PSTR`, which will print
the current value of the sensor and keep a running tally of consumed watt-hours. For more details
and backstory, see the [blog post](http://cargocultelectronics.com/2014/07/mac-power-consumption/).
