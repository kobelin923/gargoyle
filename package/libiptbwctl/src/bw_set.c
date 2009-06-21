#include "ipt_bwctl.h"

static uint32_t bandwidth_entry_length = sizeof(ip_bw);

int main(int argc, char **argv)
{
	unsigned long num_ips;
	char id[BANDWIDTH_MAX_ID_LENGTH];

	if(argc > 1)
	{
		sprintf(id, "%s", argv[1]);
	}
	else
	{
		sprintf(id, "%s", "id_1");
	}
	
	num_ips = argc -2;
	if(num_ips > 0)
	{
       		ip_bw* data = (ip_bw*)malloc(bandwidth_entry_length*num_ips);
		int arg_index = 2;
		int data_index = 0;
		while(arg_index < argc)
		{
			ip_bw next;
			int invalid = inet_aton(argv[arg_index], &(next.ip));
			arg_index++;
			if(!invalid && arg_index < argc)
			{
				invalid = sscanf(argv[arg_index], "%lld", (long long int*)&(next.bw) ) < 1 ? 1 : 0;
			}
			else
			{
				invalid = 1;
			}
			arg_index++;

			if(!invalid)
			{
				data[data_index] = next;
				data_index++;
			}	
		}
		num_ips = data_index; /* number that were successfully read */
		if(num_ips > 0)
		{
			set_bandwidth_usage_for_rule_id(id, num_ips, data);
		}
	}
	

	return 0;
}
