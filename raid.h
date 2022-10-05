
struct raid_vars
{
	size_t type_label_len;
	size_t entry_len;
	size_t btn_len;
	int type;
	char buffer[128];
}raid;

gchar *raid_type_labels[] = {"0", "1", "5", "6", "10", "50", "60"};
gchar *raid_entries[] = {"Type", "Disks", "Size", "Sets"};
char calculate_raid(int type, int disks, int size, int sets)
{
	int write_gain = 0;
	int read_gain = 0;
	int final_size = 0;
	int failover = 0;
	if(disks < 1 || size < 1)
	{
		return 0;
	}

	switch(type)
	{
		case 0: final_size = disks * size;
				write_gain = disks;
				read_gain = disks;
				failover = 0;
				break;

		case 1: if(disks < 2)
					{return 0;}
				read_gain = disks;
				final_size = size;
				failover = disks/2;
				break;

		case 5: if(disks < 3)
					{return 0;}
				read_gain = disks-1;
				final_size = (disks*size)-size;
				failover = 1;
				break;

		case 6:if(disks < 4)
					{return 0;}
				read_gain = disks-2;
				final_size = (disks*size)-(size*2);
				failover = 2;
				break;

		case 10:if(disks < 4)
					{return 0;}
				write_gain = disks/2;
				read_gain = disks;
				final_size = (disks*size)/2;
				failover = disks/2;
				break;

		case 50:if(disks < 6 || sets < 2 || disks % sets != 0)
					{return 0;}
				read_gain = disks - sets;
				final_size = (disks*size)-(size*sets);
				failover = sets;
				break;

		case 60: if(disks < 8 || sets < 2 || disks % sets != 0)
					{return 0;}
				read_gain = disks - (sets*2);
				final_size = (disks*size)-((size*sets)*2);
				failover = sets*2;
				break;
	}

	snprintf ( raid.buffer, 128, "Capacity %d TB\nSpeed gain %dX read and %dX write gain\nFault tolerance %d\n",final_size, read_gain, write_gain, failover);

	return 0;
}

void raid_type_cbk(GtkComboBox *combo_box, gpointer user_data)
{
	if (gtk_combo_box_get_active (combo_box) != 0) 
	{
		gchar *selection = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo_box));
		if(strcmp(selection, "0") == 0)
		{
			raid.type=0;
		}
		else if(strcmp(selection, "1") == 0)
		{
			raid.type=1;
		}
		else if(strcmp(selection, "5") == 0)
		{
			raid.type=5;
		}
		else if(strcmp(selection, "6") == 0)
		{
			raid.type=6;
		}
		else if(strcmp(selection, "10") == 0)
		{
			raid.type=10;
		}
		else if(strcmp(selection, "50") == 0)
		{
			raid.type=50;
		}
		else if(strcmp(selection, "60") == 0)
		{
			raid.type=60;
		}
		else 
		{
			raid.type=0;
		}
	}
}
