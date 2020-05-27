#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
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
	char gabinete[3];
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
	float medi_sub;
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
	float sub;
	float total;
};
struct ventas_reporte v_r;
FILE *ptrv_r;

struct compra_reporte{
	char medi_id[6];
	char medir_nombre[20];
	char prove_nombre[30];
	int sDia,sMes,sAno;
	int num;
	float sub;
	float total;
};
struct compra_reporte c_r;
FILE *ptrc_r;

struct ganancia_reporte{
	char medi_id[6];
	char medir_nombre[20];
	int sDia,sMes,sAno;
	int num;
	float sub;
	float unidad;
	float ganancia;
};
struct ganancia_reporte g_r;
FILE *ptrg_r;

void linkfloat(){
	float f,*p;
	p=&f;
	f=*p;
}
/*========================== FECHA Y HORA ==========================*/
int t(void){
  time_t t=time(0);  /*Tiempo real*/
  struct tm*now=localtime(&t);
	printf("\n\n\t\t\tFecha: %02d/%02d/%d", now->tm_mday,now->tm_mon+1,now->tm_year+1900);
	printf("\n\t\t\t Hora: %02d:%02d:%02d", now->tm_hour, now->tm_min,now->tm_sec);
	return 0;
}

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
		while((t[i]=getch())!='\r' && i<30)
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


/*       Incremento del identificador de cliente y proveedor       */
int i;
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
		t();    /*Funcion (fecha y tiempo)*/
		remanente(); /*Se activa cuando hay menos de 5 unidades de un producto*/
		printf("\n\n\n\t N%cmero de la opci%cn a realizar: ",163,162);
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
/*============================= Remanente =============================*/
void remanente(){
	ptr1=fopen("medical.dat","r");
	if(ptr1==NULL){
        printf("\n\t No hay registro");
	}
	while((fread(&info,sizeof(info),1,ptr1))==1){
		if(info.cantidad<5){
			printf("\n\n   %s: ",info.medi_nombre);
			printf("La cantidad de medicamento es menor a 5");
		}
	}
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
    int id;
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
        t();
		printf("\n\t1. Guardar");
		printf("\n\t2. Cancelar");
		printf("\n\tTeclea el n%cmero de la opci%cn a realizar: ",163,162);
		ch=getch();
		if(ch=='1'){
			fprintf(fp,"%d %s %s %s %s\n\n",infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email);
			fprintf(fp,"\n");
			system("cls");
			printf("\n\tProveedor a%cadido con %cxito",164, 130);
			printf("\n\t    M%cs datos [S/N]: ",160);
            ch=toupper(getche());
        }
    }
    fclose(fp);
}

/*================ Actualizar Información del Proveedor ===============*/
void prove_actual(){
    int i;
    char ch;
    int pid;
    FILE *ft;
    system("cls");
    ptr1=fopen("proveedor.dat","rb+");
    if(ptr1==NULL ){
        printf("\n\t No hay registro");
		exit(0);
    }
    printf("\n\n\t\tMODIFICAR PROVEEDOR");
    printf("\n\n\tIntroduce el ID del proveedor: ");
    scanf("%d",&pid);
    ft=fopen("infos.dat","w");
    if(ft==NULL){
        printf("\n\t No hay registro");
        exit(1);
    }
    else{
        while(fscanf(ptr1,"%d %s %s %s %s",&infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
            if(infos.prove_id==pid){
                printf("\n\t\tRegistro Existente");
                printf("\n\n%d %s %s %s %s",infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email);
                printf("\n\nNuevo nombre: ");
                entrada(infos.prove_nombre,0);
                printf("\nNueva Ciudad: ");
                entrada(infos.lugar,0);
                printf("\nNuevo N%cmero: ", 163);
                entrada(infos.mobil_no,1);
                printf("\nNuevo Email: ");
                entrada(infos.email,2);
                printf("\n\n1. Guardar");
                printf("\n2. Cancelar");
                printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ",163,162);
                ch=getch();
                if(ch=='1'){
                    fprintf(ft,"%d %s %s %s %s\n",infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email);
                    printf("\nActualizaci%cn exitosa", 162);
                    remove("proveedor.dat");
                    rename("infos.dat","proveedor.dat");
                    getch();
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
    printf("\n\n\t\t\t----------------------");
    printf("\n\t\t\t LISTA DE PROVEEDORES");
    printf("\n\t\t\t----------------------");
    printf("\n\n\t  ID. \tNOMBRE.  CIUDAD. \tNO. \t\tEMAIL.");
    printf("\n\t=============================================================");
    while(fscanf(ptr1,"%d %s %s %s %s",&infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
		printf("\n\t  %d",infos.prove_id);
		printf("\t%s",infos.prove_nombre);
		printf("\t%s",infos.lugar);
		printf("   %s",infos.mobil_no);
		printf("\t%s",infos.email);
    }
    getche();
}

/*========================= Buscar Proveedores ========================*/
void buscar(){
    int opb;
    do{
        system("cls");
        printf("Tienes dos opciones para buscar:");
	    printf("\n\t1. N%cmero ID", 163);
        printf("\n\t2. Nombre");
        printf("\n\t3. Regresar");
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
    printf("\t   Ingresa el ID del proveedor a buscar: ");
    scanf("%d",&id);
    printf("\n\t  Presiona cualquier tecla para volver al Men%c\n", 163);
    printf("\n\n\t  ID. \tNOMBRE.  CIUDAD. \tNO. \t\tEMAIL.");
    printf("\n\t=============================================================");
    while(fscanf(fp,"%d %s %s %s %s",&infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
        if(infos.prove_id==id){
            printf("\n\t  %d",infos.prove_id);
            printf("\t%s",infos.prove_nombre);
            printf("\t%s",infos.lugar);
            printf("   %s",infos.mobil_no);
            printf("\t%s",infos.email);
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
    printf("\tIngresa el nombre del proveedor a buscar: ");
    scanf("%s",&nombre);
    printf("\n\t  Presiona cualquier tecla para volver al Men%c\n", 163);
    printf("\n\n\t  ID. \tNOMBRE.  CIUDAD. \tNO. \t\tEMAIL.");
    printf("\n\t=============================================================");
    while(fscanf(fp,"%d %s %s %s %s",&infos.prove_id, infos.prove_nombre, infos.lugar, infos.mobil_no, infos.email)!=EOF){
        if(strcmp(infos.prove_nombre,nombre)==0){
			printf("\n\t  %d",infos.prove_id);
            printf("\t%s",infos.prove_nombre);
            printf("\t%s",infos.lugar);
            printf("   %s",infos.mobil_no);
            printf("\t%s",infos.email);
			break;
        }
    }
    if(strcmp(infos.prove_nombre,nombre)!=0){
		printf("\nRegistro no encontrado");
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
        printf("\t\t\t--------------------");
        printf("\n\t\t\t  MEN%c DEL CLIENTE\n", 233);
        printf("\t\t\t--------------------");
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
    int id;
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
		t();
		printf("\n\t1. Guardar");
		printf("\n\t2. Cancelar");
		printf("\n\tTeclea el n%cmero de la opci%cn a realizar: ",163,162);
		ch=getch();
		if(ch=='1'){
			fprintf(fp,"%d %s %s %s %s\n\n",info_c.clien_id,info_c.clien_nombre,info_c.mobil_no,info_c.lugar,info_c.email);
			fprintf(fp,"\n");
			fflush(stdin);
			system("cls");
			printf("\n\tCliente a%cadido con %cxito",164, 130);
			printf("\n\t   M%cs datos [S/N]: ",160);
			ch=toupper(getche());
        }
    }
    fclose(fp);
}
/*======================== Actualizar Cliente =========================*/
void clien_actual(){
    int i;
    char ch;
    int cid;
    FILE *ft;
    system("cls");
    ptr1=fopen("cliente.dat","rb+");
    if(ptr1==NULL ){
        printf("\n\t No hay registro");
		exit(0);
    }
    printf("\n\n\t\tMODIFICAR CLIENTE");
    printf("\n\n\tIntroduce el ID del cliente:  ");
    scanf("%d",&cid);
    ft=fopen("info.dat","w");
    if(ft==NULL){
        printf("\n\t No hay registro");
        exit(1);
    }
    else{
        while(fscanf(ptr1,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
            if(info_c.clien_id==cid){
                printf("\n\t\tRegistro Existente  ");
                printf("\n\n\t%d %s %s %s %s",info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email);
                printf("\n\nNuevo Nombre: ");
                entrada(info_c.clien_nombre,0);
                printf("\nNuevo N%cmero: ", 163);
                entrada(info_c.mobil_no,1);
                printf("\nNueva Ciudad: ");
                entrada(info_c.lugar,0);
                printf("\nNuevo Email: ");
                entrada(info_c.email,2);
                printf("\n\n1. Guardar");
                printf("\n2. Cancelar");
                printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ",163,162);
                ch=getch();
                if(ch=='1'){
                    fprintf(ft,"%d %s %s %s %s\n",info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email);
                    printf("\nActualizaci%cn exitosa", 162);
                    remove("cliente.dat");
                    rename("info.dat","cliente.dat");
                    getch();
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
    printf("\n\n\t\t\t-------------------");
    printf("\n\t\t\t LISTA DE CLIENTES");
    printf("\n\t\t\t-------------------");
    printf("\n\n\t  ID. \tNOMBRE.  CIUDAD. \tNO. \t\tEMAIL.");
    printf("\n\t=============================================================");
    while(fscanf(ptr1,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
        printf("\n\t  %d",info_c.clien_id);
        printf("\t%s",info_c.clien_nombre);
        printf("\t%s",info_c.lugar);
        printf("   %s",info_c.mobil_no);
        printf("\t%s",info_c.email);
    }
    getche();
}

/*========================== Buscar Clientes ==========================*/
void clien_buscar(){
    int opb;
    do{
        system("cls");
        printf("Tienes dos opciones para buscar:");
	    printf("\n\t1. N%cmero ID", 163);
        printf("\n\t2. Nombre");
        printf("\n\t3. Regresar");
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
    printf("\t    Ingresa el ID del cliente a buscar: ");
    scanf("%d",&id);
    printf("\n\t  Presiona cualquier tecla para volver al Men%c", 163);
    printf("\n\n\t  ID. \tNOMBRE.  CIUDAD. \tNO. \t\tEMAIL.");
    printf("\n\t=============================================================");
    while(fscanf(fp,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
        if(info_c.clien_id==id){
            printf("\n\t  %d",info_c.clien_id);
            printf("\t%s",info_c.clien_nombre);
            printf("\t%s",info_c.lugar);
            printf("   %s",info_c.mobil_no);
            printf("\t%s",info_c.email);
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
    printf("\t Ingresa el nombre del cliente a buscar: ");
    scanf("%s",&nombre);
    printf("\n\t  Presiona cualquier tecla para volver al Men%c", 163);
    printf("\n\n\t  ID. \tNOMBRE.  CIUDAD. \tNO. \t\tEMAIL.");
    printf("\n\t=============================================================");
    while(fscanf(fp,"%d %s %s %s %s",&info_c.clien_id, info_c.clien_nombre, info_c.mobil_no, info_c.lugar,info_c.email)!=EOF){
        if(strcmp(info_c.clien_nombre,nombre)==0){
            printf("\n\t  %d",info_c.clien_id);
            printf("\t%s",info_c.clien_nombre);
            printf("\t%s",info_c.lugar);
            printf("   %s",info_c.mobil_no);
            printf("\t%s",info_c.email);
			break;
        }
    }
    if(strcmp(info_c.clien_nombre,nombre)!=0){
		printf("\n\nRegistro no encontrado");
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
        printf("\t    ----------------------");
        printf("\n\t     MEN%c DE MEDICAMENTOS\n", 233);
        printf("\t    ----------------------");
        printf("\n\t1. A%cadir Nuevo Medicamento", 164);
        printf("\n\t2. Venta de Medicamento");
        printf("\n\t3. Inventario");
        printf("\n\t4. Buscar Medicamento");
        printf("\n\t5. Men%c Principal", u);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ", u, 162);
        scanf("%d",&opm);

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
    time_t t=time(0);
    struct tm*now=localtime(&t);
    int f, ope;
    FILE *fp;
    system("cls");

    ptrc_r=fopen("comprareport.dat","a");
    ch='S';
    while(ch=='S'){
        system("cls");
        printf("\t\t----------------------");
		printf("\n\t\t REGISTRO DE MEDICINA\n");
		printf("\t\t----------------------");
		{
		    printf("\n\tID DEL MEDICAMENTO: ");
                entrada(info.id,1);
                strcpy(id,info.id);

            fp=fopen("medical.dat","r");
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
                strcpy(c_r.medi_id,info.id);
            }

            printf("\n\tNOMBRE DEL MEDICAMENTO: ");
                entrada(info.medi_nombre,0);
                strcpy(c_r.medir_nombre,info.medi_nombre);
            printf("\n\tLOCKER: ");
                entrada(a,1);
                info.rango = atoi(a);
            printf("\n\tGABINETE: ");
                entrada(info.gabinete,2);
            printf("\n\tCOMPA%cIA: ",165);
                entrada(info.compania_nombre,0);
            printf("\n\tPROVEEDOR: ");
                entrada(info.prove_nombre,0);
                strcpy(c_r.prove_nombre,info.prove_nombre);
            printf("\n\tPRECIO DE COMPRA: ");
                entrada(a,1);
                info.unidad = atof(a);
                c_r.sub = info.unidad;
            printf("\n\tPRECIO DE VENTA: ");
                entrada(a,1);
                info.venta = atof(a);
            printf("\n\tCANTIDAD: ");
                entrada(a,1);
                info.cantidad = atoi(a);
                c_r.num = info.cantidad;
			printf("\n\tMANUFACTURA (dd-mm-aaaa): ");
                entrada(info.manu_fecha,1);
			printf("\n\tCADUCIDAD (dd-mm-aaaa): ");
                entrada(info.caducidad_fecha,1);

			printf("\n==========================================================");
			info.total=info.cantidad*info.venta;
			printf("\n\n\tTOTAL DE PRECIO VENTA = %.2f",info.total);
			info.costo=(info.unidad*info.cantidad);
			printf("\n\tTOTAL DE PRECIO COMPRA = %.2f",info.costo);
			c_r.total=info.costo;
			c_r.sDia=now->tm_mday;
			c_r.sMes=now->tm_mon+1;
			c_r.sAno=now->tm_year+1900;
        }
		printf("\n\n1. Guardar");
		printf("\n2. Cancelar");
		printf("\nTeclea el n%cmero de la opci%cn a realizar: ",163,162);
		ch=getche();
		if(ch=='1'){
			fwrite(&info,sizeof(info),1,ptr);
			fflush(stdin);
			fprintf(ptrc_r,"%s %s %s %d %.2f %.2f %02d %02d %d\n",c_r.medi_id,c_r.medir_nombre,c_r.prove_nombre,c_r.num,c_r.sub,c_r.total,c_r.sDia,c_r.sMes,c_r.sAno);
			system("cls");
			printf("\n\tMedicamento a%cadido con %cxito",164, 130);
			printf("\n\t    M%cs datos [S/N]: ", 160);
			ch=getche();
		}
    }
    fclose(ptr);
    fclose(ptrc_r);
}

/*======================== Venta de Medicamento =======================*/
void medi_venta(){
    struct ticket tic;
    time_t t=time(0);
    struct tm*now=localtime(&t);
    int j,n,a,ticketno,d,m,an;
    float b,total,sub;
    char tar[30],ch,medinombre[30],c_nombre[30],cnombre[30];
    FILE *fp,*fpc;
    int cont=0;

    d=now->tm_mday;
    m=now->tm_mon+1;
    an=now->tm_year+1900;

    ch='S';
    while(ch=='S'){
        fp = fopen("ticket.dat","a");
		ptr1 = fopen("cliente.dat","r");
		ptr = fopen("medical.dat","r");
		ptrv_r = fopen("ventareport.dat","a");
		ptrg_r = fopen("ganareport.dat","a");
		system("cls");
		printf("\n\n\tINTRODUCE EL ID DE LA MEDICINA VENDIDA: ");
		entrada(tar,1);
		j=0;
		while((fread(&info,sizeof(info),1,ptr))==1){
			if((strcmp(info.id,tar)<0) || (strcmp(info.id,tar)>0)){
				x[j] = info;
				j++;
			}
            else if((strcmp(info.id,tar)==0)){
                printf("\n\tNombre de la Medicina: %s",info.medi_nombre);
				printf("\n\tCantidad en el almac%cn: %d",130,info.cantidad);
				printf("\n\tPrecio de Venta: %.2f",info.venta);
				printf("\n\tN%c de Ticket: ", 167);
				entrada(tic.ticketno,1);
				printf("\n\tNombre del Cliente: ");
				entrada(c_nombre,0);
				printf("\n\tCantidad de productos comprados: ");
				scanf("%d",&a);
				g_r.ganancia=(info.venta-info.unidad)*a;
				x[j]=info;
				x[j].cantidad=(x[j].cantidad-a);
				x[j].total=(x[j].cantidad*info.venta);
				x[j].costo=(x[j].cantidad*info.unidad);
				x[j].salir=(x[j].venta*a);
				b=x[j].salir;
				x[j].num=a;
				j++;
				cont++;
				strcpy(tic.cnombre,c_nombre);
				strcpy(v_r.clien_nombre,c_nombre);
				strcpy(tic.medir_nombre,info.medi_nombre);
				tic.medi_num=a;
				tic.medi_sub=info.venta;
				tic.total=info.venta*a;

				tic.dia=d;
				tic.mes=m;
				tic.ano=an;

				fprintf(fp,"%s %s %s %d %.2f %.2f %02d %02d %d\n",tic.ticketno,tic.cnombre,tic.medir_nombre,tic.medi_num,tic.medi_sub,tic.total,tic.dia,tic.mes,tic.ano);
				fflush(stdin);

				fclose(fp);

                /* Reporte de Venta */
				v_r.sDia=d;
				v_r.sMes=m;
				v_r.sAno=an;
				strcpy(v_r.medi_id,tar);
				strcpy(v_r.medir_nombre,info.medi_nombre);
				v_r.num=a;
				v_r.sub=info.venta;
				v_r.total=info.venta*a;
				fprintf(ptrv_r,"%s %s %s %d %.2f %.2f %02d %02d %d\n",v_r.medi_id,v_r.medir_nombre,v_r.clien_nombre,v_r.num,v_r.sub,v_r.total,v_r.sDia,v_r.sMes,v_r.sAno);
                fflush(stdin);
                fclose(ptrv_r);

				/* Reporte de Compra */
				g_r.sDia=d;
				g_r.sMes=m;
				g_r.sAno=an;
				strcpy(g_r.medi_id,tar);
				strcpy(g_r.medir_nombre,info.medi_nombre);
				g_r.num=a;
				g_r.sub=info.venta;
				g_r.unidad=info.unidad;
				fprintf(ptrg_r,"%s %s %02d %02d %d %d %.2f %.2f %.2f\n",g_r.medi_id,g_r.medir_nombre,g_r.sDia,g_r.sMes,g_r.sAno,g_r.num,g_r.unidad,g_r.sub,g_r.ganancia);
				fflush(stdin);
				fclose(ptrg_r);
            }
		}
		printf("\n\t\t\tID_Cliente   Nombre_Cliente");
		while(fscanf(ptr1,"%d %s %s %s %s",&info_c.clien_id,info_c.clien_nombre,info_c.mobil_no,info_c.lugar,info_c.email)!=EOF){
			printf("\n\t\t\t   %d",info_c.clien_id);
			printf("\t\t%s",info_c.clien_nombre);
			getch();
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
		ptr=fopen("medical.dat","wb");
		for(i=0; i<n; i++)
		fwrite(&x[i],sizeof(x[i]),1,ptr);
		fclose(ptr);
		system("cls");
		printf("\n\t\t*Precio a pagar por el cliente = %.2f",b);
		printf("\n\t\t\t     *Cantidad Vendida = %d",a);
		getch();
		printf("\n\n\t\t\tM%cs productos [S/N]: ",160);
        ch=getche();
    }
}

/*========================= Buscar Medicamento ========================*/
void medi_buscar(){
    char mid[6];
    int c;
    system("cls");
    ptr1=fopen("medical.dat","r");
    if(ptr1==NULL){
        printf("\n\tNo hay registro");
		exit(0);
    }
    system("cls");
    printf("Introduce el ID del medicamento: ");
    scanf("%s",&mid);
    system("cls");
    printf("\n\t\t\t\tMEDICAMENTO ");
    printf("\n\n\tID \tProducto \tCantidad \tProveedor \tCaducidad ");
    printf("\n\t==================================================================\n");
    while((fread(&info,sizeof(info),1,ptr1))==1){
        if(strcmp(mid,info.id)==0){
            printf("\t%s",info.id);
			printf("\t%s",info.medi_nombre);
			printf("\t   %d",info.cantidad);
			printf("\t\t%s",info.prove_nombre);
			printf("\t\t%s",info.caducidad_fecha);
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
    int j,a,cont=0,n;
    system("cls");
    ptr=fopen("medical.dat","rb");
    if(ptr==NULL){
		printf("\n\tNo hay registro");
		exit(0);
    }
    system("cls");
    printf("\n\tPresiona ENTER para ir al MENU");
    printf("\n\n\t\tACTUALIZAR CANTIDAD DE MEDICAMENTO ");
    printf("\n\n\tIntroduce el ID del medicamento: ");
    scanf("%s",&mid);
    j=0;
    while((fread(&info,sizeof(info),1,ptr))==1){
        if((strcmp(info.id,mid)<0) || (strcmp(info.id,mid)>0)){
			x[j] = info;
			j++;
		}
		else{
			printf("\n\tNombre del Medicamento : %s",info.medi_nombre);
			printf("\n\tCantidad en el Almac%cn: %d",130,info.cantidad);
			printf("\n\tCantidad Comprada: ");
			scanf("%d",&a);
			x[j]=info;
			x[j].cantidad=(x[j].cantidad+a);
			x[j].total=(x[j].cantidad*info.venta);
			x[j].costo=(x[j].cantidad*info.unidad);
			x[j].salir=(x[j].venta*a);
			x[j].num=a;
			j++;
			cont++;
        }
    }
    if (cont==0){
        system("cls");
        printf("No hay en existencia");
        getch();
        return;
    }
    fclose(ptr);
    n=j;
    system("cls");
    ptr=fopen("medical.dat","wb");
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
		ptr1=fopen("medical.dat","r");
		if(ptr1==NULL){
			printf("\n\t No hay registro");
			exit(1);
		}
		system("cls");
		printf("\n\t\t\t  ALMACEN DE MEDICAMENTOS ");
        printf("\n\n\tID \tProducto \tCantidad \tProveedor \tCaducidad ");
		printf("\n\t==================================================================\n");
		while((fread(&info,sizeof(info),1,ptr1))==1){
			printf("\n\t%s",info.id);
			printf("\t%s",info.medi_nombre);
			printf("\t   %d",info.cantidad);
			printf("\t\t%s",info.prove_nombre);
			printf("\t\t%s",info.caducidad_fecha);
		}
		printf("\n\n\tPresiona [1] para actualizar el almac%cn y [0] para el MENU: ",130);
		scanf("%d",&c);
		switch(c){
            case 0:medicina();
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
        time_t td=time(0);
        struct tm*now=localtime(&td);
        FILE *ptrticket;
        char id[6];
        int j=1,d,m,an,k;
        float neto=0.0;
        d=now->tm_mday;
        m=now->tm_mon+1;
        an=now->tm_year+1900;
        system("cls");
        ptrticket=fopen("ticket.dat","r");
        printf("Introduce el N%c de Ticket: ",167);
        scanf("%s",&id);
        system("cls");
        printf("\nTicket N%c: ",167);
        printf("%s",id);
        printf("\nFecha: ");
        printf("%d-%d-%d",d,m,an);
        printf("\n\n No \tProducto \tCliente     Cantidad \tSub \t  Total");
        printf("\n-----------------------------------------------------------------\n");
        while(fscanf(ptrticket,"%s %s %s %d %f %f %02d %02d %d",tic.ticketno,tic.cnombre,tic.medir_nombre,&tic.medi_num,&tic.medi_sub,&tic.total,&tic.dia,&tic.mes,&tic.ano)!=EOF){
            do{
                if(strcmp(id,tic.ticketno)==0){
                    printf(" %d",j);
                    printf("\t%s",tic.medir_nombre);
                    printf("\t%s",tic.cnombre);
                    printf("\t\t%d",tic.medi_num);
                    printf("\t%.2f",tic.medi_sub);
                    printf("\t  %.2f",tic.total);
                    neto=neto+tic.total;
                    j++;
                    printf("\n\n\t\t\t\t\t------------------------");
                    printf("\n\t\t\t\t\t  Cantidad Neta: ");
                    printf("%.2f",neto);
                    printf("\n\n\n\tPresiona cualquier tecla para regresar al MENU");
                }
            }
            while(feof(ptrticket));
    }
    fclose(ptrticket);
    getch();
}

/*============================== REPORTE ==============================*/
/*========================== Menú de Reportes =========================*/
void reporte_menu(){
    int opr;
	do{
        system("cls");
        printf("\t\t------------------");
        printf("\n\t\t MEN%c DE REPORTES\n", 233);
        printf("\t\t------------------");
        printf("\n\t1. Ventas", 164);
        printf("\n\t2. Compras");
        printf("\n\t3. Ganancias");
        printf("\n\t4. Ventas Diarias");
        printf("\n\t5. Compras Diarias");
        printf("\n\t6. Men%c Principal", 163);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar: ", 163, 162);
        scanf("%d",&opr);

        switch(opr){
            case 1 :venta_rpt();
                break;
            case 2 :com_rpt();
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
    ptrv_r=fopen("ventareport.dat","r");
    if(ptrv_r==NULL){
        printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("Presiona cualquier tecla para regresar al MENU\n\n");
    printf("\n\t\t\t\tREPORTE DE VENTAS\n\n");
    printf("ID \tPRODUCTO \tCLIENTE \tCANTIDAD \tSUBTOTAL \t TOTAL \t  FECHA");
    printf("\n===========================================================================================\n");
    while(fscanf(ptrv_r,"%s %s %s %d %f %f %02d %02d %d\n",v_r.medi_id,v_r.medir_nombre,v_r.clien_nombre,&v_r.num,&v_r.sub,&v_r.total,&v_r.sDia,&v_r.sMes,&v_r.sAno)!=EOF){
		printf("%s",v_r.medi_id);
		printf("\t%s",v_r.medir_nombre);
		printf("\t%s",v_r.clien_nombre);
		printf("\t\t%d",v_r.num);
		printf("\t\t%.2f",v_r.sub);
		printf("\t\t%.2f",v_r.total);
		printf("\t%02d-%02d-%d\n",v_r.sDia,v_r.sMes,v_r.sAno);
    }
    getche();
}
/*========================= Reporte de Compras ========================*/
void com_rpt(){
    char ch;
    system("cls");
    ptrc_r=fopen("comprareport.dat","r");
    if(ptrc_r==NULL){
		printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("Presiona cualquier ENTER para regresar al MENU\n\n");
    printf("\n\t\t\t\tREPORTE DE COMPRAS\n\n");
    printf("ID \tPRODUCTO \tPROVEEDOR \tCANTIDAD \tSUBTOTAL \tTOTAL \t  FECHA");
    printf("\n===========================================================================================\n");
    while(fscanf(ptrc_r,"%s %s %s %d %f %f %02d %02d %d\n",c_r.medi_id,c_r.medir_nombre,c_r.prove_nombre,&c_r.num,&c_r.sub,&c_r.total,&c_r.sDia,&c_r.sMes,&c_r.sAno)!=EOF){
		printf("%s",c_r.medi_id);
		printf("\t%s",c_r.medir_nombre);
		printf("\t%s",c_r.prove_nombre);
		printf("\t\t%d",c_r.num);
		printf("\t\t%.2f",c_r.sub);
		printf("\t\t%.2f",c_r.total);
		printf("\t%02d-%02d-%d\n",c_r.sDia,c_r.sMes,c_r.sAno);
    }
    getche();
}
/*======================= Reporte de Ganancias ========================*/
void ganancia_rpt(){
    char ch;
    system("cls");
    ptrg_r=fopen("ganareport.dat","r");
    if(ptrg_r==NULL){
        printf("\n\t No hay registro");
        exit(0);
    }
    printf("Presiona cualquier ENTER para regresar al MENU\n\n");
    printf("\n\t\t\t\t\tREPORTE DE GANANCIAS\n\n");
    printf("ID \tPRODUCTO \tFECHA \t\tCANTIDAD \tPRECIO UNTARIO \tPRECIO VENTA \tGANANCIA");
    printf("\n=================================================================================================\n");
    while(fscanf(ptrg_r,"%s %s %02d %02d %d %d %f %f %f \n",g_r.medi_id,g_r.medir_nombre,&g_r.sDia,&g_r.sMes,&g_r.sAno,&g_r.num,&g_r.unidad,&g_r.sub,&g_r.ganancia)!=EOF){
		printf("%s",g_r.medi_id);
		printf("\t%s",g_r.medir_nombre);
		printf("\t%02d-%02d-%d",g_r.sDia,g_r.sMes,g_r.sAno);
		printf("\t%d",g_r.num);
		printf("\t\t%.2f",g_r.unidad);
		printf("\t\t%.2f",g_r.sub);
		printf("\t\t%.2f\n",g_r.ganancia);
    }
    getche();
}
/*===================== Reporte de Ventas Diarias =====================*/
void venta_rpt_diaria(){
    char ch;
    int j,d,m,an;
    float total=0.00;
    system("cls");

    ptrv_r=fopen("ventareport.dat","r");
    if(ptrv_r==NULL){
		printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("Ingresa la Fecha(dd-mm-aaaa): ");
    scanf("%d-%d-%d",&d,&m,&an);
    system("cls");
    printf("Presiona cualquier tecla para regresar al MENU\n\n");
    printf("\n\t\t\t\tREPORTE DE VENTAS\n\n");
    printf("ID \tPRODUCTO \tCLIENTE \tCANTIDAD \tSUBTOTAL \t TOTAL \t  FECHA");
    printf("\n===========================================================================================\n");
    while(fscanf(ptrv_r,"%s %s %s %d %f %f %02d %02d %d\n",v_r.medi_id,v_r.medir_nombre,v_r.clien_nombre,&v_r.num,&v_r.sub,&v_r.total,&v_r.sDia,&v_r.sMes,&v_r.sAno)!=EOF){
		if(d==v_r.sDia &&m==v_r.sMes &&an==v_r.sAno){
		printf("%s",v_r.medi_id);
		printf("\t%s",v_r.medir_nombre);
		printf("\t%s",v_r.clien_nombre);
		printf("\t\t%d",v_r.num);
		printf("\t\t%.2f",v_r.sub);
		printf("\t\t%.2f",v_r.total);
		printf("\t%02d-%02d-%d\n",v_r.sDia,v_r.sMes,v_r.sAno);
		total=total+v_r.total;
		}
	   }
	   printf("\n-------------------------------------------------------------------------------------------");
	   printf("\n\t\t\t\t\t\t\t\t\tTotal: %.2f",total);
	   getche();
}
/*===================== Reporte de Compras Diarias ====================*/
void com_rpt_diaria(){
    char ch;
    int j,d,m,an;
    float total=0.00;

    ptrc_r=fopen("comprareport.dat","r");
    if(ptrc_r==NULL){
		printf("\n\t No hay registro");
		exit(0);
    }
    system("cls");
    printf("Ingresa la Fecha(dd-mm-aaaa): ");
    scanf("%d-%d-%d",&d,&m,&an);
    system("cls");
    printf("Presiona cualquier ENTER para regresar al MENU\n\n");
    printf("\n\t\t\t\tREPORTE DE COMPRAS\n\n");
    printf("ID \tPRODUCTO \tPROVEEDOR \tCANTIDAD \tSUBTOTAL \tTOTAL \t  FECHA");
    printf("\n===========================================================================================\n");
    while(fscanf(ptrc_r,"%s %s %s %d %f %f %02d %02d %d\n",c_r.medi_id,c_r.medir_nombre,c_r.prove_nombre,&c_r.num,&c_r.sub,&c_r.total,&c_r.sDia,&c_r.sMes,&c_r.sAno)!=EOF){
        if(d==c_r.sDia &&m==c_r.sMes &&an==c_r.sAno){
            printf("%s",c_r.medi_id);
            printf("\t%s",c_r.medir_nombre);
            printf("\t%s",c_r.prove_nombre);
            printf("\t\t%d",c_r.num);
            printf("\t\t%.2f",c_r.sub);
            printf("\t\t%.2f",c_r.total);
            printf("\t%02d-%02d-%d\n",c_r.sDia,c_r.sMes,c_r.sAno);
            total=total+c_r.total;
        }
    }
    printf("\n-------------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t\t\t\tTotal: %.2f",total);
    getche();
}
