//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("Banco_Pichincha_Crediflash_1.cpp", FrInvPichincha);
USEFORM("..\..\..\InvPichincha\Extractos_Cuentas\programa\InvPichinchaLAF.cpp", FrCargarArchivos);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
             Application->Initialize();
             Application->Title = "Comunicaciones Escritas";
             Application->CreateForm(__classid(TFrInvPichincha), &FrInvPichincha);
		Application->CreateForm(__classid(TFrCargarArchivos), &FrCargarArchivos);
		Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
