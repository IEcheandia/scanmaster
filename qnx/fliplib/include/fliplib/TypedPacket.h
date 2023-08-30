///////////////////////////////////////////////////////////
//  Packet.h
//  Implementation of the Class TypedPacked
//  Created on:      30-Okt-2007 14:29:47
//  Original author: Sevitec
///////////////////////////////////////////////////////////

#if !defined(EA_CB421F9D_81A0_4d67_ADB2_A12E7EBA67DC__INCLUDED_)
#define EA_CB421F9D_81A0_4d67_ADB2_A12E7EBA67DC__INCLUDED_

#include <typeinfo>
#include "Poco/Foundation.h"
#include "Poco/Tuple.h"
#include "Poco/TypeList.h"
#include "Poco/EventArgs.h"
#include "fliplib/Fliplib.h"
#include "fliplib/Packet.h"

namespace fliplib
{	
	using Poco::Tuple;
	using Poco::NullTypeList;
	using Poco::TypeGetter;
	using Poco::TypeWrapper;
	
template<class T0, 
    class T1 = NullTypeList,
    class T2 = NullTypeList,
    class T3 = NullTypeList,
    class T4 = NullTypeList,
    class T5 = NullTypeList,
    class T6 = NullTypeList,
    class T7 = NullTypeList, 
    class T8 = NullTypeList,
    class T9 = NullTypeList,
    class T10 = NullTypeList,
    class T11 = NullTypeList,
    class T12 = NullTypeList,
    class T13 = NullTypeList,
    class T14 = NullTypeList,
    class T15 = NullTypeList,
    class T16 = NullTypeList,
    class T17 = NullTypeList,
    class T18 = NullTypeList,
    class T19 = NullTypeList>
struct TypedPacket: public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::Type Type;

    TypedPacket()
    {
    }

    
    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11), 
        typename TypeWrapper<T12>::CONSTTYPE& t12 = POCO_TYPEWRAPPER_DEFAULTVALUE(T12), 
        typename TypeWrapper<T13>::CONSTTYPE& t13 = POCO_TYPEWRAPPER_DEFAULTVALUE(T13), 
        typename TypeWrapper<T14>::CONSTTYPE& t14 = POCO_TYPEWRAPPER_DEFAULTVALUE(T14), 
        typename TypeWrapper<T15>::CONSTTYPE& t15 = POCO_TYPEWRAPPER_DEFAULTVALUE(T15), 
        typename TypeWrapper<T16>::CONSTTYPE& t16 = POCO_TYPEWRAPPER_DEFAULTVALUE(T16), 
        typename TypeWrapper<T17>::CONSTTYPE& t17 = POCO_TYPEWRAPPER_DEFAULTVALUE(T17), 
        typename TypeWrapper<T18>::CONSTTYPE& t18 = POCO_TYPEWRAPPER_DEFAULTVALUE(T18), 
        typename TypeWrapper<T19>::CONSTTYPE& t19 = POCO_TYPEWRAPPER_DEFAULTVALUE(T19)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
	}   
	
	virtual const std::type_info& type() const { return typeid(TupleType); }
};


template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10,
    class T11,
    class T12,
    class T13,
    class T14,
    class T15,
    class T16,
    class T17,
    class T18>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11), 
        typename TypeWrapper<T12>::CONSTTYPE& t12 = POCO_TYPEWRAPPER_DEFAULTVALUE(T12), 
        typename TypeWrapper<T13>::CONSTTYPE& t13 = POCO_TYPEWRAPPER_DEFAULTVALUE(T13), 
        typename TypeWrapper<T14>::CONSTTYPE& t14 = POCO_TYPEWRAPPER_DEFAULTVALUE(T14), 
        typename TypeWrapper<T15>::CONSTTYPE& t15 = POCO_TYPEWRAPPER_DEFAULTVALUE(T15), 
        typename TypeWrapper<T16>::CONSTTYPE& t16 = POCO_TYPEWRAPPER_DEFAULTVALUE(T16), 
        typename TypeWrapper<T17>::CONSTTYPE& t17 = POCO_TYPEWRAPPER_DEFAULTVALUE(T17), 
        typename TypeWrapper<T18>::CONSTTYPE& t18 = POCO_TYPEWRAPPER_DEFAULTVALUE(T18)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
 		return TupleType(*this) < TupleType(other);    
    }
    
   	virtual const std::type_info& type() const { return typeid(TupleType); }
};

template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10,
    class T11,
    class T12,
    class T13,
    class T14,
    class T15,
    class T16,
    class T17>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11), 
        typename TypeWrapper<T12>::CONSTTYPE& t12 = POCO_TYPEWRAPPER_DEFAULTVALUE(T12), 
        typename TypeWrapper<T13>::CONSTTYPE& t13 = POCO_TYPEWRAPPER_DEFAULTVALUE(T13), 
        typename TypeWrapper<T14>::CONSTTYPE& t14 = POCO_TYPEWRAPPER_DEFAULTVALUE(T14), 
        typename TypeWrapper<T15>::CONSTTYPE& t15 = POCO_TYPEWRAPPER_DEFAULTVALUE(T15), 
        typename TypeWrapper<T16>::CONSTTYPE& t16 = POCO_TYPEWRAPPER_DEFAULTVALUE(T16), 
        typename TypeWrapper<T17>::CONSTTYPE& t17 = POCO_TYPEWRAPPER_DEFAULTVALUE(T17)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
 		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};

template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10,
    class T11,
    class T12,
    class T13,
    class T14,
    class T15,
    class T16>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11), 
        typename TypeWrapper<T12>::CONSTTYPE& t12 = POCO_TYPEWRAPPER_DEFAULTVALUE(T12), 
        typename TypeWrapper<T13>::CONSTTYPE& t13 = POCO_TYPEWRAPPER_DEFAULTVALUE(T13), 
        typename TypeWrapper<T14>::CONSTTYPE& t14 = POCO_TYPEWRAPPER_DEFAULTVALUE(T14), 
        typename TypeWrapper<T15>::CONSTTYPE& t15 = POCO_TYPEWRAPPER_DEFAULTVALUE(T15), 
        typename TypeWrapper<T16>::CONSTTYPE& t16 = POCO_TYPEWRAPPER_DEFAULTVALUE(T16)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};


template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10,
    class T11,
    class T12,
    class T13,
    class T14,
    class T15>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15, NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11), 
        typename TypeWrapper<T12>::CONSTTYPE& t12 = POCO_TYPEWRAPPER_DEFAULTVALUE(T12), 
        typename TypeWrapper<T13>::CONSTTYPE& t13 = POCO_TYPEWRAPPER_DEFAULTVALUE(T13), 
        typename TypeWrapper<T14>::CONSTTYPE& t14 = POCO_TYPEWRAPPER_DEFAULTVALUE(T14), 
        typename TypeWrapper<T15>::CONSTTYPE& t15 = POCO_TYPEWRAPPER_DEFAULTVALUE(T15)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
 		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};



template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10,
    class T11,
    class T12,
    class T13,
    class T14>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14, NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11), 
        typename TypeWrapper<T12>::CONSTTYPE& t12 = POCO_TYPEWRAPPER_DEFAULTVALUE(T12), 
        typename TypeWrapper<T13>::CONSTTYPE& t13 = POCO_TYPEWRAPPER_DEFAULTVALUE(T13), 
        typename TypeWrapper<T14>::CONSTTYPE& t14 = POCO_TYPEWRAPPER_DEFAULTVALUE(T14)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
         
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};


template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10,
    class T11,
    class T12,
    class T13>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11), 
        typename TypeWrapper<T12>::CONSTTYPE& t12 = POCO_TYPEWRAPPER_DEFAULTVALUE(T12), 
        typename TypeWrapper<T13>::CONSTTYPE& t13 = POCO_TYPEWRAPPER_DEFAULTVALUE(T13)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};


template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10,
    class T11,
    class T12>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11), 
        typename TypeWrapper<T12>::CONSTTYPE& t12 = POCO_TYPEWRAPPER_DEFAULTVALUE(T12)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};

template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10,
    class T11>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10), 
        typename TypeWrapper<T11>::CONSTTYPE& t11 = POCO_TYPEWRAPPER_DEFAULTVALUE(T11)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};

template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9,
    class T10>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9), 
        typename TypeWrapper<T10>::CONSTTYPE& t10 = POCO_TYPEWRAPPER_DEFAULTVALUE(T10)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
 		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};

template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8,
    class T9>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8), 
        typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
 		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};


template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7, 
    class T8>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,T8,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
        typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7,t8), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};


template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6,
    class T7>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,T7,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6,T7>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6,T7> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6,T7>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
        typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6,t7), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};

template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5,
    class T6>
struct TypedPacket<T0,T1,T2,T3,T4,T5,T6,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5,T6>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5,T6> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5,T6>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5), 
        typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6)): 
		TupleType(t0,t1,t2,t3,t4,t5,t6), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};


template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4,
    class T5>
struct TypedPacket<T0,T1,T2,T3,T4,T5,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4,T5>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4,T5> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4,T5>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
        typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5)): 
		TupleType(t0,t1,t2,t3,t4,t5), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};

template<class T0, 
    class T1,
    class T2,
    class T3,
    class T4>
struct TypedPacket<T0,T1,T2,T3,T4,NullTypeList>:
	public Tuple<T0,T1,T2,T3,T4>, Packet
{
	typedef Tuple<T0,T1,T2,T3,T4> TupleType;
	typedef typename Tuple<T0,T1,T2,T3,T4>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
        typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4)): 
		TupleType(t0,t1,t2,t3,t4), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
 		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};

template<class T0, 
    class T1,
    class T2,
    class T3>
struct TypedPacket<T0,T1,T2,T3,NullTypeList>:
	public Tuple<T0,T1,T2,T3>, Packet
{
	typedef Tuple<T0,T1,T2,T3> TupleType;
	typedef typename Tuple<T0,T1,T2,T3>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2), 
        typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3)): 
		TupleType(t0,t1,t2,t3), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};


template<class T0, 
    class T1,
    class T2>
struct TypedPacket<T0,T1,T2,NullTypeList>:
	public Tuple<T0,T1,T2>, Packet
{
	typedef Tuple<T0,T1,T2> TupleType;
	typedef typename Tuple<T0,T1,T2>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1), 
        typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2)): 
		TupleType(t0,t1,t2), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};

template<class T0, 
    class T1>
struct TypedPacket<T0,T1,NullTypeList>:
	public Tuple<T0,T1>, Packet
{
	typedef Tuple<T0,T1> TupleType;
	typedef typename Tuple<T0,T1>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0,
        typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1)): 
		TupleType(t0,t1), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
 		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};


template<class T0>
struct TypedPacket<T0,NullTypeList>:
	public Tuple<T0>, Packet
{
	typedef Tuple<T0> TupleType;
	typedef typename Tuple<T0>::Type Type;

    TypedPacket() :
    	Packet()
    {
    }

    TypedPacket(typename TypeWrapper<T0>::CONSTTYPE& t0): 
		TupleType(t0), 
		Packet()
    {
    }

    template<int N>
    typename TypeGetter<N, Type>::ConstHeadType& get() const 
    {
        return TupleType::template get<N>();
    }

    template<int N>
    typename TypeGetter<N, Type>::HeadType& get()
    {
        return TupleType::template get<N>();
    }

    template<int N>
    void set(typename TypeGetter<N, Type>::ConstHeadType& val)
    {
        return TupleType::template set<N>(val);
    }

    bool operator == (const TypedPacket& other) const
    {
        return TupleType(*this) == TupleType(other);
    }

    bool operator != (const TypedPacket& other) const 
    {
        return !(*this == other);
    }

    bool operator < (const TypedPacket& other) const
    {
		return TupleType(*this) < TupleType(other);    
    }
        
   	virtual const std::type_info& type() const { return typeid(TupleType); }
    
};
	
}
#endif // !defined(EA_CB421F9D_81A0_4d67_ADB2_A12E7EBA67DC__INCLUDED_)
