//---------------------------------------------------------------------------

#ifndef Banco_Pichincha_Crediflash_1H
#define Banco_Pichincha_Crediflash_1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFrInvPichincha : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TTimer *Timer;
        TLabel *Label1;
        TProgressBar *Barra2;
        TImage *Image1;
        TLabel *Label3;
        TMainMenu *Menu1;
        TMenuItem *Archivo1;
	TProgressBar *ProgressBar1;
	TImage *Image2;
	void __fastcall TimerTimer(TObject *Sender);
	bool __fastcall AnalizaEmail(String Email);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
        __fastcall TFrInvPichincha(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrInvPichincha *FrInvPichincha;
//---------------------------------------------------------------------------
#endif


/*
   cambie1

   Lee la cadena de entrada (parametro 1), lo copia en la segunda cadena (parametro 2)
   saltando n tabuladores (parametro 3)
*/
void Cambie1(char *entr, char *salid, int n)
{
 int j = 0, m = 0, l;
 for(j=0; j<n; j++)
 {
  for(m=m; entr[m]!='\t'&&entr[m]!='\0'&&entr[m]!='\r'&&entr[m]!='\n'; m++);
  m++;
 }
 for(m=m, l=0; entr[m]!='\t'&&entr[m]!='\0'&&entr[m]!='\r'&&entr[m]!='\n'; m++,l++)
  salid[l]=entr[m];
 salid[l]=0;
 return;
}