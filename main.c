#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LED_PATH(x) "/sys/class/leds/" #x "/brightness"
#define LED0 LED_PATH(pwr-led)
#define LED1 LED_PATH(act-led)
#define LED2 LED_PATH(rsv-led)

#define ERR_MISS_ARG 1
#define ERR_WRONG_METHOD 2
#define ERR_WRONG_LED_DES 3

char *leds[3] = {LED0, LED1, LED2};


char *err_list[3] = {
	"Required 2 arguments.",
	"Wrong method.",
	"Wrong LED descriptor."
};


int verify(int argc, char* argv[])
{
	char *method;
	char *led;

	if (argc != 3) return -ERR_MISS_ARG;

	method = argv[1];
	led = argv[2];

	if (!(strlen(method) == 2 && !strncmp(method, "on", 2)) &&
	    !(strlen(method) == 3 && !strncmp(method, "off", 3))) {
		return -ERR_WRONG_METHOD;
	}

	if (strlen(led) != 4 || (
		strncmp(led, "LED0", 4) &&
		strncmp(led, "LED1", 4) &&
		strncmp(led, "LED2", 4))) {
		return -ERR_WRONG_LED_DES;
	}

	return 0;
}



int led_onoff(int method, int led_nr)
{
	char *led_path = leds[led_nr];
	int fd = open(led_path, O_WRONLY);
	char buffer[2];
	if (fd == -1) {
		perror("Can not open LED indicator");
		exit(1);
	}

	snprintf(buffer, 2, "%d", method);

	if (write(fd, buffer, 1) == -1) {
		perror("Can not write LED indicator");
		exit(1);
	}

	close(fd);

	return 0;
}

int main(int argc, char* argv[])
{
	int err;
	if ((err = verify(argc, argv)) < 0) {
		printf("Failed verifying arguments: %s. Check help.\n", err_list[-err-1]);
		printf("[USAGE] led_module {on | off} {LED0 | LED1 | LED2}\n");
		exit(1);
	}

	led_onoff(!!strncmp(argv[1], "off", 3), (int)(argv[2][3] - '0'));

	return 0;
}
