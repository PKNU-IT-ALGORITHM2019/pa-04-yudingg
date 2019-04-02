#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX 200
#define WEB 20000
// qsort(test, n, sizeof(int), compare);

typedef struct weblog {
	char *ip;
	char *time[10];
	char *url;
	char *status;
}Weblog;

Weblog wlg[WEB];
int n = 0;

int compareIp(const void *first, const void*second);
int compareTime(const void *first, const void*second);
void read();
void sort(char type[]);
void print(char type[]);
int main() {

	char buffer[MAX],type[MAX];

	while (1) {

		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0) read();
		else if (strcmp(buffer, "sort") == 0) {
			scanf("%s", type);
			sort(type);
		}
		else if (strcmp(buffer, "print") == 0) print(type);
		else if (strcmp(buffer, "exit") == 0) break;

	}

	return 0;

}

void read() {

	char filename[MAX];
	char line[MAX];
	char *year, *month, *day, *hour, *minute, *second;
	char *ip, *time, *url, *status,*trush;
	
	scanf("%s", filename);
	FILE*fp = fopen(filename, "r");
	while (!feof(fp)) {
		
		fgets(line, MAX, fp);

		ip = strtok(line, ",");
		time = strtok(NULL, ",");
		url = strtok(NULL, ",");
		status = strtok(NULL, "\n");

		wlg[n].ip = strdup(ip);
		wlg[n].url = strdup(url);
		wlg[n].status = strdup(status);

		if (n == 0) {
			for (int i = 0; i < 6; i++) {
				wlg[n].time[i] = strdup(time);
			}
			n++;
			continue;
		}
		for (int i = 0; i <strlen(time)-1; i++) {
			time[i] = time[i + 1];
		}
		time[strlen(time) - 1] = '\0';
		wlg[n].time[6] = strdup(time);

		day = strtok(time, "/");
		month = strtok(NULL, "/");
		year = strtok(NULL, ":");
		hour = strtok(NULL, ":");
		minute = strtok(NULL, ":");
		second = strtok(NULL, "\n");
		
		wlg[n].time[0] = strdup(year);
		wlg[n].time[1] = strdup(month);
		wlg[n].time[2] = strdup(day);
		wlg[n].time[3] = strdup(hour);
		wlg[n].time[4] = strdup(minute);
		wlg[n].time[5] = strdup(second);

		n++;
	}
	fclose(fp);

	
}

Weblog test[WEB];
void sort(char type[]) {
	
	char t[MAX];

	int p = 0, r = 1;
	if (strcmp(type, "-ip") == 0) {
		qsort(wlg, n, sizeof(Weblog), compareIp);

		while (r<n) {
			int size = 0;
			while (strcmp(wlg[p].ip, wlg[r].ip) == 0) {
				test[size++] = wlg[r];
				r++;
				if (r == n)
					break;
			}

			qsort(test, size, sizeof(Weblog), compareTime);
			for (int i = p, j = 0; i < r&&j<size; i++,j++) {
				wlg[i] = test[j];
			}
			p = r;
			r++;
		}

	}
	else if (strcmp(type, "-t") == 0) {
		qsort(wlg, n, sizeof(Weblog), compareTime);
	}
	else {
		printf("error!\n");
		return;
	}
	
}

void print(char type[]) {

	if (strcmp(type, "-t") == 0) {
		for (int i = 0; i < n-1; i++) {
			printf("%s\n", wlg[i].time[6]);
			printf("	Ip: %s\n	URL: %s\n	Status: %s\n", wlg[i].ip, wlg[i].url, wlg[i].status);
		}
	}
	else if (strcmp(type, "-ip") == 0) {
		for (int i = 0; i < n-1; i++) {
			printf("%s\n", wlg[i].ip);
			printf("	Time: %s\n	URL: %s\n	Status: %s\n", wlg[i].time[6], wlg[i].url, wlg[i].status);
		}
	}
	else {
		for (int i = 0; i < n-1; i++) {
			printf("Ip: %s\nTime: %s\nURL: %s\nStatus: %s\n", wlg[i].ip, *(wlg[i].time+6), wlg[i].url, wlg[i].status);
		}
	}

}

int compareIp(const void *first, const void*second) {
	Weblog *a = (weblog*)first;
	weblog *b = (weblog*)second;

	return strcmp(a->ip, b->ip);
}

char *mon[12] = { "Jan","Feb","Mer","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
int compareTime(const void *first, const void*second) {
	
	Weblog *a = (weblog*)first;
	weblog *b = (weblog*)second;

	int i = 0;
	for (; i < 6; i++) {
		int monA = 0, monB = 0;
		if (i == 1) {
			for (; monA < 12; monA++) {
				if (strcmp(a->time[i], mon[monA]) == 0)
					break;
			}
			for (; monB < 12; monB++) {
				if (strcmp(b->time[i], mon[monB]) == 0)
					break;
			}
			if (monA != monB)
				return monA - monB;
		}
		else if (strcmp(a->time[i], b->time[i]) != 0)
			break;
	}

	return strcmp(a->time[i], b->time[i]);
}