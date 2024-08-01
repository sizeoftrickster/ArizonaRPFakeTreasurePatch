#ifndef _SET_MATERIAL_HOOK_H_
#define _SET_MATERIAL_HOOK_H_

#include <Windows.h>
#include <kthook/kthook.hpp>
#include <vector>

#include "samp/0.3.7-R3-1/CObject.h"

using COBject__SetMaterial__Prototype = void( __thiscall* )( SAMP::CObject*, int, int, const char*, const char*, unsigned long );

class SetMaterialHook
{
	DWORD CObject__SetMaterialAddress = 0x0;

	kthook::kthook_simple<COBject__SetMaterial__Prototype> COBject_SetMaterialHook{ CObject__SetMaterialAddress };

	std::vector<int> objectsId = { 2680, 1271 };
public:
	SetMaterialHook();
	~SetMaterialHook();
private:
	void CObject__SetMaterialHooked( const decltype( COBject_SetMaterialHook )& hook, SAMP::CObject* this_, int nModel, int nIndex, const char* szTxd, const char* szTexture, unsigned long color );
}; // class SetMaterialHook

#endif // _SET_MATERIAL_HOOK_H_