//-----------------------------------------------------------------------------
//
//	TimeStamp.h
//
//	Cross-platform TimeStamp
//
//	Copyright (c) 2010 Mal Lansell <mal@lansell.org>
//	All rights reserved.
//
//	SOFTWARE NOTICE AND LICENSE
//
//	This file is part of OpenZWave.
//
//	OpenZWave is free software: you can redistribute it and/or modify
//	it under the terms of the GNU Lesser General Public License as published
//	by the Free Software Foundation, either version 3 of the License,
//	or (at your option) any later version.
//
//	OpenZWave is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public License
//	along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------
#include "Defs.h"
#include "TimeStamp.h"

#include "TimeStampImpl.h"	// Platform-specific implementation of a TimeStamp


using namespace OpenZWave;

//-----------------------------------------------------------------------------
//	<TimeStamp::TimeStamp>
//	Constructor
//-----------------------------------------------------------------------------
TimeStamp::TimeStamp
(
):
	m_pImpl( new TimeStampImpl() )
{
}

//-----------------------------------------------------------------------------
//	<TimeStamp::~TimeStamp>
//	Destructor
//-----------------------------------------------------------------------------
TimeStamp::~TimeStamp
(
)
{
	delete m_pImpl;
}

//-----------------------------------------------------------------------------
//	<TimeStamp::SetTime>
//	Sets the timestamp to now, plus an offset in milliseconds
//-----------------------------------------------------------------------------
void TimeStamp::SetTime
(
	int32 _milliseconds	// = 0
)
{
	m_pImpl->SetTime( _milliseconds );
}

//-----------------------------------------------------------------------------
//	<TimeStamp::TimeRemaining>
//	Gets the difference between now and the timestamp time in milliseconds
//-----------------------------------------------------------------------------
int32 TimeStamp::TimeRemaining
(
)
{
	return m_pImpl->TimeRemaining();
}

//-----------------------------------------------------------------------------
//	<TimeStamp::operator->
//	Overload the subtract operator to get the difference between two 
//	timestamps in milliseconds
//-----------------------------------------------------------------------------
int32 TimeStamp::operator- 
(
	TimeStamp const& _other
)
{
	return (int32)(m_pImpl - _other.m_pImpl);
}
