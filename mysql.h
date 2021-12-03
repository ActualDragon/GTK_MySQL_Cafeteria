int MySQLcheck(char query[]); //Revisar si el query arroja un empty set
int MySQLconnection(char query[]); //Conectar a MySQL
int MySQLprocedure(char procedure[], char query[]); //Realizar un procedimiento
int MySQLfind_user(char query[], char userf[], char pass[]); //Encontrar el usuario
int MySQLfind_element(char query[], char find[]); //Encontrar un elemento
int MySQLadd(char query[]); //Añadir a la base de datos
int MySQLdelete(char query[]); //Borrar de la base de datos
int MySQLexecute_query(char query[]); //Ejecutar un query
char* MySQLget_user(char query[]); //Obtener los datos de un usuario
char* MySQLreturn(char query[]); 
char* MySQLget_one(char query[]);
long MySQLget_resultset_size(char query[]);
char* MySQLget_busca(char query[]);
long MySQLget_search_size(char query[]);

int MySQLcheck(char query[]){
    
    char buffer[1024];
	
    strcpy(buffer,query);
  
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
  
    MYSQL mysql;
    MYSQL_RES *res;
  
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
        
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
        
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    if( !(res = mysql_store_result(&mysql)) ){
        
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

   if(mysql_num_rows(res) == 0){
        
        //printf("\nNo hay coincidencias.");
        mysql_free_result(res);
        mysql_close(&mysql);
        return 0;

   }else if(mysql_num_rows(res) == 1){
      
      mysql_free_result(res);
      mysql_close(&mysql);
      return 1;
      
   }else if(mysql_num_rows(res) > 1){

        //printf("\nTu busqueda arrojo mas de una coincidencia\n");
        //printf("Se recomienda buscar por ID del usuario.\n");
        mysql_free_result(res);
        mysql_close(&mysql);
        return 2;
   }

    return -1;  
}

int MySQLconnection(char query[]){
    
    char buffer[1024];      
    unsigned int i = 0;
      
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
  
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
  
    mysql_init(&mysql);
  
    strcpy(buffer, query);
    
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
        
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
        
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
    
    res = mysql_store_result(&mysql);
  
    if(!(res)){
        
        printf("\nNo hay coincidencias!\n");
        return 2;
    }
  
    while( (row = mysql_fetch_row(res)) ){
        
        i = 0;
    
        for( i=0 ; i < mysql_num_fields(res); i++ ){
      
            if(row[i] != NULL){
	
                printf("%s ",row[i]);
            
            }else{
                
                printf(" \n");
            }
        }
            fputc('\n',stdout);
    }
  
    mysql_free_result(res);
    mysql_close(&mysql);
    
    return 0;
}

int MySQLprocedure(char procedure[], char query[]){
    
    char buffer[1024];
	
    strcpy(buffer,procedure);
  
    unsigned int i = 0;
  
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
    
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
  
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
  
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
  /* Hace el procedimiento */
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
  
    strcpy(buffer,query);
  
  /* Hace el query */
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
  
    res=mysql_store_result(&mysql);
    if(!(res)){
  
        printf("\nNo hay coincidencias!\n");
        return 2;
    }
  
    while( (row = mysql_fetch_row(res)) ){
        
        i = 0;
    
        for( i=0 ; i < mysql_num_fields(res); i++ ){
            
            if(row[i] != NULL){
      
                printf("%s ",row[i]);
            
            }else{
	
                printf(" \n");
            }
        }
        
        fputc('\n',stdout);
    }
  
    mysql_free_result(res);
    mysql_close(&mysql);
    
    return 0;
}

int MySQLfind_user(char query[], char userf[], char pass[]){
   
   char buffer[1024];
	
    strcpy(buffer,query);
  
    unsigned int i = 0;

    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
    
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
  
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
  
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
  /* Hace el query */
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
  
    res=mysql_store_result(&mysql);
    if(!(res)){
  
        printf("\nNo hay coincidencias!\n");
        return 2;
    }
  
    while( (row = mysql_fetch_row(res)) ){
        
        i = 0;
    
        for( i=0 ; i < mysql_num_fields(res); i+=2 ){
            
            if(row[i] != NULL){
      
                if(strcmp(userf,row[i]) == 0 && strcmp(pass,row[i+1]) == 0){
                    
                    return 1;
                }
            }
        }
    }
  
    mysql_free_result(res);
    mysql_close(&mysql);
    
    return 0;   
}

int MySQLfind_element(char query[], char find[]){
   
    char buffer[1024];
    strcpy(buffer,query);
  
    unsigned int i = 0;
  
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
    
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
  
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
  
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
  /* Hace el query */
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
  
    res=mysql_store_result(&mysql);
    if(!(res)){
  
        printf("\nNo hay coincidencias!\n");
        return 2;
    }
  
    while( (row = mysql_fetch_row(res)) ){
        
        i = 0;
    
        for( i=0 ; i < mysql_num_fields(res); i++ ){
            
            if(row[i] != NULL){
      
                if(strcmp(find,row[i]) == 0){
                    
                    return 1;
                }
            }
        }
    }
  
    mysql_free_result(res);
    mysql_close(&mysql);
    
    return 0; 
}

int MySQLadd(char query[]){
   
   char buffer[1024];
	
    strcpy(buffer,query);
  
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
    
    MYSQL mysql;
  
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
  
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
  /* Hace el query */
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
   
   return 0;
}

int MySQLdelete(char query[]){
   
   char buffer[1024];
	
    strcpy(buffer,query);
  
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
    
    MYSQL mysql;
  
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
  
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
  /* Hace el query */
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
    
    return 0;
}

int MySQLexecute_query(char query[]){
   
   char buffer[1024];
	
    strcpy(buffer,query);
  
    char *server = "localhost";
    char *user = "ib19brc";
    char *passwd = "209275";
    char *db = "ib19brc";
    
    MYSQL mysql;
  
    mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
  
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
  /* Hace el query */
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
    
    return 0;
}

char* MySQLget_user(char query[]){
   
   char buffer[1024], rs[131072];
   char *return_rs = " ";
   strcpy(buffer,query);
  
   char *server = "localhost";
   char *user = "ib19brc";
   char *passwd = "209275";
   char *db = "ib19brc";
   
   int i = 0;
    
   MYSQL mysql;
   MYSQL_RES *res;
   MYSQL_ROW row;
  
   mysql_init(&mysql); 
  
   if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
      fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
      return(0);
   }
  
   if( mysql_select_db(&mysql,"ib19brc") ){
  
      fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
      exit(1);
   }
  
  /* Hace el query */
  
   if( mysql_query(&mysql,buffer) ){
        
      fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
      exit(1);
   }
  
   res=mysql_store_result(&mysql);
    
   if(!(res)){
  
      printf("\nNo hay coincidencias!\n");
      return " ";
   }
   
   if(mysql_num_rows(res) == 0){
        
      return_rs = "Tu búsqueda no arrojó resultados.";
      mysql_free_result(res);
      mysql_close(&mysql);
      return return_rs;
   }
   
   while((row = mysql_fetch_row(res))){
    
      if(i == 0){
         
         sprintf(rs,"Nombre: %s %s %s     Carrera: %s    Semestre: %s      Nacimiento: %s    Número de cuenta: %s    Correo: %s\n\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]);
         i++;
      
      }else{
         
         sprintf(rs,"%sNombre: %s %s %s     Carrera: %s    Semestre: %s      Nacimiento: %s    Número de cuenta: %s    Correo: %s\n\n",rs,row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]);
      }
   }
  
   //g_print("\n\n%li\n\n",strlen(rs));
   //g_print("\n\nFunción sql\n\n%s",rs);
   //g_print("\n\n");
   return_rs = malloc(sizeof(char)*strlen(rs));
   return_rs = rs;
   mysql_free_result(res);
   mysql_close(&mysql);
         //char *
   return return_rs; 
}

char* MySQLget_one(char query[]){
   
   char buffer[1024], rs[5000];
   char *return_rs = " ";
   strcpy(buffer,query);
  
   char *server = "localhost";
   char *user = "ib19brc";
   char *passwd = "209275";
   char *db = "ib19brc";
   
   int i = 0;
    
   MYSQL mysql;
   MYSQL_RES *res;
   MYSQL_ROW row;
  
   mysql_init(&mysql); 
  
   if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
      fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
      return(0);
   }
  
   if( mysql_select_db(&mysql,"ib19brc") ){
  
      fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
      exit(1);
   }
  
  /* Hace el query */
  
   if( mysql_query(&mysql,buffer) ){
        
      fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
      exit(1);
   }
  
   res=mysql_store_result(&mysql);
    
   if(!(res)){
  
      printf("\nNo hay coincidencias!\n");
      return " ";
   }
   
   if(mysql_num_rows(res) == 0){
        
      return_rs = "Tu búsqueda no arrojó resultados.";
      mysql_free_result(res);
      mysql_close(&mysql);
      return return_rs;
   }
   
   while((row = mysql_fetch_row(res))){
    
      if(i == 0){
         
         sprintf(rs,"%s",row[0]);
         i++;
      
      }else{
         
         sprintf(rs,"%s",row[0]);
      }
   }
  
   //g_print("\n\n%li\n\n",strlen(rs));
   //g_print("\n\nFunción sql\n\n%s",rs);
   //g_print("\n\n");
   return_rs = malloc(sizeof(char)*strlen(rs));
   return_rs = rs;
   mysql_free_result(res);
   mysql_close(&mysql);
         //char *
   return return_rs; 
}

char* MySQLreturn(char query[]){
   
   char buffer[1024];      
   
   char *server = "localhost";
   char *user = "ib19brc";
   char *passwd = "209275";
   char *db = "ib19brc";
   
   char regresa[3];
   char *rregresa = " ";
  
   MYSQL mysql;
   MYSQL_RES *res;
   MYSQL_ROW row;
  
   mysql_init(&mysql);
  
   strcpy(buffer, query);
    
   if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
        
      fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
      return(0);
   }
  
   if( mysql_select_db(&mysql,"ib19brc") ){
        
      fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
      exit(1);
   }
  
   if( mysql_query(&mysql,buffer) ){
        
      fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
      exit(1);
   }
    
   res = mysql_store_result(&mysql);
  
   if(!(res)){
        
      printf("\nNo hay coincidencias!\n");
      return " ";
   }
  
   while( (row = mysql_fetch_row(res)) ){
        
      sprintf(regresa,"%s",row[0]);
      //g_print("%s",regresa);
   }
  
   rregresa = regresa;
   
   mysql_free_result(res);
   mysql_close(&mysql);
    
   return rregresa;
}

long MySQLget_resultset_size(char query[]){
   
   char buffer[1024], rs[131072];
   int i;
   long tam;
	
   strcpy(buffer,query);
  
   char *server = "localhost";
   char *user = "ib19brc";
   char *passwd = "209275";
   char *db = "ib19brc";
  
   MYSQL mysql;
   MYSQL_RES *res;
   MYSQL_ROW row;
  
   mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
        
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
        
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

   if( !(res = mysql_store_result(&mysql)) ){
        
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
   }
   
   if(mysql_num_rows(res) == 0){
      
      return -1;
   }
   
   while((row = mysql_fetch_row(res))){
    
      if(i == 0){
         
         sprintf(rs,"Nombre: %s %s %s     Carrera: %s    Semestre: %s      Nacimiento: %s    Número de cuenta: %s    Correo: %s\n\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]);
         i++;
      
      }else{
         
         sprintf(rs,"%sNombre: %s %s %s     Carrera: %s    Semestre: %s      Nacimiento: %s    Número de cuenta: %s    Correo: %s\n\n",rs,row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]);
      }
   }
    
   tam = strlen(rs);
   g_print("cantidad: %li\n",tam);
   
   return tam;
}

char* MySQLget_busca(char query[]){
   char buffer[1024], rs[131072];
   char *return_rs = " ";
   strcpy(buffer,query);
  
   char *server = "localhost";
   char *user = "ib19brc";
   char *passwd = "209275";
   char *db = "ib19brc";
   
   int i = 0;
    
   MYSQL mysql;
   MYSQL_RES *res;
   MYSQL_ROW row;
  
   mysql_init(&mysql); 
  
   if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
  
      fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
      return(0);
   }
  
   if( mysql_select_db(&mysql,"ib19brc") ){
  
      fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
      exit(1);
   }
  
  /* Hace el query */
  
   if( mysql_query(&mysql,buffer) ){
        
      fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
      exit(1);
   }
  
   res=mysql_store_result(&mysql);
    
   if(!(res)){
  
      printf("\nNo hay coincidencias!\n");
      return " ";
   }
   
   if(mysql_num_rows(res) == 0){
        
      return_rs = "Tu búsqueda no arrojó resultados.";
      mysql_free_result(res);
      mysql_close(&mysql);
      return return_rs;
   }
   
   while((row = mysql_fetch_row(res))){
    
      if(i == 0){
         
         sprintf(rs,"%s    Fecha: %s\n\n",row[0],row[1]);
         i++;
      
      }else{
         
         sprintf(rs,"%sBusqueda: %s    Fecha: %s\n\n",rs,row[0],row[1]);
      }
   }
  
   //g_print("\n\n%li\n\n",strlen(rs));
   //g_print("\n\nFunción sql\n\n%s",rs);
   //g_print("\n\n");
   return_rs = malloc(sizeof(char)*strlen(rs));
   return_rs = rs;
   mysql_free_result(res);
   mysql_close(&mysql);
         //char *
   return return_rs; 
}

long MySQLget_search_size(char query[]){
   
   char buffer[1024], rs[131072];
   int i;
   long tam;
	
   strcpy(buffer,query);
  
   char *server = "localhost";
   char *user = "ib19brc";
   char *passwd = "209275";
   char *db = "ib19brc";
  
   MYSQL mysql;
   MYSQL_RES *res;
   MYSQL_ROW row;
  
   mysql_init(&mysql); 
  
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
        
        fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
        return(0);
    }
  
    if( mysql_select_db(&mysql,"ib19brc") ){
        
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
  
    if( mysql_query(&mysql,buffer) ){
        
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

   if( !(res = mysql_store_result(&mysql)) ){
        
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
   }
   
   if(mysql_num_rows(res) == 0){
      
      return -1;
   }
   
   while((row = mysql_fetch_row(res))){
    
      if(i == 0){
         
         sprintf(rs,"Busqueda: %s    Fecha: %s\n\n",row[0],row[1]);
         i++;
      
      }else{
         
         sprintf(rs,"%sBusqueda: %s    Fecha: %s\n\n",rs,row[0],row[1]);
      }
   }
    
   tam = strlen(rs);
   g_print("cantidad: %li\n",tam);
   
   return tam;
}