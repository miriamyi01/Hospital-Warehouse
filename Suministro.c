#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<windows.h>

/*Menú de proveedor*/
void proveedor();
void prove_entrada(), prove_lista(), prove_actual();
void buscar(), buscar_id(), buscar_nombre();
/*Menú del cliente*/
void cliente();
void clien_buscar(), buscar_cid(), buscar_cnombre();
void clien_entrada(), clien_lista(), clien_actual();
/*Menú del medicamento*/
void medicina();
void medi_venta(), almacen(), actual_almacen();
void medi_entrada(), medi_buscar(), remanente();
/*Ticket*/
void ticket();
/*Sobre el programa*/
void sobre();
/*Menú de Reporte*/
void reporte_menu();
void venta_rpt(), venta_rpt_diaria();
void ganancia_rpt();
void com_rpt(), com_rpt_diaria();

/*====================== ESTRUCTURAS ======================*/
struct medicamento{
    char id[6];
	char medi_nombre[20];
	int rango;
	char gabinete[2];
	int cantidad;
	float venta;
	float total;
	float unidad;
	float costo;
	float ganancia;
	float salir;
	int num;
	char com_fecha[15];
	char caducidad_fecha[15];
	char manu_fecha[15];
	int ticket_no;
	char compania_nombre[20];
	char prove_nombre[30];
};

struct medicamento info;
struct medicamento x[20];
FILE *ptr;

char a[10];

struct ticket{
	char ticketno[6];
	char cnombre[30];
	char medir_nombre[30];
	int medi_num;
	float medi_iva;
	float total;
	int dia;
	int mes;
	int ano;
};
struct ticket tic;
FILE *ptrticket;

struct ventas_reporte{
	char medi_id[6];
	char medir_nombre[20];
	char clien_nombre[30];
	int sDia,sMes,sAno;
	int num;
	float iva;
	float total;
};
struct ventas_reporte s_r;
FILE *ptrs_r;

struct compra_reporte{
	char medi_id[6];
	char medir_nombre[20];
	char prove_nombre[30];
	int sDia,sMes,sAno;
	int num;
	float iva;
	float total;
};
struct compra_reporte p_r;
FILE *ptrp_r;

struct ganancia_reporte{
	char medi_id[6];
	char medir_nombre[20];
	int sDia,sMes,sAno;
	int num;
	float iva;
	float unidad;
	float ganancia;
};
struct ganancia_reporte pr_r;
FILE *ptrpr_r;

void linkfloat(){
	float f,*p;
	p=&f;
	f=*p;
}
/*========================== FECHA Y HORA ==========================*/
int h(void){
	/* Fecha (getfecha &d)
	Hora (gethora &h) */
    time_t h=time(0);  /*Tiempo real*/
    struct tm*now=localtime(&h);
	printf("\n\n\t\t\tFecha: %d/%d/%d", now->tm_mday,now->tm_mon,now->tm_year);
	printf("\n\t\t\t Hora: %d:%d:%d", now->tm_hour, now->tm_min,now->tm_sec);
	return 0;
}

/*       Incremento del identificador de cliente y proveedor       */
int i;

/*=========================== VALIDACION ===========================*/
void entrada(char t[],int codigo){
    int i=0;
	if(codigo==0){
		while((t[i]=getch())!='\r' && i<30)
		if((t[i]>=97 && t[i]<=122) || (t[i]>=65 && t[i]<=90) || t[i]==32 || t[i]=='_'){
			printf("%c",t[i]);
			i++;
		}
		else if(t[i]==8 && i>0){
			printf("%c%c%c",8,32,8);
			i--;              /*El contador se decrementa*/
		}
	}
	else if(codigo==1){
		while((t[i]=getch())!='\r' && i<10 )
		if((t[i]>=48 && t[i]<=57) || t[i]==46 ||  t[i]=='-'){
			printf("%c",t[i]);
			i++;
		}
		else if(t[i]==8 && i>0){
			printf("%c%c%c",8,32,8);
			i--;              /*El contador se decrementa*/

		}
	}
	else if(codigo==2){
		while((t[i]=getch())!='\r' && i<30 )
		if((t[i]>=97 && t[i]<=122) || (t[i]>=65 && t[i]<=90) ||(t[i]>=48 && t[i]<=57) || t[i]==32 || t[i]==8 ||t[i]=='@'||t[i]=='.'){
			printf("%c",t[i]);
			i++;
		}
		else if(t[i]==8 && i>0){
			printf("%c%c%c",8,32,8);
			i--;
		}
	}
	t[i]='\0';
}


/*==================== Estructura de proveedor ====================*/
struct proveedor{
	int prove_id;
	char prove_nombre[25];
	char lugar[20];
	char mobil_no[11];
	char email[30];
};
struct proveedor infos;
/*========================== getprove_id ==========================*/
int getprove_id(){
 FILE *fp;
    fp=fopen("proveedor.dat","r");
    if(fp==NULL){
		printf("\n Sin registro");
		getch();
    }
    else{
        infos.prove_id=100;
		rewind(fp);
		while(fscanf(fp,"%d %s %s %s %s", &infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
		}
    }
    fclose(fp);
    return infos.prove_id+1;
}

/*==================== Estructura del cliente ====================*/
struct cliente{
	int clien_id;
	char clien_nombre[30];
	char lugar[20];
	char mobil_no[11];
	char email[50];
};
struct cliente info_c;
FILE *ptr1;
/*========================== getclien_id ==========================*/
int getclien_id(){
 FILE *fp;
    fp=fopen("cliente.dat","r");
    if(fp==NULL){
        printf("Sin registro");
		getch();
    }
    else{
		info_c.clien_id=100;
		rewind(fp);
		while(fscanf(fp,"%d %s %s %s %s", &info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
		}
	 }
    fclose(fp);
    return info_c.clien_id+1;
}

/*                           Bienvenida y menú                           */
/*========================== Pantalla de Inicio ==========================*/
void bienvenida(){
    system("cls");
        printf("\t\t\tB I E N V E N I D O");
		printf("\n\nA TU");
		printf("TU REGISTRO LOCAL DE");
		printf("MEDICAMENTOS");
		printf("\n\tCargando......");
}

/*============================ Menú Principal ===========================*/
void main_menu(){
    int op;
    char ch;
    do{
        system("cls");
        printf("\t\t-------------------------------");
        printf("\n\t\t\t  BIENVENIDO\n");
        printf("\t\t  A TU SISTEMA MEDICO VIRTUAL\n");
        printf("\t\t-------------------------------\n");
		printf("\n\t1. Proveedor");
		printf("\n\t2. Cliente");
		printf("\n\t3. Medicamentos");
		printf("\n\t4. Reporte");
		printf("\n\t5. Ticket");
		printf("\n\t6. Sobre el programa");
		printf("\n\t7. Salir");
		h();    /*Funcion (fecha y tiempo)*/
		remainder();    /*Funcion (Medicamentos<10)*/
		printf("\n\n\t N%cmero de la opci%cn a realizar: ",163,162);
		scanf("%d", &op);
        switch(op){
            case 1 :proveedor();
                break;
			case 2 :cliente();
                break;
			case 3 :medicina();
                break;
			case 4 :reporte_menu();
                break;
			case 5 :ticket();
                break;
			case 6 :sobre();
                break;
			case 7:
                printf("\n%cDeseas salir ahora? S/N: ", 168);
                ch=(getche());
                ch=toupper(ch);
                if(ch=='S'){
                    system("cls");
                    printf("\nEspera un momento....");
                    exit(0);
                }
                else{
                    main_menu();
                }
			default:
			printf("\nFavor de ingresar SOLAMENTE los n%cmeros (1-7)", 163);
			getch();
		}
	}
	while(op!=7);
}

/*========================== Funcion Principal ==========================*/
int main(){
	system("cls");
    main_menu();
}


/*========================== Sobre el Programa ========================*/
void sobre(){
    int c;
    system("cls");
    do{
        printf("\n\t\t***** REGISTRO LOCAL DE MEDICAMENTOS *****");
        printf("\n\tEste proyecto es un administrador local, donde podr%cs:",160);
        printf("\n\t o A%cadir MEDICAMENTOS, CLIENTES y PROVEDORES (Detalladamente)", 164);
        printf("\n\t o Modificar y eliminar los registros");
        printf("\n\t o Buscar Medicina, Cliente, Proveedor y sus detalles");
        printf("\n\t o Consultar el Balance General:");
        printf("\n\t      - Perdidas y Ganancias");
        printf("\n\t      - Compras y Ventas");
        printf("\n\t o Revisar el inventario y el registro de tickets\n", 160);
        printf("\n\n\n\t     ----- Presiona 1 para ir al Men%c Principal -----\t", 163);
        scanf("%d", &c);
        switch(c){
            case 1 :main_menu();
            puts("\nPresiona 1, por favor");
            getch();
        }
    }
    while(c!=1);
}


/*============================== PROVEEDOR ==============================*/
/*========================== Menú de Proveedor ==========================*/
void proveedor(){
    int opp, u=163;
    do{
        system("cls");
        printf("\t\t--------------------");
        printf("\n\t\t MEN%c DEL PROOVEDOR\n", 233);
        printf("\t\t--------------------");
        printf("\n\t1. A%cadir Proveedor", 164);
        printf("\n\t2. Actualizar Proveedor");
        printf("\n\t3. Buscar Proveedor");
        printf("\n\t4. Lista de Proveedores");
        printf("\n\t5. Men%c Principal", u);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ", u, 162);
        scanf("%d",&opp);

        switch(opp){
            case 1 :prove_entrada();
                break;
            case 2 :prove_actual();
                break;
            case 3 :buscar();
                break;
            case 4 :prove_lista();
                break;
            case 5 :main_menu();
                break;
            default:
                printf("\nFavor de ingresar SOLAMENTE los n%cmeros (1-5)", 163);
                getch();
        }
    }
    while(opp!=5);
}

/*========================= Añadir Proveedor ==========================*/
void prove_entrada(){
    int id, op;
    char ch;
    FILE *fp;
    system("cls");

    fp=fopen("proveedor.dat","a");
    if(fp==NULL){
        printf("\n No hay registro");
		exit(0);
    }
    system("cls");
    ch='S';
    while(ch=='S'){
        system("cls");

		printf("\n\n\t\tA%cADE UN PROOVEDOR", 165);
		infos.prove_id=getprove_id();
		printf("\n\n\tID DEL PROVEEDOR: %d ",infos.prove_id);
		printf("\n\tNOMBRE DEL PROVEEDOR: ");
		entrada(infos.prove_nombre,0);
		printf("\n\tCIUDAD: ");
		entrada(infos.lugar,0);
		printf("\n\tNO. DE CONTACTO: ");
		entrada(infos.mobil_no,1);
		printf("\n\tEMAIL: ");
		entrada(infos.email,2);
        h();
		printf("\n\t1. Guardar");
		printf("\n\t2. Cancelar");
		printf("\n\tTeclea el n%cmero de la opci%cn a realizar: ",163,162);
		scanf("%d", &op);
		if(op==1){
			fprintf(fp,"%d %s %s %s %s\n\n",infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email);
			fprintf(fp,"\n");
			system("cls");
			printf("\tProveedor a%cadido con %cxito",164, 130);
			printf("\nM%cs datos [S/N]: ",160);
            ch=getche();
        }
    }
    fclose(fp);
}

/*================ Actualizar Información del Proveedor ===============*/
void prove_actual(){
    int i, op;
    char ch;
    int pid;
    FILE *ft;
    system("cls");
    ptr1=fopen("proveedor.dat","rb+");
    if(ptr1==NULL ){
        printf("\n\t No hay registro");
		exit(0);
    }
    printf("\nMODIFICAR PROVEEDOR");
    printf("\n\tIntroduce el ID del proveedor:  ");
    scanf("%d",&pid);
    ft=fopen("proveedor.dat","w");
    if(ft==NULL){
        printf("No hay registro");
        exit(1);
    }
    else{
        while(fscanf(ptr1,"%d %s %s %s %s",&infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
            if(infos.prove_id==pid){
                printf(" Registro Existente  ");
                printf("%d %s %s %s %s",infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email);
                printf("Nuevo nombre: ");
                entrada(infos.prove_nombre,0);
                printf("Nuevo N%cmero: ", 163);
                entrada(infos.mobil_no,1);
                printf("Nueva Ciudad: ");
                entrada(infos.lugar,0);
                printf("Nuevo Email: ");
                entrada(infos.email,2);
                printf("\n1. Guardar");
                printf("\n2. Cancelar");
                printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ");
                scanf("%d", op);
                if(op==1){
                    fprintf(ft,"%d %s %s %s %s\n",infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email);
                    printf("Actualizaci%cn exitosa", 162);
                    remove("infos.dat");
                    rename("infos.dat","proveedor.dat");
                }
            }
        else{
            fprintf(ft,"%d %s %s %s %s\n",infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email);
            fflush(stdin);
        }
        }
    fclose(ft);
    fclose(ptr1);
    }
}

/*======================== Lista de Proveedores =======================*/
void prove_lista(){
    char ch;
    int j;
    system("cls");
    ptr1=fopen("proveedor.dat","r");
    if(ptr1==NULL){
        printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("\nPresiona cualquier tecla para volver al Men%c del Proveedor", 163);
    printf("\nLISTA DE PROVEEDORES");
    printf("ID.  NOMBRE.      CIUDAD.     NO.         EMAIL");
    printf("================================================");
    while(fscanf(ptr1,"%d %s %s %s %s",&infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
		printf(" %d",infos.prove_id);
		printf(" %s",infos.prove_nombre);
		printf(" %s",infos.lugar);
		printf(" %s",infos.mobil_no);
		printf(" %s",infos.email);
    }
    getche();
}

/*========================= Buscar Proveedores ========================*/
void buscar(){
    int opb;
    do{
        system("cls");
        printf("Tienes dos opciones para buscar:");
	    printf("1. N%cmero ID", 163);
        printf("2. Nombre");
        printf("3. Regresar");
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ", 163, 162);
        scanf("%d", &opb);
        switch(opb){
            case 1: buscar_id();
                break;
            case 2: buscar_nombre();
                break;
            case 3: proveedor();
                break;
            default:
                printf("\nFavor de ingresar SOLAMENTE los n%cmeros (1-3)");
                getch();
	   }
    }
    while(opb!=3);
}
/*============================== Buscar ID ============================*/
void buscar_id(){
    int id;
    FILE *fp;
    fp=fopen("proveedor.dat","r");
    if(fp==NULL){
	     printf("\n No hay registro");
    }
    system("cls");
    printf("Ingresa el ID del proveedor a buscar:");
    scanf("%d",&id);
    printf("\nPresiona cualquier tecla para volver al Men%c", 163);
    printf("ID.  NOMBRE.      CIUDAD.     NO.         EMAIL");
    printf("================================================");
    while(fscanf(fp,"%d %s %s %s %s",&infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
        if(infos.prove_id==id){
			printf(" %d",infos.prove_id);
			printf(" %s",infos.prove_nombre);
			printf(" %s",infos.lugar);
			printf(" %s",infos.mobil_no);
			printf(" %s",infos.email);
			break;
		}
    }
    if(infos.prove_id!=id){
		printf("\n\nRegistro no encontrado");
    }
    fclose(fp);
    getche();
}
/*============================ Buscar Nombre ==========================*/
void buscar_nombre(){
    char nombre[20];
    FILE *fp;
    fp=fopen("proveedor.dat","r");
    if(fp==NULL){
        printf("\n No hay registro");
    }
    system("cls");
    fp=fopen("proveedor.dat","rb");
    printf("Ingresa el nombre del proveedor a buscar:");
    printf("\nPresiona cualquier tecla para volver al Men%c", 163);
    printf("ID.  NOMBRE.      CIUDAD.     NO.         EMAIL");
    printf("================================================");
    while(fscanf(fp,"%d %s %s %s %s",&infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
        if(strcmp(infos.prove_nombre,nombre)==0){
			printf(" %d",infos.prove_id);
			printf(" %s",infos.prove_nombre);
			printf(" %s",infos.lugar);
			printf(" %s",infos.mobil_no);
			printf(" %s",infos.email);
			break;
        }
    }
    if(strcmp(infos.prove_nombre,nombre)!=0){
		printf("Registro no encontrado");
    }
    fclose(ptr1);
    getche();
}


/*============================== CLIENTE ==============================*/
/*========================== Menú de Cliente ==========================*/
void cliente(){
    int opc, u=163;
    do{
        system("cls");
        printf("\t\t--------------------");
        printf("\n\t\t  MEN%c DEL CLIENTE\n", 233);
        printf("\t\t--------------------");
        printf("\n\t1. A%cadir Cliente", 164);
        printf("\n\t2. Actualizar Cliente");
        printf("\n\t3. Buscar Cliente");
        printf("\n\t4. Lista de Clientes");
        printf("\n\t5. Men%c Principal", u);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ", u, 162);
        scanf("%d",&opc);

        switch(opc){
            case 1 :clien_entrada();
                break;
            case 2 :clien_actual();
                break;
            case 3 :clien_buscar();
                break;
            case 4 :clien_lista();
                break;
            case 5 :main_menu();
                break;
            default:
                printf("\nFavor de ingresar SOLAMENTE los n%cmeros (1-5)", 163);
                getch();
        }
    }
    while(opc!=5);
}

/*========================== Añadir Cliente ===========================*/
void clien_entrada(){
    int op, id;
    char ch;
    FILE *fp;
    system("cls");
    fp=fopen("cliente.dat","a");
    if(fp==NULL){
        printf("\n No hay registro");
		exit(0);
    }
    system("cls");
    ch='S';
    while(ch=='S'){
        system("cls");
		printf("\n\n\t\tA%cADE UN CLIENTE", 165);
		info_c.clien_id=getclien_id();
		printf("\n\n\tID DEL CLIENTE: %d",info_c.clien_id);
		printf("\n\tNOMBRE DEL CLIENTE: ");
		entrada(info_c.clien_nombre,0);
		printf("\n\tCIUDAD: ");
		entrada(info_c.lugar,0);
		printf("\n\tNO. DE CONTACTO: ");
		entrada(info_c.mobil_no,1);
		printf("\n\tEMAIL: ");
		entrada(info_c.email,2);
		h();
		printf("\n\t1. Guardar");
		printf("\n\t2. Cancelar");
		printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ",163);
		scanf("%d", &op);
		if(op==1){
			fprintf(fp,"%d %s %s %s %s\n\n",info_c.clien_id,info_c.clien_nombre,info_c.mobil_no,info_c.lugar,info_c.email);
			fprintf(fp,"\n");
			system("cls");
			printf("\tCliente a%cadido con %cxito",164, 130);
			printf("\nM%cs datos [S/N]: ",160);
			ch=getche();
        }
    }
    fclose(fp);
}
/*======================== Actualizar Cliente =========================*/
void clien_actual(){
    int i, op;
    char ch;
    int cid;
    FILE *ft;
    system("cls");
    ptr1=fopen("cliente.dat","rb+");
    if(ptr1==NULL ){
        printf("\n\t No hay registro");
		exit(0);
    }
    printf("\nMODIFICAR CLIENTE");
    printf("\n\tIntroduce el ID del cliente:  ");
    scanf("%d",&cid);
    ft=fopen("cliente.txt","w");
    if(ft==NULL){
        printf("No hay registro");
        exit(1);
    }
    else{
        while(fscanf(ptr1,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
            if(info_c.clien_id==cid){
                printf(" Registro Existente  ");
                printf("%d %s %s %s %s",info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email);
                printf("Nuevo nombre: ");
                entrada(info_c.clien_nombre,0);
                printf("Nuevo N%cmero: ", 163);
                entrada(info_c.mobil_no,1);
                printf("Nueva Ciudad: ");
                entrada(info_c.lugar,0);
                printf("Nuevo Email: ");
                entrada(info_c.email,2);
                printf("\n1. Guardar");
                printf("\n2. Cancelar");
                printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ");
                scanf("%d", op);
                if(op==1){
                    fprintf(ft,"%d %s %s %s %s\n",info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email);
                    printf("Actualizaci%cn exitosa", 162);
                    remove("info_c.dat");
                    rename("info_c.dat","cliente.dat");
                }
        }
            else{
                fprintf(ft,"%d %s %s %s %s\n",info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email);
                fflush(stdin);
            }
        }
    fclose(ft);
    fclose(ptr1);
    }
}

/*========================= Lista de Clientes =========================*/
void clien_lista(){
    char ch;
    int j;
    system("cls");
    ptr1=fopen("cliente.dat","r");
    if(ptr1==NULL){
        printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("\nPresiona cualquier tecla para volver al Men%c del Cliente", 163);
    printf("\nLISTA DE CLIENTES");
    printf("ID.  NOMBRE.      CIUDAD.     NO.         EMAIL");
    printf("================================================");
    while(fscanf(ptr1,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
        printf(" %d",info_c.clien_id);
        printf(" %s",info_c.clien_nombre);
        printf(" %s",info_c.lugar);
        printf(" %s",info_c.mobil_no);
        printf(" %s",info_c.email);
    }
    getche();
}

/*========================== Buscar Clientes ==========================*/
void clien_buscar(){
    int opb;
    do{
        system("cls");
        printf("Tienes dos opciones para buscar:");
	    printf("1. N%cmero ID", 163);
        printf("2. Nombre");
        printf("3. Regresar");
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ", 163, 162);
        scanf("%d", &opb);
        switch(opb){
            case 1: buscar_cid();
                break;
            case 2: buscar_cnombre();
                break;
            case 3: cliente();
                break;
            default:
                printf("\nFavor de ingresar SOLAMENTE los n%cmeros (1-3)");
                getch();
	   }
    }
    while(opb!=3);
}
/*============================== Buscar ID ============================*/
void buscar_cid(){
    int id;
    FILE *fp;
    fp=fopen("cliente.dat","r");
    if(fp==NULL){
	     printf("\n No hay registro");
    }
    system("cls");
    printf("Ingresa el ID del proveedor a buscar:");
    scanf("%d",&id);
    printf("\nPresiona cualquier tecla para volver al Men%c", 163);
    printf("ID.  NOMBRE.      CIUDAD.     NO.         EMAIL");
    printf("================================================");
    while(fscanf(fp,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
        if(info_c.clien_id==id){
			printf(" %d",info_c.clien_id);
			printf(" %s",info_c.clien_nombre);
			printf(" %s",info_c.lugar);
			printf(" %s",info_c.mobil_no);
			printf(" %s",info_c.email);
			break;
		}
    }
    if(info_c.clien_id!=id){
		printf("\n\nRegistro no encontrado");
    }
    fclose(fp);
    getche();
}
/*============================ Buscar Nombre ==========================*/
void buscar_cnombre(){
    char nombre[20];
    FILE *fp;
    fp=fopen("cliente.dat","r");
    if(fp==NULL){
        printf("\n No hay registro");
    }
    system("cls");
    fp=fopen("cliente.dat","rb");
    printf("Ingresa el nombre del proveedor a buscar:");
    printf("\nPresiona cualquier tecla para volver al Men%c", 163);
    printf("ID.  NOMBRE.      CIUDAD.     NO.         EMAIL");
    printf("================================================");
    while(fscanf(fp,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
        if(strcmp(info_c.clien_nombre,nombre)==0){
			printf(" %d",info_c.clien_id);
			printf(" %s",info_c.clien_nombre);
			printf(" %s",info_c.lugar);
			printf(" %s",info_c.mobil_no);
			printf(" %s",info_c.email);
			break;
        }
    }
    if(strcmp(info_c.clien_nombre,nombre)!=0){
		printf("Registro no encontrado");
    }
    fclose(ptr1);
    getche();
}


/*============================ MEDICAMENTO ============================*/
/*======================== Menú de Medicamento ========================*/
void medicina(){
    int opm, u=163;
    do{
        system("cls");
        printf("-----------------------");
        printf("\nMEN%c DE MEDICAMENTOS\n", 233);
        printf("-----------------------");
        printf("\n\t1. A%cdir Nueva Medicina", 164);
        printf("\n\t2. Venta de Medicamento");
        printf("\n\t3. Inventario");
        printf("\n\t4. Buscar Medicamento");
        printf("\n\t5. Men%c Principal", u);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ", u, 162);
        scanf("%d",opm);

        switch(opm){
            case 1 :medi_entrada();
                break;
            case 2 :medi_venta();
                break;
            case 3 :almacen();
                break;
            case 4 :medi_buscar();
                break;
            case 5 :main_menu();
                break;
            default:
                printf("\nFavor de ingresar SOLAMENTE los n%cmeros (1-5)", 163);
                getch();
        }
    }
    while(opm!=5);
}

/*========================= Nuevo Medicamento =========================*/
void medi_entrada(){
    char ch,id[6];
    int f, ope, opm;
    FILE *fp;
    system("cls");

    ptrp_r=fopen("provereporte.dat","a");
    ope=1;
    while(ope==1){
        system("cls");
        printf("---------------------");
		printf(" REGISTRO DE MEDICINA ");
		printf("---------------------");
		{
		    printf("\n\tID DEL MEDICAMENTO: ");
                entrada(info.id,1);
                strcpy(id,info.id);

            fp=fopen("medica.dat","r");
			while((fread(&info,sizeof(info),1,fp))==1){
                if(strcmp(id,info.id)==0){
                    f=1;
                    break;
                }
			}
			fclose(fp);
			if(f==1){
				printf("El ID ya existe");
				getche();
				system("cls");
				medi_entrada();
			}
            else{
                ptr=fopen("medical.dat","a+b");
                strcpy(info.id,id);
                strcpy(p_r.medi_id,info.id);
            }

            printf("\n\tNOMBRE DEL MEDICAMENTO: ");
                entrada(info.medi_nombre,0);
                strcpy(p_r.medir_nombre,info.medi_nombre);
            printf("\n\tLOCKER: ");
                entrada(a,1);
                info.rango = atoi(a);
            printf("\n\tGABINETE: ");
                entrada(info.gabinete,2);
            printf("\n\tCOMPA%cIA: ",165);
                entrada(info.compania_nombre,0);
            printf("\n\tPROVEEDOR: ");
                entrada(info.prove_nombre,0);
                strcpy(p_r.prove_nombre,info.prove_nombre);
            printf("\n\tPRECIO DE COMPRA: ");
                entrada(a,1);
                info.unidad= atof(a);
                p_r.iva=info.unidad;
            printf("\n\tPRECIO DE VENTA: ");
                entrada(a,1);
                info.venta = atof(a);
            printf("\n\tCANTIDAD: ");
                entrada(a,1);
                info.cantidad = atoi(a);
                p_r.num=info.cantidad;
			printf("\n\tMANUFACTURA (dd-mm-aaaa): ");
                entrada(info.manu_fecha,1);
			printf("\n\tCADUCIDAD (dd-mm-aaaa): ");
                entrada(info.caducidad_fecha,1);

			printf("==========================================================");
			info.total=info.cantidad*info.venta;
			printf("TOTAL DE PRECIO DE VENTA = %.2f",info.total);
			info.costo=(info.unidad*info.cantidad);
			printf("TOTAL DE PRECIO DE COMPRA = %.2f",info.costo);
			p_r.total=info.costo;
        }
		printf("1. Guardar");
		printf("2. Cancelar");
		printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ");
		scanf("%d", &opm);
		if(opm==1){
			fwrite(&info,sizeof(info),1,ptr);
			fprintf(ptrp_r,"%s %s %s %d %.2f %.2f \n",p_r.medi_id,p_r.medir_nombre,p_r.prove_nombre,p_r.num,p_r.iva,p_r.total);
			system("cls");
			printf("Medicamento a%cadido con %cxito",164, 130);
			printf("Más medicamentos [S/N]");
			ch=getche();
            if(ch=='S'){
				system("cls");
				medi_entrada();
			}
		}
    }
    fclose(ptr);
    fclose(ptrp_r);
}

/*======================== Venta de Medicamento =======================*/
void medi_venta(){
    struct ticket tic;
    int ope,j,n,i,a,ticketno;
    float b,total,iva;
    char tar[30],ch,medinombre[30],c_nombre[30],cnombre[30];
    FILE *fp,*fpc;
    int cont=0;
    ope=1;
    while(ope==1){
        fp = fopen("dticket.dat","a");
		ptr1 = fopen("cliente.dat","r");
		ptr = fopen("medica.dat","r");
		ptrs_r = fopen("ventareport.dat","a");
		ptrpr_r = fopen("comprareport.dat","a");
		system("cls");
		printf("ID_Cliente   Nombre_Cliente");
		while(fscanf(ptr1,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
			printf("%d",info_c.clien_id);
			printf("%s",info_c.clien_nombre);
		}
		printf("INTRODUCE EL ID DE LA MEDICINA VENDIDA: ");
		j=0;
		while((fread(&info,sizeof(info),1,ptr))==1){
			if((strcmp(info.id,tar)<0) || (strcmp(info.id,tar)>0)){
				x[j] = info;
				j++;
			}
            else if((strcmp(info.id,tar)==0)){
                printf(" Nombre de la Medicina: %s",info.medi_nombre);
				printf(" Cantidad en el almac%cn: %d",130,info.num);
				printf(" Precio de Venta  : %.2f",info.venta);
				printf("N%c de Ticket     : ", 167);
				scanf("%d",&tic.ticketno);
				printf("Nombre del Cliente: ");
				scanf("%s",&c_nombre);
				printf("Cantidad de productos comprados: ");
				scanf("%d",&a);
				pr_r.ganancia=(info.venta-info.unidad)*a;
				x[j]=info;
				x[j].cantidad=(x[j].cantidad-a);
				x[j].total=(x[j].cantidad*info.venta);
				x[j].costo=(x[j].cantidad*info.unidad);
				x[j].salir=(x[j].venta*a);
				b=x[j].salir;
				x[j].num=a;
				j++;
				cont++;
				strcpy(s_r.clien_nombre,c_nombre);
            }
		}
		if (cont==0){
			system("cls");
			printf("No hay en existencia");
			getch();
			return;
		}
		fclose(ptr1);
		fclose(ptr);
		n=j;
		system("cls");
		ptr=fopen("medica.dat","wb");
		for(i=0; i<n; i++)
		fwrite(&x[i],sizeof(x[i]),1,ptr);
		fclose(ptr);
		system("cls");
		printf("*Precio pagado por el cliente = %.2f",b);
		printf("*            Cantidad Vendida = %d",a);
		getch();
		printf("Más productos [S/N]");
			ch=getche();
            if(ch=='S'){
				system("cls");
				medi_venta();
			}
	   }
}

/*========================= Buscar Medicamento ========================*/
void medi_buscar(){
    char mid[6];
    int c;
    system("cls");
    ptr1=fopen("medica.dat","r");
    if(ptr1==NULL){
        printf("\n\tNo hay registro");
		exit(0);
    }
    system("cls");
    printf("Introduce el ID del medicamento: ");
    scanf("%s",&mid);
    system("cls");
    printf(" MEDICAMENTO ");
    printf("ID   Producto       Cantidad          Proveedor         Caducidad ");
    printf("==================================================================\n");
    while((fread(&info,sizeof(info),1,ptr1))==1){
        if(strcmp(mid,info.id)==0){
            printf(" %s",info.id);
            printf(" %s",info.medi_nombre);
            printf(" %d",info.cantidad);
            printf(" %s",info.prove_nombre);
            printf(" %s",info.caducidad_fecha);
            break;
        }
    }
    if(strcmp(mid,info.id)!=0){
		printf("No hay en existencia");
    }
    getche();
}

/*====================== Actualizar Medicamentos ======================*/
void actual_almacen(){
    char mid[6];
    int j,a,count=0,n;
    system("cls");
    ptr=fopen("medical.dat","rb");
    if(ptr==NULL){
		printf("\n\tNo hay registro");
		exit(0);
    }
    system("cls");
    printf("Presiona ENTER para ir al MENU");
    printf(" ACTUALIZAR CANTIDAD DE MEDICAMENTO ");
    printf("Introduce el ID del medicamento: ");
    scanf("%s",&mid);
    j=0;
    while((fread(&info,sizeof(info),1,ptr))==1){
        if((strcmp(info.id,mid)<0) || (strcmp(info.id,mid)>0)){
			x[j] = info;
			j++;
		}
		else{
			printf("Nombre del Medicamento : %s",info.medi_nombre);
			printf("Cantidad en el Almac%cn: %d",130,info.cantidad);
			printf("Nueva Cantidad: ");
			scanf("%d",&a);
			x[j]=info;
			x[j].cantidad=(x[j].cantidad+a);
			x[j].total=(x[j].cantidad*info.venta);
			x[j].costo=(x[j].cantidad*info.unidad);
			x[j].salir=(x[j].venta*a);
			x[j].num=a;
			j++;
			count++;
        }
    }
    if (count==0){
        system("cls");
        printf("No hay en existencia");
        getch();
        return;
    }
    fclose(ptr);
    n = j;
    system("cls");
    ptr=fopen("medica.dat","wb");
    for(i=0; i<n; i++)
    fwrite(&x[i],sizeof(x[i]),1,ptr);
    fclose(ptr);
}

/*============================== ALMACEN ==============================*/
void almacen(){
    char ch;
    int c;
    do{
        system("cls");
		ptr1=fopen("medica.dat","r");
		if(ptr1==NULL){
			printf("\n\t No hay registro");
			exit(1);
		}
		system("cls");
		printf(" ALMACEN DE MEDICAMENTOS ");
        printf("ID   Producto       Cantidad          Proveedor         Caducidad ");
		printf("==================================================================\n");
		while((fread(&info,sizeof(info),1,ptr1))==1){
			printf(" %s",info.id);
			printf(" %s",info.medi_nombre);
			printf(" %d",info.cantidad);
			printf(" %s",info.prove_nombre);
			printf(" %s",info.caducidad_fecha);
		};
		printf("Presiona [1] para actualizar el almac%cn y [0] para el MENU",130);
		scanf("%d",&c);
		switch(c){
            case 0:main_menu();
                break;
			case 1:actual_almacen();
                break;
		}
    }
    while(c!=1);
    getche();
}

/*=============================== Ticket ==============================*/
void ticket(){
        FILE *ptrticket;
        char id[6];
        int j=1;
        float neto=0.0;
        system("cls");
        ptrticket=fopen("dticket.dat","r");
        printf("Introduce el N%c de Ticket: ",167);
        scanf("%s",&id);
        system("cls");
        printf("\nTicket N%c: ",167);
        printf("%s",id);
        printf("\nNombre del Cliente: ");
        printf(" No   Producto       Cantidad          IVA         Total ");
        printf("\n-------------------------------------------------------");
        while(fscanf(ptrticket,"%s %s %s %d %f %f %d %d %d",tic.ticketno,tic.cnombre,tic.medir_nombre,&tic.medi_num,&tic.medi_iva,&tic.total)!=EOF){
        do{
            if(strcmp(id,tic.ticketno)==0){
                printf(" %d",j);
                printf(" %s",tic.medir_nombre);
                printf(" %s",tic.cnombre);
                printf(" %d",tic.medi_num);
                printf(" %.2f",tic.medi_iva);
                printf(" %.2f",tic.total);
                neto=neto+tic.total;
                j++;
                printf("                                ");
                printf("Presiona cualquier tecla para regresar al MENU");
            }
        }
        while(feof(ptrticket));
}
    printf("---------------------------------------------------------------------");
    printf("Cantidad Neta: ");
    printf("%.2f",neto);
    fclose(ptrticket);
    getch();
}

/*============================== REPORTE ==============================*/
/*========================== Menú de Reportes =========================*/
void reporte_menu(){
    int opr;
	do{
        system("cls");
        printf("--------------------");
        printf("\nMEN%c DE REPORTES\n", 233);
        printf("--------------------");
        printf("\n\t1. Compras", 164);
        printf("\n\t2. Ventas");
        printf("\n\t3. Ganancias");
        printf("\n\t4. Ventas Diarias");
        printf("\n\t5. Compras Diarias");
        printf("\n\t6. Men%c Principal", 163);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ", 163, 162);
        scanf("%d",opr);

        switch(opr){
            case 1 :com_rpt();
                break;
            case 2 :venta_rpt();
                break;
            case 3 :ganancia_rpt();
                break;
            case 4 :venta_rpt_diaria();
                break;
            case 5 :com_rpt_diaria();
                break;
            case 6 :main_menu();
                break;
            default:
                printf("\nFavor de ingresar SOLAMENTE los n%cmeros (1-5)", 163);
                getch();
        }
    }
	while(opr!=6);
}
/*========================= Reporte de Ventas =========================*/
void venta_rpt(){
    char ch;
    system("cls");
    ptrs_r=fopen("ventareport.dat","r");
    if(ptrs_r==NULL){
        printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("Presiona cualquier tecla para regresar al MENU");
    printf("REPORTE DE VENTAS\n");
    printf("ID    PRODUCTO    NOMBRE DEL CLIENTE    CANTIDAD    IVA    TOTAL");
    printf("\n===================================================================");
    while(fscanf(ptrs_r,"%s %s %s %d %f %f %d %d %d\n",s_r.medi_id,s_r.medir_nombre,s_r.clien_nombre,&s_r.num,&s_r.iva,&s_r.total)!=EOF){
		printf("%s",s_r.medi_id);
		printf("%s",s_r.medir_nombre);
		printf("%s",s_r.clien_nombre);
		printf("%d",s_r.num);
		printf("%.2f",s_r.iva);
		printf("%.2f",s_r.total);
    }
    getche();
}
/*========================= Reporte de Compras ========================*/
void com_rpt(){
    char ch;
    system("cls");
    ptrp_r=fopen("comprareport.dat","r");
    if(ptrp_r==NULL){
		printf("\n\t No hay registro");
		exit(0);
    }
    printf("Presiona cualquier ENTER para regresar al MENU");
    printf("REPORTE DE COMPRAS\n");
    printf("ID    PRODUCTO    PROVEEDOR    CANTIDAD    IVA    TOTAL");
    printf("\n===================================================================");
    while(fscanf(ptrp_r,"%s %s %s %d %f %f %d %d %d\n",p_r.medi_id,p_r.medir_nombre,p_r.prove_nombre,&p_r.num,&p_r.iva,&p_r.total)!=EOF){
		printf("%s",p_r.medi_id);
		printf("%s",p_r.medir_nombre);
		printf("%s",p_r.prove_nombre);
		printf("%d",p_r.num);
		printf("%.2f",p_r.iva);
		printf("%.2f",p_r.total);
    }
    getche();
}
/*======================= Reporte de Ganancias ========================*/
void ganancia_rpt(){
    char ch;
    system("cls");
    ptrpr_r=fopen("ganareport.dat","r");
    if(ptrpr_r==NULL){
        printf("\n\t No hay registro");
        exit(0);
    }
    printf("Presiona cualquier ENTER para regresar al MENU");
    printf("REPORTE DE GANANCIAS\n");
    printf("ID   PRODUCTO   CANTIDAD   PRECIO UNTARIO   PRECIO VENTA   IVA   GANANCIA");
    printf("\n===================================================================");
    while(fscanf(ptrpr_r,"%s %s %d %d %d %d %f %f %f \n",pr_r.medi_id,pr_r.medir_nombre,&pr_r.num,&pr_r.unidad,&pr_r.iva,&pr_r.ganancia)!=EOF){
		printf("%s",pr_r.medi_id);
		printf("%s",pr_r.medir_nombre);
		printf("%d",pr_r.num);
		printf("%.2f",pr_r.unidad);
		printf("%.2f",pr_r.iva);
		printf("%.2f",pr_r.ganancia);
		printf("%c",124);
    }
    getche();
}
/*===================== Reporte de Ventas Diarias =====================*/
void venta_rpt_diaria(){
    char ch;
    int j,d,m,y;
    float total=0.00;
    system("cls");

    ptrs_r=fopen("ventareport.dat","r");
    if(ptrs_r==NULL){
		printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("Ingresa la Fecha(dd-mm-yyyy):  ");
    scanf("%d-%d-%d",&d,&m,&y);
    system("cls");
    printf("Presiona cualquier tecla para regresar al MENU");
    printf("REPORTE DE VENTAS\n");
    printf("ID    PRODUCTO    NOMBRE DEL CLIENTE    CANTIDAD    IVA    TOTAL    FECHA");
    printf("===========================================================================");
    while(fscanf(ptrs_r,"%s %s %s %d %f %f %d %d %d\n",s_r.medi_id,s_r.medir_nombre,s_r.clien_nombre,&s_r.num,&s_r.iva,&s_r.total,&s_r.sDia,&s_r.sMes,&s_r.sAno)!=EOF){
		if(d==s_r.sDia &&m== s_r.sMes && y==s_r.sAno){
		printf("%s",s_r.medi_id);
		printf("%s",s_r.medir_nombre);
		printf("%s",s_r.clien_nombre);
		printf("%d",s_r.num);
		printf("%.2f",s_r.iva);
		printf("%.2f",s_r.total);
		printf("%d-%d-%d",s_r.sDia,s_r.sMes,s_r.sAno);
		total=total+s_r.total;
		}
	   }
	   printf("-------------------------------------------------------------------");
	   printf("Total:        %.2f",total);
	   getche();
}
/*===================== Reporte de Compras Diarias ====================*/
void com_rpt_diaria(){
    char ch;
    int j,d,m,y;
    float total=0.00;

    ptrp_r=fopen("purreport.dat","r");
    if(ptrp_r==NULL){
		printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("Ingresa la Fecha(dd-mm-yyyy):  ");
    scanf("%d-%d-%d",&d,&m,&y);
    system("cls");
    printf("Presiona cualquier ENTER para regresar al MENU");
    printf("REPORTE DE COMPRAS\n");
    printf("ID    PRODUCTO    PROVEEDOR    CANTIDAD    IVA    TOTAL    FECHA");
    printf("======================================================================");
    while(fscanf(ptrp_r,"%s %s %s %d %f %f %d %d %d\n",p_r.medi_id,p_r.medir_nombre,p_r.prove_nombre,&p_r.num,&p_r.iva,&p_r.total,&p_r.sDia,&p_r.sMes,&p_r.sAno)!=EOF){
        if(d==p_r.sDia &&m== p_r.sMes && y==p_r.sAno){
            printf("%s",p_r.medi_id);
            printf("%s",p_r.medir_nombre);
            printf("%s",p_r.prove_nombre);
            printf("%d",p_r.num);
            printf("%.2f",p_r.iva);
            printf("%.2f",p_r.total);
            printf("%d-%d-%d",p_r.sDia,p_r.sMes,p_r.sAno);
            total=total+p_r.total;
        }
    }
    printf("-------------------------------------------------------------------");
    printf("\nTotal:        %.2f",total);
    getche();
}
