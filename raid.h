struct raid_vars
{
	size_t combo_len;
	size_t entry_len;
	size_t btn_len;
	int type;
	char buffer[128];
}raid;
char calculate_raid(int type, int disks, int size, int sets)
{
	int write_gain = 0;
	int read_gain = 0;
	int final_size = 0;
	int fail_over = 0;
	if(disks < 1 || size < 1)
		return 0;

	switch(type)
	{
		case 0: final_size = disks * size;
				write_gain = disks;
				read_gain = disks;
				fail_over = 0;
				break;
		case 1: if(disks < 2)
					{return 0;}
				read_gain = disks;
				final_size = size;
				fail_over = disks/2;
				break;
		case 5: if(disks < 3)
					{return 0;}
				read_gain = disks-1;
				final_size = (disks*size)-size;
				fail_over = 1;
				break;
		case 6:if(disks < 4)
					{return 0;}
				read_gain = disks-2;
				final_size = (disks*size)-(size*2);
				fail_over = 2;
				break;
		case 10:if(disks < 4)
					{return 0;}
				write_gain = disks/2;
				read_gain = disks;
				final_size = (disks*size)/2;
				fail_over = disks/2;
				break;
		case 50:if(disks < 6 || sets < 2 || disks % sets != 0)
					{return 0;}
				read_gain = disks - sets;
				final_size = (disks*size)-(size*sets);
				fail_over = sets;
				break;
		case 60: if(disks < 8 || sets < 2 || disks % sets != 0)
					{return 0;}
				read_gain = disks - (sets*2);
				final_size = (disks*size)-((size*sets)*2);
				fail_over = sets*2;
				break;
	}

	snprintf ( raid.buffer, 128, "%dx %dtb disks in raid %d yields %d tb of data with X%d read increase and X%d write increase and %d drive fail_over\n", disks, size, type, final_size, read_gain, write_gain, fail_over);
	return 0;
}

void raid_type_cbk(GtkComboBox *combo_box, gpointer user_data)
{
	gchar *selection = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo_box));
	raid.type = atoi(selection);
}