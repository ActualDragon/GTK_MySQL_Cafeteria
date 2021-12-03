#include <stdio.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include <time.h>
#include <stdint.h>
#include <string.h> 

#include "gtkFunc.h"
#include "bdStructs_Funcs.h"
#include "mysql.h" 
 
int InicioSesion(void); //Pantalla donde se puede ingresar como usuario, administrador o invitado
int RegistroUsuario(GtkWidget *boton, gpointer data); //Registrar un nuevo usuario
int MenuAdmin(gpointer data); //Ventana hogar para el administrador
int MenuUsuario(gpointer data); //Ventana hogar para el usuario normal
int MenuInvitado(GtkWidget *boton, gpointer data); //Ventana hogar para el usuario invitado
int ModificarMenu(GtkWidget *widget, gpointer data); //El administrador modifica el menu
int VAgregarElemento(GtkWidget *boton, gpointer data); //El administrador puede agregar un elemento al menu
int VEliminarElemento(GtkWidget *boton, gpointer data); //El administrador puede eliminar un elemento del menu
int VModificarUsuario(GtkWidget *boton, gpointer data); //El administrador puede modificar el perfil de cualquier usuario
int VBuscarUsuario(GtkWidget *boton, gpointer data); //Busqueda de usuarios por apellido, cuenta, carrera, etc
int MiPerfil(GtkWidget *boton, gpointer data); //El usuario puede ver su perfil
int MiPerfilAdmin(gpointer data); //El administrador puede ver su perfil
int AdminBusca(GtkWidget *boton, gpointer data); //El administrdor puede buscar usuarios por tipo de usuario
int ModificaPerfil(GtkWidget *boton, gpointer data); //El usuario puede modificar su perfil
int Amigos(GtkWidget *widget, gpointer data); //Ventana que le pregunta al usuario si quiere agregar o eliminar amigos
int VAgregarAmigo(GtkWidget *widget, gpointer data); //El usuario puede agregar un amigo
int VEliminarAmigo(GtkWidget *widget, gpointer data); //El usuario puede eliminar un amigo
int VTodosLosUsuarios(GtkWidget *boton, gpointer data); //Ver todos los usuarios registrados en la base de datos
int MisAmigos(GtkWidget *widget, gpointer data); //El usuario puede ver su lista de amigos
int InvitaAmigos(gpointer data); //El usuario le puede invitar algun elemento del menu a un amigo
int VerBusquedas(GtkWidget *widget, gpointer data); //El administrador puede ver todas las busquedas que realizó un usuario
int ConfirmaCompra(gpointer data); //Ventana que le pregunta al usuario si está seguro de su compra
int MiConsumo(GtkWidget *widget, gpointer data); //Despliega el consumo del usuario
int ConsumoUsuarios(GtkWidget *widget, gpointer data);

int main(int argc, char *argv[]){

    gtk_init(&argc,&argv);
    InicioSesion();

    return 0;
}

/* @brief Esta función esta diseñada para mostrar la ventana de inicio de sesión del usuario o administrador del sistema, presenta dos entryboxes
 * una para el usuario y otra para la contraseña del mismo.
 * Además permite hacer el registro de un nuevo usuario o bien ingresar al sistema siendo un usuario invitado */

int InicioSesion(void){
    //Declaración de variables
    GtkWidget *window;
    GtkWidget *hboxex, *hboxex1, *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5;
    GtkWidget *vbox;
    GtkWidget *lusuario, *lcontra, *tusuario, *tcontra;
    GtkWidget *bingresa, *bregistra, *binvitado;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacioex, *espacioex0, *espacioex1, *espacioex2;
    GtkWidget *linfo;

    GtkWidget *textbienvenida, *espaciotext0, *espaciotext1;

    GdkColor colorventana, coloretiquetas, colorboton;

    PangoFontDescription *fuente;
    GtkTextBuffer *buffer;
    
    St_ingresa ingreso;

    //Creación de la ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    ingreso.ventana = window;
    
    gdk_color_parse("#ff3e3e",&colorventana);
    gdk_color_parse("#ffffff",&coloretiquetas);
    gdk_color_parse("#e9e9e9",&colorboton);

    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window),"Proyecto Final");
    gtk_signal_connect(GTK_OBJECT(window),"destroy", G_CALLBACK(destroy), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL,&colorventana);

    /* Creación de labels, entryboxes, espacios y botones */
    lusuario = gtk_label_new("Usuario: ");
    lcontra = gtk_label_new("Contraseña: ");
    linfo = gtk_label_new(" ");
    ingreso.linfo = linfo; 

    gtk_widget_modify_fg(GTK_WIDGET(lusuario),GTK_STATE_NORMAL,&coloretiquetas);
    gtk_widget_modify_fg(GTK_WIDGET(lcontra),GTK_STATE_NORMAL,&coloretiquetas);

    tusuario = gtk_entry_new();
    tcontra = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(tcontra), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(tcontra),'*');

    ingreso.tusuario = tusuario;
    ingreso.tcontra = tcontra;

    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacioex = gtk_label_new(" ");
    espacioex0 = gtk_label_new(" ");
    espacioex1 = gtk_label_new(" ");
    espacioex2 = gtk_label_new(" ");

    espaciotext0 = gtk_label_new(" ");
    espaciotext1 = gtk_label_new(" ");
    
    //Botones de la pantalla de inicio
    bingresa = add_button("Ingresar", RecibeUsuario, &ingreso);
    gtk_widget_modify_fg(GTK_WIDGET(bingresa),GTK_STATE_NORMAL,&colorboton);
    gtk_widget_modify_fg(GTK_WIDGET(bingresa),GTK_STATE_ACTIVE,&colorboton);
    bregistra = add_button("Registrarse", RegistroUsuario, &ingreso);
    gtk_widget_modify_fg(GTK_WIDGET(bregistra),GTK_STATE_NORMAL,&colorboton);
    gtk_widget_modify_fg(GTK_WIDGET(bregistra),GTK_STATE_ACTIVE,&colorboton);
    binvitado = add_button("Usuario invitado", MenuInvitado, &ingreso);
    gtk_widget_modify_fg(GTK_WIDGET(binvitado),GTK_STATE_NORMAL,&colorboton);
    gtk_widget_modify_fg(GTK_WIDGET(binvitado),GTK_STATE_ACTIVE,&colorboton);

    /* Text view de bienvenida */
    fuente = pango_font_description_from_string("Monospace Bold 20");
    textbienvenida = gtk_text_view_new();
    gtk_widget_modify_font(textbienvenida,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textbienvenida),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textbienvenida));
    gtk_text_buffer_set_text(buffer," ¡Bienvenido! ",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textbienvenida),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textbienvenida),FALSE);
    
    //gtk_entry_set_text(GTK_ENTRY(tusuario),"209275-1");
    //gtk_entry_set_text(GTK_ENTRY(tcontra),"Toques14");

    /* Creación de cajas */
    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(TRUE,5);
    hbox2 = gtk_hbox_new(TRUE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    hbox5 = gtk_hbox_new(FALSE,5);

    hboxex = gtk_hbox_new(FALSE,5);
    hboxex1 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);

    /* Empaquetado */
    gtk_box_pack_start_defaults(GTK_BOX(hboxex), espacioex);

    gtk_box_pack_start_defaults(GTK_BOX(hbox0), espaciotext0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox0), textbienvenida);
    gtk_box_pack_start_defaults(GTK_BOX(hbox0), espaciotext1);

    gtk_box_pack_start_defaults(GTK_BOX(hboxex1), espacioex2);

    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lusuario);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tusuario);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2), lcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2), tcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), bingresa);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), espacio1);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacioex0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), linfo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacioex1);

    gtk_box_pack_start_defaults(GTK_BOX(hbox5), bregistra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), binvitado);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxex);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxex1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

/* @brief Esta función despliega una ventana que permite registrar a un usuario nuevo, pidiendo todos los datos para ser necesario el registro,
 * el nombre, los apellidos, fecha de nacimiento, semestre, carrera, correo electrónico y carrera */

int RegistroUsuario(GtkWidget *boton, gpointer data){

    //Declaración de variables
    GtkWidget *ventana;
    GtkWidget *lnombre, *lappaterno, *lapmaterno, *lcarrera, *lsemestre, *lnac, *lcuenta, *lcorreo, *lcontra, *lconfcontra;
    GtkWidget *tnombre, *tappaterno, *tapmaterno, *tcarrera, *tsemestre, *tcuenta, *tcorreo, *tcontra, *tconfcontra;
    GtkWidget *ldia, *lmes, *lanio, *tdia, *tmes, *tanio;

    GtkWidget *hboxe, *hboxt, *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5, *hbox6, *hbox7;
    GtkWidget *hboxaux, *hboxaux1, *hboxaux2, *hboxaux3, *hboxaux4;
    GtkWidget *vbox;
    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6, *espacio7, *espacio8, *espacio9;
    GtkWidget *espacio10, *espacio11, *espacio12, *espacio13, *espacio14, *espacio15, *espacio16, *espacio17, *espacio18;
    GtkWidget *espacioe, *espaciot1, *espaciot2, *espacioaux, *espacioaux1, *espacioaux2;
    GtkWidget *espacioaux3, *espacioaux4, *linfo;
    GtkWidget *textview;

    GtkWidget *bregistrar, *bregresa;
    
    GdkColor colorventana, coloretiquetas, colorboton;
    
    gdk_color_parse("#f99090",&colorventana);
    gdk_color_parse("#ffffff",&coloretiquetas);
    gdk_color_parse("#e9e9e9",&colorboton);

    char combo_number[5];
    char *carreras[36] = {"Actuaria","Administracion de empresas","Administracion de la hospitalidad","Administracion de negocios internacionales"
                        ,"Arquitectura","Ciencias teologicas","Comunicacion","Contaduria","Ciencias politicas","Derecho","Diseño grafico"
                        ,"Diseño de indumentaria y moda","Diseño industrial","Diseño interactivo","Diseño textil","Economia","Filosofia","Finanzas"
                        ,"Historia del arte","Historia","Ingenieria de alimentos","Ingenieria biomedica","Ingenieria civil","Ingenieria fisica"
                        ,"Ingenieria industrial","Ingenieria mecanica","Ingenieria mecatronica","Ingenieria quimica","Ingenieria en telecomunicaciones",
                        "Literatura","Mercadotecnia","Nutricion","Pedagogia","Psicologia","Relaciones internacionales","Sustentabilidad ambiental"};

    St_ingresa *datos = (St_ingresa*) data;
    St_registra registro;
    St_ingresa regresa;

    PangoFontDescription *fuente;
    GtkTextBuffer *buffer;

    gtk_widget_destroy(datos->ventana);

    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(ventana), "Registro de usuario");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);
    gtk_widget_modify_bg(GTK_WIDGET(ventana),GTK_STATE_NORMAL,&colorventana);

    /* Declaración de un textview para el título */
    fuente = pango_font_description_from_string("Monospace Bold 20");
    textview = gtk_text_view_new();
    gtk_widget_modify_font(textview,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textview),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
    gtk_text_buffer_set_text(buffer,"- REGISTRO DE USUARIO -",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview),FALSE);

    /* Otras etiquetas */
    lnombre = gtk_label_new("Nombre: ");
    lappaterno = gtk_label_new("Apellido paterno: ");
    lapmaterno = gtk_label_new("Apellido materno: ");
    lcarrera = gtk_label_new("Carrera: ");
    lsemestre = gtk_label_new("Semestre: ");
    lnac = gtk_label_new("- Fecha de nacimiento -");
    ldia = gtk_label_new("Dia: ");
    lmes = gtk_label_new("Mes: ");
    lanio = gtk_label_new("Año: ");
    lcuenta = gtk_label_new("Cuenta: ");
    lcorreo = gtk_label_new("Correo: ");
    lcontra = gtk_label_new("Contraseña: ");
    lconfcontra = gtk_label_new("Confirmar contraseña: ");

    tnombre = gtk_entry_new();
    registro.tnombre = tnombre;
    tappaterno = gtk_entry_new();
    registro.tappaterno = tappaterno;
    tapmaterno = gtk_entry_new();
    registro.tapmaterno = tapmaterno;
    tcuenta = gtk_entry_new();
    registro.tcuenta = tcuenta;
    tcorreo = gtk_entry_new();
    registro.tcorreo = tcorreo;
    tcontra = gtk_entry_new();
    registro.tcontra = tcontra;
    tconfcontra = gtk_entry_new();
    registro.tconfcontra = tconfcontra;

    gtk_entry_set_visibility(GTK_ENTRY(tcontra), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(tcontra),'*');
    gtk_entry_set_visibility(GTK_ENTRY(tconfcontra), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(tconfcontra),'*');

    tcarrera = gtk_combo_box_new_text();
    registro.tcarrera = tcarrera;
    gtk_widget_modify_bg(GTK_WIDGET(tcarrera),GTK_STATE_NORMAL,&colorboton);
    tdia = gtk_combo_box_new_text();
    registro.tdia = tdia;
    gtk_widget_modify_bg(GTK_WIDGET(tdia),GTK_STATE_NORMAL,&colorboton);
    tmes = gtk_combo_box_new_text();
    registro.tmes = tmes;
    gtk_widget_modify_bg(GTK_WIDGET(tmes),GTK_STATE_NORMAL,&colorboton);
    tanio = gtk_combo_box_new_text();
    registro.tanio = tanio;
    gtk_widget_modify_bg(GTK_WIDGET(tanio),GTK_STATE_NORMAL,&colorboton);
    tsemestre = gtk_combo_box_new_text();
    registro.tsemestre = tsemestre;
    gtk_widget_modify_bg(GTK_WIDGET(tsemestre),GTK_STATE_NORMAL,&colorboton);

    /* Combo boxes */
    for(int i = 0 ; i < 36 ; i++){

        gtk_combo_box_append_text(GTK_COMBO_BOX(tcarrera),carreras[i]);

    }

    for(int i = 1 ; i <= 15 ; i++){

        sprintf(combo_number,"%i",i);
        gtk_combo_box_append_text(GTK_COMBO_BOX(tsemestre),combo_number);
    }

    for(int i = 1 ; i <= 31 ; i++){

        sprintf(combo_number,"%i",i);
        gtk_combo_box_append_text(GTK_COMBO_BOX(tdia),combo_number);
    }

    for(int i = 1 ; i <= 12 ; i++){

        sprintf(combo_number,"%i",i);
        gtk_combo_box_append_text(GTK_COMBO_BOX(tmes),combo_number);
    }

    for(int i = 2015 ; i >= 1921 ; i--){

        sprintf(combo_number,"%i",i);
        gtk_combo_box_append_text(GTK_COMBO_BOX(tanio),combo_number);
    }

    //Creación de espacios y cajas
    hboxe = gtk_hbox_new(FALSE,1);
    hboxt = gtk_hbox_new(FALSE,1);
    hbox0 = gtk_hbox_new(FALSE,1);
    hbox1 = gtk_hbox_new(FALSE,1);
    hbox2 = gtk_hbox_new(FALSE,1);
    hbox3 = gtk_hbox_new(FALSE,1);
    hbox4 = gtk_hbox_new(FALSE,1);
    hbox5 = gtk_hbox_new(FALSE,1);
    hbox6 = gtk_hbox_new(FALSE,1);
    hbox7 = gtk_hbox_new(FALSE,1);

    hboxaux = gtk_hbox_new(FALSE,1);
    hboxaux1 = gtk_hbox_new(FALSE,1);
    hboxaux2 = gtk_hbox_new(FALSE,1);
    hboxaux3 = gtk_hbox_new(FALSE,1);
    hboxaux4 = gtk_hbox_new(FALSE,1);

    vbox = gtk_vbox_new(TRUE,1);

    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new("      ");
    espacio2 = gtk_label_new("      ");
    espacio3 = gtk_label_new("      ");
    espacio4 = gtk_label_new("      ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio7 = gtk_label_new(" ");
    espacio8 = gtk_label_new(" ");
    espacio9 = gtk_label_new(" ");
    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");
    espacio12 = gtk_label_new(" ");
    espacio13 = gtk_label_new(" ");
    espacio14 = gtk_label_new(" ");
    espacio15 = gtk_label_new(" ");
    espacio16 = gtk_label_new(" ");
    espacio17 = gtk_label_new(" ");
    espacio18 = gtk_label_new(" ");

    espacioe = gtk_label_new(" ");
    espaciot1 = gtk_label_new(" ");
    espaciot2 = gtk_label_new(" ");

    espacioaux = gtk_label_new(" ");
    espacioaux1 = gtk_label_new(" ");
    espacioaux2 = gtk_label_new(" ");
    espacioaux3 = gtk_label_new(" ");
    espacioaux4 = gtk_label_new(" ");

    linfo = gtk_label_new(" ");
    registro.linfo = linfo;

    bregistrar = add_button("Registrarse",RegistraUsuario,&registro);
    bregresa = add_button("Regresar", RegresaInicio, &regresa);
    gtk_widget_modify_bg(GTK_WIDGET(bregistrar),GTK_STATE_NORMAL,&colorboton);
    gtk_widget_modify_bg(GTK_WIDGET(bregistrar),GTK_STATE_ACTIVE,&colorboton);
    gtk_widget_modify_bg(GTK_WIDGET(bregresa),GTK_STATE_NORMAL,&colorboton);
    gtk_widget_modify_bg(GTK_WIDGET(bregresa),GTK_STATE_ACTIVE,&colorboton);
    regresa.ventana = ventana;

    /* Rellenando cajas */

    gtk_box_pack_start_defaults(GTK_BOX(hboxe), espacioe);

    gtk_box_pack_start_defaults(GTK_BOX(hboxt), espaciot1);
    gtk_box_pack_start_defaults(GTK_BOX(hboxt), textview);
    gtk_box_pack_start_defaults(GTK_BOX(hboxt), espaciot2);

    gtk_box_pack_start_defaults(GTK_BOX(hbox0), espacio0);

    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lnombre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tnombre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lappaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tappaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lapmaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tapmaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio4);

    gtk_box_pack_start_defaults(GTK_BOX(hbox2), espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(hbox3), lnac);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux), espacioaux);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacio6);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), ldia);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), tdia);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacio7);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), lmes);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), tmes);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacio8);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), lanio);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), tanio);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacio9);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux1), espacioaux1);

    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lcuenta);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tcuenta);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio11);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lcarrera);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tcarrera);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio12);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lsemestre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tsemestre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio13);

    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio14);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lcorreo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tcorreo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio15);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio16);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lconfcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tconfcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio17);

    gtk_box_pack_start_defaults(GTK_BOX(hbox7), espacio18);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), espacioaux2);
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), bregistrar);
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), bregresa);
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), espacioaux3);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux3), espacioaux4);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux4), linfo);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxe);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxt);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox6);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox7);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux4);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);

    gtk_main();

    return 0;
}

/* @brief Despliega una ventana que muestra todas las opciones de las que dispone un administrador, modificar el menú, busca usuarios por diferentes criterios,
 * consultar el gasto que realizan los usuarios, modificar su perfil o bien modificar el perfil de otros usuarios */

int MenuAdmin(gpointer data){

    //Declaración de variables
    GtkWidget *ventana;
    GtkWidget *barra, *bmopciones, *bmadmin, *musuarios, *mopciones, *mbuscar, *mtodos, *mmenu, *mmodificar, *mperfil, *msalir, *miconsumo;
    GtkWidget *bmventas, *bmmenu, *bmusuarios, *mconsumo, *mamigos, *mmisamigos, *magamigos, *bmamigos, *madmin, *madbusca, *madbusquedas;
    GtkWidget *lbienvenido, *mumodificar;

    GtkWidget *comboalimentos, *combobebidas, *bagregar, *bcomprar, *textalimentos, *textbebidas, *textcarrito;
    GtkWidget *llista, *blimpiar;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5, *hbox6, *hbox7, *hbox8, *hbox9;
    GtkWidget *hbox10, *hbox11, *hbox12, *hbox13, *hbox14;
    GtkWidget *vbox0, *vbox1, *vbox2;
    GtkWidget *vboxespacio0, *vboxespacio1;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6, *espacio7, *espacio8, *espacio9;
    GtkWidget *espacio10, *espacio11, *espacio12, *espacio13, *espacio14, *espacio15, *espacio16, *espacio17, *espacio18, *espacio19;
    GtkWidget *espacio20, *espacio21, *espacio22;

    GtkWidget *radiomio, *radioamigo;
    
    char bienvenida[50];
    
    GdkColor colorventana;
    gdk_color_parse("#d3d1d1",&colorventana);

    St_ingresa *datos = (St_ingresa*) data;
    St_busca_usuario guarda;
    St_ingresa regresa;
    St_menu combo;
    St_comandas comanda;
    comanda.para = 0;
    comanda.pedido = 0;
    comanda.total = 0;
    
    PangoFontDescription *fuente;
    GtkTextBuffer *buffer;

    gtk_widget_destroy(datos->ventana);
  
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_modify_bg(GTK_WIDGET(ventana),GTK_STATE_NORMAL,&colorventana);
    regresa.ventana = ventana;

    gtk_window_set_title(GTK_WINDOW(ventana), "Administrador");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    sprintf(bienvenida,"¡Bienvenido %s!",datos->usuario);
    lbienvenido = gtk_label_new(bienvenida);

    guarda.numcuenta = datos->usuario;
    comanda.numcuenta = datos->usuario;

    /* Creación de las variables necesarias para hacer la barra de estado */
    barra = gtk_menu_bar_new();
    bmopciones = gtk_menu_new();
    bmusuarios = gtk_menu_new();
    bmmenu = gtk_menu_new();
    bmamigos = gtk_menu_new();
    bmadmin = gtk_menu_new();

    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio7 = gtk_label_new(" ");
    espacio8 = gtk_label_new(" ");
    espacio9 = gtk_label_new(" ");

    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");
    espacio12 = gtk_label_new(" ");
    espacio13 = gtk_label_new(" ");
    espacio14 = gtk_label_new(" ");
    espacio15 = gtk_label_new(" ");
    espacio16 = gtk_label_new(" ");
    espacio17 = gtk_label_new(" ");
    espacio18 = gtk_label_new(" ");
    espacio19 = gtk_label_new(" ");
    
    espacio20 = gtk_label_new("         ");
    espacio21 = gtk_label_new("         ");
    espacio22 = gtk_label_new(" ");

    /* Creación de combo boxes */
    comboalimentos = get_menu(0);        /* Alimentos */
    comanda.comida = comboalimentos;
    combo.combomenu = comboalimentos; 
    combobebidas = get_menu(1);        /* Bebidas */
    comanda.bebida = combobebidas; 
    llista = gtk_label_new(" "); 
    comanda.carrito = llista; 
    
    /* Creacion de radio buttons */
    
    radiomio = gtk_radio_button_new_with_label(NULL,"Para mi");
    gtk_signal_connect (GTK_OBJECT (radiomio),"toggled",GTK_SIGNAL_FUNC(RadioMio),&comanda);

    radioamigo = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON (radiomio)),"Para un amigo");
    gtk_signal_connect(GTK_OBJECT(radioamigo),"toggled",GTK_SIGNAL_FUNC(RadioAmigo),&comanda);
     
    /* Creación de la barra de opciones */

    mopciones = gtk_menu_item_new_with_label("Opciones");
    musuarios = gtk_menu_item_new_with_label("Usuarios");
    mmenu = gtk_menu_item_new_with_label("Menú");
    mamigos = gtk_menu_item_new_with_label("Amigos");
    madmin = gtk_menu_item_new_with_label("Admin");

    mperfil = gtk_menu_item_new_with_label("Mi perfil");
    miconsumo = gtk_menu_item_new_with_label("Mi consumo");
    msalir = gtk_menu_item_new_with_label("Salir");
    gtk_signal_connect(GTK_OBJECT(miconsumo),"activate",GTK_SIGNAL_FUNC(MiConsumo),&guarda);
    gtk_signal_connect(GTK_OBJECT(msalir),"activate",GTK_SIGNAL_FUNC(RegresaInicio),&regresa);
    gtk_signal_connect(GTK_OBJECT(mperfil),"activate",GTK_SIGNAL_FUNC(MiPerfil),&guarda);
    
    madbusca = gtk_menu_item_new_with_label("Busca por tipo de usuario");
    gtk_signal_connect(GTK_OBJECT(madbusca),"activate",GTK_SIGNAL_FUNC(AdminBusca),&guarda);
    madbusquedas = gtk_menu_item_new_with_label("Busquedas de cada usuario");
    gtk_signal_connect(GTK_OBJECT(madbusquedas),"activate",GTK_SIGNAL_FUNC(VerBusquedas),&guarda);

    mtodos = gtk_menu_item_new_with_label("Todos los usuarios");
    mbuscar = gtk_menu_item_new_with_label("Buscar usuario");
    mumodificar = gtk_menu_item_new_with_label("Modificar información de usuario");
    mconsumo = gtk_menu_item_new_with_label("Consumo de usuario por mes");
    gtk_signal_connect(GTK_OBJECT(mtodos),"activate",GTK_SIGNAL_FUNC(VTodosLosUsuarios),NULL);
    gtk_signal_connect(GTK_OBJECT(mumodificar),"activate",GTK_SIGNAL_FUNC(VModificarUsuario),NULL);
    gtk_signal_connect(GTK_OBJECT(mbuscar),"activate",GTK_SIGNAL_FUNC(VBuscarUsuario),&guarda);
    gtk_signal_connect(GTK_OBJECT(mconsumo),"activate",GTK_SIGNAL_FUNC(ConsumoUsuarios),NULL);

    mmodificar = gtk_menu_item_new_with_label("Modificar menu");
    gtk_signal_connect(GTK_OBJECT(mmodificar),"activate",GTK_SIGNAL_FUNC(ModificarMenu),&combo);

    mmisamigos = gtk_menu_item_new_with_label("Mis amigos");
    gtk_signal_connect(GTK_OBJECT(mmisamigos),"activate",GTK_SIGNAL_FUNC(MisAmigos),&guarda);
    magamigos = gtk_menu_item_new_with_label("Agregar o eliminar amigos");
    gtk_signal_connect(GTK_OBJECT(magamigos),"activate",GTK_SIGNAL_FUNC(Amigos),&guarda);
    
    
    gtk_menu_append(GTK_MENU(bmadmin),madbusca);
    gtk_menu_append(GTK_MENU(bmadmin),madbusquedas);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(madmin),bmadmin);

    gtk_menu_append(GTK_MENU(bmmenu),mmodificar);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mmenu),bmmenu);

    gtk_menu_append(GTK_MENU(bmusuarios),mumodificar);
    gtk_menu_append(GTK_MENU(bmusuarios),mbuscar);
    gtk_menu_append(GTK_MENU(bmusuarios),mtodos);
    gtk_menu_append(GTK_MENU(bmusuarios),mconsumo);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(musuarios), bmusuarios);

    gtk_menu_append(GTK_MENU(bmamigos),mmisamigos);
    gtk_menu_append(GTK_MENU(bmamigos),magamigos);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mamigos), bmamigos);

    gtk_menu_append(GTK_MENU(bmopciones),mperfil);
    gtk_menu_append(GTK_MENU(bmopciones),miconsumo);
    gtk_menu_append(GTK_MENU(bmopciones),msalir);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mopciones), bmopciones);

    gtk_menu_bar_append(GTK_MENU_BAR(barra), mopciones);
    gtk_menu_bar_append(GTK_MENU_BAR(barra), mmenu);
    gtk_menu_bar_append(GTK_MENU_BAR(barra), musuarios);
    gtk_menu_bar_append(GTK_MENU_BAR(barra), mamigos);
    gtk_menu_bar_append(GTK_MENU_BAR(barra), madmin);

    blimpiar = add_button("Vaciar carrito",VaciarCarrito,&comanda);
    bagregar = add_button("Añadir",AnadirCarrito,&comanda);
    bcomprar = add_button("Comprar",Comprar,&comanda);

    /* Text Views */

    fuente = pango_font_description_from_string("Monospace Bold 14");

    textalimentos = gtk_text_view_new();
    gtk_widget_modify_font(textalimentos,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textalimentos),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textalimentos));
    gtk_text_buffer_set_text(buffer,"ALIMENTOS",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textalimentos),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textalimentos),FALSE);

    textbebidas = gtk_text_view_new();
    gtk_widget_modify_font(textbebidas,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textbebidas),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textbebidas));
    gtk_text_buffer_set_text(buffer,"BEBIDAS",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textbebidas),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textbebidas),FALSE);

    textcarrito = gtk_text_view_new();
    gtk_widget_modify_font(textcarrito,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textcarrito),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textcarrito));
    gtk_text_buffer_set_text(buffer,"CARRITO",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textcarrito),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textcarrito),FALSE);

    /* Empaquetado */

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    hbox5 = gtk_hbox_new(FALSE,5);
    hbox6 = gtk_hbox_new(FALSE,5);
    hbox7 = gtk_hbox_new(FALSE,5);
    hbox8 = gtk_hbox_new(FALSE,5);
    hbox9 = gtk_hbox_new(FALSE,5);

    hbox10 = gtk_hbox_new(FALSE,5);
    hbox11 = gtk_hbox_new(FALSE,5);
    hbox12 = gtk_hbox_new(FALSE,5);
    hbox13 = gtk_hbox_new(FALSE,5);
    hbox14 = gtk_hbox_new(FALSE,5);

    vbox0 = gtk_vbox_new(FALSE,5);
    vbox1 = gtk_vbox_new(FALSE,5);
    vbox2 = gtk_vbox_new(FALSE,5);
    
    vboxespacio0 = gtk_vbox_new(FALSE,5);
    vboxespacio1 = gtk_vbox_new(FALSE,5);

    gtk_box_pack_start(GTK_BOX(vbox0), barra, FALSE, FALSE, 0);

    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lbienvenido);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),espacio1);

    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vboxespacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vbox1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vbox2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vboxespacio1);

    gtk_box_pack_start_defaults(GTK_BOX(vboxespacio0),espacio20);
    gtk_box_pack_start_defaults(GTK_BOX(vboxespacio1),espacio21);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox4);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),textalimentos);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio3);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox5);

    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),comboalimentos);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox6);

    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio6);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),textbebidas);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio7);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox7);

    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio8);
    gtk_box_pack_start_defaults(GTK_BOX(hbox7),combobebidas);
    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio9);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox8);
 
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),bagregar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio11);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),blimpiar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio22);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox9);
 
    gtk_box_pack_start_defaults(GTK_BOX(hbox9),espacio12);

    /* Empaquetado para el vbox 2 */

    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox10);

    gtk_box_pack_start_defaults(GTK_BOX(hbox10),espacio13);
    gtk_box_pack_start_defaults(GTK_BOX(hbox10),textcarrito);
    gtk_box_pack_start_defaults(GTK_BOX(hbox10),espacio14);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox11);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),espacio15);
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),llista);
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),espacio16);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox12);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),espacio17);
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),bcomprar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),espacio18);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox13);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox13),radiomio);
    gtk_box_pack_start_defaults(GTK_BOX(hbox13),radioamigo);

    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox14);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox14),espacio19);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox3);

    gtk_container_add(GTK_CONTAINER(ventana), vbox0);
    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

/* @brief Despliega el menu del usuario y todas respectivas sus opciones */

int MenuUsuario(gpointer data){

    //Declaración de variables
    GtkWidget *ventana;
    GtkWidget *barra, *bmopciones, *mopciones;
    GtkWidget *msalir, *mperfil, *mconsumo, *mamigos, *mmisamigos, *magamigos, *bmamigos, *musuarios, *mtodos, *mbuscar, *bmusuarios;
    GtkWidget *lbienvenido, *llista, *radiomio, *radioamigo, *blimpiar, *hbox11, *hbox12, *hbox13, *hbox14, *vboxespacio0, *vboxespacio1;

    GtkWidget *comboalimentos, *combobebidas, *bagregar, *bcomprar, *textalimentos, *textbebidas, *textcarrito;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5, *hbox6, *hbox7, *hbox8, *hbox9;
    GtkWidget *hbox10;
    GtkWidget *vbox0, *vbox1, *vbox2;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6, *espacio7, *espacio8, *espacio9, *espacio20, *espacio21, *espacio22, *espacio15, *espacio16, *espacio17, *espacio18, *espacio19;
    GtkWidget *espacio10, *espacio11, *espacio12, *espacio13, *espacio14;

    char bienvenida[50];

    St_ingresa *datos = (St_ingresa*) data;
    St_busca_usuario guarda;
    St_ingresa regresa;
    St_menu combo;
    St_comandas comanda;
    comanda.para = 0;
    comanda.pedido = 0;
    comanda.total = 0;
    
    GdkColor colorventana;
    gdk_color_parse("#d76363",&colorventana);

    PangoFontDescription *fuente;
    GtkTextBuffer *buffer;

    gtk_widget_destroy(datos->ventana);

    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    regresa.ventana = ventana;
    gtk_widget_modify_bg(GTK_WIDGET(ventana),GTK_STATE_NORMAL,&colorventana);
    gtk_window_set_title(GTK_WINDOW(ventana), "Menú usuarios");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    sprintf(bienvenida,"¡Bienvenido %s!",datos->usuario);
    lbienvenido = gtk_label_new(bienvenida);

    guarda.numcuenta = datos->usuario;
    comanda.numcuenta = datos->usuario;

    /* Creación de las variables necesarias para hacer la barra de estado */
    barra = gtk_menu_bar_new();
    bmopciones = gtk_menu_new();
    bmamigos = gtk_menu_new();
    bmusuarios = gtk_menu_new();

    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio7 = gtk_label_new(" ");
    espacio8 = gtk_label_new(" ");
    espacio9 = gtk_label_new(" ");

    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");
    espacio12 = gtk_label_new(" ");
    espacio13 = gtk_label_new(" ");
    espacio14 = gtk_label_new(" ");
    espacio15 = gtk_label_new(" ");
    espacio16 = gtk_label_new(" ");
    espacio17 = gtk_label_new(" ");
    espacio18 = gtk_label_new(" ");
    espacio19 = gtk_label_new(" ");
    
    espacio20 = gtk_label_new("         ");
    espacio21 = gtk_label_new("         ");
    espacio22 = gtk_label_new(" ");

    /* Creación de combo boxes */
    comboalimentos = get_menu(0);        /* Alimentos */
    comanda.comida = comboalimentos;
    combo.combomenu = comboalimentos; 
    combobebidas = get_menu(1);        /* Bebidas */
    comanda.bebida = combobebidas; 
    llista = gtk_label_new(" "); 
    comanda.carrito = llista;
    
    /* Creacion de radio buttons */
    radiomio = gtk_radio_button_new_with_label(NULL,"Para mi");
    gtk_signal_connect (GTK_OBJECT (radiomio),"toggled",GTK_SIGNAL_FUNC(RadioMio),&comanda);

    radioamigo = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON (radiomio)),"Para un amigo");
    gtk_signal_connect(GTK_OBJECT(radioamigo),"toggled",GTK_SIGNAL_FUNC(RadioAmigo),&comanda);

    /* Creación de la barra de opciones */
    mopciones = gtk_menu_item_new_with_label("Opciones");
    mamigos = gtk_menu_item_new_with_label("Amigos");

    mconsumo = gtk_menu_item_new_with_label("Mi consumo");
    gtk_signal_connect(GTK_OBJECT(mconsumo),"activate",GTK_SIGNAL_FUNC(MiConsumo),&guarda);
    mperfil = gtk_menu_item_new_with_label("Mi perfil");
    msalir = gtk_menu_item_new_with_label("Salir");
    musuarios = gtk_menu_item_new_with_label("Usuarios");
    gtk_signal_connect(GTK_OBJECT(msalir),"activate",GTK_SIGNAL_FUNC(RegresaInicio),&regresa);
    gtk_signal_connect(GTK_OBJECT(mperfil),"activate",GTK_SIGNAL_FUNC(MiPerfil),&guarda);

    mmisamigos = gtk_menu_item_new_with_label("Mis amigos");
    gtk_signal_connect(GTK_OBJECT(mmisamigos),"activate",GTK_SIGNAL_FUNC(MisAmigos),&guarda);
    magamigos = gtk_menu_item_new_with_label("Agregar o eliminar amigos");
    gtk_signal_connect(GTK_OBJECT(magamigos),"activate",GTK_SIGNAL_FUNC(Amigos),&guarda);

    gtk_menu_append(GTK_MENU(bmopciones),mconsumo);
    gtk_menu_append(GTK_MENU(bmopciones),mperfil);
    gtk_menu_append(GTK_MENU(bmopciones),msalir);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mopciones), bmopciones);
    
    mtodos = gtk_menu_item_new_with_label("Todos los usuarios");
    mbuscar = gtk_menu_item_new_with_label("Buscar usuario");
    gtk_signal_connect(GTK_OBJECT(mbuscar),"activate",GTK_SIGNAL_FUNC(VBuscarUsuario),&guarda);
    gtk_signal_connect(GTK_OBJECT(mtodos),"activate",GTK_SIGNAL_FUNC(VTodosLosUsuarios),&guarda);

    gtk_menu_append(GTK_MENU(bmamigos),mmisamigos);
    gtk_menu_append(GTK_MENU(bmamigos),magamigos);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mamigos), bmamigos);
    
    gtk_menu_append(GTK_MENU(bmusuarios),mbuscar);
    gtk_menu_append(GTK_MENU(bmusuarios),mtodos);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(musuarios), bmusuarios);

    gtk_menu_bar_append(GTK_MENU_BAR(barra), mopciones);
    gtk_menu_bar_append(GTK_MENU_BAR(barra), mamigos);
    gtk_menu_bar_append(GTK_MENU_BAR(barra), musuarios);

    bagregar = add_button("Añadir",Click,NULL);

    /* Text Views */

    fuente = pango_font_description_from_string("Monospace Bold 14");

    textalimentos = gtk_text_view_new();
    gtk_widget_modify_font(textalimentos,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textalimentos),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textalimentos));
    gtk_text_buffer_set_text(buffer,"ALIMENTOS",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textalimentos),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textalimentos),FALSE);

    textbebidas = gtk_text_view_new();
    gtk_widget_modify_font(textbebidas,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textbebidas),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textbebidas));
    gtk_text_buffer_set_text(buffer,"BEBIDAS",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textbebidas),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textbebidas),FALSE);

    textcarrito = gtk_text_view_new();
    gtk_widget_modify_font(textcarrito,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textcarrito),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textcarrito));
    gtk_text_buffer_set_text(buffer,"CARRITO",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textcarrito),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textcarrito),FALSE);
    
    blimpiar = add_button("Vaciar carrito",VaciarCarrito,&comanda);
    bagregar = add_button("Añadir",AnadirCarrito,&comanda);
    bcomprar = add_button("Comprar",Comprar,&comanda);

    guarda.linfo=comanda.linfo;
    /* Empaquetado */

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    hbox5 = gtk_hbox_new(FALSE,5);
    hbox6 = gtk_hbox_new(FALSE,5);
    hbox7 = gtk_hbox_new(FALSE,5);
    hbox8 = gtk_hbox_new(FALSE,5);
    hbox9 = gtk_hbox_new(FALSE,5);

    hbox10 = gtk_hbox_new(FALSE,5);
    hbox11 = gtk_hbox_new(FALSE,5);
    hbox12 = gtk_hbox_new(FALSE,5);
    hbox13 = gtk_hbox_new(FALSE,5);
    hbox14 = gtk_hbox_new(FALSE,5);

    vbox0 = gtk_vbox_new(FALSE,5);
    vbox1 = gtk_vbox_new(FALSE,5);
    vbox2 = gtk_vbox_new(FALSE,5);
    
    vboxespacio0 = gtk_vbox_new(FALSE,5);
    vboxespacio1 = gtk_vbox_new(FALSE,5);

    gtk_box_pack_start(GTK_BOX(vbox0), barra, FALSE, FALSE, 0);

    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lbienvenido);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),espacio1);

    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vboxespacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vbox1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vbox2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vboxespacio1);

    gtk_box_pack_start_defaults(GTK_BOX(vboxespacio0),espacio20);
    gtk_box_pack_start_defaults(GTK_BOX(vboxespacio1),espacio21);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox4);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),textalimentos);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio3);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox5);

    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),comboalimentos);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox6);

    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio6);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),textbebidas);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio7);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox7);

    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio8);
    gtk_box_pack_start_defaults(GTK_BOX(hbox7),combobebidas);
    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio9);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox8);
 
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),bagregar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio11);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),blimpiar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio22);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox9);
 
    gtk_box_pack_start_defaults(GTK_BOX(hbox9),espacio12);

    /* Empaquetado para el vbox 2 */

    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox10);

    gtk_box_pack_start_defaults(GTK_BOX(hbox10),espacio13);
    gtk_box_pack_start_defaults(GTK_BOX(hbox10),textcarrito);
    gtk_box_pack_start_defaults(GTK_BOX(hbox10),espacio14);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox11);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),espacio15);
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),llista);
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),espacio16);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox12);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),espacio17);
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),bcomprar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),espacio18);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox13);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox13),radiomio);
    gtk_box_pack_start_defaults(GTK_BOX(hbox13),radioamigo);

    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox14);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox14),espacio19);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox3);

    gtk_container_add(GTK_CONTAINER(ventana), vbox0);
    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

/* @brief Despliega el menu del invitado y todas respectivas sus opciones */

int MenuInvitado(GtkWidget *boton, gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana;
    GtkWidget *barra, *bmopciones, *mopciones;
    GtkWidget *msalir;

    GtkWidget *lbienvenido, *llista, *radiomio, *blimpiar, *hbox11, *hbox12, *hbox13, *hbox14, *vboxespacio0, *vboxespacio1;
    GtkWidget *comboalimentos, *combobebidas, *bagregar, *bcomprar, *textalimentos, *textbebidas, *textcarrito;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5, *hbox6, *hbox7, *hbox8, *hbox9;
    GtkWidget *hbox10;
    GtkWidget *vbox0, *vbox1, *vbox2;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6, *espacio7, *espacio8, *espacio9, *espacio20, *espacio21, *espacio22;
    GtkWidget *espacio10, *espacio11, *espacio12, *espacio13, *espacio14, *espacio15, *espacio16, *espacio17, *espacio18, *espacio19;

    char bienvenida[50];
    
    GdkColor colorventana;
    gdk_color_parse("#F1e0BC",&colorventana);

    St_ingresa *datos = (St_ingresa*) data;
    St_ingresa regresa;
    St_comandas comanda;
    St_menu combo;
    comanda.para = 0;
    comanda.pedido = 0;
    comanda.total = 0;
    comanda.numcuenta = "000000-0";//Creamos un usuario 'fantasma' como el invitado en la base de datos para facilitar el manejo

    PangoFontDescription *fuente;
    GtkTextBuffer *buffer;

    gtk_widget_destroy(datos->ventana);

    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    regresa.ventana = ventana;
    gtk_widget_modify_bg(GTK_WIDGET(ventana),GTK_STATE_NORMAL,&colorventana);

    gtk_window_set_title(GTK_WINDOW(ventana), "Menú usuarios");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    sprintf(bienvenida,"¡Bienvenido!");
    lbienvenido = gtk_label_new(bienvenida);
    
    /* Creación de las variables necesarias para hacer la barra de estado */
    barra = gtk_menu_bar_new();
    bmopciones = gtk_menu_new();

    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio7 = gtk_label_new(" ");
    espacio8 = gtk_label_new(" ");
    espacio9 = gtk_label_new(" ");

    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");
    espacio12 = gtk_label_new(" ");
    espacio13 = gtk_label_new(" ");
    espacio14 = gtk_label_new(" ");
    espacio15 = gtk_label_new(" ");
    espacio16 = gtk_label_new(" ");
    espacio17 = gtk_label_new(" ");
    espacio18 = gtk_label_new(" ");
    espacio19 = gtk_label_new(" ");
    espacio20 = gtk_label_new(" ");
    espacio21 = gtk_label_new(" ");
    espacio22 = gtk_label_new(" ");

     /* Creación de combo boxes */
    comboalimentos = get_menu(0);        /* Alimentos */
    comanda.comida = comboalimentos;
    combo.combomenu = comboalimentos; 
    combobebidas = get_menu(1);         /*Bebidas */
    comanda.bebida = combobebidas; 
    llista = gtk_label_new(" "); 
    comanda.carrito = llista;
    
    /* Creacion de radio button */
    radiomio = gtk_radio_button_new_with_label(NULL,"Para mi");
    gtk_signal_connect (GTK_OBJECT (radiomio),"toggled",GTK_SIGNAL_FUNC(RadioMio),&comanda);

    /* Creación de la barra de opciones */
    mopciones = gtk_menu_item_new_with_label("Opciones");

    //mconsumo = gtk_menu_item_new_with_label("Mi consumo");
    msalir = gtk_menu_item_new_with_label("Salir");
    gtk_signal_connect(GTK_OBJECT(msalir),"activate",GTK_SIGNAL_FUNC(RegresaInicio),&regresa);

    //gtk_menu_append(GTK_MENU(bmopciones),mconsumo);
    gtk_menu_append(GTK_MENU(bmopciones),msalir);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mopciones), bmopciones);

    gtk_menu_bar_append(GTK_MENU_BAR(barra), mopciones);

    bagregar = add_button("Añadir",Click,NULL);
    
    /* Text Views */
    fuente = pango_font_description_from_string("Monospace Bold 14");

    textalimentos = gtk_text_view_new();
    gtk_widget_modify_font(textalimentos,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textalimentos),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textalimentos));
    gtk_text_buffer_set_text(buffer,"ALIMENTOS",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textalimentos),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textalimentos),FALSE);

    textbebidas = gtk_text_view_new();
    gtk_widget_modify_font(textbebidas,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textbebidas),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textbebidas));
    gtk_text_buffer_set_text(buffer,"BEBIDAS",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textbebidas),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textbebidas),FALSE);

    textcarrito = gtk_text_view_new();
    gtk_widget_modify_font(textcarrito,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textcarrito),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textcarrito));
    gtk_text_buffer_set_text(buffer,"CARRITO",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textcarrito),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textcarrito),FALSE);
    
    blimpiar = add_button("Vaciar carrito",VaciarCarrito,&comanda);
    bagregar = add_button("Añadir",AnadirCarrito,&comanda);
    bcomprar = add_button("Comprar",Comprar,&comanda);
    
    /* Empaquetado */
    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    hbox5 = gtk_hbox_new(FALSE,5);
    hbox6 = gtk_hbox_new(FALSE,5);
    hbox7 = gtk_hbox_new(FALSE,5);
    hbox8 = gtk_hbox_new(FALSE,5);
    hbox9 = gtk_hbox_new(FALSE,5);

    hbox10 = gtk_hbox_new(FALSE,5);
    hbox11 = gtk_hbox_new(FALSE,5);
    hbox12 = gtk_hbox_new(FALSE,5);
    hbox13 = gtk_hbox_new(FALSE,5);
    hbox14 = gtk_hbox_new(FALSE,5);

    vbox0 = gtk_vbox_new(FALSE,5);
    vbox1 = gtk_vbox_new(FALSE,5);
    vbox2 = gtk_vbox_new(FALSE,5);
    
    vboxespacio0 = gtk_vbox_new(FALSE,5);
    vboxespacio1 = gtk_vbox_new(FALSE,5);

    gtk_box_pack_start(GTK_BOX(vbox0), barra, FALSE, FALSE, 0);

    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lbienvenido);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),espacio1);

    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vboxespacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vbox1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vbox2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),vboxespacio1);

    gtk_box_pack_start_defaults(GTK_BOX(vboxespacio0),espacio20);
    gtk_box_pack_start_defaults(GTK_BOX(vboxespacio1),espacio21);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox4);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),textalimentos);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio3);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox5);

    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),comboalimentos);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox6);

    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio6);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),textbebidas);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio7);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox7);

    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio8);
    gtk_box_pack_start_defaults(GTK_BOX(hbox7),combobebidas);
    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio9);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox8);
 
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),bagregar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio11);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),blimpiar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox8),espacio22);

    gtk_box_pack_start_defaults(GTK_BOX(vbox1),hbox9);
 
    gtk_box_pack_start_defaults(GTK_BOX(hbox9),espacio12);

    /* Empaquetado para el vbox 2 */
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox10);

    gtk_box_pack_start_defaults(GTK_BOX(hbox10),espacio13);
    gtk_box_pack_start_defaults(GTK_BOX(hbox10),textcarrito);
    gtk_box_pack_start_defaults(GTK_BOX(hbox10),espacio14);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox11);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),espacio15);
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),llista);
    gtk_box_pack_start_defaults(GTK_BOX(hbox11),espacio16);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox12);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),espacio17);
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),bcomprar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox12),espacio18);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox13);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox13),radiomio);

    gtk_box_pack_start_defaults(GTK_BOX(vbox2),hbox14);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox14),espacio19);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox0), hbox3);

    gtk_container_add(GTK_CONTAINER(ventana), vbox0);
    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

/* @brief Se depliega una ventana para administradores con la opción de agregar o eliminar opciones del menú */

int ModificarMenu(GtkWidget *widget, gpointer datos){

    //Declaración de vaariables
    GtkWidget *ventana;
    GtkWidget *bagregar, *bquitar;

    GtkWidget *hbox0, *hbox1, *hbox2;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4;

    St_mod_menu data;
    St_menu *anterior = (St_menu*)datos;

    data.menu = anterior->combomenu;

    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    data.ventana = ventana;
    gtk_window_set_title(GTK_WINDOW(ventana), "Modificar menú");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    //Creación de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");

    bagregar = add_button("Agregar elemento al menú",VAgregarElemento,&data);
    bquitar = add_button("Quitar o modificar elemento del menú",VEliminarElemento,&data);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,15);
    hbox2 = gtk_hbox_new(FALSE,5);
    vbox = gtk_vbox_new(FALSE,5);

    /* Empaquetado */
    gtk_box_pack_start_defaults(GTK_BOX(hbox0), espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), bagregar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), bquitar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2), espacio4);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

int VAgregarElemento(GtkWidget *boton, gpointer data){

    //Declaracion de variables
    GtkWidget *ventana;

    GtkWidget *lelemento, *telemento, *lprecio, *tprecio, *bagrega, *lestatus;
    GtkWidget *combotipo;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *hboxex1, *hboxex2;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6;
    GtkWidget *espacioex1, *espacioex2, *espacioex3;

    char *tipo[2] = {"Alimento","Bebida"};

    St_mod_menu *datos = (St_mod_menu*)data;
    St_mod_menu datos1;

    datos1.menu = datos->menu;
    gtk_widget_destroy(datos->ventana);

    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Agregar elemento");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    lelemento = gtk_label_new("Nombre:");
    lprecio = gtk_label_new("Precio:");

    combotipo = gtk_combo_box_new_text();
    datos1.combotipo = combotipo;

    for(int i = 0 ; i < 2 ; i++){gtk_combo_box_append_text(GTK_COMBO_BOX(combotipo),tipo[i]);} //Insertar elementos en la combo box

    //Creación de espacios, labels, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");

    espacioex1 = gtk_label_new(" ");
    espacioex2 = gtk_label_new(" ");
    espacioex3 = gtk_label_new(" ");

    lestatus = gtk_label_new(" ");
    datos1.lestatus = lestatus;

    telemento = gtk_entry_new();
    datos1.telemento = telemento;
    tprecio = gtk_entry_new();
    datos1.tprecio = tprecio;

    bagrega = add_button("Agregar",RecibeElemento,&datos1);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);

    hboxex1 = gtk_hbox_new(FALSE,5);
    hboxex2 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);

    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hboxex1),espacioex1);

    gtk_box_pack_start_defaults(GTK_BOX(hboxex2),espacioex2);
    gtk_box_pack_start_defaults(GTK_BOX(hboxex2),combotipo);
    gtk_box_pack_start_defaults(GTK_BOX(hboxex2),espacioex3);

    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lelemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),telemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lprecio);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),tprecio);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),lestatus);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),bagrega);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio5);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio6);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxex1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxex2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

int VEliminarElemento(GtkWidget *boton, gpointer data){

    //Declaración de variables
    GtkWidget *ventana;

    GtkWidget *lelemento, *telemento, *belimina, *lestatus;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5;

    St_mod_menu *datos = (St_mod_menu*) data;
    St_mod_menu datos1;

    gtk_widget_destroy(datos->ventana); 

    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Eliminar elemento");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    lelemento = gtk_label_new("Nombre:");

    //Creación de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");

    lestatus = gtk_label_new(" ");
    datos1.lestatus = lestatus;

    telemento = gtk_entry_new();
    datos1.telemento = telemento;

    belimina = add_button("Eliminar",BorraElemento,&datos1);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);

    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lelemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),telemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),lestatus);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),belimina);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

int VModificarUsuario(GtkWidget *boton, gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana;

    GtkWidget *lelemento, *telemento, *belimina, *lestatus;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5;

    St_registra datos;

    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    datos.ventana = ventana;
    gtk_window_set_title(GTK_WINDOW(ventana), "Modificar información");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    lelemento = gtk_label_new("Número de cuenta:");

    //Creación de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");

    lestatus = gtk_label_new(" ");
    datos.linfo = lestatus;
 
    telemento = gtk_entry_new();
    datos.tcuenta = telemento;

    belimina = add_button("Buscar",BuscaModifica,&datos);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);

    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lelemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),telemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),lestatus);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),belimina);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

int VBuscarUsuario(GtkWidget *boton, gpointer data){

    //Declaracion de variables
    GtkWidget *ventana;

    GtkWidget *lappaterno, *lcarrera, *lsemestre, *lncuenta, *lnac, *ldia, *lmes, *lanio;
    GtkWidget *tappaterno, *tcarrera, *tsemestre, *tncuenta, *tdia, *tmes, *tanio;
    GtkWidget *bbusca, *linfo, *lres;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5, *hbox6, *hbox7, *hbox8, *hbox9, *hbox10, *hbox11;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio2, *espacio3, *espacio5, *espacio6, *espacio7, *espacio8, *espacio9, *espacio10, *espacio11, *espacio12, *espacio13;
    GtkWidget *espacio14, *espacio15, *espacio16, *espacio17, *espacio18;

    char combo_number[5];

    St_busca_usuario *anterior = (St_busca_usuario *)data;

    St_busca_usuario datos;

    char *carreras[36] = {"Actuaria","Administracion de empresas","Administracion de la hospitalidad","Administracion de negocios internacionales"
                        ,"Arquitectura","Ciencias teologicas","Comunicacion","Contaduria","Ciencias politicas","Derecho","Diseño grafico"
                        ,"Diseño de indumentaria y moda","Diseño industrial","Diseño interactivo","Diseño textil","Economia","Filosofia","Finanzas"
                        ,"Historia del arte","Historia","Ingenieria de alimentos","Ingenieria biomedica","Ingenieria civil","Ingenieria fisica"
                        ,"Ingenieria industrial","Ingenieria mecanica","Ingenieria mecatronica","Ingenieria quimica","Ingenieria en telecomunicaciones",
                        "Literatura","Mercadotecnia","Nutricion","Pedagogia","Psicologia","Relaciones internacionales","Sustentabilidad ambiental"};

    //g_print("/nVBuscarUsuario: %s", anterior->numcuenta);
    datos.numcuenta = anterior->numcuenta;

    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Búsqueda de usuario");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    //Crear las labels
    lappaterno = gtk_label_new("Apellido paterno:");

    lcarrera = gtk_label_new("Carrera:");
    lsemestre = gtk_label_new("Semestre:");
    lncuenta = gtk_label_new("Número de cuenta:");

    lnac = gtk_label_new("Fecha de nacimiento ");
    ldia = gtk_label_new("Dia:");
    lmes = gtk_label_new("Mes:");
    lanio = gtk_label_new("Año:");

    linfo = gtk_label_new(" ");
    datos.linfo = linfo;
    lres = gtk_label_new(" ");
    datos.lres = lres;

    tappaterno = gtk_entry_new();
    datos.tappaterno = tappaterno;

    tcarrera = gtk_combo_box_new_text();
    datos.tcarrera = tcarrera;

    //Crear entryboxes
    tsemestre = gtk_combo_box_new_text();
    datos.tsemestre = tsemestre;
    tdia = gtk_combo_box_new_text();
    datos.tdia = tdia;
    tmes = gtk_combo_box_new_text();
    datos.tmes = tmes;
    tanio = gtk_combo_box_new_text();
    datos.tanio = tanio;

    //Insertar elementos en los combo boxes
    for(int i = 0 ; i < 36 ; i++){gtk_combo_box_append_text(GTK_COMBO_BOX(tcarrera),carreras[i]);}

    for(int i = 1 ; i <= 12 ; i++){

        sprintf(combo_number,"%i",i);
        gtk_combo_box_append_text(GTK_COMBO_BOX(tsemestre),combo_number);
    }

    for(int i = 1 ; i <= 31 ; i++){

        sprintf(combo_number,"%i",i);
        gtk_combo_box_append_text(GTK_COMBO_BOX(tdia),combo_number);
    }

    for(int i = 1 ; i <= 12 ; i++){

        sprintf(combo_number,"%i",i);
        gtk_combo_box_append_text(GTK_COMBO_BOX(tmes),combo_number);
    }

    for(int i = 2021 ; i >= 1921 ; i--){

        sprintf(combo_number,"%i",i);
        gtk_combo_box_append_text(GTK_COMBO_BOX(tanio),combo_number);
    }

    gtk_combo_box_append_text(GTK_COMBO_BOX(tsemestre), "Fósil");

    tncuenta = gtk_entry_new();
    datos.tcuenta = tncuenta;

    //Creación de espacios,botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio7 = gtk_label_new(" ");
    espacio8 = gtk_label_new(" ");
    espacio9 = gtk_label_new(" ");
    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");
    espacio12 = gtk_label_new(" ");
    espacio13 = gtk_label_new(" ");
    espacio14 = gtk_label_new(" ");
    espacio15 = gtk_label_new(" ");
    espacio16 = gtk_label_new(" ");
    espacio17 = gtk_label_new(" ");
    espacio18 = gtk_label_new(" ");

    bbusca = add_button("Buscar",BuscaUsuario,&datos);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    hbox5 = gtk_hbox_new(FALSE,5);
    hbox6 = gtk_hbox_new(FALSE,5);
    hbox7 = gtk_hbox_new(FALSE,5);
    hbox8 = gtk_hbox_new(FALSE,5);
    hbox9 = gtk_hbox_new(FALSE,5);
    hbox10 = gtk_hbox_new(FALSE,5);
    hbox11 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);

    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);

    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lappaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),tappaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio3);

    gtk_box_pack_start_defaults(GTK_BOX(hbox2), lnac);

    gtk_box_pack_start_defaults(GTK_BOX(hbox3), espacio9);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), ldia);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), tdia);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), espacio10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), lmes);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), tmes);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), espacio11);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), lanio);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), tanio);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), espacio12);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio5);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),lcarrera);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),tcarrera);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio6);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),lsemestre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),tsemestre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio7);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),lncuenta);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),tncuenta);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio8);

    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio13);

    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio14);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),bbusca);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio15);

    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio16);

    gtk_box_pack_start_defaults(GTK_BOX(hbox8),linfo);

    gtk_box_pack_start_defaults(GTK_BOX(hbox9),espacio17);

    gtk_box_pack_start_defaults(GTK_BOX(hbox10),lres);

    gtk_box_pack_start_defaults(GTK_BOX(hbox11),espacio18);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox6);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox7);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox8);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox9);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox10);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox11);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

int MiPerfil(GtkWidget *boton, gpointer data){ 

    //Declaración de variables
    GtkWidget *ventana, *bmodificar;
    GtkWidget *lnombre, *lappaterno, *lapmaterno, *lcarrera, *lsemestre, *lcuenta, *lcorreo, *lcontra, *lconfcontra, *lcumple;
    GtkWidget *tnombre, *tappaterno, *tapmaterno, *tcarrera, *tsemestre, *tcuenta, *tcorreo, *tcontra, *tconfcontra, *tcumple;
    GtkWidget *vbox;
    GtkWidget *hboxe, *hboxt, *hbox0, *hbox1, *hbox2, *hbox4, *hbox5, *hbox6, *hbox7;
    GtkWidget *hboxaux, *hboxaux1, *hboxaux2, *hboxaux3, *hboxaux4, *hboxaux5;
    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6;
    GtkWidget *espacio10, *espacio11, *espacio12, *espacio13, *espacio14, *espacio15, *espacio16, *espacio17, *espacio18, *espacio19, *espacio20;
    GtkWidget *espacioe, *espaciot1, *espaciot2, *espacioaux, *espacioaux1, *espacioaux2;
    GtkWidget *espacioaux3, *linfo, *textview;
    //GtkWidget *tdia, *tmes, *tanio;
    
    char query[100];
    char *carrera, *semestre, *cuenta, *cumple;
    
    St_busca_usuario *anterior = (St_busca_usuario *)data;
    St_registra datos;
    
    datos.numcuenta = anterior->numcuenta;
    
    //g_print("Cuenta: %s",datos.numcuenta);
    PangoFontDescription *fuente;
    GtkTextBuffer *buffer;

    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(ventana), FALSE);
    gtk_window_set_title(GTK_WINDOW(ventana),"Mi perfil");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy", G_CALLBACK(destroy), NULL);
    
    fuente = pango_font_description_from_string("Monospace Bold 20");
    textview = gtk_text_view_new();
    gtk_widget_modify_font(textview,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textview),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
    gtk_text_buffer_set_text(buffer,"- MI PERFIL -",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview),FALSE);

    /* Etiquetas */
    lnombre = gtk_label_new("Nombre: ");
    lappaterno = gtk_label_new("Ap. Paterno: ");
    lapmaterno = gtk_label_new("Ap. Materno: ");
    lcumple = gtk_label_new("Cumpleaños: ");
    lcarrera = gtk_label_new("Carrera: ");
    lsemestre = gtk_label_new("Semestre: ");
    lcuenta = gtk_label_new("Cuenta: ");
    lcorreo = gtk_label_new("Correo: ");
    lcontra = gtk_label_new("Contraseña: ");
    lconfcontra = gtk_label_new("Confirma Contraseña: ");
    
    //Entryboxes
    tnombre = gtk_entry_new();
    datos.tnombre = tnombre;
    tappaterno = gtk_entry_new();
    datos.tappaterno = tappaterno;
    tapmaterno = gtk_entry_new();
    datos.tapmaterno = tapmaterno;
    tcorreo = gtk_entry_new();
    datos.tcorreo = tcorreo;
    tcontra = gtk_entry_new();
    datos.tcontra = tcontra;
    tconfcontra = gtk_entry_new();
    datos.tconfcontra = tconfcontra;
    
    //Obtener la información del usuario de la base de datos y guardarlo en labels
    sprintf(query,"SELECT carrera FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    carrera = MySQLget_one(query);
    tcarrera = gtk_label_new(carrera);
    
    sprintf(query,"SELECT numcuenta FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    cuenta = MySQLget_one(query);
    tcuenta = gtk_label_new(cuenta);
    
    sprintf(query,"SELECT nombre FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.nombre, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tnombre), datos.nombre);
   
    sprintf(query,"SELECT appaterno FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.appaterno, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tappaterno),datos.appaterno);
    
    sprintf(query,"SELECT apmaterno FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.apmaterno, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tapmaterno),datos.apmaterno);
    
    sprintf(query,"SELECT correo FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.correo, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tcorreo),datos.correo);
    
    sprintf(query,"SELECT contra FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.contra, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tcontra),datos.contra);

    sprintf(query,"SELECT nacimiento FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    cumple = MySQLget_one(query);
    tcumple = gtk_label_new(cumple);

    gtk_entry_set_visibility(GTK_ENTRY(tcontra), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(tcontra),'*');
    gtk_entry_set_visibility(GTK_ENTRY(tconfcontra), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(tconfcontra),'*');

    //tdia = gtk_combo_box_new_text();
    //tmes = gtk_combo_box_new_text();
    //tanio = gtk_combo_box_new_text();
    sprintf(query,"SELECT semestre FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    semestre = MySQLget_one(query);
    tsemestre = gtk_label_new(semestre);
    
    /* Empaquetamos todo */
    bmodificar = add_button("Modificar perfil",ModificarPerfil,&datos);

    hboxe = gtk_hbox_new(FALSE,1);
    hboxt = gtk_hbox_new(FALSE,1);
    hbox0 = gtk_hbox_new(FALSE,1);
    hbox1 = gtk_hbox_new(FALSE,1);
    hbox2 = gtk_hbox_new(FALSE,1);
    hbox4 = gtk_hbox_new(FALSE,1);
    hbox5 = gtk_hbox_new(FALSE,1);
    hbox6 = gtk_hbox_new(FALSE,1);
    hbox7 = gtk_hbox_new(FALSE,1);

    hboxaux = gtk_hbox_new(FALSE,1);
    hboxaux1 = gtk_hbox_new(FALSE,1);
    hboxaux2 = gtk_hbox_new(FALSE,1);
    hboxaux3 = gtk_hbox_new(FALSE,1);
    hboxaux4 = gtk_hbox_new(FALSE,1);
    hboxaux5 = gtk_hbox_new(FALSE,1);

    vbox = gtk_vbox_new(FALSE,5);

    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new("      ");
    espacio2 = gtk_label_new("      ");
    espacio3 = gtk_label_new("      ");
    espacio4 = gtk_label_new("      ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");
    espacio12 = gtk_label_new(" ");
    espacio13 = gtk_label_new(" ");
    espacio14 = gtk_label_new(" ");
    espacio15 = gtk_label_new(" ");
    espacio16 = gtk_label_new(" ");
    espacio17 = gtk_label_new(" ");
    espacio18 = gtk_label_new(" ");
    espacio19 = gtk_label_new(" ");
    espacio20 = gtk_label_new(" ");

    espacioe = gtk_label_new(" ");
    espaciot1 = gtk_label_new(" ");
    espaciot2 = gtk_label_new(" ");

    espacioaux = gtk_label_new(" ");
    espacioaux1 = gtk_label_new(" ");
    espacioaux2 = gtk_label_new(" ");
    espacioaux3 = gtk_label_new(" ");

    linfo = gtk_label_new(" ");
    datos.linfo = linfo;

    /* Rellenando cajas */
    gtk_box_pack_start_defaults(GTK_BOX(hboxe), espacioe);

    gtk_box_pack_start_defaults(GTK_BOX(hboxt), espaciot1);
    gtk_box_pack_start_defaults(GTK_BOX(hboxt), textview);
    gtk_box_pack_start_defaults(GTK_BOX(hboxt), espaciot2);

    gtk_box_pack_start_defaults(GTK_BOX(hbox0), espacio0);

    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lnombre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tnombre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lappaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tappaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lapmaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tapmaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio4);

    gtk_box_pack_start_defaults(GTK_BOX(hbox2), espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux), espacioaux);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4), lcumple);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), tcumple);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacio6);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux1), espacioaux1);

    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lcuenta);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tcuenta);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio11);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lcarrera);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tcarrera);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio12);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lsemestre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tsemestre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio13);

    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio14);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lcorreo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tcorreo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio15);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio16);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lconfcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tconfcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio17);

    gtk_box_pack_start_defaults(GTK_BOX(hbox7), espacio18);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), espacioaux2);
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), bmodificar);
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), espacioaux3);
    
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux3), espacio19);
    
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux4), linfo);
    
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux5), espacio20);
 
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxe);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxt);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox6);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox7);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux5);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);
    gtk_widget_show_all(ventana);
    
    gtk_main();

    return 0;
}

int MiPerfilAdmin(gpointer data){
       
    //Declaración de variables
    GtkWidget *ventana, *bmodificar;
    GtkWidget *lnombre, *lappaterno, *lapmaterno, *lcarrera, *lsemestre, *lcuenta, *lcorreo, *lcontra, *lconfcontra, *lcumple;
    GtkWidget *tnombre, *tappaterno, *tapmaterno, *tcarrera, *tsemestre, *tcuenta, *tcorreo, *tcontra, *tconfcontra, *tcumple;
    GtkWidget *vbox;
    GtkWidget *hboxe, *hboxt, *hbox0, *hbox1, *hbox2, *hbox4, *hbox5, *hbox6, *hbox7;
    GtkWidget *hboxaux, *hboxaux1, *hboxaux2, *hboxaux3, *hboxaux4, *hboxaux5;
    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6;
    GtkWidget *espacio10, *espacio11, *espacio12, *espacio13, *espacio14, *espacio15, *espacio16, *espacio17, *espacio18, *espacio19, *espacio20;
    GtkWidget *espacioe, *espaciot1, *espaciot2, *espacioaux, *espacioaux1, *espacioaux2;
    GtkWidget *espacioaux3, *linfo, *textview;
    ///GtkWidget *tdia, *tmes, *tanio;
     
    char query[100];
    char *carrera, *semestre, *cuenta, *cumple;
    
    St_registra *anterior = (St_registra *)data;
    St_registra datos;
    
    datos.numcuenta = anterior->cuenta; 
    
    //g_print("Cuenta: %s",datos.numcuenta);
    PangoFontDescription *fuente;
    GtkTextBuffer *buffer;

    //Creación de la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(ventana), FALSE);
    gtk_window_set_title(GTK_WINDOW(ventana),"Mi perfil");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy", G_CALLBACK(destroy), NULL);
    
    fuente = pango_font_description_from_string("Monospace Bold 20");
    textview = gtk_text_view_new();
    gtk_widget_modify_font(textview,fuente);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(textview),GTK_JUSTIFY_CENTER);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
    gtk_text_buffer_set_text(buffer,"- MI PERFIL -",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview),FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview),FALSE);

    /* Etiquetas */
    lnombre = gtk_label_new("Nombre: ");
    lappaterno = gtk_label_new("Ap. Paterno: ");
    lapmaterno = gtk_label_new("Ap. Materno: ");
    lcumple = gtk_label_new("Cumpleaños: ");
    lcarrera = gtk_label_new("Carrera: ");
    lsemestre = gtk_label_new("Semestre: ");
    lcuenta = gtk_label_new("Cuenta: ");
    lcorreo = gtk_label_new("Correo: ");
    lcontra = gtk_label_new("Contraseña: ");
    lconfcontra = gtk_label_new("Confirma Contraseña: ");
     
    //Entryboxes
    tnombre = gtk_entry_new();
    datos.tnombre = tnombre;
    tappaterno = gtk_entry_new();
    datos.tappaterno = tappaterno;
    tapmaterno = gtk_entry_new();
    datos.tapmaterno = tapmaterno;
    tcorreo = gtk_entry_new();
    datos.tcorreo = tcorreo;
    tcontra = gtk_entry_new();
    datos.tcontra = tcontra;
    tconfcontra = gtk_entry_new();
    datos.tconfcontra = tconfcontra;
    
    //Obtener los datos del usuario de la base de datos y guardarlos en las labels
    sprintf(query,"SELECT carrera FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    carrera = MySQLget_one(query);
    tcarrera = gtk_label_new(carrera);
    
    sprintf(query,"SELECT numcuenta FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    cuenta = MySQLget_one(query);
    tcuenta = gtk_label_new(cuenta);
    
    sprintf(query,"SELECT nombre FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.nombre, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tnombre), datos.nombre);
   
    sprintf(query,"SELECT appaterno FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.appaterno, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tappaterno),datos.appaterno);
    
    sprintf(query,"SELECT apmaterno FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.apmaterno, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tapmaterno),datos.apmaterno);
    
    sprintf(query,"SELECT correo FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.correo, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tcorreo),datos.correo);
    
    sprintf(query,"SELECT contra FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(datos.contra, MySQLget_one(query));
    gtk_entry_set_text(GTK_ENTRY(tcontra),datos.contra);

    sprintf(query,"SELECT nacimiento FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    cumple = MySQLget_one(query);
    tcumple = gtk_label_new(cumple);
    
    //Remplazar la contraseña con * en el entrybox
    gtk_entry_set_visibility(GTK_ENTRY(tcontra), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(tcontra),'*');
    gtk_entry_set_visibility(GTK_ENTRY(tconfcontra), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(tconfcontra),'*');

    //tdia = gtk_combo_box_new_text();
    //tmes = gtk_combo_box_new_text();
    //tanio = gtk_combo_box_new_text();
    sprintf(query,"SELECT semestre FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    semestre = MySQLget_one(query);
    tsemestre = gtk_label_new(semestre);
    
    /* Empaquetamos todo */
    bmodificar = add_button("Modificar perfil",ModificarPerfil,&datos);

    hboxe = gtk_hbox_new(FALSE,1);
    hboxt = gtk_hbox_new(FALSE,1);
    hbox0 = gtk_hbox_new(FALSE,1);
    hbox1 = gtk_hbox_new(FALSE,1);
    hbox2 = gtk_hbox_new(FALSE,1);
    hbox4 = gtk_hbox_new(FALSE,1);
    hbox5 = gtk_hbox_new(FALSE,1);
    hbox6 = gtk_hbox_new(FALSE,1);
    hbox7 = gtk_hbox_new(FALSE,1);

    hboxaux = gtk_hbox_new(FALSE,1);
    hboxaux1 = gtk_hbox_new(FALSE,1);
    hboxaux2 = gtk_hbox_new(FALSE,1);
    hboxaux3 = gtk_hbox_new(FALSE,1);
    hboxaux4 = gtk_hbox_new(FALSE,1);
    hboxaux5 = gtk_hbox_new(FALSE,1);

    vbox = gtk_vbox_new(FALSE,5);

    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new("      ");
    espacio2 = gtk_label_new("      ");
    espacio3 = gtk_label_new("      ");
    espacio4 = gtk_label_new("      ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");
    espacio12 = gtk_label_new(" ");
    espacio13 = gtk_label_new(" ");
    espacio14 = gtk_label_new(" ");
    espacio15 = gtk_label_new(" ");
    espacio16 = gtk_label_new(" ");
    espacio17 = gtk_label_new(" ");
    espacio18 = gtk_label_new(" ");
    espacio19 = gtk_label_new(" ");
    espacio20 = gtk_label_new(" ");

    espacioe = gtk_label_new(" ");
    espaciot1 = gtk_label_new(" ");
    espaciot2 = gtk_label_new(" ");

    espacioaux = gtk_label_new(" ");
    espacioaux1 = gtk_label_new(" ");
    espacioaux2 = gtk_label_new(" ");
    espacioaux3 = gtk_label_new(" ");

    linfo = gtk_label_new(" ");
    datos.linfo = linfo;

    /* Rellenando cajas */
    gtk_box_pack_start_defaults(GTK_BOX(hboxe), espacioe);

    gtk_box_pack_start_defaults(GTK_BOX(hboxt), espaciot1);
    gtk_box_pack_start_defaults(GTK_BOX(hboxt), textview);
    gtk_box_pack_start_defaults(GTK_BOX(hboxt), espaciot2);

    gtk_box_pack_start_defaults(GTK_BOX(hbox0), espacio0);

    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lnombre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tnombre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lappaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tappaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), lapmaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), tapmaterno);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio4);

    gtk_box_pack_start_defaults(GTK_BOX(hbox2), espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux), espacioaux);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4), lcumple);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), tcumple);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacio6);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux1), espacioaux1);

    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lcuenta);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tcuenta);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio11);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lcarrera);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tcarrera);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio12);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), lsemestre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), tsemestre);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5), espacio13);

    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio14);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lcorreo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tcorreo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio15);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio16);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), lconfcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), tconfcontra);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6), espacio17);

    gtk_box_pack_start_defaults(GTK_BOX(hbox7), espacio18);

    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), espacioaux2);
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), bmodificar);
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux2), espacioaux3);
    
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux3), espacio19);
    
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux4), linfo);
    
    gtk_box_pack_start_defaults(GTK_BOX(hboxaux5), espacio20);
 
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxe);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxt);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox6);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox7);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hboxaux5);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);
    gtk_widget_show_all(ventana);
    
    gtk_main();

    return 0;
}

int AdminBusca(GtkWidget *boton, gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana;

    GtkWidget *lusuario;
    GtkWidget *tusuario;
    GtkWidget *bbusca, *linfo, *lres;

    GtkWidget *hbox0, *hbox1, *hbox4, *hbox5, *hbox6, *hbox7, *hbox8, *hbox9, *hbox10, *hbox11;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio8;
    GtkWidget *espacio13, *espacio14, *espacio15, *espacio16, *espacio17, *espacio18;

    St_busca_usuario *anterior = (St_busca_usuario *)data;

    St_busca_usuario datos;
    
    datos.numcuenta = anterior->numcuenta;

    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Búsqueda de tipo de usuario");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    //Creación de labels
    lusuario = gtk_label_new("Tipo de Usuario:");
    
    linfo = gtk_label_new(" ");
    datos.linfo = linfo;
    lres = gtk_label_new(" ");
    datos.lres = lres;
    
    tusuario = gtk_entry_new();
    datos.tusuario = tusuario;
    
    //Creación de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio8 = gtk_label_new(" ");
    espacio13 = gtk_label_new(" ");
    espacio14 = gtk_label_new(" ");
    espacio15 = gtk_label_new(" ");
    espacio16 = gtk_label_new(" ");
    espacio17 = gtk_label_new(" ");
    espacio18 = gtk_label_new(" ");
    
    bbusca = add_button("Buscar",BuscaTipo,&datos);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    hbox5 = gtk_hbox_new(FALSE,5);
    hbox6 = gtk_hbox_new(FALSE,5);
    hbox7 = gtk_hbox_new(FALSE,5);
    hbox8 = gtk_hbox_new(FALSE,5);
    hbox9 = gtk_hbox_new(FALSE,5);
    hbox10 = gtk_hbox_new(FALSE,5);
    hbox11 = gtk_hbox_new(FALSE,5);
    
    vbox = gtk_vbox_new(FALSE,5);

    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);

    gtk_box_pack_start_defaults(GTK_BOX(hbox4),lusuario);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),tusuario);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio8);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio13);

    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio14);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),bbusca);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio15);

    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio16);

    gtk_box_pack_start_defaults(GTK_BOX(hbox8),linfo);

    gtk_box_pack_start_defaults(GTK_BOX(hbox9),espacio17);

    gtk_box_pack_start_defaults(GTK_BOX(hbox10),lres);

    gtk_box_pack_start_defaults(GTK_BOX(hbox11),espacio18);
    
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox6);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox7);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox8);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox9);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox10);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox11);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

int Amigos(GtkWidget *widget, gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana;
    GtkWidget *bagregar, *bquitar;

    GtkWidget *hbox0, *hbox1, *hbox2;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4;

    St_busca_usuario *anterior = (St_busca_usuario *)data;
    St_busca_usuario datos;
    
    datos.numcuenta = anterior->numcuenta;
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    datos.ventana = ventana;
    gtk_window_set_title(GTK_WINDOW(ventana), "Agregar o eliminar amigos");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    //Creación de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");

    bagregar = add_button("Agregar amigo",VAgregarAmigo,&datos);
    bquitar = add_button("Eliminar amigo",VEliminarAmigo,&datos);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,15);
    hbox2 = gtk_hbox_new(FALSE,5);
    vbox = gtk_vbox_new(FALSE,5);

    /* Empaquetado */
    gtk_box_pack_start_defaults(GTK_BOX(hbox0), espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), bagregar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), bquitar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2), espacio4);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;  
}

int VAgregarAmigo(GtkWidget *boton, gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana;

    GtkWidget *lelemento, *telemento, *belimina, *lestatus;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5;
 
    St_busca_usuario *datos = (St_busca_usuario*) data;
    gtk_widget_destroy(datos->ventana);
    
    St_busca_usuario datos1;
    datos1.numcuenta = datos->numcuenta; 
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Agregar amigo");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    lelemento = gtk_label_new("Número de cuenta o apellido paterno:");

    //Creacion de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");

    lestatus = gtk_label_new(" ");
    datos1.linfo = lestatus;

    telemento = gtk_entry_new();
    datos1.tusuario = telemento;

    belimina = add_button("Agregar amigo",AgregaAmigo,&datos1);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
 
    vbox = gtk_vbox_new(FALSE,5);

    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lelemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),telemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),lestatus);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),belimina);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();
    
    return 0;
}

int VEliminarAmigo(GtkWidget *boton, gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana;

    GtkWidget *lelemento, *telemento, *belimina, *lestatus;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5;
 
    St_busca_usuario *datos = (St_busca_usuario*) data;
    gtk_widget_destroy(datos->ventana);
    
    St_busca_usuario datos1;
    datos1.numcuenta = datos->numcuenta; 
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Eliminar amigo");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    lelemento = gtk_label_new("Número de cuenta o apellido paterno:");

    //Creacion de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");

    lestatus = gtk_label_new(" ");
    datos1.linfo = lestatus;

    telemento = gtk_entry_new();
    datos1.tusuario = telemento;

    belimina = add_button("Eliminar",EliminaAmigo,&datos1); 

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);
    
    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lelemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),telemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),lestatus);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),belimina);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

int VTodosLosUsuarios(GtkWidget *boton, gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana, *scroll, *usuarios, *vbox;
    int rs_size;
    char *resultset;
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Todos los usuarios");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);
    gtk_widget_set_size_request(ventana, 900, 300);
    
    //Obtener cada usuario
    rs_size = MySQLget_resultset_size("SELECT nombre, appaterno, apmaterno, carrera, semestre, nacimiento, numcuenta, correo FROM pf_usuarios");
    resultset = malloc(sizeof(char)*(rs_size+1));
    resultset = MySQLget_user("SELECT nombre, appaterno, apmaterno, carrera, semestre, nacimiento, numcuenta, correo FROM pf_usuarios");
    resultset[rs_size + 1] = '\0';
    
    //Empaquetado
    scroll = gtk_scrolled_window_new(NULL, NULL);
    usuarios = gtk_label_new(resultset);
    
    gtk_container_set_border_width(GTK_CONTAINER(scroll), 5);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll), usuarios);

    vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), scroll);
    
    gtk_container_add(GTK_CONTAINER(ventana), vbox);
    gtk_widget_show_all(ventana);
    
    gtk_main();
    
    return 0;
}

int MisAmigos(GtkWidget *widget, gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana, *scroll, *usuarios, *vbox;
    int rs_size;
    char *resultset, query[200], query2[200], id[2];
    
    St_busca_usuario *anterior = (St_busca_usuario *)data;
    St_registra datos;
    
    datos.numcuenta = anterior->numcuenta;
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Mis Amigos");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);
    gtk_widget_set_size_request(ventana, 900, 300);
    
    //Obtener todos los amigos del usuario
    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos.numcuenta);
    strcpy(id,MySQLget_one(query));
    sprintf(query2,"SELECT nombre, appaterno, apmaterno, carrera, semestre, nacimiento, numcuenta, correo FROM pf_amigos a, pf_usuarios WHERE a.idUsuario = %s AND a.idAmigo = pf_usuarios.idUsuario",id);
    rs_size = MySQLcheck(query2);
    
    if(rs_size!=0){ //Validar que el usuario tenga amigos
        rs_size = MySQLget_resultset_size(query2);
        resultset = malloc(sizeof(char)*(rs_size+1));
        resultset = MySQLget_user(query2);
        resultset[rs_size + 1] = '\0';
        
    }
    else{
        //g_print("Negative Size: %d\n",rs_size);
        resultset = MySQLget_user(query2);
    }

    //Empaquetado
    scroll = gtk_scrolled_window_new(NULL, NULL);
    usuarios = gtk_label_new(resultset);
    
    gtk_container_set_border_width(GTK_CONTAINER(scroll), 5);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll), usuarios);

    vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), scroll);
    
    gtk_container_add(GTK_CONTAINER(ventana), vbox);
    gtk_widget_show_all(ventana);
    
    gtk_main();
    
    return 0;
}

int InvitaAmigos(gpointer data){
    
    //Declaracion de variables
    GtkWidget *ventana;

    GtkWidget *lelemento, *comboamigo, *belimina, *lestatus, *bregresa;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6;

    char *idUsuario, query[300], total[40];
    int usuario;
    
    St_comandas *datos = (St_comandas*) data;
    St_comandas datos1;

    //Obtener el id del usuario
    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",datos->numcuenta);
    idUsuario = MySQLreturn(query);
    usuario = atoi(idUsuario); 
    
    datos1.numcuenta = datos->numcuenta;
    datos1.pedido = datos->pedido;
    datos1.total = datos->total;
    
    for(int i = 0 ; i < datos->pedido ; i++){
        
        datos1.pedidos[i] = datos->pedidos[i];
    }
    
    //Obtener los amigos de dicho usuario 
    sprintf(query,"SELECT u.numcuenta, u.nombre, u.appaterno FROM pf_amigos a, pf_usuarios u WHERE a.idUsuario = %i AND a.idAmigo = u.idUsuario",usuario);
    comboamigo = get_my_friends(query);
    datos1.comboamigo = comboamigo; 
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    datos1.ventana = ventana;
    gtk_window_set_title(GTK_WINDOW(ventana), "Selección amigo");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    lelemento = gtk_label_new("Selecciona un amigo:"); 

    //Creacion de espacios y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" "); 
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");

    sprintf(total,"Total de tu compra: %.2f",datos1.total);
    lestatus = gtk_label_new(total);

    belimina = add_button("Comprar",RegistrarCompraAmigos,&datos1);
    bregresa = add_button("Regresar",Regresar,&datos1);
    
    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5); 
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);

    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lelemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),comboamigo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),lestatus);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),belimina);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),bregresa);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio6);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

/* @brief Esta función despliega una ventana que pide al administrador (es una ventana de solo administrador) el número de cuenta o apellido paterno del cual se desea
 * obtener la información de las búsquedas que ha realizado, abrirá una ventana de tipo scroll window para poder mostrar la información en pantalla */

int VerBusquedas(GtkWidget *widget, gpointer data){
    
    GtkWidget *ventana;

    GtkWidget *lelemento, *telemento, *belimina, *lestatus;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5;
 
    St_busca_usuario usuario;
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    usuario.ventana = ventana;
    gtk_window_set_title(GTK_WINDOW(ventana), "Búsquedas usuario");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    lelemento = gtk_label_new("Número de cuenta o apellido paterno:");

    //Creacion de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");

    lestatus = gtk_label_new(" ");
    usuario.linfo = lestatus;

    telemento = gtk_entry_new();
    usuario.tusuario = telemento;

    belimina = add_button("Consultar",ImprimeBusquedas,&usuario); 

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);
    
    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lelemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),telemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),lestatus);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),belimina);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio5);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();
    
    return 0;
}

/* @brief Se despliega una ventana que despliega en pantalla el subtotal de la compra, con la posibilidad de concretar la compra o bien, regresar
 * a la ventana del menú para poder seguir comprando o no comprar nada en absoluto */

int ConfirmaCompra(gpointer data){
    
    //Declaración de variables
    GtkWidget *ventana;
    GtkWidget *bagregar, *bquitar;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;// *hbox5;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6, *espacio7; //*espacio8;
    GtkWidget *ltotal;
    
    char total[300];

    St_comandas *comanda = (St_comandas*) data;
    St_comandas comanda1;
    
    comanda1.pedido = comanda->pedido;
    comanda1.numcuenta = comanda->numcuenta;
    comanda1.carrito = comanda->carrito;
    
    //g_print("%s",comanda1.numcuenta); 
    
    for(int i = 0 ; i < comanda->pedido ; i++){
        
        comanda1.pedidos[i] = comanda->pedidos[i];
    }
    
    //Creación de la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    comanda1.ventana = ventana;
    gtk_window_set_title(GTK_WINDOW(ventana), "Confirmar compra");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);
    
    sprintf(total,"El total de tu compra es de %.2f",comanda->total);
    
    //Creacion de espacios y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio7 = gtk_label_new(" ");
    //espacio8 = gtk_label_new(" ");

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    //hbox5 = gtk_hbox_new(FALSE,5);
    
    vbox = gtk_vbox_new(FALSE,5);
    
    ltotal = gtk_label_new(total);
    
    //Creación de botones 
    bagregar = add_button("Comprar",RegistrarCompra,&comanda1);
    bquitar = add_button("Regresar",Regresar,&comanda1);

    /* Empaquetado */
    gtk_box_pack_start_defaults(GTK_BOX(hbox3), espacio5);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacio6);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), ltotal);
    gtk_box_pack_start_defaults(GTK_BOX(hbox4), espacio7);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox0), espacio0);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), bagregar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio2);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), bquitar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1), espacio3);
    gtk_box_pack_start_defaults(GTK_BOX(hbox2), espacio4);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    //gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5); 
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();
 
    return 0;
}

/* @brief Muestra el consumo del mes en curso en pantalla así como también el consumo del mes seleccionado, ambos datos se muestran con su respectivo
 * descuento (20% de descuento sobrel el total) */

int MiConsumo(GtkWidget *widget, gpointer data){
    
    GtkWidget *ventana, *meses, *lconsumomes, *bconsultar;
    GtkWidget *lconsumo;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5, *hbox6, *hbox7;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6, *espacio7, *espacio8, *espacio9;
    GtkWidget *espacio10, *espacio11;
    
    char *mes[12] = {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
    char fecha[3], cdelmes[80],query[300];
    float cmes;
    int id; 
    St_busca_usuario* datos = (St_busca_usuario*) data;
    St_comandas comanda;
    
    comanda.numcuenta = datos->numcuenta;
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Mi consumo");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    meses = gtk_combo_box_new_text();
    comanda.comboamigo = meses;

    for(int i = 0 ; i < 12 ; i++){gtk_combo_box_append_text(GTK_COMBO_BOX(meses),mes[i]);}
    
    time_t t = time(NULL);  
    struct tm *tiempolocal = localtime(&t);
    strftime(fecha,3,"%m",tiempolocal);
    
    sprintf(query,"SELECT idUsuario FROM pf_usuarios WHERE numcuenta = '%s'",comanda.numcuenta);
    id = atoi(MySQLreturn(query));
    
    sprintf(query,"SELECT m.precio FROM pf_comandas c, pf_menu m WHERE idUsuario = %i AND c.orden = m.idElemento AND EXTRACT(MONTH FROM c.fecha) = %i",id,atoi(fecha));
    
    if(MySQLcheck(query) >= 1){
    
        sprintf(query,"SELECT SUM(m.precio) FROM pf_comandas c, pf_menu m WHERE idUsuario = %i AND c.orden = m.idElemento AND EXTRACT(MONTH FROM c.fecha) = %i",id,atoi(fecha));
        cmes = atof(MySQLreturn(query));
        
        if(atoi(fecha) == 1){sprintf(cdelmes,"Consumo del mes de enero: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 2){sprintf(cdelmes,"Consumo del mes de febrero: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 3){sprintf(cdelmes,"Consumo del mes de marzo: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 4){sprintf(cdelmes,"Consumo del mes de abril: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 5){sprintf(cdelmes,"Consumo del mes de mayo: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 6){sprintf(cdelmes,"Consumo del mes de junio: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 7){sprintf(cdelmes,"Consumo del mes de julio: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 8){sprintf(cdelmes,"Consumo del mes de agosto: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 9){sprintf(cdelmes,"Consumo del mes de septiembre: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 10){sprintf(cdelmes,"Consumo del mes de octubre: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 11){sprintf(cdelmes,"Consumo del mes de noviembre: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
        if(atoi(fecha) == 12){sprintf(cdelmes,"Consumo del mes de diciembre: %.2f\nDescuento vigente: %.2f\nTotal: %.2f",cmes, cmes*0.2, cmes*0.8);}
    
        lconsumo = gtk_label_new(cdelmes);
         
    }else{lconsumo = gtk_label_new("Aun no existe ningún registro de consumo en este mes.");}
    
    lconsumomes = gtk_label_new(" ");
    comanda.linfo = lconsumomes;
    
    //Creacion de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio7 = gtk_label_new(" ");
    espacio8 = gtk_label_new(" ");
    espacio9 = gtk_label_new(" ");
    
    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");
    
    bconsultar = add_button("Consultar",ConsumoMes,&comanda);

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    hbox5 = gtk_hbox_new(FALSE,5);
    hbox6 = gtk_hbox_new(FALSE,5);
    hbox7 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);

    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lconsumo);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),espacio3);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),meses);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio5);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio6);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio7);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),bconsultar);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio8);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio9);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),lconsumomes);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio10);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio11);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox6);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}

/* @brief Ventana que despliga información del consumo mensual de un usuario determinado busca de acuerdo a dos criterios, ya sea por apellido paterno
 * o bien por el número de cuenta del usuario, se deberá seleccionar un mes del cual se quiere obtener la información */

int ConsumoUsuarios(GtkWidget *widget, gpointer data){

    GtkWidget *ventana;

    GtkWidget *lelemento, *telemento, *belimina, *lestatus, *meses;

    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5, *hbox6, *hbox7;
    GtkWidget *vbox;

    GtkWidget *espacio0, *espacio1, *espacio2, *espacio3, *espacio4, *espacio5, *espacio6, *espacio7, *espacio8, *espacio9;
    GtkWidget *espacio10, *espacio11;
 
    char *mes[12] = {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
    St_comandas comanda;
    
    //Crear la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    comanda.ventana = ventana;
    gtk_window_set_title(GTK_WINDOW(ventana), "Consumo de usuarios");
    gtk_signal_connect(GTK_OBJECT(ventana),"destroy",G_CALLBACK(destroy),NULL);

    lelemento = gtk_label_new("Número de cuenta o apellido paterno:");

    meses = gtk_combo_box_new_text();
    comanda.comboamigo = meses;

    for(int i = 0 ; i < 12 ; i++){gtk_combo_box_append_text(GTK_COMBO_BOX(meses),mes[i]);}
    
    //Creacion de espacios, botones y cajas
    espacio0 = gtk_label_new(" ");
    espacio1 = gtk_label_new(" ");
    espacio2 = gtk_label_new(" ");
    espacio3 = gtk_label_new(" ");
    espacio4 = gtk_label_new(" ");
    espacio5 = gtk_label_new(" ");
    espacio6 = gtk_label_new(" ");
    espacio7 = gtk_label_new(" ");
    espacio8 = gtk_label_new(" ");
    espacio9 = gtk_label_new(" ");
    
    espacio10 = gtk_label_new(" ");
    espacio11 = gtk_label_new(" ");

    lestatus = gtk_label_new(" ");
    comanda.linfo = lestatus;

    telemento = gtk_entry_new();
    comanda.tusuario = telemento;

    belimina = add_button("Consultar",ConsumoMesUsuario,&comanda); 

    hbox0 = gtk_hbox_new(FALSE,5);
    hbox1 = gtk_hbox_new(FALSE,5);
    hbox2 = gtk_hbox_new(FALSE,5);
    hbox3 = gtk_hbox_new(FALSE,5);
    hbox4 = gtk_hbox_new(FALSE,5);
    hbox5 = gtk_hbox_new(FALSE,5);
    hbox6 = gtk_hbox_new(FALSE,5);
    hbox7 = gtk_hbox_new(FALSE,5);

    vbox = gtk_vbox_new(FALSE,5);
    
    //Empaquetado
    gtk_box_pack_start_defaults(GTK_BOX(hbox0),espacio0);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio1);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),lelemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),telemento);
    gtk_box_pack_start_defaults(GTK_BOX(hbox1),espacio2);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox2),espacio3);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio4);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),meses);
    gtk_box_pack_start_defaults(GTK_BOX(hbox3),espacio5);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox4),espacio6);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio7);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),belimina);
    gtk_box_pack_start_defaults(GTK_BOX(hbox5),espacio8);
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio9);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),lestatus);
    gtk_box_pack_start_defaults(GTK_BOX(hbox6),espacio10); 
    
    gtk_box_pack_start_defaults(GTK_BOX(hbox7),espacio11);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox0);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox1);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox2);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox3);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox4);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox6);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox7);

    gtk_container_add(GTK_CONTAINER(ventana), vbox);

    gtk_widget_show_all(ventana);
    gtk_main();

    return 0;
}