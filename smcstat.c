#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include "smc.h"
#include "parse_smc_value.h"

int main(int argc, char** argv) {
	const char* keys[] = {
		"PAPC",
		"PBLC",
		"PC0C", // CPU0 Core
		"PC0R", // Mainboard S0 Rail
		"PC1C", // CPU1 Core
		"PC2C", // CPU2 Core
		"PC3C", // CPU3 Core Always 0?
		"PCLT",
		"PCPC", // CPU Package Cores
		"PCPG", // CPU Package Graphics
		"PCPL", // Always reads 45.00
		"PCPT", // CPU Package Total
		"PDTR", // System total???
		"PG0C", // GPU0 Core
		"PG0R", // GPU Rail
		"PG1C", // GPU1 Core Always 0
		"PG2C", // GPU2 Core Always 0
		"PG3C", // GPU3 Core Always 0
		"PHDC",
		"PHPC",
		"PHSC",
		"PLDC",
		"PM0R", // Memory Rail
		"PN0R", // Northbridge Rail
		"PO0R",
		"PPBR", // Changes, but unknown
		"PSBC",
		"PSTR", // System total
		"PTHC", // Always reads 66.00
		"PZ0E", // Always reads 66.00
		"PZ0F",
		"PZ0R",
		"PZ1E", // Always reads 45.00
		"PZ1F",
		"PZ1R",
		"PZ2E", // Always reads 53.00
		"PZ2F",
		"PZ2R",
		"PZ3E", // Always reads 13.50
		"PZ3F", // Always 0
		"PZ3R", // Always 0
		0
	};

	int idx = -1;
	while (keys[++idx]) {
		printf("%5s ", keys[idx]);
	}
	printf("\n");

	io_connect_t connection;
	if (kIOReturnSuccess != SMCOpen("AppleSMC", &connection)) {
		fprintf(stderr, "Unable to open SMC connection\n");
		return -1;
	}

	while (true) {
		idx = -1;
		while (keys[++idx]) {
			SMCVal_t val;
			if (kIOReturnSuccess != SMCReadKey(connection, keys[idx], &val)) {
				fprintf(stderr, "Unable to read key <%s>\n", keys[idx]);
				return -1;
			}

			float decoded = parse_smc_value(&val);

			printf("%5.2f ", decoded);
		}
		printf("\n");
		sleep(1);
	}

	SMCClose(connection);

	printf("\n");
}
