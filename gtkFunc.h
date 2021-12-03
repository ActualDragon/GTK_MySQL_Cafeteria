/* @brief Esta función destruye una ventana. */

void destroy(GtkWidget *widget, gpointer data){
    
    gtk_main_quit();
}

/* @brief Crea un nuevo botón el cual recibe un título, una función a la que llamará y los parámetros de la función a la que llama.
 * @param const gchar *text, gpointer func, gpointer func_data*/

GtkWidget *add_button(const gchar *text, gpointer func, gpointer func_data){
    
    GtkWidget *boton;
    
    boton = gtk_button_new_with_label(text);
    gtk_signal_connect(GTK_OBJECT(boton), "clicked", GTK_SIGNAL_FUNC(func), func_data);
    
    return boton;
}

void Click(GtkButton *button, gpointer data){
    
    g_print("botón");   
}

/* @brief Retorna un GtkWidget combobox con todos los elementos del menú, de acuerdo al modo utilizado, regresa alimentos o bebidas del menú
 * @param int mode
 * @return combomenu */

GtkWidget *get_menu(int mode){
    
    GtkWidget *combomenu;
    char buffer[1024];
    
    /* Variables para MySQL */
    
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
    unsigned int i = 0;
    char cad[100];
    
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    if(mode == 0){strcpy(buffer,"SELECT nombre, precio FROM pf_menu WHERE tipo = 'A'");}
    if(mode == 1){strcpy(buffer,"SELECT nombre, precio FROM pf_menu WHERE tipo = 'B'");}
    combomenu = gtk_combo_box_new_text();
    
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
  
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
    
    /* Procesamiento del query */
    
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
  
    res=mysql_store_result(&mysql);
    
    if(!(res)){
  
        printf("\nNo hay coincidencias!\n");
        return 0;
    }
    
    while((row = mysql_fetch_row(res))){
        
        i = 0;
    
        for(i=0 ; i < mysql_num_fields(res); i=i+2){
            
            if(row[i] != NULL){
                strcpy(cad,row[0]);
                strcat(cad, " $");
                strcat(cad, row[i+1]);
                gtk_combo_box_append_text(GTK_COMBO_BOX(combomenu),cad);
            }
        }
    }
  
    gtk_combo_box_append_text(GTK_COMBO_BOX(combomenu)," ");
  
    mysql_free_result(res);
    mysql_close(&mysql);
    
    return combomenu; 
}

GtkWidget *get_my_friends(char query[]){
    
    GtkWidget *combofriends;
    char buffer[1024];
    strcpy(buffer, query);
    /* Variables para MySQL */
    
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
    unsigned int i = 0;
    char cad[100];
    
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    combofriends = gtk_combo_box_new_text();
    
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
  
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
    
    /* Procesamiento del query */
    
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
  
    res=mysql_store_result(&mysql);
    
    if(!(res)){
  
        printf("\nNo hay coincidencias!\n");
        return 0;
    }
    
    while((row = mysql_fetch_row(res))){
        
        i = 0;
    
        for(i=0 ; i < mysql_num_fields(res); i=i+3){
            
            if(row[i] != NULL){
                
                strcpy(cad,row[0]);
                strcat(cad, " - ");
                strcat(cad, row[i+1]);
                strcat(cad, " ");
                strcat(cad, row[i+2]);
                gtk_combo_box_append_text(GTK_COMBO_BOX(combofriends),cad);
            }
        }
    }
  
    mysql_free_result(res);
    mysql_close(&mysql);
    
    return combofriends;
}

