#include<stdio.h>
#include<time.h>
#include<stdlib.h>

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
void medi_venta(), balance(), update_balance();
void medi_entrada(), medi_buscar(), remanente();
/*Ticket*/
void ticket();
/*Sobre el programa*/
void sobre();
/*Menú de Reporte*/
void reporte_menu();
void reporte();
void venta_rpt(), venta_rpt_daily();
void ganancia_rpt();
void com_rpt(), com_rpt_daily();

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
	char vent_fecha[15];
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
	char medinombre[30];
	int medi_num;
	float medi_precio;
	float total;
	int dia;
	int mes;
	int ano;

};
struct ticket fac;
FILE *ptrticket;

struct ventas_reporte{
	char medi_id[6];
	char medir_nombre[20];
	char clien_nombre[30];
	int sDia,sMes,sAno;
	int num;
	float precio;
	float total;
};
struct ventas_reporte s_r;
FILE *ptrs_r;

struct compra_reporte{
	char medi_id[6];
	char medir_nombre[20];
	char prove_nombre[30];
	int sDay,sMonth,sYear;
	int num;
	float rate;
	float total;
};
struct compra_reporte p_r;
FILE *ptrp_r;

struct ganancia_reporte{
	char medi_id[6];
	char medir_nombre[20];
	int sDia,sMes,sAno;
	int num;
	float rate;
	float unit;
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
	printf("Date: %d/%d/%d ",now->tm_mday,now->tm_mon,now->tm_year);
	printf("Time: %d:%d:%d",now->tm_hour, now->tm_min,now->tm_sec);
	return 0;
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
		printf("Sin registro");
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

/*                           Bienvenida y menú                            */
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
    char ch, o=162;
    do{
        system("cls");
		printf("\n\t1. Informaci%cn del proveedor", o);
		printf("\n\t2. Informaci%cn del cliente", o);
		printf("\n\t3. Medicamentos");
		printf("\n\t4. Reporte");
		printf("\n\t5. Ticket");
		printf("\n\t6. Sobre el programa");
		printf("\n\t7. Salir");
		t();    /*Funcion (fecha y tiempo)*/
		printf("\n\n\t\tBienvenido a tu Sistema Medico");
		remainder();    /*Funcion (Medicamentos<10)*/
		printf("\n\t N%cmero de la opci%cn a realizar: ",163,o);
		scanf("%d",op);

        switch(op){
            case 1 :proveedor();
                break;
			case 2 :cliente();
                break;
			case 3 :medicina();
                break;
			case 4 :reporte();
                break;
			case 5 :ticket();
                break;
			case 6 :sobre();
                break;
			case 7:
                printf("%c\nDeseas salir ahora? S/N :", 168);
                ch=(getche());
                ch=toupper(ch);
                if(ch=='S'){
                    system("cls");
                    printf("\nEspera un momento.......");
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

/*============================== Proveedor ==============================*/
/*========================== Menú de Proveedor ==========================*/
void proveedor(){
    int opp, u=163;
    do{
        printf("----------------");
        printf("\nMEN%c DEL PROOVEDOR\n", 233);
        printf("----------------");
        printf("\n\t1. A%cdir Proveedor", 164);
        printf("\n\t2. Actualizar Proveedor");
        printf("\n\t3. Buscar Proveedor");
        printf("\n\t4. Lista de Proveedores");
        printf("\n\t5. Men%c Principal", u);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar:", u, 162);
        scanf("%d",opp);

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

/*============================== Cliente ==============================*/
/*========================== Menú de Cliente ==========================*/
void cliente(){
    int opc, u=163;
    do{
        printf("----------------");
        printf("\nMEN%c DEL CLIENTE\n", 233);
        printf("----------------");
        printf("\n\t1. A%cdir Cliente", 164);
        printf("\n\t2. Actualizar Cliente");
        printf("\n\t3. Buscar Cliente");
        printf("\n\t4. Lista de Clientes");
        printf("\n\t5. Men%c Principal", u);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar:", u, 162);
        scanf("%d",opc);

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

/*============================== Cliente ==============================*/
/*========================== Menú de Cliente ==========================*/
void medicina(){
    int opm, u=163;
    do{
        printf("----------------");
        printf("\nMEN%c DE MEDICAMENTOS\n", 233);
        printf("----------------");
        printf("\n\t1. A%cdir Nueva Medicina", 164);
        printf("\n\t2. Venta de Medicamento");
        printf("\n\t3. Inventario");
        printf("\n\t4. Buscar Medicamento");
        printf("\n\t5. Men%c Principal", u);
        printf("\n\nTeclea el n%cmero de la opci%cn a realizar:", u, 162);
        scanf("%d",opm);

        switch(opm){
            case 1 :medi_entrada();
                break;
            case 2 :medi_venta();
                break;
            case 3 :balance();
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

/*======================= Menú Sobre el Programa ======================*/
void sobre(){
    int c;
    system("cls");
    do{
        printf("***** REGISTRO LOCAL DE MEDICAMENTOS *****");
        printf("o Este proyecto es sobre un administrador local");
        printf("\n\to Podr%cs a%cadir Medicina, Cliente, Proveedor (Detalladamente)", 160,164);
        printf("\n\to Modificar y eliminar los registros");
        printf("\n\to Buscar Medicina, Cliente, Proveedor y sus detalles");
        printf("\n\to Podr%cs revisar el inventario", 160);
        printf("\n--- Presiona 1 para ir al Men%c Principal ---", 163);
        scanf("\n%d", c);
        switch(c){
            case 1:main_menu();
            puts("\nPresiona 1, por favor");
            getch();
        }
    }
    while(c!=1);
}
