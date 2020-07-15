// Generated by gencpp from file nox_msgs/Bound.msg
// DO NOT EDIT!


#ifndef NOX_MSGS_MESSAGE_BOUND_H
#define NOX_MSGS_MESSAGE_BOUND_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace nox_msgs
{
template <class ContainerAllocator>
struct Bound_
{
  typedef Bound_<ContainerAllocator> Type;

  Bound_()
    : lower(0.0)
    , upper(0.0)  {
    }
  Bound_(const ContainerAllocator& _alloc)
    : lower(0.0)
    , upper(0.0)  {
  (void)_alloc;
    }



   typedef double _lower_type;
  _lower_type lower;

   typedef double _upper_type;
  _upper_type upper;





  typedef boost::shared_ptr< ::nox_msgs::Bound_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nox_msgs::Bound_<ContainerAllocator> const> ConstPtr;

}; // struct Bound_

typedef ::nox_msgs::Bound_<std::allocator<void> > Bound;

typedef boost::shared_ptr< ::nox_msgs::Bound > BoundPtr;
typedef boost::shared_ptr< ::nox_msgs::Bound const> BoundConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nox_msgs::Bound_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nox_msgs::Bound_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nox_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'nox_msgs': ['/media/yarten/DATA/Project/ROS/NOX_Project/nox/src/nox_msgs/msg'], 'nav_msgs': ['/opt/ros/melodic/share/nav_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/melodic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::Bound_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::Bound_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::Bound_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::Bound_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::Bound_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::Bound_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nox_msgs::Bound_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6ee96d1273d88ec3f7d4c1bef2f7bba1";
  }

  static const char* value(const ::nox_msgs::Bound_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6ee96d1273d88ec3ULL;
  static const uint64_t static_value2 = 0xf7d4c1bef2f7bba1ULL;
};

template<class ContainerAllocator>
struct DataType< ::nox_msgs::Bound_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nox_msgs/Bound";
  }

  static const char* value(const ::nox_msgs::Bound_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nox_msgs::Bound_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 lower # lower bound\n"
"float64 upper # upper bound\n"
;
  }

  static const char* value(const ::nox_msgs::Bound_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nox_msgs::Bound_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.lower);
      stream.next(m.upper);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Bound_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nox_msgs::Bound_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nox_msgs::Bound_<ContainerAllocator>& v)
  {
    s << indent << "lower: ";
    Printer<double>::stream(s, indent + "  ", v.lower);
    s << indent << "upper: ";
    Printer<double>::stream(s, indent + "  ", v.upper);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NOX_MSGS_MESSAGE_BOUND_H
