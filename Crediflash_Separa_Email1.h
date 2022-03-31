//---------------------------------------------------------------------------

#ifndef Crediflash_Separa_Email1H
#define Crediflash_Separa_Email1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TOpenDialog *OpenDialog1;
        TProgressBar *Barra1;
        TLabel *Label2;
        TImage *Image2;
        TLabel *Label3;
        TLabel *Label4;
	TLabel *Label1;
        void __fastcall Button1Click(TObject *Sender);
		  void __fastcall Timer1Timer(TObject *Sender);
		  bool __fastcall AnalizaEmail(String Email);
		  void __fastcall procesa_salida();
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
