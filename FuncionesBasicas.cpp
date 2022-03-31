#include <stdio.h>
#include <vcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#pragma hdrstop
#define MAXLCADF 2000


//---------------------------------------------------------------------------


char *Space(char *lineain,int rango)
{
  char espacios[1000];
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

char *Mid(char *destino,char *origen,int inicial,int rango)
{
  int i=0,a=0;

  for(a=0,i=inicial;a < rango;i++,a++)
  {
    destino[a]=origen[i];
  }
//  destino[a]=0;
  return destino;
}

//---------------------------------------------------------------------------

char *FECHAEXP(char *corfecha)
{
  char dia[10],mes[20],ano[10];

  memset(dia,'\0',sizeof(dia));
  memset(mes,'\0',sizeof(mes));
  memset(ano,'\0',sizeof(ano));
  Mid(dia,corfecha,0, 2);
  Mid(mes,corfecha,3, 2);
  Mid(ano,corfecha,6, 4);

  if(strcmp(mes,"01")==0)
    strcpy(mes,"Enero");
  else if(strcmp(mes,"02")==0)
    strcpy(mes,"Febrero");
  else if(strcmp(mes,"03")==0)
    strcpy(mes,"Marzo");
  else if(strcmp(mes,"04")==0)
    strcpy(mes,"Abril");
  else if(strcmp(mes,"05")==0)
    strcpy(mes,"Mayo");
  else if(strcmp(mes,"06")==0)
    strcpy(mes,"Junio");
  else if(strcmp(mes,"07")==0)
    strcpy(mes,"Julio");
  else if(strcmp(mes,"08")==0)
    strcpy(mes,"Agosto");
  else if(strcmp(mes,"09")==0)
    strcpy(mes,"Septiembre");
  else if(strcmp(mes,"10")==0)
    strcpy(mes,"Octubre");
  else if(strcmp(mes,"11")==0)
    strcpy(mes,"Noviembre");
  else if(strcmp(mes,"12")==0)
    strcpy(mes,"Diciembre");

  sprintf(corfecha,"%s%s%s%s%s", dia," de ",mes," de ",ano);
  return(corfecha);
}

///-----------------------------FUNCION-----------------------------------///

void REMPLACE(char *CR, char *CC)
{
char tmp;
tmp=*CR;
*CR=*CC;
*CC=tmp;
}
//---------------------FUNCION LIMPIA LINEA-------------------------------------

char *LimpiaLinea(char *Linea)
{
int J=0,a=0,LString=0;
char Aux[1000];
LString=strlen(Linea);

for (J=0;J<=LString;J++){
a=Linea[J];
if((Linea[J]=='´')  ||(Linea[J]=='¤') || (Linea[J]=='\"')||(Linea[J]=='"')||
   (Linea[J]=='µ') || (Linea[J]=='£') || (Linea[J]=='º') ||
   (Linea[J]=='!') || (Linea[J]=='³') || (Linea[J]=='|'))Linea[J]=' ';

//if((Linea[J]==','))Linea[J]='.';

   if (a== -107)
            Linea[J]='\ó';
}
return (Linea);
}
//------------------------FUNCION REGIONAL -------------------------------------
char *CampRegional(char *Regional)
{
    int Cunt=0,LString=0;

    LString=strlen(Regional);
    for (Cunt=0;Cunt<=LString;Cunt++)
    Regional[Cunt] = toupper(Regional[Cunt]);

    if(strstr(Regional,"Cali")||strstr(Regional,"CALI")!=NULL)
        strcpy(Regional,"Cali");
    else if (strstr(Regional,"Medell")||strstr(Regional,"MEDELL")!=NULL)
        strcpy(Regional,"Medellín");
    else if(strstr(Regional,"Bucaramanga")||strstr(Regional,"BUCARAMANGA")!=NULL)
        strcpy(Regional,"Bucaramanga");
    else
        strcpy(Regional,"Bogotá");

 return (Regional);
}
//------------------------FUNCION REGIONAL X DEPARATAMENTO ---------------------
char *CampRegionalxDepto(char *Regional)
{
    int Cunt=0,LString=0;

    LString=strlen(Regional);
    for (Cunt=0;Cunt<=LString;Cunt++) Regional[Cunt] = toupper(Regional[Cunt]);
       //
   if(strstr(Regional,"VALLE")!=NULL)
        strcpy(Regional,"Cali");
    else if (strstr(Regional,"ANTIOQUIA")!=NULL)
        strcpy(Regional,"Medellín");
    else if(strstr(Regional,"SANTANDER")!=NULL)
        strcpy(Regional,"Bucaramanga");
    else
        strcpy(Regional,"Bogotá");

 return (Regional);
}


///-----------------------------FUNCION-----------------------------------///
char *ELIM_ESP_IZQ(char *CadEnt)
{
        int i,j;
	char Aux[500];

        for(i=0;CadEnt[i]==' ';i++);// SALTA LOS ESPACIOS

        memset(Aux,'\0',sizeof(Aux));
        Aux[0]=' ';

        for(i=i,j=0;CadEnt[i]!='\0';i++,j++)Aux[j]=CadEnt[i]; //PASO DE CADENA

        memset(CadEnt,'\0',sizeof(CadEnt));
	strcpy(CadEnt,Aux);
	return CadEnt;
}
///-----------------------------FUNCION-----------------------------------///
char *ELIM_CERO_IZQ(char *CadEnt)
{
        int i,j;
	char Aux[500];

        for(i=0;CadEnt[i]=='0';i++);// SALTA LOS ESPACIOS

        memset(Aux,'\0',sizeof(Aux));
        Aux[0]='0';

        for(i=i,j=0;CadEnt[i]!='\0';i++,j++)Aux[j]=CadEnt[i]; //PASO DE CADENA

        memset(CadEnt,'\0',sizeof(CadEnt));
	strcpy(CadEnt,Aux);
	return CadEnt;
}

//------------------------FUNCION REGIONAL X DEPARATAMENTO ---------------------
char *DelSpace(char *Campos)
{
//nota ya debe venir la cadena limpia de caractes extraños
int CP,CN,Ini=0,i,LString=0;
char AUX[1000],Campo2[1000];

   memset(AUX,'\0',sizeof(AUX));
   memset(Campo2,'\0',sizeof(Campo2));
   strcpy(AUX,Campos);

   LString=strlen(AUX);
   for(CP=0,CN=0;CP<LString||AUX[CP]!='\0';CP++){

   if ((AUX[CP]==' ') && (Ini==0)) continue;
   else if ((AUX[CP]!=' '))
   {
   Campo2[CN]=AUX[CP];
   Ini=1;
   CN++;
   }
   if ((AUX[CP]==' ') && (AUX[CP+1]!=' ')&&(AUX[CP+1]!='\0')){
      Campo2[CN]=AUX[CP];
        CN++;
   }
 }

 strcpy(Campos,Campo2);
 return (Campos);
}


 ///-----------------------------FUNCION-----------------------------------///
char *EnteroFULL(char *CadEnt)
{
        int i,j,LString=0;
	char Aux[500];
//        strcpy(Aux,CadEnt);
        LString=strlen(CadEnt);
        for(i=0,j=0;i<LString;i++)
             if(CadEnt[i]!='\.'&& CadEnt[i]!='\,'&& CadEnt[i]!='\-' && CadEnt[i]!='\ '){
              CadEnt[j]=CadEnt[i];
                      j++;}
             CadEnt[j]=0;
	return CadEnt;
}
 ///-----------------------------FUNCION-----------------------------------///
char *DirEMail(char *CadEnt)
{
 int i=0,j=0,CG=0,LString=0;
 char Aux[500];

   if (strstr(CadEnt,"@"))
      {
       do
         {
          LString=strlen(CadEnt);
          for(i=i,j=0;i<LString && CadEnt[i]!='\ '&&CadEnt[i]!='\/'&&CadEnt[i]!='\-';i++)
              {
              CadEnt[j]=CadEnt[i];
              j++;
              }
          CadEnt[j]=0;
          if (!strstr(CadEnt,"@"))
              {
              CadEnt[j]='\ ';
              i++;
              }
          else
              CG=1;
        }while (CG!=1);
    }else

/*    if(strstr(CadEnt,"/")||strstr(CadEnt,"-")||strstr(CadEnt," ")){
      for(i=0;i<strlen(CadEnt);i++)
           if(CadEnt[i]=='\/'||CadEnt[i]=='\-')
              CadEnt[i]=';';
           else
              CadEnt[i]=CadEnt[i];

           //CadEnt[j]=0;
         if (strstr(CadEnt," "))
              DelSpace(CadEnt);
        }
     if (!strstr(CadEnt,"@"))
 */   memset(CadEnt,'\0',sizeof(CadEnt));

     return CadEnt;
}
//---------------------------------------------------------------------------

//================Funcion Para Buscar y Remplazar los Tab===================
char *RempChar(char *CadEnt, char Delim)
{
 int i=0,LongChar=0;

 LongChar=strlen(CadEnt);
 for (i==0;i<LongChar;i++)
     if (CadEnt[i]==Delim)
         CadEnt[i]='\ ';
 return CadEnt;
}

//---------------------------------------------------------------------------

//================Funcion Para Buscar y Remplazar Cartacters===================

char *RemplazaDelimiter(char *CadEnt,char DelIni, char DelEnd)
{
 int i=0,LongChar=0;
 LongChar=strlen(CadEnt);
 for (i==0;i<LongChar;i++)
     if (CadEnt[i]==DelIni)
         CadEnt[i]=DelEnd;
 return CadEnt;
}

//---------------------------------------------------------------------------

//================Funcion Para Buscar setiar campos===================

char *CompCamp(char *CadEnt, int MxC,char ValR)
{
  char CadenaR[1000],Comodin[1000];
  int KK=0;

  memset(Comodin,'\0',sizeof(Comodin));
  strcpy(Comodin,CadEnt);

  memset(CadenaR,'\0',sizeof(CadenaR));
  for (KK=0;KK<MxC;KK++)
            CadenaR[KK]= ValR;
  memmove(CadenaR+(strlen(CadenaR)-strlen(Comodin)),Comodin,strlen(Comodin));
  memset(CadEnt,'\0',sizeof(CadEnt));
  strcpy(CadEnt,CadenaR);

 return CadEnt;
}
//================Elimina Tíldes===================

char *DelTilde(char *CadEnt)
{
 int i=0,LongChar=0;
 LongChar=strlen(CadEnt);
 for (i==0;i<LongChar;i++){
	  if (CadEnt[i]== 'á' || CadEnt[i]== 'à')
			CadEnt[i]='a';
	  else if (CadEnt[i]== 'é' || CadEnt[i]== 'è')
			CadEnt[i]='e';
	  else if (CadEnt[i]== 'í' || CadEnt[i]== 'i')
			CadEnt[i]='i';
	  else if (CadEnt[i]== 'ó' || CadEnt[i]== 'ò')
			CadEnt[i]='o';
	  else if (CadEnt[i]== 'ú' || CadEnt[i]== 'ù')
			CadEnt[i]= 117;
	  else if (CadEnt[i]== 'Á' || CadEnt[i]== 'À')
			CadEnt[i]='A';
	  else if (CadEnt[i]== 'É' || CadEnt[i]== 'È')
			CadEnt[i]='E';
	  else if (CadEnt[i]== 'Í' || CadEnt[i]== 'Ì')
			CadEnt[i]='I';
	  else if (CadEnt[i]== 'Ó' || CadEnt[i]== 'Ò')
			CadEnt[i]='O';
	  else if (CadEnt[i]== 'Ú' || CadEnt[i]== 'Ù')
			CadEnt[i]='U';
 }
 return CadEnt;
}

//================Mayus===================

char *MinToMayus(char *CadEnt)
{
 int i=0,LongChar=0;
 LongChar=strlen(CadEnt);
 for (i==0;i<LongChar;i++)
        CadEnt[i]= toupper(CadEnt[i]);
 return CadEnt;
}


//================Funcion Insertar Campo x Delimitador ===================

char *InsertCamp(char *LinEnt,char *ValInsert, int PsInst, char Delt)
{
  char CadenaR[MAXLCADF],Comodin[MAXLCADF],ValInsert2[MAXLCADF];
  int KK=0,JJ=0,TCI=0,ContDelt=0,LengChar=0,LengChar2=0;

  memset(Comodin,'\0',sizeof(Comodin));  strcpy(Comodin,LinEnt);
  memset(ValInsert2,'\0',sizeof(ValInsert2));  strcpy(ValInsert2,ValInsert);
  memset(CadenaR,'\0',sizeof(CadenaR));

  LengChar=strlen(Comodin);
  for (KK=0,JJ=0;KK<=LengChar;KK++,JJ++)
       {
         if(Comodin[KK]==Delt){
            ContDelt++;
            if (ContDelt==PsInst){
                CadenaR[KK]=Comodin[JJ];KK++;
                LengChar2=strlen(ValInsert2);
                for (KK=KK,TCI=0;TCI<LengChar2;KK++,TCI++)  CadenaR[KK]=ValInsert2[TCI];
             }//End pos=pos
        }// end if del
        CadenaR[KK]=Comodin[JJ];
   } //end for
           CadenaR[KK++]='\n';
  memset(LinEnt,'\0',sizeof(LinEnt));  strcpy(LinEnt,CadenaR);

 return LinEnt;
}
//================Cont Char===================

int ContChar(char *CadEnt,char TChar )
{
 int NT=0,i,LongChar=0;
 LongChar=strlen(CadEnt);

 for (NT=0,i=0;i<LongChar;i++)
        if(CadEnt[i]==TChar)
                NT++;
 NT++;
 return NT;
}

//---------------------------------------------------------------------------
void CortaCad(char *Cadena)
{
  int i;

  ELIM_ESP_IZQ(Cadena);
//  DelSpace(Cadena);

  for(i = strlen(Cadena); (i >= 0) && (Cadena[i] <= ' '); i --){
    if ((Cadena[i]!='á') && (Cadena[i]!='é')&&(Cadena[i]!='ó')&&(Cadena[i]!='í')&&(Cadena[i]!='ú'))
    Cadena[i] = 0;
    }
}

//---------------------------------------------------------------------------

void CortaCad2(char *Cadena)
{
  int i;

  for(i = strlen(Cadena); (i >= 0) && (Cadena[i] <= ' '); i --)
    Cadena[i] = 0;
}

//---------------------------------------------------------------------------

void Campo(char* Fuente, char* Destino, int Posic, char Delim)
{
  int i,LString=0;
  char Aux[2000], *CadPtr, Detecta, Caden[2000];
  LString=strlen(Fuente);

  for(i=0;i<=LString+1;i++)
  {
    if((Fuente[i]=='´') || (Fuente[i]=='"') ||(Fuente[i]=='\"') ||(Fuente[i]=='¤') ||
     (Fuente[i]=='µ') || (Fuente[i]=='£') || (Fuente[i]=='º')||
     (Fuente[i]=='!') || (Fuente[i]=='³'))
     Aux[i]=' ';

   // else if(Fuente[i]=='\,')Aux[i]='\.';

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

///-----------------------------FUNCION-----------------------------------///
char *SeparaMiles(char *Auxiliar)
{
 int n, a, m,LongChar=0;
 char caden[31];

  CortaCad(Auxiliar);
  ELIM_CERO_IZQ(Auxiliar);
  ELIM_ESP_IZQ(Auxiliar);
  memset(caden,' ',sizeof(caden));
  n=30;
  a=0;
  m=0;
  LongChar=strlen(Auxiliar);
  for(m=LongChar;m>=0;m--)
  {
   if(((a==3+2) || (a==6+2) || (a==9+2) || (a==12+2) || (a==15+2) || (a==18+2)) && a!=LongChar)
   {
    caden[n]=Auxiliar[m];
    n--;
    caden[n]='.';
    n--;
   }   else if((a==2)&& a!=LongChar) {
            caden[n]=Auxiliar[m];
            n--;
            caden[n]=',';
            n--;
   }
   else
   {
    caden[n]=Auxiliar[m];
    n--;
   }
   a++;
  }
  CortaCad(caden);
  ELIM_CERO_IZQ(caden);
  ELIM_ESP_IZQ(caden);
    if (strlen(caden)==1)
      strcat(caden,",00");
  memset(Auxiliar,'\0',sizeof(Auxiliar));
  strcpy(Auxiliar,caden);
  return Auxiliar;
}
