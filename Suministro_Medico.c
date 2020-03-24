#include<stdio.h>
#include<time.h>

/*Incremento del identificador de cliente y proveedor*/
int i, getclien_id(), getprove_id();
/*Bienvenida y menú*/
void bienvenida(), main_menu();
/*Toda la casilla*/
void main_box(), box1(), wbox();
/*Ticket*/
void bill();
/*Menú del medicamento*/
void medicina();
void medi_venta(), balance(), update_balance();
void medi_entrada(), medi_buscar(), remanente();
/*Menú de proveedor*/
void proveedor();
void prove_entrada(), prove_lista(), prove_actual();
void buscar(), buscar_id(), buscar_nombre();
/*Menú del cliente*/
void cliente();
void clien_buscar(), buscar_cid(), buscar_cnombre();
void clien_entrada(), clien_lista(), clien_actual();
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
	char manu_fecha[15];
	int ticket_no;
	char compania_nombre[20];
	char prove_nombre[30];
};

struct medicamento info;
struct medicamento x[20];
FILE *ptr;

char a[10];
struct proveedor{
	int prove_id;
	char prove_nombre[25];
	char lugar[20];
	char mobil_no[11];
	char email[30];

};
struct proveedor infos;

struct cliente{
	int cust_id;
	char cust_nombre[30];
	char lugar[20];
	char mob_no[11];
	char email[50];

};
struct cliente info_c;
FILE *ptr1;

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

/*====================== FECHA Y HORA ======================*/
int h(void){
	/* Fecha (getfecha &d)
	Hora (gethora &h) */
    time_t h=time(0);  /*Tiempo real*/
    struct tm*now=localtime(&h);
	printf("Date: %d/%d/%d ",now->tm_mday,now->tm_mon,now->tm_year);
	printf("Time: %d:%d:%d",now->tm_hour, now->tm_min,now->tm_sec);
	return 0;
}

