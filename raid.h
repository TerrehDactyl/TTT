struct raid_vars
{
	size_t combo_len;
	size_t entry_len;
	size_t btn_len;
	int type;
	char buffer[128];
}raid;

char calculate_raid(int type, int disks, float size, int sets)
{
	int write_gain = 0;
	int read_gain = 0;
	float final_size = 0;
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
					{
						snprintf(raid.buffer, 128, "raid 1 requires a minimum of 2 disks");
						return 0;
					}
				read_gain = disks;
				final_size = size;
				fail_over = disks/2;
				break;
		case 5: if(disks < 3)
					{
						snprintf(raid.buffer, 128, "raid 5 requires a minimum of 3 disks");
						return 0;
					}
				read_gain = disks-1;
				final_size = (disks*size)-size;
				fail_over = 1;
				break;
		case 6:if(disks < 4)
					{
						snprintf(raid.buffer, 128, "raid 6 requires a minimum of 4 disks");
						return 0;
					}
				read_gain = disks-2;
				final_size = (disks*size)-(size*2);
				fail_over = 2;
				break;
		case 10:if(disks < 4)
					{
						snprintf(raid.buffer, 128, "raid 10 requires a minimum of 4 disks");
						return 0;
					}
				write_gain = disks/2;
				read_gain = disks;
				final_size = (disks*size)/2;
				fail_over = disks/2;
				break;
		case 50:if(disks < 6 || sets < 2 || disks % sets != 0)
					{
						snprintf(raid.buffer, 128, "raid 50 requires a minimum of 6 disks, 2 sets, and the disks must be evenly divisible by the number of sets");
						return 0;
					}
				read_gain = disks - sets;
				final_size = (disks*size)-(size*sets);
				fail_over = sets;
				break;
		case 60: if(disks < 8 || sets < 2 || disks % sets != 0)
					{
						snprintf(raid.buffer, 128, "raid 60 requires a minimum of 8 disks, 2 sets, and the disks must be evenly divisible by the number of sets");
						return 0;
					}
				read_gain = disks - (sets*2);
				final_size = (disks*size)-((size*sets)*2);
				fail_over = sets*2;
				break;
	}
	snprintf(raid.buffer, 128, "%dx %.2ftb disks in raid %d yields %.2ftb of data with X%d read increase and X%d write increase and %d drive failover\n", disks, size, type, final_size, read_gain, write_gain, fail_over);
	return 0;
}

void raid_type_cbk(GtkComboBox *combo_box, gpointer user_data)
{
	raid.type = atoi(gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo_box)));
}

void run_raid() //this whole functions is a lot of wtf, i'm sure i can do this like, WAY better.
{
	gtk_text_buffer_set_text(gwidget.buffer, "", -1);
    const gchar *ascii_entries[raid.entry_len];
    int int_entries[raid.entry_len]; //wtf
    get_entry_text(gwidget.raid_entries, ascii_entries, raid.entry_len);

    if(&raid.type == NULL) //wtf this is dumb
        raid.type = 0;
    calculate_raid(raid.type, atoi(ascii_entries[0]), atoi(ascii_entries[1]), atoi(ascii_entries[2]));
    gtk_text_buffer_set_text ( gwidget.buffer, raid.buffer, -1); //displays input.num1 
}
