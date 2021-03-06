// Generated by gencpp from file nox_msgs/DrivingCommand.msg
// DO NOT EDIT!


#ifndef NOX_MSGS_MESSAGE_DRIVINGCOMMAND_H
#define NOX_MSGS_MESSAGE_DRIVINGCOMMAND_H


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
struct DrivingCommand_
{
  typedef DrivingCommand_<ContainerAllocator> Type;

  DrivingCommand_()
    : header()
    , vehicle_id(0)
    , target_steering(0.0)
    , target_speed(0.0)  {
    }
  DrivingCommand_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , vehicle_id(0)
    , target_steering(0.0)
    , target_speed(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint64_t _vehicle_id_type;
  _vehicle_id_type vehicle_id;

   typedef double _target_steering_type;
  _target_steering_type target_steering;

   typedef double _target_speed_type;
  _target_speed_type target_speed;





  typedef boost::shared_ptr< ::nox_msgs::DrivingCommand_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nox_msgs::DrivingCommand_<ContainerAllocator> const> ConstPtr;

}; // struct DrivingCommand_

typedef ::nox_msgs::DrivingCommand_<std::allocator<void> > DrivingCommand;

typedef boost::shared_ptr< ::nox_msgs::DrivingCommand > DrivingCommandPtr;
typedef boost::shared_ptr< ::nox_msgs::DrivingCommand const> DrivingCommandConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nox_msgs::DrivingCommand_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nox_msgs::DrivingCommand_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::nox_msgs::DrivingCommand_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::DrivingCommand_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::DrivingCommand_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::DrivingCommand_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::DrivingCommand_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::DrivingCommand_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nox_msgs::DrivingCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "51a5a3894a3ca315070b06a4943b8ab3";
  }

  static const char* value(const ::nox_msgs::DrivingCommand_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x51a5a3894a3ca315ULL;
  static const uint64_t static_value2 = 0x070b06a4943b8ab3ULL;
};

template<class ContainerAllocator>
struct DataType< ::nox_msgs::DrivingCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nox_msgs/DrivingCommand";
  }

  static const char* value(const ::nox_msgs::DrivingCommand_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nox_msgs::DrivingCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ----------------------------------\n"
"# 跟踪模块给底层执行的通信消息\n"
"\n"
"Header  header\n"
"uint64  vehicle_id\n"
"float64 target_steering # 轮偏角，弧度\n"
"float64 target_speed    # 秒速\n"
"\n"
"# ----------------------------------\n"
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

  static const char* value(const ::nox_msgs::DrivingCommand_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nox_msgs::DrivingCommand_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.vehicle_id);
      stream.next(m.target_steering);
      stream.next(m.target_speed);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DrivingCommand_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nox_msgs::DrivingCommand_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nox_msgs::DrivingCommand_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "vehicle_id: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.vehicle_id);
    s << indent << "target_steering: ";
    Printer<double>::stream(s, indent + "  ", v.target_steering);
    s << indent << "target_speed: ";
    Printer<double>::stream(s, indent + "  ", v.target_speed);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NOX_MSGS_MESSAGE_DRIVINGCOMMAND_H
