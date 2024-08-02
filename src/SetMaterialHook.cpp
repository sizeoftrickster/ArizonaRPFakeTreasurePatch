#include "SetMaterialHook.h"
#include "samp/common.h"

SetMaterialHook::SetMaterialHook() {
	auto sampHandle = SAMP::GetHandle();
	auto version = SAMP::GetVersion();
	switch ( version ) {
		// R1
		case ( SAMP::Version::R1 ): {
			CObject__SetMaterialAddress = sampHandle + 0xA2ED0;
			break;
		}
		// R3
		case ( SAMP::Version::R3 ): {
			CObject__SetMaterialAddress = sampHandle + 0xA7CA0;
			break;
		}
		default: {
			return;
		}
	}
	COBject_SetMaterialHook.set_dest( CObject__SetMaterialAddress );
	COBject_SetMaterialHook.set_cb([this]( auto&&... args ) {
		return SetMaterialHook::CObject__SetMaterialHooked( args... );
	});
	COBject_SetMaterialHook.install();
}

SetMaterialHook::~SetMaterialHook() {
	COBject_SetMaterialHook.remove();
}

void SetMaterialHook::CObject__SetMaterialHooked( const decltype( COBject_SetMaterialHook ) & hook, SAMP::CObject* this_, int nModel, int nIndex, const char* szTxd, const char* szTexture, unsigned long color ) {
	//printf("nModel: %d | nIndex: %d | szTxd: %s | szTexture: %s | color: %d\n", nModel, nIndex, szTxd, szTexture, color);
	auto myObj = this_;

	for ( int i : objectsId ) {
		if ( myObj->m_nModel == i && nModel == NULL ) {
			// Telegram -> fazenda1486
			myObj->m_nModel = 1486;
			myObj->Remove();
			myObj->DeleteRwObject();
		}
	}

	return hook.get_trampoline()( myObj, nModel, nIndex, szTxd, szTexture, color );
}