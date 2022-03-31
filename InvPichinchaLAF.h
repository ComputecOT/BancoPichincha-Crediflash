//---------------------------------------------------------------------------

#ifndef InvPichinchaLAFH
#define InvPichinchaLAFH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFrCargarArchivos : public TForm
{
__published:	// IDE-managed Components
    TBitBtn *BitBNo;
    TImage *Image3;
    TMemo *MLoadFiles;
    TBitBtn *BitBSi;
private:	// User declarations
public:		// User declarations
    __fastcall TFrCargarArchivos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrCargarArchivos *FrCargarArchivos;
//---------------------------------------------------------------------------
#endif
