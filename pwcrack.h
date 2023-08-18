struct pw_vars
{
	size_t combo_label_len;
	size_t btn_len;
}pwcrack;
void pwcrack_combo_cbk(GtkComboBox *combo_box, gpointer user_data)
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
void crack()
{

}