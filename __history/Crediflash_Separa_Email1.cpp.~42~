//---------------------------------------------------------------------------

#include <vcl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <StrUtils.hpp>
#pragma hdrstop

#include "Crediflash_Separa_Email1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

long TamArch=0, ProgArc=0, AcumArc=0;
char matriz[5000][2000], matrizM[5000][2000], Aceptacion[5], Cuenta[30],Direccion[200],DirChar[60];
int I=0, j=0,ContDet=0, ContCli=0,cont=0, flagmail=0,contMuest=0;
FILE *Archivo2,*Salida,*SalidaMuest;

TStringList* campos;
TStringList* listaEmailOk;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
	campos = new TStringList();
	campos->Sorted = false; // Indicar que no va a ordenar
	campos->Delimiter = ';'; // Define delimitador
	campos->StrictDelimiter = true; // Divida los campos unicamente por el delimitador indicado

	listaEmailOk = new TStringList();
	listaEmailOk->Sorted = true;
	listaEmailOk->Duplicates = dupIgnore;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  exit(1);
}

//---------------------------------------------------------------------------

void StrUprX(char *cad)
{
  int i;

  for(i = 0; cad[i]; i ++)
    if((cad[i] >= 'a') && (cad[i] <= 'z'))
      cad[i] = (char)((cad[i] - 'a') + 'A');
}

//---------------------------------------------------------------------------

char *Mid(char *dato,char *lineain,int inicial,int rango)
{
  int k=0,a=0;

  for(a=0,k=inicial;a < rango;k++,a++)
  {
    dato[a]=lineain[k];
  }
  dato[a]=0;
  return dato;
}

//---------------------------------------------------------------------------

void CortaCad(char *Cadena)
{
  int i;

  for(i = strlen(Cadena); (i >= 0) && (Cadena[i] <= ' '); i --)
    Cadena[i] = 0;
}

//---------------------------------------------------------------------------

char *elim_esp_izq(char *CadEnt)
{
  int i, a;
  char Aux[500];

  for(i=0;CadEnt[i]==' ';i++);
   memset(Aux,'\0',sizeof(Aux));
  Aux[0]=' ';
  for(i=i,a=0;CadEnt[i]!='\0';i++,a++) Aux[a]=CadEnt[i];
    memset(CadEnt,'\0',sizeof(CadEnt));
  strcpy(CadEnt,Aux);
 return CadEnt;
}

//---------------------------------------------------------------------------

char *Space(char *lineain,int rango)
{
  char espacios[500];
  int i=0,a=0;
  memset(espacios,'\0',sizeof(espacios));
  for(i = strlen(lineain); (i >= 0) && (lineain[i] <= ' '); i --)
    lineain[i] = 0;

  a = rango - strlen(lineain);
  for(i=0;i<a;i++)
  {
    espacios[i]=' ';
  }
  strcat(lineain,espacios);
  return lineain;
}

//---------------------------------------------------------------------------

void Campo(char* Fuente, char* Destino, int Posic, char Delim)
{
  int i;
  char Aux[500], *CadPtr, Detecta, Caden[500];

  for(i=0;i<=strlen(Fuente);i++)
  {
    if((Fuente[i]=='´') || (Fuente[i]=='"') || (Fuente[i]=='à') || (Fuente[i]=='\"') || (Fuente[i]=='Á') || (Fuente[i]=='¤') || (Fuente[i]=='µ') || (Fuente[i]=='â') || (Fuente[i]=='£') || (Fuente[i]=='º') || (Fuente[i]==',') || (Fuente[i]=='Ã') || (Fuente[i]=='Â') || (Fuente[i]=='!') || (Fuente[i]=='³'))
     Aux[i]=' ';
    else
     Aux[i]=Fuente[i];
  }
  Aux[i]=0;
  CortaCad(Aux);
  CadPtr = NULL;
  Detecta = 1;


  for(i = 0; Aux[i]; i++)
  {
    if(Posic == 0)
    {
      Posic --;
      CadPtr = Aux + i;
    }
    if((Aux[i] == Delim) && Detecta)
    {
      Aux[i] = 0;
      Posic --;
    }
    if((Delim == ',') && (Aux[i] == '"') && (Aux[i] == '´'))
      Detecta = (char)(1 - Detecta);
  }
  if(CadPtr)
  {
    strcpy(Destino, CadPtr);
    if((Destino[0] == '"')&&(Destino[strlen(Destino) - 1] == '"')
        && (strlen(Destino) > 1))
    {
      for(i = 1; Destino[i + 1]; i ++)
		  Destino[i - 1] = Destino[i];
		Destino[i - 1] = 0;
	 }
  }
  else
	 Destino[0] = 0;
}

// ---------------------------------------------------------------------------

bool __fastcall TForm1::AnalizaEmail(String Email) {
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

void __fastcall TForm1::procesa_salida()
{
	char linea[2000];
	char MatrizChar[200][50],lineaChar[2000],CuentaChar[30],CampoChar[200];
	int flag=0,l=0,k=0,m=0;

	while(flag==0)
	{
		memset(linea,'\0',sizeof(linea));
		fgets(linea, 2000, Archivo2);
		if(feof(Archivo2))
			break;

		if(linea[0]=='1' && linea[1]=='A'){
			if(cont>=1){
				if(listaEmailOk->Count >=1 && flagmail==1 && (strcmp(Aceptacion,"S")==0 || strcmp(Aceptacion,"s")==0)){
					for(int d=0; d < listaEmailOk->Count; d++){
						memset(DirChar,'\0',sizeof(DirChar));
						strcpy(DirChar,listaEmailOk->Strings[d].t_str());
						Space(DirChar,50);
						for(k=0;k<cont;k++){
							if(k==0 && matrizM[k][0]=='1' &&  matrizM[k][1]=='A')
								memcpy(matrizM[k]+151,DirChar,50);
							fprintf(Salida,"%s",matrizM[k]);
							if(contMuest<=19)
								fprintf(SalidaMuest,"%s",matrizM[k]);
						}
					}
					contMuest++;
					memset(matrizM,'\0',sizeof(matrizM));
				}else{
					for(k=0;k<cont;k++)
					{
						fprintf(Salida,"%s",matriz[k]);
						if(contMuest<=19)
							fprintf(SalidaMuest,"%s",matriz[k]);
					}
					contMuest++;
				}

				for(k=0;k<cont;k++)
				{
					if(k==0 && matriz[k][0]=='1' &&  matriz[k][1]=='A')
						matriz[k][1055]='A';
					fprintf(Salida,"%s",matriz[k]);
				}
				memset(matriz,'\0',sizeof(matriz));
			}

			listaEmailOk->Clear();
			flagmail=0;
			cont=0;

			memset(Aceptacion,'\0',sizeof(Aceptacion));
			memcpy(Aceptacion,linea+1055,1);
			elim_esp_izq(Aceptacion);
			CortaCad(Aceptacion);

			memset(Direccion,'\0',sizeof(Direccion));
			memcpy(Direccion,linea+151,50);
			elim_esp_izq(Direccion);
			CortaCad(Direccion);

			campos->Clear();
			campos->DelimitedText = Direccion;
			for (int d = 0; d < campos->Count; d++) {
				String emailAux = campos->Strings[d];
				emailAux = ReplaceStr(emailAux, " ", "");
				bool result = AnalizaEmail(emailAux);
				if(result && !emailAux.IsEmpty()){
					flagmail=1;
					listaEmailOk->Add(emailAux);
				}
			}
			if((flagmail==1) && (strcmp(Aceptacion,"S")==0 || strcmp(Aceptacion,"s")==0)){
				memset(matrizM[cont],'\0',sizeof(matrizM[cont]));
				strcpy(matrizM[cont],linea);
			}

//			linea[1055]='N';
			linea[1055]='S';
			memset(matriz[cont],'\0',sizeof(matriz[cont]));
			strcpy(matriz[cont],linea);
			cont++;
			flag=1;
		}
		else
		{
			if((flagmail==1) && (strcmp(Aceptacion,"S")==0 || strcmp(Aceptacion,"s")==0)){
				memset(matrizM[cont],'\0',sizeof(matrizM[cont]));
				strcpy(matrizM[cont],linea);
			}

			memset(matriz[cont],'\0',sizeof(matriz[cont]));
			strcpy(matriz[cont],linea);
			cont++;
		}
	}
	Timer1->Enabled=true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	char mensaje[2000],lineaOut[4000],linea[2000],credit[20];
	int l=0,k=0,contt=0;

   Timer1->Enabled=false;


	if((Archivo2 = fopen("../salidas/Pichincha_Crediflash_P2.Doc1", "r")) == NULL)
	{
		memset(mensaje,'\0',sizeof(mensaje));
		sprintf(mensaje,"No se puede crear %s\nVerifique e Inicie nuevamente el proceso", "../salidas/Pichincha_Crediflash_P2.Doc1");
		if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
			exit(1);
	}
	fseek(Archivo2, 0, SEEK_END);
	TamArch += ftell(Archivo2);
	rewind(Archivo2);

	if((Salida = fopen("../salidas/Pichincha_Crediflash.Doc1", "w")) == NULL)
	{
		memset(mensaje,'\0',sizeof(mensaje));
		sprintf(mensaje,"No se puede crear %s\nVerifique e Inicie nuevamente el proceso", "../salidas/Pichincha_Crediflash.Doc1");
		if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
			exit(1);
	}

	if((SalidaMuest = fopen("../salidas/Pichincha_Crediflash_Muest.Doc1", "w")) == NULL)
	{
		memset(mensaje,'\0',sizeof(mensaje));
		sprintf(mensaje,"No se puede crear %s\nVerifique e Inicie nuevamente el proceso", "../salidas/Pichincha_Crediflash_Muest.Doc1");
		if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
			exit(1);
	}

	Label3->Caption="PROCESANDO";
	Application->ProcessMessages();

	while(!feof(Archivo2))
   {
      ProgArc = ftell(Archivo2);
      Barra1->Position = (int)((((double)ProgArc + (double)AcumArc) / (double)TamArch) * 100);
		procesa_salida();
      Timer1->Enabled=false;
		Application->ProcessMessages();
	}
   AcumArc += ProgArc;
	fclose(Archivo2);

	if(listaEmailOk->Count >=1 && flagmail==1 && (strcmp(Aceptacion,"S")==0 || strcmp(Aceptacion,"s")==0)){
		for(int d=0; d < listaEmailOk->Count; d++){
			memset(DirChar,'\0',sizeof(DirChar));
			strcpy(DirChar,listaEmailOk->Strings[d].t_str());
			Space(DirChar,50);
			for(k=0;k<cont;k++){
				if(k==0 && matrizM[k][0]=='1' &&  matrizM[k][1]=='A')
					memcpy(matrizM[k]+151,DirChar,50);
				fprintf(Salida,"%s",matrizM[k]);
				if(contMuest<=19)
					fprintf(SalidaMuest,"%s",matrizM[k]);
			}
		}
		contMuest++;
		memset(matrizM,'\0',sizeof(matrizM));
	}else{
		for(k=0;k<cont;k++)
		{
			fprintf(Salida,"%s",matriz[k]);
			if(contMuest<=19)
				fprintf(SalidaMuest,"%s",matriz[k]);
		}
		contMuest++;
	}

	for(k=0;k<cont;k++)
	{
		if(k==0 && matriz[k][0]=='1' &&  matriz[k][1]=='A')
			matriz[k][1055]='A';
		fprintf(Salida,"%s",matriz[k]);
	}
	memset(matriz,'\0',sizeof(matriz));

  Label3->Caption="PROCESADO";
  Application->ProcessMessages();

  fflush(Salida);
  fclose(Salida);
  fflush(SalidaMuest);
  fclose(SalidaMuest);
  exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose=false;
	if (MessageDlg("USTED ESTA CERRANDO EL PROGRAMA DE CREDIFLASH.\nESTA SEGURO QUE DESEA CANCELARLO?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
		exit(9);
}
//---------------------------------------------------------------------------

