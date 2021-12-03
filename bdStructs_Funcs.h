typedef struct{
    
    GtkWidget *tusuario;
    GtkWidget *tcontra;
    GtkWidget *ventana;
    GtkWidget *linfo;
    
    char usuario[20];
    char contra[20];
    
}St_ingresa;

typedef struct{
    
    GtkWidget *combomenu;
    
}St_menu;

typedef struct{
    
    GtkWidget *ventana;
    GtkWidget *telemento, *tprecio;
    GtkWidget *lestatus;
    GtkWidget *menu;
    GtkWidget *combotipo;
    
    char elemento[30];
    float precio;
    
}St_mod_menu;

typedef struct{
    
    GtkWidget *ventana;
    GtkWidget *tnombre, *tappaterno, *tapmaterno;
    GtkWidget *tcarrera, *tsemestre, *tcuenta, *tusuario;
    GtkWidget *tdia, *tmes, *tanio;
    GtkWidget *linfo, *lres;
    
    char* numcuenta, usuario[30];
    
}St_busca_usuario;

typedef struct{
    
    GtkWidget *ventana;
    
    GtkWidget *tnombre, *tappaterno, *tapmaterno;
    GtkWidget *tdia, *tmes, *tanio;
    GtkWidget *tcuenta, *tcarrera, *tsemestre;
    GtkWidget *tcorreo, *tcontra, *tconfcontra;
    GtkWidget *linfo, *resultset;
    
    char* numcuenta;
    
    char nombre[30], appaterno[30], apmaterno[30];
    char dia[5], mes[5], anio[5], semestre[5];
    char cuenta[30], carrera[50], correo[30];
    char contra[30], confcontra[30];
    
}St_registra;

typedef struct{
    
    GtkWidget *comida, *bebida, *carrito, *ventana, *linfo;
    GtkWidget *comboamigo, *tusuario;
    
    int para;  /* 0 es para mi, 1 es para un amigo */
    char *numcuenta;
    int pedidos[30], pedido;
    float total;
    
}St_comandas;


int MenuAdmin(gpointer data);
int MenuUsuario(gpointer data);
int InicioSesion();
int MiPerfilAdmin(gpointer data);
int InvitaAmigos(gpointer data);
int ConfirmaCompra(gpointer data);
void VentanaBusquedas(gpointer data);

int MySQLfind_user(char query[], char userf[], char pass[]);
int MySQLfind_element(char query[], char find[]);
int MySQLadd(char query[]);
int MySQLdelete(char query[]);
char* MySQLget_user(char query[]);
char* MySQLreturn(char query[]);
char* MySQLget_busca(char query[]);
int MySQLcheck(char query[]);
long MySQLget_resultset_size(char query[]);
int MySQLexecute_query(char query[]);
long MySQLget_search_size(char query[]);

/* @brief Esta función sirve para obtener el usuario que ingresa sesión, lo busca en la base de datos de usuarios y luego en la de administradores */

void RecibeUsuario(GtkButton *button, gpointer data){

    const gchar *c_usuario, *c_contra;
    St_ingresa *datos = (St_ingresa*)data;
    
    int encontrado;
    
    c_usuario = gtk_entry_get_text(GTK_ENTRY(datos->tusuario));
    c_contra = gtk_entry_get_text(GTK_ENTRY(datos->tcontra));
    
    if(c_usuario[0] != '\0' && c_contra[0] != '\0'){
        
        strcpy(datos->usuario,c_usuario);
        strcpy(datos->contra,c_contra);
    
        encontrado = MySQLfind_user("SELECT numcuenta, contra FROM pf_usuarios WHERE tipo = 'A'",datos->usuario,datos->contra);
        
        if(encontrado == 1){
            
            MenuAdmin(data);
        
        }else{
            
            encontrado = MySQLfind_user("SELECT numcuenta, contra FROM pf_usuarios WHERE tipo = 'U'",datos->usuario,datos->contra);
            
            if(encontrado == 1){
                
                MenuUsuario(data);
            
            }else{
                
                gtk_label_set_text(GTK_LABEL(datos->linfo),"Su usuario o contraseña son incorrectas.");
            }
        }
    
    }else{
       
       gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de ingresar los datos solicitados."); 
    }
}

/* @bief Esta función permite recibir el elemento a agregar en el menú así como también su precio */

void RecibeElemento(GtkButton *button, gpointer data){
    
    const gchar *c_elemento, *c_precio, *c_tipo;
    char cprecio[20], query[200], tipo[20];
    int encontrado;
    St_mod_menu *datos = (St_mod_menu*)data;
    
    c_elemento = gtk_entry_get_text(GTK_ENTRY(datos->telemento));
    c_precio = gtk_entry_get_text(GTK_ENTRY(datos->tprecio));
    c_tipo = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->combotipo));

    if(c_elemento[0] != '\0' && c_precio[0] != '\0' && c_tipo != NULL){
        
        strcpy(datos->elemento,c_elemento);
        //g_print("%s",datos->elemento);
        strcpy(cprecio,c_precio);
        //g_print("%s",cprecio);
        strcpy(tipo,c_tipo);
        datos->precio = atof(c_precio);
    
        encontrado = MySQLfind_element("SELECT nombre FROM pf_menu",datos->elemento);
        //g_print("%s",tipo);
        
        if(encontrado == 1){
            
            gtk_label_set_text(GTK_LABEL(datos->lestatus),"¡Esto ya se encuentra en el menú!");
        
        }else{
            
            if(strcmp(tipo,"Alimento") == 0){
             
                sprintf(query,"INSERT INTO pf_menu(nombre,precio,tipo) VALUES('%s',%.2f,'A')",datos->elemento,datos->precio);
                MySQLadd(query);
                gtk_label_set_text(GTK_LABEL(datos->lestatus),"Elemento añadido exitosamente, los cambios se verán reflejados al próximo inicio de sesión.");   
                
            }
            
            if(strcmp(tipo,"Bebida") == 0){
                
                sprintf(query,"INSERT INTO pf_menu(nombre,precio,tipo) VALUES('%s',%.2f,'B')",datos->elemento,datos->precio);
                MySQLadd(query);
                gtk_label_set_text(GTK_LABEL(datos->lestatus),"Elemento añadido exitosamente, los cambios se verán reflejados al próximo inicio de sesión.");    
            }
        }
    
    }else{
        
        gtk_label_set_text(GTK_LABEL(datos->lestatus),"¡Favor de llenar todos los datos!");
    }
}

/* @bief Esta función permite buscar en la base de datos un alimento o bebida para poder eliminarlo de la base de datos */

void BorraElemento(GtkButton *button, gpointer data){
    
    const gchar *c_elemento;
    char query[200];
    int encontrado;
    St_mod_menu *datos = (St_mod_menu*)data;
    
    c_elemento = gtk_entry_get_text(GTK_ENTRY(datos->telemento));

    if(c_elemento[0] != '\0'){
        
        strcpy(datos->elemento,c_elemento);
        encontrado = MySQLfind_element("SELECT nombre FROM pf_menu",datos->elemento);
        
        if(encontrado == 1){
            
            gtk_label_set_text(GTK_LABEL(datos->lestatus),"Menú actualizado, los cambios se verán reflejados al próximo inicio de sesión.");
            sprintf(query,"DELETE FROM pf_menu WHERE nombre = '%s'",datos->elemento);
            MySQLdelete(query);
        
        }else{
            
            gtk_label_set_text(GTK_LABEL(datos->lestatus),"¡Esto no se encuentra en el menú!");
        }
    }
}

/* @brief Esta función permite buscar en la base de datos un usuario de acuerdo a diversos criterios, o bien una combinación de los criterios presentados en la ventana
 * de busqueda, además, guarda las busquedas realizadas así como el usuario que la realizó */

void BuscaUsuario(GtkButton *button, gpointer data){
    
    const gchar *c_appaterno, *c_carrera, *c_semestre, *c_ncuenta;
    const gchar *c_dia, *c_mes, *c_anio;
    St_busca_usuario *datos = (St_busca_usuario*)data;
    
    int fecha, queryadd, id;
    long rs_size;
    
    char cappaterno[20], ccarrera[20], cncuenta[20];
    char query[300], temp[70], date[11], csemestre[3], busqueda[300];
    char *resultset;
    
    fecha = 1;
    queryadd = 0;
    
    g_print("%s\n",datos->numcuenta);

    c_appaterno = gtk_entry_get_text(GTK_ENTRY(datos->tappaterno));
    
    c_ncuenta = gtk_entry_get_text(GTK_ENTRY(datos->tcuenta));
    c_semestre = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tsemestre));
    
    c_carrera = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tcarrera));
    c_dia = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tdia));
    c_mes = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tmes));
    c_anio = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tanio));
    
    /* Comprobaciones */
    
    time_t t = time(NULL);
    struct tm *tiempolocal = localtime(&t);
    strftime(date,11,"%Y-%m-%d",tiempolocal);
    
    if(c_dia == NULL || c_mes == NULL || c_anio == NULL){
        
        fecha = 0;
    
    }else{
        
        sprintf(date,"%s-%s-%s",c_anio,c_mes,c_dia);
    }
    
    if(c_appaterno[0] == '\0' && c_ncuenta[0] == '\0' && c_semestre == NULL && c_carrera == NULL && fecha == 0){
        
        gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de llenar al menos un campo.");
              
    }else{
        
        strcpy(query, "SELECT nombre, appaterno, apmaterno, carrera, semestre, nacimiento, numcuenta, correo FROM pf_usuarios");
        
        sprintf(busqueda," ");
        
        if(c_appaterno[0] !=  '\0' && queryadd == 0){
            
            strcpy(cappaterno, c_appaterno);            
            sprintf(temp, " WHERE appaterno = '%s'", cappaterno);
            strcat(query,temp);
            queryadd++;
            
            sprintf(temp," Apellido Paterno: %s ",cappaterno);
            strcat(busqueda,temp);
        }
        
        if(c_ncuenta[0] !=  '\0' && queryadd == 0){
          
            strcpy(cncuenta, c_ncuenta);            
            sprintf(temp, " WHERE numcuenta = '%s'", cncuenta);
            strcat(query,temp);
            queryadd++;
            
            sprintf(temp," Numero de cuenta: %s ",cncuenta);
            strcat(busqueda,temp);
            
        }else if(c_ncuenta[0] !=  '\0' && queryadd == 1){
            
            strcpy(cncuenta, c_ncuenta);            
            sprintf(temp, " AND numcuenta = '%s'", cncuenta);
            strcat(query,temp);
            
            sprintf(temp," Numero de cuenta: %s ",cncuenta);
            strcat(busqueda,temp);
        }
        
        if(c_carrera !=  NULL && queryadd == 0){
            
            strcpy(ccarrera, c_carrera);            
            sprintf(temp, " WHERE carrera = '%s'", ccarrera);
            strcat(query,temp);
            queryadd++;
            
            sprintf(temp," Carrera: %s ",ccarrera);
            strcat(busqueda,temp);
            
        }else if(c_carrera !=  NULL && queryadd == 1){
            
            strcpy(ccarrera, c_carrera);            
            sprintf(temp, " AND carrera = '%s'", ccarrera);
            strcat(query,temp);
            
            sprintf(temp," Carrera: %s ",ccarrera);
            strcat(busqueda,temp);
        }
        
        if(c_semestre != NULL && queryadd == 0){
            
            strcpy(csemestre, c_semestre);            
            sprintf(temp, " WHERE semestre = %i", atoi(csemestre));
            strcat(query,temp);
            queryadd++;
            
            sprintf(temp," Semestre: %i ",atoi(csemestre));
            strcat(busqueda,temp);
            
        }else if(c_semestre != NULL && queryadd == 1){
            
            strcpy(csemestre, c_semestre);            
            sprintf(temp, " AND semestre = %i", atoi(csemestre));
            strcat(query,temp);
            
            sprintf(temp," Semestre: %i ",atoi(csemestre));
            strcat(busqueda,temp);
        }
        
        if(fecha != 0 && queryadd == 0){
                      
            sprintf(temp, " WHERE nacimiento = '%s'",date);
            strcat(query,temp);
            queryadd++;
            
            sprintf(temp," FEcha de nacimiento: %s ",date);
            strcat(busqueda,temp);
            
        }else if(fecha != 0 && queryadd == 1){
            
            sprintf(temp, " AND nacimiento = '%s'",date);
            strcat(query,temp);
            
            sprintf(temp," Fecha de nacimiento: %s ",date);
            strcat(busqueda,temp);
        }
        
        rs_size = MySQLget_resultset_size(query);
        
        if(rs_size != -1){
            
            resultset = malloc(sizeof(char)*(rs_size+1));
            resultset = MySQLget_user(query);
            resultset[rs_size + 1] = '\0';
        
            sprintf(temp,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->numcuenta);
            id = atoi(MySQLreturn(temp));
            
            sprintf(temp,"INSERT INTO pf_busquedas(idUsuario,busqueda,fecha) VALUES(%i,'%s','%s')",id,busqueda,date);
            MySQLexecute_query(temp);
            
            g_print("query: %s",temp);
        
            gtk_label_set_text(GTK_LABEL(datos->lres),resultset);
        
        }else{
            
            sprintf(temp,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->numcuenta);
            id = atoi(MySQLreturn(temp));
            
            sprintf(temp,"INSERT INTO pf_busquedas(idUsuario,busqueda,fecha) VALUES(%i,'%s','%s')",id,busqueda,date);
            MySQLexecute_query(temp);
            
            g_print("query: %s",temp);
            
            gtk_label_set_text(GTK_LABEL(datos->lres),"¡Tu búsqueda no arrojó ningún resultado!");
        }
    }
}

void RegistraUsuario(GtkButton *button, gpointer data){
    
    const gchar *c_nombre, *c_appaterno, *c_apmaterno, *c_dia, *c_mes, *c_anio;
    const gchar *c_cuenta, *c_carrera, *c_semestre, *c_correo, *c_contra, *c_confcontra;
    
    char query[1024], fecha[15], check[400];
    int mysql;
    
    St_registra *datos = (St_registra*)data;
    
    c_nombre = gtk_entry_get_text(GTK_ENTRY(datos->tnombre));
    c_appaterno = gtk_entry_get_text(GTK_ENTRY(datos->tappaterno));
    c_apmaterno = gtk_entry_get_text(GTK_ENTRY(datos->tapmaterno));
    c_cuenta = gtk_entry_get_text(GTK_ENTRY(datos->tcuenta));
    c_correo = gtk_entry_get_text(GTK_ENTRY(datos->tcorreo));
    c_contra = gtk_entry_get_text(GTK_ENTRY(datos->tcontra));
    c_confcontra = gtk_entry_get_text(GTK_ENTRY(datos->tconfcontra));
    
    c_dia = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tdia));
    c_mes = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tmes));
    c_anio = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tanio));
    c_carrera = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tcarrera));
    c_semestre = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->tsemestre));
    
    if(c_nombre[0] == '\0' || c_appaterno[0] == '\0' || c_apmaterno[0] == '\0' || c_cuenta[0] == '\0' || c_correo[0] == '\0' || c_contra[0] == '\0' || c_confcontra[0] == '\0' || c_dia == NULL || c_mes == NULL || c_anio == NULL || c_semestre == NULL || c_carrera == NULL){
        
        gtk_label_set_text(GTK_LABEL(datos->linfo),"Para completar el registro, debes de llenar todos los campos.");
    
    }else if(strlen(c_nombre) >= 30 || strlen(c_appaterno) >= 30 || strlen(c_apmaterno) >= 30 || strlen(c_apmaterno) >= 30 || strlen(c_cuenta) >= 10 || strlen(c_correo) >= 30 || strlen(c_contra) >= 30){
        
        gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de ingresar un nombre válido.");
    
    }else{
        
        if(strcmp(c_contra,c_confcontra) != 0){
            
            gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Las contraseñas ingresadas no coinciden!");
            
        }else{
            
            gtk_label_set_text(GTK_LABEL(datos->linfo)," ");
        
            strcpy(datos->nombre,c_nombre);
            strcpy(datos->appaterno,c_appaterno);
            strcpy(datos->apmaterno,c_apmaterno);
            strcpy(datos->cuenta,c_cuenta);
            strcpy(datos->correo,c_correo);
            strcpy(datos->contra,c_confcontra);
            
            strcpy(datos->dia,c_dia);
            strcpy(datos->mes,c_mes);
            strcpy(datos->anio,c_anio);
            strcpy(datos->semestre,c_semestre);
            strcpy(datos->carrera,c_carrera);
            
            sprintf(fecha,"%i-%i-%i",atoi(datos->anio),atoi(datos->mes),atoi(datos->dia));
            sprintf(check,"SELECT * FROM pf_usuarios WHERE numcuenta = '%s'",datos->cuenta);
            
            mysql = MySQLcheck(check);
            
            if(mysql == 0){
                
                sprintf(query,"INSERT INTO pf_usuarios(nombre,appaterno,apmaterno,carrera,semestre,nacimiento,numcuenta,correo,contra,tipo) VALUES('%s','%s','%s','%s',%i,'%s','%s','%s','%s','U')",datos->nombre,datos->appaterno,datos->apmaterno,datos->carrera,atoi(datos->semestre),fecha,datos->cuenta,datos->correo,datos->contra);
                //g_print("%s",query);
                gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Registro completado!");
                MySQLadd(query);
            
            }else{
                
                gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Este usuario ya se encuentra registrado!");
            }
        }
    }
}

void RegresaInicio(GtkButton *button, gpointer data){
    
    St_ingresa *datos = (St_ingresa*)data;
    gtk_widget_destroy(datos->ventana);
    
    InicioSesion();
}

void BuscaTipo(GtkWidget *boton, gpointer data){
    
    const gchar *usuarioclea, *usuario;
    char *resultset;
    char query[125];
    long rs_size;
    St_busca_usuario *datos = (St_busca_usuario*)data;
    
    usuario = gtk_entry_get_text(GTK_ENTRY(datos->tusuario));
    if(usuario[0] == '\0'){
        gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de indicar un tipo de usuario");
    }
    else{
        if((usuario[0]!='A')&&(usuario[0]!='U')){
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de indicar un tipo de usuario valido");
        }
        else{
            sprintf(query,"SELECT nombre, appaterno, apmaterno, carrera, semestre, nacimiento, numcuenta, correo FROM pf_usuarios WHERE tipo = '%s'",usuario);
            rs_size = MySQLget_resultset_size(query);
            g_print("resulset: %li\n",rs_size);
            resultset = malloc(sizeof(char)*(rs_size + 1));
            resultset = MySQLget_user(query);
            resultset[rs_size + 1] = '\0';
            gtk_label_set_text(GTK_LABEL(datos->lres),resultset);
        } 
    }
    
}

void ModificarPerfil(GtkWidget *boton, gpointer data){
    
    const gchar *c_nombre, *c_appaterno, *c_apmaterno, *c_correo, *c_contra, *c_confcontra;
    char query[300];
    
    St_registra *datos = (St_registra*)data;
    
    c_nombre = gtk_entry_get_text(GTK_ENTRY(datos->tnombre));
    c_appaterno = gtk_entry_get_text(GTK_ENTRY(datos->tappaterno));
    c_apmaterno = gtk_entry_get_text(GTK_ENTRY(datos->tapmaterno));
    c_correo = gtk_entry_get_text(GTK_ENTRY(datos->tcorreo));
    c_contra = gtk_entry_get_text(GTK_ENTRY(datos->tcontra));
    c_confcontra = gtk_entry_get_text(GTK_ENTRY(datos->tconfcontra));
    
    if(strcmp(datos->nombre, c_nombre) == 0 && strcmp(datos->appaterno, c_appaterno) == 0 && strcmp(datos->apmaterno, c_apmaterno) == 0 &&
       strcmp(datos->correo, c_correo) == 0 && strcmp(datos->contra, c_contra) == 0 && c_confcontra[0] == '\0'){
        
        gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Nada que cambiar!");
    
    }else if(strcmp(datos->contra, c_contra) == 0 && c_confcontra[0] != '\0'){
        
        gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Las contraseñas no coinciden!");
    
    }else{
        
        if(strcmp(datos->nombre, c_nombre) != 0){
            
            /* Guardamos el nuevo nombre */
            sprintf(query, "UPDATE pf_usuarios SET nombre = '%s' WHERE numcuenta = '%s'",c_nombre,datos->numcuenta);
            strcpy(datos->nombre, c_nombre);
            MySQLexecute_query(query);
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Tus datos han sido actualizados.");
        }
        
        if(strcmp(datos->appaterno, c_appaterno) != 0){
            
            sprintf(query, "UPDATE pf_usuarios SET appaterno = '%s' WHERE numcuenta = '%s'",c_appaterno,datos->numcuenta);
            strcpy(datos->appaterno, c_appaterno);
            MySQLexecute_query(query);
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Tus datos han sido actualizados.");
        }
        
        if(strcmp(datos->apmaterno, c_apmaterno) != 0){
            
            sprintf(query, "UPDATE pf_usuarios SET apmaterno = '%s' WHERE numcuenta = '%s'",c_apmaterno,datos->numcuenta);
            strcpy(datos->apmaterno, c_apmaterno);
            MySQLexecute_query(query);
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Tus datos han sido actualizados.");
        }
        
        if(strcmp(datos->correo, c_correo) != 0){
            
            sprintf(query, "UPDATE pf_usuarios SET correo = '%s' WHERE numcuenta = '%s'",c_correo,datos->numcuenta);
            strcpy(datos->correo, c_correo);
            MySQLexecute_query(query);
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Tus datos han sido actualizados.");
        }
        
        if(strcmp(datos->contra, c_contra) != 0){
            
            if(strcmp(c_contra, c_confcontra) == 0){
                
                sprintf(query, "UPDATE pf_usuarios SET contra = '%s' WHERE numcuenta = '%s'",c_contra,datos->numcuenta);
                strcpy(datos->contra, c_contra);
                MySQLexecute_query(query);
                gtk_label_set_text(GTK_LABEL(datos->linfo),"Tus datos han sido actualizados.");
                gtk_entry_set_text(GTK_ENTRY(datos->tconfcontra),"");
            
            }else{
                
                gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Las contraseñas no coinciden!");
                
            }
        }
    }
}

void BuscaModifica(GtkWidget *boton, gpointer data){
    
    const gchar *c_busca;
    
    char check[300];
    int mysql;
    
    St_registra *datos = (St_registra*)data;
    c_busca = gtk_entry_get_text(GTK_ENTRY(datos->tcuenta));
    
    sprintf(check,"SELECT * FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
    mysql = MySQLcheck(check);
    
    if(mysql == 1){
        
        strcpy(datos->cuenta,c_busca);
        gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Encontrado!");
        gtk_widget_destroy(datos->ventana);
        MiPerfilAdmin(datos);
        
    }else{
        
        gtk_label_set_text(GTK_LABEL(datos->linfo),"¡No se ha podido encontrar este usuario!");
        
    }
}

void AgregaAmigo(GtkWidget *boton, gpointer data){
    
    const gchar *c_busca;
    int mysql, mysql1;
    char query[300],check[300];
    char *idUsuario, *idAmigo;
    int usuario, amigo;
    St_busca_usuario *datos = (St_busca_usuario*)data;
    
    c_busca = gtk_entry_get_text(GTK_ENTRY(datos->tusuario));
    
    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->numcuenta);
    idUsuario = MySQLreturn(query);
    usuario = atoi(idUsuario);
    
    /* Buscamos en la base de datos */
    
    sprintf(check,"SELECT * FROM pf_usuarios WHERE appaterno = '%s'",c_busca);
    mysql = MySQLcheck(check);

    if(c_busca[0] != '\0'){
        
        if(mysql == 0){
        
            sprintf(check,"SELECT * FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
            mysql = MySQLcheck(check);
            
            if(mysql == 0){
               
                gtk_label_set_text(GTK_LABEL(datos->linfo),"No se ha encontrado el usuario.");
             
            }else{
                
                sprintf(query,"SELECT u.numcuenta FROM pf_amigos a, pf_usuarios u WHERE a.idUsuario = %i AND a.idAmigo = u.idUsuario AND u.numcuenta = '%s'",usuario, c_busca);
                mysql1 = MySQLcheck(query);
                //g_print("\n %s \n",query);
                
                if(mysql1 == 0){
                
                    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
                    idAmigo = MySQLreturn(query);
                    amigo = atoi(idAmigo);
                    
                    if(amigo == usuario){
                        
                        gtk_label_set_text(GTK_LABEL(datos->linfo),"No te puedes agregar a ti mismo.");
                     
                    }else{
                        
                        gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Amigo agregado!");
                        sprintf(query,"INSERT INTO pf_amigos(idUsuario, idAmigo) VALUES(%i,%i)",usuario,amigo);
                        MySQLexecute_query(query);
                    } 
                    
                }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Ya son amigos!");}
            }

        }else if(mysql >= 2){
         
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Se han encontrado más de un usuario, favor de usar el número de cuenta.");
  
        }else{
            
            sprintf(query,"SELECT u.numcuenta FROM pf_amigos a, pf_usuarios u WHERE a.idUsuario = %i AND a.idAmigo = u.idUsuario AND u.appaterno = '%s'",usuario, c_busca);
            mysql1 = MySQLcheck(query);
            //g_print("\n %s \n",query);
            
            if(mysql1 == 0){

                sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE appaterno = '%s'",c_busca);
                idAmigo = MySQLreturn(query);
                amigo = atoi(idAmigo);
                    
                if(amigo == usuario){
                        
                    gtk_label_set_text(GTK_LABEL(datos->linfo),"No te puedes agregar a ti mismo.");
                     
                }else{
                        
                    gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Amigo agregado!");
                    sprintf(query,"INSERT INTO pf_amigos(idUsuario, idAmigo) VALUES(%i,%i)",usuario,amigo);
                    MySQLexecute_query(query);
                } 
            
            }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Ya son amigos!");}
        }
        
    }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de llenar el campo.");}     
}

void EliminaAmigo(GtkWidget *boton, gpointer data){
    
    const gchar *c_busca;
    int mysql, mysql1;
    char query[300],check[300];
    char *idUsuario, *idAmigo;
    int usuario, amigo;
    St_busca_usuario *datos = (St_busca_usuario*)data;
    
    c_busca = gtk_entry_get_text(GTK_ENTRY(datos->tusuario));
    
    /* Recibe el id del Usuario ejecutando la operación */
    
    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->numcuenta);
    idUsuario = MySQLreturn(query);
    usuario = atoi(idUsuario);
    
    /* Buscamos en la base de datos */
    
    sprintf(check,"SELECT * FROM pf_usuarios WHERE appaterno = '%s'",c_busca);
    mysql = MySQLcheck(check);

    if(c_busca[0] != '\0'){
        
        /* Busca el usuario en la base de datos por apellido paterno */
        
        if(mysql == 0){
        
            sprintf(check,"SELECT * FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
            mysql = MySQLcheck(check);
            
            if(mysql == 0){
               
                gtk_label_set_text(GTK_LABEL(datos->linfo),"No se ha encontrado el usuario.");
             
            }else{
                
                sprintf(query,"SELECT u.numcuenta FROM pf_amigos a, pf_usuarios u WHERE a.idUsuario = %i AND a.idAmigo = u.idUsuario AND u.numcuenta = '%s'",usuario, c_busca);
                mysql1 = MySQLcheck(query);
                //g_print("\n %s \n",query);
                
                if(mysql1 == 1){
                
                    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
                    idAmigo = MySQLreturn(query);
                    amigo = atoi(idAmigo);

                    gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Amigo eliminado!");
                    sprintf(query,"DELETE FROM pf_amigos WHERE idUsuario = %i AND idAmigo = %i",usuario,amigo);
                    
                    MySQLexecute_query(query);
                    
                }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Este usuario no es tu amigo.");}
            }

        }else if(mysql >= 2){
         
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Se han encontrado más de un usuario, favor de usar el número de cuenta.");
  
        }else{
            
            sprintf(query,"SELECT u.numcuenta FROM pf_amigos a, pf_usuarios u WHERE a.idUsuario = %i AND a.idAmigo = u.idUsuario AND u.appaterno = '%s'",usuario, c_busca);
            mysql1 = MySQLcheck(query);
            
            if(mysql1 == 1){
                
                sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE appaterno = '%s'",c_busca);
                idAmigo = MySQLreturn(query);
                amigo = atoi(idAmigo);
                    
                gtk_label_set_text(GTK_LABEL(datos->linfo),"¡Amigo eliminado!");
                sprintf(query,"DELETE FROM pf_amigos WHERE idUsuario = %i AND idAmigo = %i",usuario,amigo);
                
                MySQLexecute_query(query);
            
            }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Este usuario no es tu amigo.");}
        }
        
    }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de llenar el campo.");}     
}

/* @brief Imprime las búsquedas de los usuarios */

void ImprimeBusquedas(GtkWidget *widget, gpointer data){
    
    const gchar *c_busca;
    int mysql;
    char query[300],check[300];
    int usuario;
    St_busca_usuario *datos = (St_busca_usuario*)data;
    
    c_busca = gtk_entry_get_text(GTK_ENTRY(datos->tusuario));
    
    /* Buscamos en la base de datos */
    
    sprintf(check,"SELECT * FROM pf_usuarios WHERE appaterno = '%s'",c_busca);
    mysql = MySQLcheck(check);

    if(c_busca[0] != '\0'){
        
        /* Busca el usuario en la base de datos por apellido paterno */
        
        if(mysql == 0){
        
            /* Busca el usuario en la base de datos por numero de cuenta */
        
            sprintf(check,"SELECT * FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
            mysql = MySQLcheck(check);
            
            if(mysql == 0){
               
                gtk_label_set_text(GTK_LABEL(datos->linfo),"No se ha encontrado el usuario.");
             
            }else{

                sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
                usuario = atoi(MySQLreturn(query));
                
                sprintf(query,"SELECT * FROM pf_busquedas WHERE idUsuario = %i",usuario);
                mysql = MySQLcheck(query);
                //g_print("query: %s",query);
                
                if(mysql >= 1){
                
                    strcpy(datos->usuario,c_busca);
                    g_print("%s\n",datos->usuario);
                    VentanaBusquedas(datos);
                    
                }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Este usuario no tiene busquedas registradas.");}
            }

        }else if(mysql >= 2){
         
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Se han encontrado más de un usuario, favor de usar el número de cuenta.");
  
        }else{
            
            sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE appaterno = '%s'",c_busca);
            usuario = atoi(MySQLreturn(query));
            
            sprintf(query,"SELECT * FROM pf_busquedas WHERE idUsuario = %i",usuario);
            mysql = MySQLcheck(query);
            
            if(mysql >= 1){
                
                strcpy(datos->usuario,c_busca);
                g_print("%s\n",datos->usuario);
                VentanaBusquedas(datos);
            
            }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Este usuario no tiene busquedas registradas.");}
        }
        
    }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de llenar el campo.");}
}

void VentanaBusquedas(gpointer data){
    
    char *resultset;
    char query[225];
    long rs_size;
    int usuario;
    GtkWidget *ventana, *scroll, *usuarios, *vbox;
    
    St_busca_usuario *datos = (St_busca_usuario*)data;
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Busquedas del usuario");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);
    gtk_widget_set_size_request(ventana, 900, 300);
    
    g_print("usuario %s:\n",datos->usuario);
    
    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->usuario);
    usuario = atoi(MySQLreturn(query));
  
    g_print("query %s:\n",query);
    g_print("usuario %i:\n",usuario);
    
    sprintf(query,"SELECT busqueda, fecha FROM pf_busquedas WHERE idUsuario = %i",usuario);//Obtener las busquedas realizadas, y la fecha en la que se hicieron
    
    rs_size = MySQLget_search_size(query); //Obtener el tamaño del arreglo donde se almacenan las busquedas
    resultset = malloc(sizeof(char)*(rs_size+1));//Alocar suficiente espacio para que quepan todas las busquedas
    resultset = MySQLget_busca(query);
    resultset[rs_size + 1] = '\0';
    usuarios = gtk_label_new(resultset);
    
    g_print("rs_size %li:\n",rs_size);
    
    scroll = gtk_scrolled_window_new(NULL, NULL);

    gtk_container_set_border_width(GTK_CONTAINER(scroll), 5);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll), usuarios);
    
    vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), scroll);
    
    gtk_container_add(GTK_CONTAINER(ventana), vbox);
    gtk_widget_show_all(ventana);
    
    gtk_main();
}

/* @brief Detecta si el radio button con la etiqueta "Para mi" es activaado */

void RadioMio(GtkWidget *radio, gpointer data){
    
    St_comandas *dato = (St_comandas*)data;
    dato->para = 0;
}

void RadioAmigo(GtkWidget *radio, gpointer data){
    
    St_comandas *dato = (St_comandas*)data;
    dato->para = 1;
}

void Comprar(GtkButton *boton, gpointer data){
    
    const gchar *carrito;
    St_comandas *dato = (St_comandas*)data;
    char query[300];
    int check, id;
    
    carrito = gtk_label_get_text(GTK_LABEL(dato->carrito));
    
    if(strcmp(carrito, " ") != 0){
    
        for(int i = 0 ; i < dato->pedido ; i++){
        
            sprintf(query,"SELECT precio FROM pf_menu WHERE idElemento = %i", dato->pedidos[i]);
            dato->total = dato->total  + atoi(MySQLreturn(query));
        }
        
        if(dato->para == 0){
            
            ConfirmaCompra(dato);
            
        }else if(dato->para == 1){
            
            g_print("Cuenta %s\n",dato->numcuenta);
            
            sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",dato->numcuenta);
            id = atoi(MySQLreturn(query));
            
            sprintf(query, "SELECT idAmigo FROM pf_amigos WHERE idUsuario = %i",id);
            check = MySQLcheck(query);
            
            if(check != 0){
                
                InvitaAmigos(dato);
                g_print("Para amigo");
            
            }else{
                
                g_print("No hay amigos");
            }
        }
        
        gtk_label_set_text(GTK_LABEL(dato->carrito)," ");
        dato->total = 0;
        dato->pedido = 0;
    
    }else{g_print("No hay nada");}
}

void AnadirCarrito(GtkButton *boton, gpointer data){
    
    const gchar *combocomida, *combobebida, *carrito, *c_carro;
    St_comandas *dato = (St_comandas*)data;
    char carro[1700], ecarro[1700], producto[40], query[300];
    int algo = 0;
    int ID;
    
    combocomida = gtk_combo_box_get_active_text(GTK_COMBO_BOX(dato->comida));
    combobebida = gtk_combo_box_get_active_text(GTK_COMBO_BOX(dato->bebida));
    carrito = gtk_label_get_text(GTK_LABEL(dato->carrito));
    
    /* No hay cosas en el carrito */
    
    if(dato->pedido < 29){
    
        if(strcmp(carrito," ") == 0){
            
            /* No hubo cosas en combocomida */
            
            if(combocomida != NULL && algo == 0 && strcmp(combocomida, " ") != 0){
                
                sprintf(carro,"%s",combocomida);
                strcat(carro,"\n");
                algo = 1;
                
                sscanf(combocomida,"%[^$]",producto);
                producto[strlen(producto)-1] = '\0';
                
                sprintf(query,"SELECT idElemento FROM pf_menu WHERE nombre = '%s'",producto);
                ID = atoi(MySQLreturn(query));
                
                dato->pedidos[dato->pedido] = ID;
                dato->pedido = (dato->pedido) + 1;
            }
            
            if(combobebida != NULL && algo == 0){
                
                sprintf(carro,"%s",combobebida);
                strcat(carro,"\n");
                algo = 1;
                
                sscanf(combobebida,"%[^$]",producto);
                producto[strlen(producto)-1] = '\0';
                
                sprintf(query,"SELECT idElemento FROM pf_menu WHERE nombre = '%s'",producto);
                ID = atoi(MySQLreturn(query));
                
                dato->pedidos[dato->pedido] = ID;
                dato->pedido = (dato->pedido) + 1;
            
            }else if(combobebida != NULL && algo == 1  && strcmp(combobebida, " ") != 0){
                
                strcat(carro,combobebida);
                strcat(carro,"\n");
                
                sscanf(combobebida,"%[^$]",producto);
                producto[strlen(producto)-1] = '\0';
                
                sprintf(query,"SELECT idElemento FROM pf_menu WHERE nombre = '%s'",producto);
                ID = atoi(MySQLreturn(query));
                
                dato->pedidos[dato->pedido] = ID;
                dato->pedido = (dato->pedido) + 1;
            }
            
            gtk_label_set_text(GTK_LABEL(dato->carrito),carro);
            
        }else if(strcmp(carrito," ") != 0){
            
            c_carro = gtk_label_get_text(GTK_LABEL(dato->carrito));
            sprintf(ecarro,"%s",c_carro);
            
            if(combocomida != NULL && strcmp(combocomida, " ") != 0){
                
                strcat(ecarro,combocomida);
                strcat(ecarro,"\n");
                
                sscanf(combocomida,"%[^$]",producto);
                producto[strlen(producto)-1] = '\0';
                
                sprintf(query,"SELECT idElemento FROM pf_menu WHERE nombre = '%s'",producto);
                ID = atoi(MySQLreturn(query));
                
                dato->pedidos[dato->pedido] = ID;
                dato->pedido = (dato->pedido) + 1;
            }
            
            if(combobebida != NULL && strcmp(combobebida, " ") != 0){
                
                strcat(ecarro,combobebida);
                strcat(ecarro,"\n");
                
                sscanf(combobebida,"%[^$]",producto);
                producto[strlen(producto)-1] = '\0';
                
                sprintf(query,"SELECT idElemento FROM pf_menu WHERE nombre = '%s'",producto);
                ID = atoi(MySQLreturn(query));
                
                dato->pedidos[dato->pedido] = ID;
                dato->pedido = (dato->pedido) + 1;
            }
            
            gtk_label_set_text(GTK_LABEL(dato->carrito),ecarro);  
        }
    }
}

void VaciarCarrito(GtkButton *boton, gpointer data){
    
    St_comandas *dato = (St_comandas*)data;
    
    gtk_label_set_text(GTK_LABEL(dato->carrito)," ");
    dato->pedido = 0;
    dato->total = 0;
}

void Regresar(GtkButton *boton, gpointer data){
    
    St_comandas *dato = (St_comandas*)data;
    
    dato->pedido = 0;
    dato->total = 0;
    gtk_widget_destroy(dato->ventana);
}

/* @brief Esta función permite registrar las compras propias en la base de datos */

void RegistrarCompra(GtkButton *boton, gpointer data){
    
    St_comandas *dato = (St_comandas*)data;
    char query[300], *tipo, fecha[11];
    int id;
    
    time_t t = time(NULL);
    struct tm *tiempolocal = localtime(&t);
    strftime(fecha,11,"%Y-%m-%d",tiempolocal);
    
    g_print("Usuario: %s",dato->numcuenta);
    
    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",dato->numcuenta);
    id = atoi(MySQLreturn(query));
    
    sprintf(query,"SELECT tipo FROM pf_usuarios WHERE numcuenta = '%s'",dato->numcuenta);
    tipo = MySQLreturn(query);
        
    for(int i = 0 ; i < dato->pedido ; i++){
        
        sprintf(query,"INSERT INTO pf_comandas(idUsuario,tipoUsuario,orden,fecha,tipoOrden) VALUES(%i,'%s',%i,'%s','Propia')",id,tipo,dato->pedidos[i],fecha);
        MySQLexecute_query(query);
    }
    
    g_print("fuera\n");
    dato->pedido = 0;
    dato->total = 0;
    gtk_label_set_text(GTK_LABEL(dato->carrito)," ");
    gtk_widget_destroy(dato->ventana);
}

/* @brief Esta función registra la compra para un amigo en la base de datos */

void RegistrarCompraAmigos(GtkButton *boton, gpointer data){
    
    St_comandas *dato = (St_comandas*)data;
    const gchar *amigo;
    char query[300],query2[300], *tipo, ctipo[2], fecha[11], numcuentamigo[9];
    int id, idamigo;
    
    time_t t = time(NULL);
    struct tm *tiempolocal = localtime(&t);
    strftime(fecha,11,"%Y-%m-%d",tiempolocal);
    
    amigo = gtk_combo_box_get_active_text(GTK_COMBO_BOX(dato->comboamigo));
    
    if(amigo != NULL){
    
        sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",dato->numcuenta);
        id = atoi(MySQLreturn(query));
        
        sprintf(query2,"SELECT tipo FROM pf_usuarios WHERE numcuenta = '%s'",dato->numcuenta);
        tipo = MySQLreturn(query2);
        strcpy(ctipo,tipo);
        
        sscanf(amigo,"%[^ ]",numcuentamigo);
        
        sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",numcuentamigo);
        idamigo = atoi(MySQLreturn(query));
        
        for(int i = 0 ; i < dato->pedido ; i++){
    
            sprintf(query,"INSERT INTO pf_comandas(idUsuario,tipoUsuario,orden,fecha,tipoOrden,idAmigo) VALUES(%i,'%s',%i,'%s','Amigo',%i)",id,ctipo,dato->pedidos[i],fecha,idamigo);
            MySQLexecute_query(query);
        }
        
        gtk_widget_destroy(dato->ventana);
    }
}

/* @brief Imprime en una etiqueta el consumo del mes solicitado por el usuario */

void ConsumoMes(GtkButton *boton, gpointer data){
    
    const gchar *mes;
    char query[300], cdelmes[100];
    int id, mysql, fecha;
    float cmes;
    St_comandas *datos = (St_comandas*) data;
    
    mes = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->comboamigo));
    
    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->numcuenta);
    id = atoi(MySQLreturn(query));
    
    if(mes != NULL){
        
        sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->numcuenta);
        id = atoi(MySQLreturn(query));
        
        if(strcmp(mes,"Enero") == 0){fecha = 1;}
        if(strcmp(mes,"Febrero") == 0){fecha = 2;}
        if(strcmp(mes,"Marzo") == 0){fecha = 3;}
        if(strcmp(mes,"Abril") == 0){fecha = 4;}
        if(strcmp(mes,"Mayo") == 0){fecha = 5;}
        if(strcmp(mes,"Junio") == 0){fecha = 6;}
        if(strcmp(mes,"Julio") == 0){fecha = 7;}
        if(strcmp(mes,"Agosto") == 0){fecha = 8;}
        if(strcmp(mes,"Septiembre") == 0){fecha = 9;}
        if(strcmp(mes,"Octubre") == 0){fecha = 10;}
        if(strcmp(mes,"Noviembre") == 0){fecha = 11;}
        if(strcmp(mes,"Diciembre") == 0){fecha = 12;}
        
        sprintf(query,"SELECT m.precio FROM pf_comandas c, pf_menu m WHERE idUsuario = %i AND c.orden = m.idElemento AND EXTRACT(MONTH FROM c.fecha) = %i",id,fecha);
        mysql = MySQLcheck(query);
        
        g_print("mysql %i:\n",mysql);
        
        if(mysql != 0){
            
            sprintf(query,"SELECT SUM(m.precio) FROM pf_comandas c, pf_menu m WHERE idUsuario = %i AND c.orden = m.idElemento AND EXTRACT(MONTH FROM c.fecha) = %i",id,fecha);
            cmes = atof(MySQLreturn(query));
            sprintf(cdelmes,"Consumo del mes de %s: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",mes,cmes, cmes*0.2, cmes*0.8);
            gtk_label_set_text(GTK_LABEL(datos->linfo),cdelmes);
            
        }else if(mysql == 0){

            gtk_label_set_text(GTK_LABEL(datos->linfo),"No hubo ningún consumo en el mes seleccionado.");}
        
    }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de seleccionar un mes.");}
}

/* @brief Esta función busca la información del consumo de un usuario en específico en un mes en específico */

void ConsumoMesUsuario(GtkButton *boton, gpointer data){
    
    const gchar *c_busca, *c_mes;
    int mysql;
    char query[300],check[300], cdelmes[100];
    int amigo, fecha;
    float cmes;
    St_comandas *datos = (St_comandas*)data;
    
    c_busca = gtk_entry_get_text(GTK_ENTRY(datos->tusuario));
    
    /* Recibe el id del Usuario ejecutando la operación */
    
    /*sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->numcuenta);
    idUsuario = MySQLreturn(query);
    usuario = atoi(idUsuario);*/
    
    /* Buscamos en la base de datos */
    
    sprintf(check,"SELECT * FROM pf_usuarios WHERE appaterno = '%s'",c_busca);
    mysql = MySQLcheck(check);

    if(c_busca[0] != '\0'){
        
        /* Busca el usuario en la base de datos por apellido paterno */
        
        if(mysql == 0){
            
            /* Si no lo encuentra, busca por número de cuenta */
        
            sprintf(check,"SELECT * FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
            mysql = MySQLcheck(check);
            
            if(mysql == 0){
               
                gtk_label_set_text(GTK_LABEL(datos->linfo),"No se ha encontrado el usuario.");
             
            }else{
                
                /* Recibir el mes del que se desea obtener el consumo */
                
                c_mes = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->comboamigo));
                
                if(c_mes != NULL){
                
                    if(strcmp(c_mes,"Enero") == 0){fecha = 1;}
                    if(strcmp(c_mes,"Febrero") == 0){fecha = 2;}
                    if(strcmp(c_mes,"Marzo") == 0){fecha = 3;}
                    if(strcmp(c_mes,"Abril") == 0){fecha = 4;}
                    if(strcmp(c_mes,"Mayo") == 0){fecha = 5;}
                    if(strcmp(c_mes,"Junio") == 0){fecha = 6;}
                    if(strcmp(c_mes,"Julio") == 0){fecha = 7;}
                    if(strcmp(c_mes,"Agosto") == 0){fecha = 8;}
                    if(strcmp(c_mes,"Septiembre") == 0){fecha = 9;}
                    if(strcmp(c_mes,"Octubre") == 0){fecha = 10;}
                    if(strcmp(c_mes,"Noviembre") == 0){fecha = 11;}
                    if(strcmp(c_mes,"Diciembre") == 0){fecha = 12;}
                    
                    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",c_busca);
                    amigo = atoi(MySQLreturn(query));
                    
                    sprintf(query,"SELECT m.precio FROM pf_comandas c, pf_menu m WHERE idUsuario = %i AND c.orden = m.idElemento AND EXTRACT(MONTH FROM c.fecha) = %i",amigo,fecha);
                    mysql = MySQLcheck(query);
                    
                    g_print("%s\n",query);
  
                    if(mysql >= 1){
                    
                        sprintf(query,"SELECT SUM(m.precio) FROM pf_comandas c, pf_menu m WHERE idUsuario = %i AND c.orden = m.idElemento AND EXTRACT(MONTH FROM c.fecha) = %i",amigo,fecha);
                        cmes = atof(MySQLreturn(query));
                        sprintf(cdelmes,"Consumo del mes de %s: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",c_mes,cmes, cmes*0.2, cmes*0.8);
                        gtk_label_set_text(GTK_LABEL(datos->linfo),cdelmes);
                        
                    }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"No se ha encontrado información.");}
                
                }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de seleccionar un mes.");}
            }

        }else if(mysql >= 2){
         
            gtk_label_set_text(GTK_LABEL(datos->linfo),"Se han encontrado más de un usuario, favor de usar el número de cuenta.");
  
        }else{
            
            c_mes = gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->comboamigo));
                
            if(c_mes != NULL){
                
                if(strcmp(c_mes,"Enero") == 0){fecha = 1;}
                if(strcmp(c_mes,"Febrero") == 0){fecha = 2;}
                if(strcmp(c_mes,"Marzo") == 0){fecha = 3;}
                if(strcmp(c_mes,"Abril") == 0){fecha = 4;}
                if(strcmp(c_mes,"Mayo") == 0){fecha = 5;}
                if(strcmp(c_mes,"Junio") == 0){fecha = 6;}
                if(strcmp(c_mes,"Julio") == 0){fecha = 7;}
                if(strcmp(c_mes,"Agosto") == 0){fecha = 8;}
                if(strcmp(c_mes,"Septiembre") == 0){fecha = 9;}
                if(strcmp(c_mes,"Octubre") == 0){fecha = 10;}
                if(strcmp(c_mes,"Noviembre") == 0){fecha = 11;}
                if(strcmp(c_mes,"Diciembre") == 0){fecha = 12;}
                    
                sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE appaterno = '%s'",c_busca);
                amigo = atoi(MySQLreturn(query));
                
                sprintf(query,"SELECT m.precio FROM pf_comandas c, pf_menu m WHERE idUsuario = %i AND c.orden = m.idElemento AND EXTRACT(MONTH FROM c.fecha) = %i",amigo,fecha);
                mysql = MySQLcheck(query);
  
                if(mysql >= 1){
                    
                    sprintf(query,"SELECT SUM(m.precio) FROM pf_comandas c, pf_menu m WHERE idUsuario = %i AND c.orden = m.idElemento AND EXTRACT(MONTH FROM c.fecha) = %i",amigo,fecha);
                    cmes = atof(MySQLreturn(query));
                    sprintf(cdelmes,"Consumo del mes de %s: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",c_mes,cmes, cmes*0.2, cmes*0.8);
                    gtk_label_set_text(GTK_LABEL(datos->linfo),cdelmes);
                        
                }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"No se ha encontrado información.");}
                
            }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de seleccionar un mes.");}
        }
        
    }else{gtk_label_set_text(GTK_LABEL(datos->linfo),"Favor de llenar el campo.");} 
}
