// Generated by gencpp from file nox_msgs/Function.msg
// DO NOT EDIT!


#ifndef NOX_MSGS_MESSAGE_FUNCTION_H
#define NOX_MSGS_MESSAGE_FUNCTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <nox_msgs/Bound.h>

namespace nox_msgs
{
template <class ContainerAllocator>
struct Function_
{
  typedef Function_<ContainerAllocator> Type;

  Function_()
    : coeff()
    , x()
    , type(0)  {
    }
  Function_(const ContainerAllocator& _alloc)
    : coeff(_alloc)
    , x(_alloc)
    , type(0)  {
  (void)_alloc;
    }



   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _coeff_type;
  _coeff_type coeff;

   typedef  ::nox_msgs::Bound_<ContainerAllocator>  _x_type;
  _x_type x;

   typedef uint32_t _type_type;
  _type_type type;



  enum {
    Unknown = 0u,
    Polynomial = 1u,
  };


  typedef boost::shared_ptr< ::nox_msgs::Function_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nox_msgs::Function_<ContainerAllocator> const> ConstPtr;

}; // struct Function_

typedef ::nox_msgs::Function_<std::allocator<void> > Function;

typedef boost::shared_ptr< ::nox_msgs::Function > FunctionPtr;
typedef boost::shared_ptr< ::nox_msgs::Function const> FunctionConstPtr;

// constants requiring out of line definition

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nox_msgs::Function_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nox_msgs::Function_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nox_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'nox_msgs': ['/media/yarten/DATA/Project/ROS/NOX_Project/nox/src/nox_msgs/msg'], 'nav_msgs': ['/opt/ros/melodic/share/nav_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/melodic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::Function_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::Function_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::Function_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::Function_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::Function_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::Function_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nox_msgs::Function_<ContainerAllocator> >
{
  static const char* value()
  {
    return "66b9b5919bd082f396d53fadbe598d04";
  }

  static const char* value(const ::nox_msgs::Function_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x66b9b5919bd082f3ULL;
  static const uint64_t static_value2 = 0x96d53fadbe598d04ULL;
};

template<class ContainerAllocator>
struct DataType< ::nox_msgs::Function_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nox_msgs/Function";
  }

  static const char* value(const ::nox_msgs::Function_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nox_msgs::Function_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Description of a math function\n"
"\n"
"float64[] coeff  # 函数系数\n"
"Bound   x        # 定义域\n"
"\n"
"# -----------------------------------\n"
"uint32  type     # 函数类型（决定了系数的意义）\n"
"\n"
"uint32 Unknown    = 0\n"
"uint32 Polynomial = 1\n"
"================================================================================\n"
"MSG: nox_msgs/Bound\n"
"float64 lower # lower bound\n"
"float64 upper # upper bound\n"
;
  }

  static const char* value(const ::nox_msgs::Function_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nox_msgs::Function_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.coeff);
      stream.next(m.x);
      stream.next(m.type);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Function_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nox_msgs::Function_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nox_msgs::Function_<ContainerAllocator>& v)
  {
    s << indent << "coeff[]" << std::endl;
    for (size_t i = 0; i < v.coeff.size(); ++i)
    {
      s << indent << "  coeff[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.coeff[i]);
    }
    s << indent << "x: ";
    s << std::endl;
    Printer< ::nox_msgs::Bound_<ContainerAllocator> >::stream(s, indent + "  ", v.x);
    s << indent << "type: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.type);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NOX_MSGS_MESSAGE_FUNCTION_H
