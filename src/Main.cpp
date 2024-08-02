#include "Main.h"
#include "SetMaterialHook.h"

AsiPlugin::AsiPlugin() {
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	CTimer__UpdateHook.set_cb([this]( auto&&... args ) { 
		return AsiPlugin::CTimer__UpdateHooked( args... ); 
	});
	CTimer__UpdateHook.install();
}

AsiPlugin::~AsiPlugin() {
	CTimer__UpdateHook.remove();
}

void AsiPlugin::CTimer__UpdateHooked( const decltype( CTimer__UpdateHook )& hook ) {
	static bool isInitialized{ false };
	if ( !isInitialized ) {
			setMaterialHook = std::make_unique<SetMaterialHook>();
			isInitialized = true;
	}
	return hook.get_trampoline()();
}