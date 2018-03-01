//--------------------------------
//  (c) Reliable Software, 2004-06
//--------------------------------
#include "precompiled.h"
#include "TopCtrl.h"
#include "OutSink.h"
#include "WebBrowserRegistry.h"
#include "Resource/resource.h"
#include <Win/WinMain.h>
#include <Win/WinClass.h>
#include <Win/WinMaker.h>
#include <Win/MsgLoop.h>
#include <Handlers.h>

Out::Sink TheOutput;
WebBrowserRegistry TheRegistry ("WebBrowser");

int Win::Main (Win::Instance hInst, char const * cmdParam, int cmdShow)
{
    try
    {
        // Create top window class
		Win::Class::TopMaker topWinClass (ID_MAIN, hInst, ID_MAIN);
        topWinClass.Register ();

		Win::MessagePrepro msgPrepro;
		TopCtrl ctrl;

		// Create top window (hidden)
		ResString caption (hInst, ID_CAPTION);
		Win::TopMaker topWin (caption, ID_MAIN, hInst);
		Win::Dow::Handle appWin = topWin.Create (&ctrl);

		// Display top window
		Win::Placement placement (appWin);
		TheRegistry.ReadPlacement (placement);
		placement.CombineShowCmd (cmdShow);
		appWin.SetPlacement (placement);

		// The main message loop
		return msgPrepro.Pump ();
    }
    catch (Win::Exception e)
    {
        TheOutput.Display (e);
    }
    catch (...)
    {
		Win::ClearError ();
        TheOutput.Display ("Internal error: Unknown exception", Out::Error);
    }
	return 0;
}
