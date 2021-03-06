// Generated by gencpp from file nox_msgs/SignalArray.msg
// DO NOT EDIT!


#ifndef NOX_MSGS_MESSAGE_SIGNALARRAY_H
#define NOX_MSGS_MESSAGE_SIGNALARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <nox_msgs/Signal.h>

namespace nox_msgs
{
template <class ContainerAllocator>
struct SignalArray_
{
  typedef SignalArray_<ContainerAllocator> Type;

  SignalArray_()
    : header()
    , signals()  {
    }
  SignalArray_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , signals(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::nox_msgs::Signal_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::nox_msgs::Signal_<ContainerAllocator> >::other >  _signals_type;
  _signals_type signals;





  typedef boost::shared_ptr< ::nox_msgs::SignalArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nox_msgs::SignalArray_<ContainerAllocator> const> ConstPtr;

}; // struct SignalArray_

typedef ::nox_msgs::SignalArray_<std::allocator<void> > SignalArray;

typedef boost::shared_ptr< ::nox_msgs::SignalArray > SignalArrayPtr;
typedef boost::shared_ptr< ::nox_msgs::SignalArray const> SignalArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nox_msgs::SignalArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nox_msgs::SignalArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nox_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'nox_msgs': ['/media/yarten/DATA/Project/ROS/NOX_Project/nox/src/nox_msgs/msg'], 'nav_msgs': ['/opt/ros/melodic/share/nav_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/melodic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::SignalArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::SignalArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::SignalArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::SignalArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::SignalArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::SignalArray_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nox_msgs::SignalArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e4596184f932a6ff57e796666c3e3c45";
  }

  static const char* value(const ::nox_msgs::SignalArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe4596184f932a6ffULL;
  static const uint64_t static_value2 = 0x57e796666c3e3c45ULL;
};

template<class ContainerAllocator>
struct DataType< ::nox_msgs::SignalArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nox_msgs/SignalArray";
  }

  static const char* value(const ::nox_msgs::SignalArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nox_msgs::SignalArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"\n"
"Signal[] signals\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: nox_msgs/Signal\n"
"# Description a signal\n"
"\n"
"# -----------------------------------\n"
"\n"
"int32 flag\n"
"\n"
"uint32 GENERAL   = 0\n"
"uint32 EMERGENCY = 1\n"
"uint32 ERROR     = 2\n"
"uint32 SYSTEM    = 3\n"
"\n"
"# ------------------------------------\n"
"\n"
"int32 type\n"
"\n"
"int32 code\n"
"\n"
"string description\n"
;
  }

  static const char* value(const ::nox_msgs::SignalArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nox_msgs::SignalArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.signals);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SignalArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nox_msgs::SignalArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nox_msgs::SignalArray_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "signals[]" << std::endl;
    for (size_t i = 0; i < v.signals.size(); ++i)
    {
      s << indent << "  signals[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::nox_msgs::Signal_<ContainerAllocator> >::stream(s, indent + "    ", v.signals[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // NOX_MSGS_MESSAGE_SIGNALARRAY_H
