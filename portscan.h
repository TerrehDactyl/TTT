#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_INT 32767
void start_scan();
void cancel_scan();
void create_socket(int port, const char *ipaddress, FILE *fp);
void extract_ipaddress(const char *source_string, int ipaddress[]);
void find_range(int start_ip[], int end_ip[], int range[]);
char *format_ipaddress(int unformatted[]);
void cycle_and_scan(int range[], int start_ip[], int start, int end, FILE *fp);

struct input_variables
{
	const char *entry_text[4];
	size_t label_len;
	size_t btn_len;
	int start_ip[4];
	int end_ip[4];
	int range[4];
	GtkWidget *entries[4];
	size_t entry_len;
}pscan;

gchar *pscan_btn_labels[] = {"Start Scan", "Cancel Scan"};
void *pscan_btn_cbks[] = {start_scan, cancel_scan};
gchar *pscan_labels[] = {"Starting Port\n", "Ending Port\n", "Start IP\n", "End IP\n"};
void start_scan()
{
	FILE *fp;
	fp = fopen("Results.txt", "w");
	get_entry_text(pscan.entries, pscan.entry_text, pscan.label_len);
	int start = atoi(pscan.entry_text[0]);
	int end = atoi(pscan.entry_text[1]);

	extract_ipaddress(pscan.entry_text[2], pscan.start_ip);
	extract_ipaddress(pscan.entry_text[3], pscan.end_ip);
	find_range(pscan.start_ip, pscan.end_ip, pscan.range);
	if(pscan.end_ip == NULL || (pscan.range[0] == 0 && pscan.range[1] == 0 && pscan.range[2] == 0 && pscan.range[3] == 0))
		for(int port = start; port<=end; port++)
			create_socket(port, pscan.entry_text[2], fp);
	else
		cycle_and_scan(pscan.range, pscan.start_ip, start, end, fp);

	fclose(fp);
	system("xdg-open Results.txt");
}

void find_range(int start_ip[], int end_ip[], int range[])
{
	for (int i = 0; i < 4; i++)
		range[i] = end_ip[i] - start_ip[i];
}

void cancel_scan()
{exit(1);}

char *format_ipaddress(int unformatted[])
{
	static char formatted[48];
	snprintf(formatted, sizeof(formatted), "%d.%d.%d.%d", unformatted[0], unformatted[1], unformatted[2], unformatted[3]);
	return formatted;
}

void cycle_and_scan(int range[], int start_ip[], int start, int end, FILE *fp)
{
	int octet = 3;
	while(1)
	{
		find_range(start_ip, pscan.end_ip, pscan.range);

		if(range[3] != -1 || range[2] != 0 || range[1] != 0 || range[0] != 0)
		{
			while(1)
			{
				find_range(start_ip, pscan.end_ip, pscan.range);

				if(range[3] != -1 || range[2] != 0 || range[1] != 0 || range[0] != 0)
				{
							if(start_ip[octet] > 255)
							{
								start_ip[octet] = 0;
								start_ip[octet-1] += 1;
								break;
							}
							g_print("start_ip[octet] %d, octet %d \n",start_ip[octet], octet);
							for(int port = start; port<=end; port++)
								{create_socket(port, format_ipaddress(start_ip), fp);}

							start_ip[3]++;
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

void create_socket(int port, const char *ipaddress, FILE *fp)
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
	fprintf(fp, "%s Port: %d is %s\n", ipaddress, port, result);
	close(network_socket); 
}

void extract_ipaddress(const char *source_string, int ipaddress[])
{
	unsigned short len = strlen(source_string);
	unsigned char oct[4]={0},cnt=0,cnt1=0;
	char buf[5];

	for(int i=0;i<len;i++)
	{
		if(source_string[i]!='.')
			buf[cnt++] = source_string[i];

		if(source_string[i]=='.' || i==len-1)
			buf[cnt]='\0', cnt = 0, oct[cnt1++]=atoi(buf);
	}
	for(int i = 0; i < 4; i++)
		ipaddress[i]=oct[i];
}