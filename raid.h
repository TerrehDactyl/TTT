
struct raid_vars
{
	size_t type_label_len;
	size_t entry_len;
	size_t btn_len;
}raid;

gchar *raid_type_labels[] = {"0", "1", "5", "6", "10", "50", "60"};
gchar *raid_entries[] = {"Type", "Disks", "Size", "Sets"};
void calculate_raid(int type, int disks, int size, int sets)
{
	int write_gain = 0;
	int read_gain = 0;
	int final_size = 0;
	int failover = 0;
	if(disks < 1 || size < 1)
	{
		return;
	}

	switch(type)
	{
		case 0: final_size = disks * size;
				write_gain = disks;
				read_gain = disks;
				failover = 0;
				break;

		case 1: if(disks < 2)
					{return;}
				read_gain = disks;
				final_size = size;
				failover = disks/2;
				break;

		case 5: if(disks < 3)
					{return;}
				read_gain = disks-1;
				final_size = (disks*size)-size;
				failover = 1;
				break;

		case 6:if(disks < 4)
					{return;}
				read_gain = disks-2;
				final_size = (disks*size)-(size*2);
				failover = 2;
				break;

		case 10:if(disks < 4)
					{return;}
				write_gain = disks/2;
				read_gain = disks;
				final_size = (disks*size)/2;
				failover = disks/2;
				break;

		case 50:if(disks < 6 || sets < 2 || disks % sets != 0)
					{return;}
				read_gain = disks - sets;
				final_size = (disks*size)-(size*sets);
				failover = sets;
				break;

		case 60: if(disks < 8 || sets < 2 || disks % sets != 0)
					{return;}
				read_gain = disks - (sets*2);
				final_size = (disks*size)-((size*sets)*2);
				failover = sets*2;
				break;
	}
	printf("%dx %dtb disks in raid %d yields %d tb of data with X%d read increase and X%d write increase and %d drive failover\n", disks, size, type, final_size, read_gain, write_gain, failover);
}

void raid_type_cbk(GtkComboBox *combo_box, gpointer user_data)
{
	if (gtk_combo_box_get_active (combo_box) != 0) 
	{
		gchar *selection = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo_box));
		if(strcmp(selection, "first label") == 0)
		{
			g_print("you selected the first label");
		}
		else if(strcmp(selection, "second label") == 0)
		{
			g_print("you selected the second label");
		}
		else if(strcmp(selection, "third label") == 0)
		{
			g_print("you selected the third label");
		}
	}
}