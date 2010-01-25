//-----------------------------------------------------------------------------
//
//	SwitchToggleMultilevel.cpp
//
//	Implementation of the Z-Wave COMMAND_CLASS_SWITCH_TOGGLE_MULTILEVEL
//
//	Copyright (c) 2010 Mal Lansell <openzwave@lansell.org>
//
//	SOFTWARE NOTICE AND LICENSE
//
//	This file is part of OpenZWave.
//
//	OpenZWave is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published
//	by the Free Software Foundation, either version 3 of the License,
//	or (at your option) any later version.
//
//	OpenZWave is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

#include "CommandClasses.h"
#include "SwitchToggleMultilevel.h"
#include "Defs.h"
#include "Msg.h"
#include "Driver.h"
#include "Node.h"
#include "Log.h"

#include "ValueByte.h"
#include "ValueStore.h"

using namespace OpenZWave;

static enum SwitchToggleMultilevelCmd
{
    SwitchToggleMultilevelCmd_Set				= 0x01,
    SwitchToggleMultilevelCmd_Get				= 0x02,
    SwitchToggleMultilevelCmd_Report			= 0x03,
    SwitchToggleMultilevelCmd_StartLevelChange	= 0x04,
    SwitchToggleMultilevelCmd_StopLevelChange	= 0x05
};


//-----------------------------------------------------------------------------
// <SwitchToggleMultilevel::RequestState>                                                   
// Request current state from the device                                       
//-----------------------------------------------------------------------------
void SwitchToggleMultilevel::RequestState
(
)
{
    Msg* pMsg = new Msg( "SwitchToggleMultilevelCmd_StartLevelChange", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true );
    pMsg->Append( GetNodeId() );
    pMsg->Append( 2 );
    pMsg->Append( GetCommandClassId() );
    pMsg->Append( SwitchToggleMultilevelCmd_StartLevelChange );
    pMsg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
    Driver::Get()->SendMsg( pMsg );
}

//-----------------------------------------------------------------------------
// <SwitchToggleMultilevel::HandleMsg>
// Handle a message from the Z-Wave network
//-----------------------------------------------------------------------------
bool SwitchToggleMultilevel::HandleMsg
(
    uint8 const* _pData,
    uint32 const _length,
	uint32 const _instance	// = 0
)
{
    if (SwitchToggleMultilevelCmd_Report == (SwitchToggleMultilevelCmd)_pData[0])
    {
		Log::Write( "Received SwitchToggleMultiLevel report from node %d: level=%d", GetNodeId(), _pData[1] );

		GetNode()->SetLevel( _pData[1] );
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------
// <SwitchToggleMultilevel::Set>
// Toggle the state of the switch
//-----------------------------------------------------------------------------
void SwitchToggleMultilevel::Set
(
)
{
	Log::Write( "SwitchToggleMultilevel::Set - Toggling the state of node %d", GetNodeId() );
	Msg* pMsg = new Msg( "SwitchToggleMultilevel Set", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true );		
	pMsg->Append( GetNodeId() );
	pMsg->Append( 2 );
	pMsg->Append( GetCommandClassId() );
	pMsg->Append( SwitchToggleMultilevelCmd_Set );
	pMsg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
}

//-----------------------------------------------------------------------------
// <SwitchToggleMultilevel::StartLevelChange>
// Start the level changing
//-----------------------------------------------------------------------------
void SwitchToggleMultilevel::StartLevelChange
(
	SwitchToggleMultilevelDirection const _direction,
	bool const _bIgnoreStartLevel,
	bool const _bRollover
)
{
	uint8 param = (uint8)_direction;
	param |= ( _bIgnoreStartLevel ? 0x20 : 0x00 );
	param |= ( _bRollover ? 0x80 : 0x00 );

	Log::Write( "SwitchMultilevel::StartLevelChange - Starting a level change on node %d, Direction=%d, IgnoreStartLevel=%s and rollover=%s", GetNodeId(), (_direction==SwitchToggleMultilevelDirection_Up) ? "Up" : "Down", _bIgnoreStartLevel ? "True" : "False", _bRollover ? "True" : "False" );
	Msg* pMsg = new Msg( "SwitchMultilevel StartLevelChange", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true );		
	pMsg->Append( GetNodeId() );
	pMsg->Append( 3 );
	pMsg->Append( GetCommandClassId() );
	pMsg->Append( SwitchToggleMultilevelCmd_StartLevelChange );
	pMsg->Append( param );
	pMsg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
}

//-----------------------------------------------------------------------------
// <SwitchToggleMultilevel::StopLevelChange>
// Stop the level changing
//-----------------------------------------------------------------------------
void SwitchToggleMultilevel::StopLevelChange
(
)
{
	Log::Write( "SwitchToggleMultilevel::StopLevelChange - Stopping the level change on node %d", GetNodeId() );
	Msg* pMsg = new Msg( "SwitchToggleMultilevel StopLevelChange", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true );		
	pMsg->Append( GetNodeId() );
	pMsg->Append( 2 );
	pMsg->Append( GetCommandClassId() );
	pMsg->Append( SwitchToggleMultilevelCmd_StopLevelChange );
	pMsg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
}

//-----------------------------------------------------------------------------
// <SwitchToggleMultilevel::CreateVars>
// Create the values managed by this command class
//-----------------------------------------------------------------------------
void SwitchToggleMultilevel::CreateVars
(
	uint8 const _instance
)
{
	Node* pNode = GetNode();
	if( pNode )
	{
		ValueStore* pStore = pNode->GetValueStore();
		if( pStore )
		{
			Value* pValue = new ValueByte( GetNodeId(), GetCommandClassId(), _instance, 0, "Level", false, 0  );
			pStore->AddValue( pValue );
			pValue->Release();
		}
	}
}

