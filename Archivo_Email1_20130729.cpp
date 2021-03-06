//---------------------------------------------------------------------------

#include <vcl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#pragma hdrstop

#include "Archivo_Email1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

long TamArch=0, ProgArc=0, AcumArc=0;
char matriz[5000][1000];
int I=0, j=0,ContDet=0, ContCli=0, ContNew=0;
FILE *Archivo2,*Salida,*Salida2,*archord,*correo,*SalidaNew;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
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
  char Aux[1000], *CadPtr, Detecta, Caden[1000];

  for(i=0;i<=strlen(Fuente);i++)
  {
    if((Fuente[i]=='?') || (Fuente[i]=='"') || (Fuente[i]=='?') || (Fuente[i]=='\"') || (Fuente[i]=='?') || (Fuente[i]=='?') || (Fuente[i]=='?') || (Fuente[i]=='?') || (Fuente[i]=='?') || (Fuente[i]=='?') || (Fuente[i]==',') || (Fuente[i]=='?') || (Fuente[i]=='?') || (Fuente[i]=='!') || (Fuente[i]=='?'))
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
    if((Delim == ',') && (Aux[i] == '"') && (Aux[i] == '?'))
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

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
   char mensaje[2000],lineaOut[4000],linea[2000],credit[20],Cadena[1000],orden[10],comando[1000],NomArchivo[200],nominter[200],Salnominter[200];
   char campo1[50],campo3[50],campo4[50],campo5[200],campo22[10],campo7[100],campo44[200];
   char nomNew[200],parte1[110],parte2[110];  
   int l=0,k=0,contt=0,len=0;

   Timer1->Enabled=false;


	if((archord = fopen("../actualiz/BcoPicCrflash_OrdenPro.txt", "r")) == NULL)
	{
		memset(mensaje,'\0',sizeof(mensaje));
		sprintf(mensaje,"No se puede abrir %s\nVerifique e Inicie nuevamente el proceso", "../actualiz/BcoPicCrflash_OrdenPro.txt");
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
   sprintf(comando,"%s%s%s","del D:\\Ordenes\\Normales\\",orden,"\\*.ctm");
   system(comando);

   memset(comando,'\0',sizeof(comando));
   sprintf(comando,"%s%s%s%s%s","dir /B D:\\Ordenes\\Normales\\",orden,"\\*ENVIOS_WEB*.plus > D:\\Ordenes\\Normales\\",orden,"\\Total_archivo.ctm");
   system(comando);

   memset(comando,'\0',sizeof(comando));
   sprintf(comando,"%s%s%s","D:\\Ordenes\\Normales\\",orden,"\\Total_archivo.ctm");

	if((Archivo2 = fopen(comando, "r")) != NULL)
   {
      fseek(Archivo2, 0, SEEK_END);
      TamArch += ftell(Archivo2);
      rewind(Archivo2);

      Label3->Caption="PROCESADO"; 
      Label3->Refresh();
      Form1->Refresh();

      while(!feof(Archivo2))
      {
         memset(Cadena,'\0',sizeof(Cadena));
         fgets(Cadena, 1000, Archivo2);
         CortaCad(Cadena);
         if(strlen(Cadena)<=10)
            continue;

			if(strstr(Cadena,"_COLOR_")==NULL)
				continue;

			ProgArc = ftell(Archivo2);
			Barra1->Position = (int)((((double)ProgArc + (double)AcumArc) / (double)TamArch) * 100);
         Application->ProcessMessages();      

         memset(NomArchivo,'\0',sizeof(NomArchivo));
         strcpy(NomArchivo,Cadena);

         memset(nominter,'\0',sizeof(nominter));
         sprintf(nominter,"%s%s%s","D:\\Ordenes\\Normales\\",orden,"\\");
         strcat(nominter,Cadena);

         memset(parte1,'\0',sizeof(parte1));
         memset(parte2,'\0',sizeof(parte2));
         memcpy(parte1,Cadena,7);
         memcpy(parte2,Cadena+7,100);

         memset(Salnominter,'\0',sizeof(Salnominter));
         sprintf(Salnominter,"%s%s%s","D:\\Ordenes\\Normales\\",orden,"\\");
         strcat(Salnominter,parte1);
         strcat(Salnominter,"COLOR_");
         strcat(Salnominter,parte2);

         if((correo = fopen(nominter, "r")) == NULL)
         {
            memset(mensaje,'\0',sizeof(mensaje));
            sprintf(mensaje,"No se puede abrir %s\nVerifique e Inicie nuevamente el proceso", nominter);
            if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
               exit(0);
         }

         len=strlen(Salnominter);
         Salnominter[len-4]=0;
         strcat(Salnominter,"txt");

         if((Salida = fopen(Salnominter, "w")) == NULL)
         {
            memset(mensaje,'\0',sizeof(mensaje));
            sprintf(mensaje,"No se puede abrir %s\nVerifique e Inicie nuevamente el proceso", Salnominter);
            if (MessageDlg(mensaje, mtConfirmation, TMsgDlgButtons() << mbOK, 0) == mrOk)
               exit(0);
         }

         while(!feof(correo))
         {
            memset(Cadena,'\0',sizeof(Cadena));
            fgets(Cadena, 1000, correo);
            CortaCad(Cadena);
            if(strlen(Cadena)<=10)
               continue;

            Campo(Cadena, campo1, 0, '\t');     //Barcode
            Campo(Cadena, campo3, 2, '\t');     //Cedula O Clave PDF
            Campo(Cadena, campo4, 3, '\t');     //Cuenta
            Campo(Cadena, campo5, 4, '\t');     //Nombre
				Campo(Cadena, campo7, 6, '\t');     //Direcci?n Web Pdf
				Campo(Cadena, campo22, 21, '\t');   //Reserva 3
            Campo(Cadena, campo44, 43, '\t');     //Corte Pdf

            fprintf(Salida,"%s\t%s%s%s\t%s\t%s%s%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
						  campo7,
						  "Pichincha/Crediflash/BcoPichincha_Crflash_",campo4,".pdf",
						  campo3,
						  "BcoPichincha_Crflash_",campo4,".pdf",
						  orden,
						  campo1,
						  campo5,
						  campo3,
						  campo4,
						  campo22);
         }
         fflush(Salida);
         fclose(Salida);

         memset(comando,'\0',sizeof(comando));
         sprintf(comando,"%s%s%s%s%s","copy /Y ",Salnominter," D:\\Ordenes\\mail\\",orden,"\\");
         system(comando);
      }
      AcumArc += ProgArc;
   }

   fclose(Archivo2);
   fflush(SalidaNew);
   fclose(SalidaNew);
   exit(0);
}
//---------------------------------------------------------------------------

