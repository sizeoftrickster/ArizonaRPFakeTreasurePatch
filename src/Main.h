#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <memory>
#include "kthook/kthook.hpp"

using CTimer__Update_Prototype = void( __cdecl* )();

class AsiPlugin
{
	std::unique_ptr<class SetMaterialHook> setMaterialHook;

	kthook::kthook_simple<CTimer__Update_Prototype> CTimer__UpdateHook{ 0x58A330 };
public:
	explicit AsiPlugin();
	virtual ~AsiPlugin();
private:
	void CTimer__UpdateHooked( const decltype( CTimer__UpdateHook )& hook );
} AsiPlugin;

#endif // _MAIN_H_#pragma once
