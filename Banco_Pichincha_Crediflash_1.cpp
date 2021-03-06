//---------------------------------------------------------------------------

#include <vcl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#pragma hdrstop
#include "Banco_Pichincha_Crediflash_1.h"
#include "FuncionesBasicas.cpp"
#include "InvPichinchaLAF.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define MAXLCAD 1500

FILE *Archivo,*Salida, *SalidaM, *SalidaPdf, *BaseCedula, *BaseCedulaMail;

int xx=0,Xy=0, x=0, I=0, Y=0, NumClient=0, Numarch=0, Blancas=0, Impresiones=0, HojasSimplex=0, Extractos=0, HojasDuplex=0,
	 TImpresiones=0, THojasSimplex=0, TExtractos=0, THojasDuplex=0;
char mes[5], ciclo[5], linea[MAXLCAD],NomProceso[100],Password[25],Direccion[300],Sitio[200],Ciudad[100],Depto[100],
	  DireccionM[300];
char Matriz[30][300],nomarchivo[100][100];

char pagina[10], consedav[15], apreciado[30], nombre[65], direccion[65], sitio[180], periodo[20], pais[25];

double TamArch, ProgArc, AcumArc, AcumArcA, TamArchA;
TFrInvPichincha *FrInvPichincha;

//---------------------------------------------------------------------------
__fastcall TFrInvPichincha::TFrInvPichincha(TComponent* Owner)
        : TForm(Owner)
{
  char producto[50];

}

// ---------------------------------------------------------------------------

bool __fastcall TFrInvPichincha::AnalizaEmail(String Email) {
	// crear una funcion de tipo true o false
	int posicionArroba = 0;
	int posicionPunto = 0;
	String dominio = "";

	if (Email.Length() > 3) { // pregunta si la longitud del email es mayor que 3
		posicionArroba = Pos("@", Email); // obtiene la posicion del arroba dentro del email

		if (posicionArroba >= 3) { // si la posicion del arroba es mayor o igual que 3
			dominio = Email.SubString(posicionArroba + 1,
				(Email.Length() - posicionArroba + 1)); // obtengo un substring del email en la posicion del arroba +1 de la longitud del email - la posicion del arroba +1

			posicionPunto = Pos(".", dominio); // posicion contiene un punto en el dominio
			if (posicionPunto > 2) { // si la posicion punto es mayor que 2
				if (posicionPunto < dominio.Length()) { // si la longitud del dominio es menor que posicion punto
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}

		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

//---------------------------------------------------------------------------

void __fastcall TFrInvPichincha::TimerTimer(TObject *Sender)
{
	FILE *BaseCedulaRAC, *archord;
	char archiv[200],lineaRAC[2000],Campo1[30],Campo2[30],TipoDir[5];
	char mensaje[1000],Cadena[1000],comando[1000],orden[10];
	int zz=0, cont=0, j=0, l=0, k=0;
	__int64 Campo1Num=0;


	Timer->Enabled=false;
	Label1->Caption = "PROCESANDO...";

	FrCargarArchivos->MLoadFiles->Lines->Clear();

	OpenDialog1->Options.Clear();
	OpenDialog1->Options << ofAllowMultiSelect << ofFileMustExist;
	OpenDialog1->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	OpenDialog1->FilterIndex = 2; // start the dialog showing all files
	if (OpenDialog1->Execute())
	{
		for (I = 0; I < OpenDialog1->Files->Count; I ++)
		{
			Archivo = fopen(OpenDialog1->Files->Strings[I].t_str(), "r");
			FrCargarArchivos->MLoadFiles->Lines->Add (OpenDialog1->Files->Strings[I].t_str());
			fseek(Archivo, 0, SEEK_END);
			TamArch += ftell(Archivo);
			fclose(Archivo);
		}
	}


	if (FrCargarArchivos->ShowModal()==mrNo){
		exit(0);
	}

	Barra2->Position = 0;
	Salida = fopen("../salidas/Pichincha_Crediflash_P1.Doc1","w+");
//	SalidaM = fopen("../salidas/Pichincha_Crediflash_M.Doc1","w+");
//	SalidaPdf = fopen("../salidas/Pichincha_Crediflash_EMAIL.Doc1","w+");

	if((archord = fopen("../actualiz/BcoPicCrflash_OrdenPro.txt", "r")) == NULL)
	{
		memset(mensaje,'\0',sizeof(mensaje));
		sprintf(mensaje,"No se puede abrir %s\nVerifique e Inicie nuevamente el proceso", "../actualiz/BcoPicConsol_OrdenPro.txt");
		if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
			exit(0);
	}

	while(!feof(archord))
	{
		memset(Cadena,'\0',sizeof(Cadena));
		fgets(Cadena, 1000, archord);
		CortaCad(Cadena);
		if(strlen(Cadena)<=10)
			continue;

		memset(orden,'\0',sizeof(orden));
		Campo(Cadena, orden, 5, '\t');
	}

	fclose(archord);

	memset(comando,'\0',sizeof(comando));
	sprintf(comando,"%s%s","mkdir D:\\Ordenes\\Mail\\",orden);
	system(comando);

	memset(comando,'\0',sizeof(comando));
	sprintf(comando,"%s%s","mkdir D:\\Ordenes\\Pdfs\\",orden);
	system(comando);
	memset(comando,'\0',sizeof(comando));
	sprintf(comando,"%s%s%s","mkdir D:\\Ordenes\\Pdfs\\",orden,"\\pdfs");
	system(comando);
	memset(comando,'\0',sizeof(comando));
	sprintf(comando,"%s%s%s","mkdir D:\\Ordenes\\Pdfs\\",orden,"\\DTB");
	system(comando);
	memset(comando,'\0',sizeof(comando));
	sprintf(comando,"%s%s%s","mkdir D:\\Ordenes\\Pdfs\\",orden,"\\Conf");
	system(comando);

	if((archord = fopen("../programa/PDF_BcoPic_Crflash.ops", "w")) == NULL)
	{
		memset(mensaje,'\0',sizeof(mensaje));
		sprintf(mensaje,"No se puede abrir %s\nVerifique e Inicie nuevamente el proceso", "../programa/PDF_Pichincha_Crflash.ops");
		if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
			exit(0);
	}

	fprintf(archord,"%s\n","<Input>");
	fprintf(archord,"%s\n\n","DataInput=\"../salidas/Pichincha_Crediflash.Doc1\"");
	fprintf(archord,"%s\n","<Journal>");
	fprintf(archord,"%s%s%s%s\n","jrn1=","D:/Ordenes/pdfs/",orden,"/pdfs/PDF_BcoPic_Crflash.jrn");
	fprintf(archord,"%s%s%s%s\n\n","jrn2=","D:/Ordenes/pdfs/",orden,"/pdfs/PDF_BcoPic_Crflash_Vector.jrn");
	fprintf(archord,"%s%s%s%s\n\n","jrn3=","D:/Ordenes/pdfs/",orden,"/DTB/Base.txt");
	fprintf(archord,"%s\n","<Output>");
	fprintf(archord,"%s%s%s%s\n","Output1=","D:/Ordenes/pdfs/",orden,"/pdfs/BcoPichincha_Crflash_%3.pdf");

	fflush(archord);
	fclose(archord);

	memset(comando,'\0',sizeof(comando));
	sprintf(comando,"%s%s%s","D:/Ordenes/Pdfs/",orden,"/Conf/Campos.txt");

	if((archord = fopen(comando, "w")) == NULL)
	{
		memset(mensaje,'\0',sizeof(mensaje));
		sprintf(mensaje,"No se puede abrir %s\nVerifique e Inicie nuevamente el proceso", comando);
		if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
			exit(0);
	}

	fprintf(archord,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n","No.Producto","Nombre","Direccion","Sitio","Tipo_Producto","Identificacion","BcoPichincha_Crflash_");

	fflush(archord);
	fclose(archord);

	if((archord = fopen("../programa/Mail_BcoPic_Crflash.ops", "w")) == NULL)
	{
		memset(mensaje,'\0',sizeof(mensaje));
		sprintf(mensaje,"No se puede abrir %s\nVerifique e Inicie nuevamente el proceso", "../programa/MAIL_Pichincha_Crflash.ops");
		if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
			exit(0);
	}

	fprintf(archord,"%s\n","<Input>");
	fprintf(archord,"%s\n\n","DataInput=\"../salidas/Pichincha_Crediflash_EMAIL.Doc1\"");
	fprintf(archord,"%s\n","<Journal>");
	fprintf(archord,"%s%s%s%s\n","jrn1=","D:/Ordenes/Mail/",orden,"/Mail_BcoPic_Crflash.jrn");
	fprintf(archord,"%s%s%s%s\n\n","jrn2=","D:/Ordenes/Mail/",orden,"/Mail_BcoPic_Crflash_Vector.jrn");
	fprintf(archord,"%s\n","<Output>");
	fprintf(archord,"%s%s%s%s\n","Output1=","D:/Ordenes/Mail/",orden,"/BcoPichincha_Crflash_%3.pdf");

	fflush(archord);
	fclose(archord);

	memset(comando,'\0',sizeof(comando));
	sprintf(comando,"%s%s","copy /Y ..\\programa\\consulta\\* D:\\Ordenes\\pdfs\\",orden);
	system(comando);


	for(Y=0;Y<I;Y++)
	{
		Archivo=fopen(OpenDialog1->Files->Strings[Y].t_str(),"r");
		Label1->Caption= (AnsiString("Procesando\n") + OpenDialog1->Files->Strings[Y].t_str() );
		fseek(Archivo, 0, SEEK_END);
		TamArchA = ftell(Archivo);
		rewind(Archivo);

		while(!feof(Archivo))
		{
			ProgArc = ftell(Archivo);
			FrInvPichincha->Barra2->Position = (int)((((double)ProgArc + (double)AcumArc) / (double)TamArch) * 100);
			ProgressBar1->Position = (int)((((double)ProgArc + (double)AcumArcA) / (double)TamArchA) * 100);
			Application->ProcessMessages();

			memset(linea,'\0',sizeof(linea));
			if(!fgets(linea,MAXLCAD,Archivo) || strlen(linea)<1)
				continue;

			if(strstr(linea,"\t")!=NULL || strstr(linea,"\"")!=NULL || strstr(linea,"|")!=NULL)
			{
				l=strlen(linea);
				for(k=0;k<=l;k++)
					if(linea[k]=='\t' || linea[k]=='"' || linea[k]=='|')
						linea[k]=' ';
			}

//			Campo(linea, emaistr, 4, ';');
//			result = AnalizaEmail(emailAux);
			fprintf(Salida,"%s",linea);

		}
		AcumArc += ProgArc;
		Application->ProcessMessages();
		FrInvPichincha->Refresh();
		fflush(Archivo);
		fclose(Archivo);
	}
	fflush(Salida); fclose(Salida);
//	fflush(SalidaM); fclose(SalidaM);
//	fflush(SalidaPdf); fclose(SalidaPdf);


	Label1->Caption = "TERMINADO!!!!!";
	Application->ProcessMessages();
	exit(1);

}

//---------------------------------------------------------------------------

void __fastcall TFrInvPichincha::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	CanClose=false;
	if (MessageDlg("USTED ESTA CERRANDO EL PROGRAMA DE BANCO PICHINCHA.\nESTA SEGURO QUE DESEA CANCELARLO?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
		exit(9);
}
//---------------------------------------------------------------------------


