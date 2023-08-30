///////////////////////////////////////////////////////////
//  Packet.h
//  Implementation of the Class Packet
//  Created on:      30-Okt-2007 14:29:47
//  Original author: Sevitec
///////////////////////////////////////////////////////////

#if !defined(EA_CB421F9D_81A0_4d66_ADB2_A12E7EBA67DC__INCLUDED_)
#define EA_CB421F9D_81A0_4d66_ADB2_A12E7EBA67DC__INCLUDED_

#include <typeinfo>
#include "Poco/Foundation.h"
#include "Poco/EventArgs.h"
#include "fliplib/Fliplib.h"

namespace fliplib
{

	/**
	 * Beschreibt den Type eines Paketes
	 */
	class FLIPLIB_API PacketType
	{

	public:
		PacketType() {}
		PacketType(const PacketType& packet) {}

		virtual ~PacketType() {}
		virtual const std::type_info& type() const = 0;
	};

	/**
	 * Packet
	 */
	class FLIPLIB_API Packet : public Poco::EventArgs, public PacketType
	{

	public:
		Packet();
		Packet(const Packet& packet);
		virtual ~Packet();

		Packet& operator=(const Packet& obj);

		bool isValid();

	protected:
		bool valid_;

	};


	/**
	 * Leeres Packet
	 */
	class FLIPLIB_API EmptyPacket : public Packet
	{
	public:
		EmptyPacket () {};
		virtual ~EmptyPacket() {};
		virtual const std::type_info& type() const { return typeid(void); }
	};

}

#endif // !defined(EA_CB421F9D_81A0_4d66_ADB2_A12E7EBA67DC__INCLUDED_)
