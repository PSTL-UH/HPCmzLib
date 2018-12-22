#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2018 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to convert System.Convert methods which convert from
//	floating point types to integral types.
//----------------------------------------------------------------------------------------
#include <cmath>

class FloatingPointToInteger
{
public:
	static char ToSByte(double source)
	{
		char floor = (char)std::floor(source);
		if (std::abs(source - floor) == 0.5)
		{
			if (floor % 2 == 0)
				return floor;
			else
				return (char)std::ceil(source);
		}
		else if (std::abs(source - floor) < 0.5)
			return floor;
		else
			return (char)std::ceil(source);
	}

	static unsigned char ToByte(double source)
	{
		unsigned char floor = (unsigned char)std::floor(source);
		if (std::abs(source - floor) == 0.5)
		{
			if (floor % 2 == 0)
				return floor;
			else
				return (unsigned char)std::ceil(source);
		}
		else if (std::abs(source - floor) < 0.5)
			return floor;
		else
			return (unsigned char)std::ceil(source);
	}

	static short ToInt16(double source)
	{
		short floor = (short)std::floor(source);
		if (std::abs(source - floor) == 0.5)
		{
			if (floor % 2 == 0)
				return floor;
			else
				return (short)std::ceil(source);
		}
		else if (std::abs(source - floor) < 0.5)
			return floor;
		else
			return (short)std::ceil(source);
	}

	static unsigned short ToUInt16(double source)
	{
		unsigned short floor = (unsigned short)std::floor(source);
		if (std::abs(source - floor) == 0.5)
		{
			if (floor % 2 == 0)
				return floor;
			else
				return (unsigned short)std::ceil(source);
		}
		else if (std::abs(source - floor) < 0.5)
			return floor;
		else
			return (unsigned short)std::ceil(source);
	}

	static int ToInt32(double source)
	{
		int floor = (int)std::floor(source);
		if (std::abs(source - floor) == 0.5)
		{
			if (floor % 2 == 0)
				return floor;
			else
				return (int)std::ceil(source);
		}
		else if (std::abs(source - floor) < 0.5)
			return floor;
		else
			return (int)std::ceil(source);
	}

	static unsigned int ToUInt32(double source)
	{
		unsigned int floor = (unsigned int)std::floor(source);
		if (std::abs(source - floor) == 0.5)
		{
			if (floor % 2 == 0)
				return floor;
			else
				return (unsigned int)std::ceil(source);
		}
		else if (std::abs(source - floor) < 0.5)
			return floor;
		else
			return (unsigned int)std::ceil(source);
	}

	static long long ToInt64(double source)
	{
		long long floor = (long long)std::floor(source);
		if (std::abs(source - floor) == 0.5)
		{
			if (floor % 2 == 0)
				return floor;
			else
				return (long long)std::ceil(source);
		}
		else if (std::abs(source - floor) < 0.5)
			return floor;
		else
			return (long long)std::ceil(source);
	}

	static unsigned long long ToUInt64(double source)
	{
		unsigned long long floor = (unsigned long long)std::floor(source);
		if (std::abs(source - floor) == 0.5)
		{
			if (floor % 2 == 0)
				return floor;
			else
				return (unsigned long long)std::ceil(source);
		}
		else if (std::abs(source - floor) < 0.5)
			return floor;
		else
			return (unsigned long long)std::ceil(source);
	}
};
