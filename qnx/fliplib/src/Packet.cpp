///////////////////////////////////////////////////////////
//  Packet.cpp
//  Implementation of the Class Packet
//  Created on:      30-Okt-2007 14:29:47
//  Original author: Sevitec
///////////////////////////////////////////////////////////

#include "fliplib/Packet.h"

using fliplib::Packet;


Packet::Packet() :
	valid_(true)	
{

}

Packet::Packet(const Packet& packet) :
	valid_(packet.valid_)	
{

}

Packet::~Packet(){

}

Packet& Packet::operator=(const Packet& obj)
{
	valid_ = obj.valid_;
  	return *this;
}

bool Packet::isValid()
{
	return valid_;
}
