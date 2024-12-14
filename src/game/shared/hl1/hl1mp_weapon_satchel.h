//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef HL1_WEAPON_SATCHEL_H
#define HL1_WEAPON_SATCHEL_H
#ifdef _WIN32
#pragma once
#endif


#ifndef CLIENT_DLL
#include "hl1/hl1_basegrenade.h"
#include "hl1/hl1_basecombatweapon_shared.h"
#endif


#ifdef CLIENT_DLL
#define CWeaponSatchel_HL1 C_WeaponSatchel_HL1
#endif


//-----------------------------------------------------------------------------
// CWeaponSatchel_HL1
//-----------------------------------------------------------------------------

class CWeaponSatchel_HL1 : public CBaseHL1CombatWeapon
{
	DECLARE_CLASS( CWeaponSatchel_HL1, CBaseHL1CombatWeapon );

	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
public:

	CWeaponSatchel_HL1( void );

	void	Equip( CBaseCombatCharacter *pOwner );
	bool	HasAnyAmmo( void );
	bool	CanDeploy( void );
	void	Precache( void );
	void	PrimaryAttack( void );
	void	SecondaryAttack( void );
	void	WeaponIdle( void );
	bool	Deploy( void );
	bool	Holster( CBaseCombatWeapon *pSwitchingTo = NULL );

	void		ItemPostFrame( void );
	const char	*GetViewModel( int viewmodelindex = 0 ) const;
	const char	*GetWorldModel( void ) const;

	bool	HasChargeDeployed() { return ( m_iChargeReady != 0 ); }

	void	OnRestore( void );

//	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

#ifndef CLIENT_DLL
	DECLARE_ACTTABLE();
#endif

private:
	void	Throw( void );
	void	ActivateSatchelModel( void );
	void	ActivateRadioModel( void );

private:
	CNetworkVar( int, m_iRadioViewIndex );
	CNetworkVar( int, m_iRadioWorldIndex );
	CNetworkVar( int, m_iSatchelViewIndex );
	CNetworkVar( int, m_iSatchelWorldIndex );
	CNetworkVar( int, m_iChargeReady );
};


#ifndef CLIENT_DLL
//-----------------------------------------------------------------------------
// CSatchelCharge_HL1
//-----------------------------------------------------------------------------

class CSatchelCharge_HL1 : public CHL1BaseGrenade
{
public:
	DECLARE_CLASS( CSatchelCharge_HL1, CHL1BaseGrenade );

	CSatchelCharge_HL1();


	void	Spawn( void );
	void	Precache( void );
	void	SatchelTouch( CBaseEntity *pOther );
	void	SatchelThink( void );
	void	SatchelUse( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );

	DECLARE_DATADESC();

private:
	Vector	m_vLastPosition;
	float	m_flNextBounceSoundTime;
	bool	m_bInAir;

private:
	void	BounceSound( void );
	void	UpdateSlideSound( void );
	void	Deactivate( void );
};
#endif


#endif // HL1_WEAPON_SATCHEL_H