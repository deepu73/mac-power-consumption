#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include "smc.h"
#include "parse_smc_value.h"

int main(int argc, char** argv) {
	if (argc != 2 || (argc >= 2 && strlen(argv[1]) != 4)) {
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "  %s <SMC sensor register>\n", argv[0]);
		fprintf(stderr, "  Some fun sensors:\n");
		fprintf(stderr, "  PCPT: CPU Package Total\n");
		fprintf(stderr, "  PG0C: CPU Package Total\n");
		fprintf(stderr, "  PM0R: Memory Rail\n");
		fprintf(stderr, "  PSTR: System Total\n");
		return -1;
	}

	const char* sensor = argv[1];


	io_connect_t connection;
	if (kIOReturnSuccess != SMCOpen("AppleSMC", &connection)) {
		fprintf(stderr, "Unable to open SMC connection\n");
		return -1;
	}

	printf("Monitoring %s\n", sensor);
	printf("Instant Watts | Watt-Hours\n");
	printf("--------------+-----------\n");

	double watt_seconds = 0;

	while (true) {
		SMCVal_t val;
		if (kIOReturnSuccess != SMCReadKey(connection, sensor, &val)) {
			fprintf(stderr, "Unable to read key <%s>\n", sensor);
			return -1;
		}

		float instant_watts = parse_smc_value(&val);

		watt_seconds += instant_watts;

		double watt_hours = watt_seconds / 60 / 60;

		printf("%14.2f|%11.2f\n", instant_watts, watt_hours);
		sleep(1);
	}

	SMCClose(connection);

	printf("\n");
}
