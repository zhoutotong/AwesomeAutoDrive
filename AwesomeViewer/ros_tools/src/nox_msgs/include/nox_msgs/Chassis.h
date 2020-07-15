// Generated by gencpp from file nox_msgs/Chassis.msg
// DO NOT EDIT!


#ifndef NOX_MSGS_MESSAGE_CHASSIS_H
#define NOX_MSGS_MESSAGE_CHASSIS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace nox_msgs
{
template <class ContainerAllocator>
struct Chassis_
{
  typedef Chassis_<ContainerAllocator> Type;

  Chassis_()
    : header()
    , gear(0)
    , speed(0.0)
    , steering(0.0)
    , mode(0)
    , throttle(0.0)
    , brake(0.0)  {
    }
  Chassis_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , gear(0)
    , speed(0.0)
    , steering(0.0)
    , mode(0)
    , throttle(0.0)
    , brake(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef int8_t _gear_type;
  _gear_type gear;

   typedef double _speed_type;
  _speed_type speed;

   typedef double _steering_type;
  _steering_type steering;

   typedef uint32_t _mode_type;
  _mode_type mode;

   typedef double _throttle_type;
  _throttle_type throttle;

   typedef double _brake_type;
  _brake_type brake;



  enum {
    GEAR_NONE = 0,
    GERA_P = 16,
    GEAR_R = 32,
    GEAR_N = 48,
    GEAR_D = 64,
    GEAR_1 = 1,
    GEAR_2 = 2,
    GEAR_3 = 3,
    GEAR_4 = 4,
    GEAR_5 = 5,
    GEAR_6 = 6,
  };


  typedef boost::shared_ptr< ::nox_msgs::Chassis_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nox_msgs::Chassis_<ContainerAllocator> const> ConstPtr;

}; // struct Chassis_

typedef ::nox_msgs::Chassis_<std::allocator<void> > Chassis;

typedef boost::shared_ptr< ::nox_msgs::Chassis > ChassisPtr;
typedef boost::shared_ptr< ::nox_msgs::Chassis const> ChassisConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nox_msgs::Chassis_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nox_msgs::Chassis_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nox_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'nox_msgs': ['/home/huotuo/Projects/nox-1.0/nox/src/nox_msgs/msg'], 'nav_msgs': ['/opt/ros/melodic/share/nav_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/melodic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::Chassis_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::Chassis_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::Chassis_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::Chassis_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::Chassis_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::Chassis_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nox_msgs::Chassis_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e6ee3fbf88a842a684bd6958788340b8";
  }

  static const char* value(const ::nox_msgs::Chassis_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe6ee3fbf88a842a6ULL;
  static const uint64_t static_value2 = 0x84bd6958788340b8ULL;
};

template<class ContainerAllocator>
struct DataType< ::nox_msgs::Chassis_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nox_msgs/Chassis";
  }

  static const char* value(const ::nox_msgs::Chassis_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nox_msgs::Chassis_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Description the state of chassis\n"
"\n"
"Header header\n"
"\n"
"int8    gear       # 档位，1, 2, 3..., 0表示无档位\n"
"float64 speed      # 秒速\n"
"float64 steering   # 轮偏角，弧度\n"
"uint32  mode       # 无人车模式（保留）\n"
"\n"
"float64 throttle   #you men ta ban\n"
"\n"
"float64 brake      #sha che ta ban\n"
"\n"
"# -----------------------------------\n"
"\n"
"int8 GEAR_NONE = 0\n"
"int8 GERA_P = 16\n"
"int8 GEAR_R = 32\n"
"int8 GEAR_N = 48\n"
"int8 GEAR_D = 64\n"
"int8 GEAR_1 = 1\n"
"int8 GEAR_2 = 2\n"
"int8 GEAR_3 = 3\n"
"int8 GEAR_4 = 4\n"
"int8 GEAR_5 = 5\n"
"int8 GEAR_6 = 6\n"
"\n"
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
;
  }

  static const char* value(const ::nox_msgs::Chassis_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nox_msgs::Chassis_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.gear);
      stream.next(m.speed);
      stream.next(m.steering);
      stream.next(m.mode);
      stream.next(m.throttle);
      stream.next(m.brake);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Chassis_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nox_msgs::Chassis_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nox_msgs::Chassis_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "gear: ";
    Printer<int8_t>::stream(s, indent + "  ", v.gear);
    s << indent << "speed: ";
    Printer<double>::stream(s, indent + "  ", v.speed);
    s << indent << "steering: ";
    Printer<double>::stream(s, indent + "  ", v.steering);
    s << indent << "mode: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.mode);
    s << indent << "throttle: ";
    Printer<double>::stream(s, indent + "  ", v.throttle);
    s << indent << "brake: ";
    Printer<double>::stream(s, indent + "  ", v.brake);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NOX_MSGS_MESSAGE_CHASSIS_H