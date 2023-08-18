#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_INT 32767
void startscan();
void cancelscan();
void createsocket(int port, const char *ipaddress, FILE *filepointer);
void extractIpAddress(const char *sourceString, int ipaddress[]);
void findrange(int startip[], int endip[], int range[]);
char *formatipaddress(int unformatted[]);
void cycleandscan(int range[], int startip[], int start, int end, FILE *filepointer);

struct input_variables
{
	const char *entrytext[4];
	size_t label_len;
	size_t btn_len;
	int startip[4];
	int endip[4];
	int range[4];
	GtkWidget *entries[4];
	size_t entry_len;
}pscan;

gchar *pscan_btn_labels[] = {"Start Scan", "Cancel Scan"};
void *pscan_btn_cbks[] = {startscan, cancelscan};
gchar *pscan_labels[] = {"Starting Port\n", "Ending Port\n", "Start IP\n", "End IP\n"};
void startscan()
{
	FILE *filepointer;
	filepointer = fopen("Results.txt", "w");
	get_entry_text(pscan.entries, pscan.entrytext, pscan.label_len);
	int start = atoi(pscan.entrytext[0]);
	int end = atoi(pscan.entrytext[1]);

	extractIpAddress(pscan.entrytext[2], pscan.startip);
	extractIpAddress(pscan.entrytext[3], pscan.endip);
	findrange(pscan.startip, pscan.endip, pscan.range);
	if(pscan.endip == NULL || (pscan.range[0] == 0 && pscan.range[1] == 0 && pscan.range[2] == 0 && pscan.range[3] == 0))
		for(int port = start; port<=end; port++)
			createsocket(port, pscan.entrytext[2], filepointer);
	else
		cycleandscan(pscan.range, pscan.startip, start, end, filepointer);

	fclose(filepointer);
	system("xdg-open Results.txt");
}

void findrange(int startip[], int endip[], int range[])
{
	for (int i = 0; i < 4; i++)
		range[i] = endip[i] - startip[i];
}

void cancelscan()
{exit(1);}

char *formatipaddress(int unformatted[])
{
	static char formatted[48];
	snprintf(formatted, sizeof(formatted), "%d.%d.%d.%d", unformatted[0], unformatted[1], unformatted[2], unformatted[3]);
	return formatted;
}

void cycleandscan(int range[], int startip[], int start, int end, FILE *filepointer)
{
	int octet = 3;
	while(1)
	{
		findrange(startip, pscan.endip, pscan.range);

		if(range[3] != -1 || range[2] != 0 || range[1] != 0 || range[0] != 0)
		{
			while(1)
			{
				findrange(startip, pscan.endip, pscan.range);

				if(range[3] != -1 || range[2] != 0 || range[1] != 0 || range[0] != 0)
				{
							if(startip[octet] > 255)
							{
								startip[octet] = 0;
								startip[octet-1] += 1;
								break;
							}
							g_print("startip[octet] %d, octet %d \n",startip[octet], octet);
							for(int port = start; port<=end; port++)
								{createsocket(port, formatipaddress(startip), filepointer);}

							startip[3]++;
				}
				else
					break;
			}
		}
		octet--;
		if(octet == 0)
		{
			break;
		}
	}
}

void createsocket(int port, const char *ipaddress, FILE *filepointer)
{
	struct sockaddr_in server_address;
	char *result;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	int network_socket = socket(AF_INET, SOCK_STREAM, 0); 
	if (network_socket < 0 ) 
		g_print("socket creation failed...\n"); 

	server_address.sin_addr.s_addr = inet_addr(ipaddress);
	if (connect(network_socket,(struct sockaddr *) &server_address,sizeof server_address) <0)
		result = "closed";
	else
		result = "open";

	g_print("%s Port: %d is %s\n", ipaddress, port, result);
	fprintf(filepointer, "%s Port: %d is %s\n", ipaddress, port, result);
	close(network_socket); 
}

void extractIpAddress(const char *sourceString, int ipaddress[])
{
	unsigned short len = strlen(sourceString);
	unsigned char oct[4]={0},cnt=0,cnt1=0;
	char buf[5];

	for(int i=0;i<len;i++)
	{
		if(sourceString[i]!='.')
			buf[cnt++] = sourceString[i];

		if(sourceString[i]=='.' || i==len-1)
			buf[cnt]='\0', cnt = 0, oct[cnt1++]=atoi(buf);
	}
	for(int i = 0; i < 4; i++)
		ipaddress[i]=oct[i];
}