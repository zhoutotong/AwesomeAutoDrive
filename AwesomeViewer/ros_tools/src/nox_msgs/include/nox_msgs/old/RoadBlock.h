// Generated by gencpp from file nox_msgs/RoadBlock.msg
// DO NOT EDIT!


#ifndef NOX_MSGS_MESSAGE_ROADBLOCK_H
#define NOX_MSGS_MESSAGE_ROADBLOCK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <nox_msgs/RoadPoint.h>

namespace nox_msgs
{
template <class ContainerAllocator>
struct RoadBlock_
{
  typedef RoadBlock_<ContainerAllocator> Type;

  RoadBlock_()
    : points()
    , target_index(0)
    , minSpeed(0.0)
    , maxSpeed(0.0)  {
    }
  RoadBlock_(const ContainerAllocator& _alloc)
    : points(_alloc)
    , target_index(0)
    , minSpeed(0.0)
    , maxSpeed(0.0)  {
  (void)_alloc;
    }



   typedef std::vector< ::nox_msgs::RoadPoint_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::nox_msgs::RoadPoint_<ContainerAllocator> >::other >  _points_type;
  _points_type points;

   typedef int32_t _target_index_type;
  _target_index_type target_index;

   typedef double _minSpeed_type;
  _minSpeed_type minSpeed;

   typedef double _maxSpeed_type;
  _maxSpeed_type maxSpeed;





  typedef boost::shared_ptr< ::nox_msgs::RoadBlock_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nox_msgs::RoadBlock_<ContainerAllocator> const> ConstPtr;

}; // struct RoadBlock_

typedef ::nox_msgs::RoadBlock_<std::allocator<void> > RoadBlock;

typedef boost::shared_ptr< ::nox_msgs::RoadBlock > RoadBlockPtr;
typedef boost::shared_ptr< ::nox_msgs::RoadBlock const> RoadBlockConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nox_msgs::RoadBlock_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nox_msgs::RoadBlock_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::nox_msgs::RoadBlock_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::RoadBlock_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::RoadBlock_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::RoadBlock_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::RoadBlock_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::RoadBlock_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nox_msgs::RoadBlock_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d4577629fb38300fd83e880116646806";
  }

  static const char* value(const ::nox_msgs::RoadBlock_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd4577629fb38300fULL;
  static const uint64_t static_value2 = 0xd83e880116646806ULL;
};

template<class ContainerAllocator>
struct DataType< ::nox_msgs::RoadBlock_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nox_msgs/RoadBlock";
  }

  static const char* value(const ::nox_msgs::RoadBlock_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nox_msgs::RoadBlock_<ContainerAllocator> >
{
  static const char* value()
  {
    return "RoadPoint[] points # 可以选择的道路点\n\
int32 target_index # 推荐的道路点\n\
float64 minSpeed\n\
float64 maxSpeed\n\
\n\
================================================================================\n\
MSG: nox_msgs/RoadPoint\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 yaw\n\
";
  }

  static const char* value(const ::nox_msgs::RoadBlock_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nox_msgs::RoadBlock_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.points);
      stream.next(m.target_index);
      stream.next(m.minSpeed);
      stream.next(m.maxSpeed);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RoadBlock_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nox_msgs::RoadBlock_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nox_msgs::RoadBlock_<ContainerAllocator>& v)
  {
    s << indent << "points[]" << std::endl;
    for (size_t i = 0; i < v.points.size(); ++i)
    {
      s << indent << "  points[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::nox_msgs::RoadPoint_<ContainerAllocator> >::stream(s, indent + "    ", v.points[i]);
    }
    s << indent << "target_index: ";
    Printer<int32_t>::stream(s, indent + "  ", v.target_index);
    s << indent << "minSpeed: ";
    Printer<double>::stream(s, indent + "  ", v.minSpeed);
    s << indent << "maxSpeed: ";
    Printer<double>::stream(s, indent + "  ", v.maxSpeed);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NOX_MSGS_MESSAGE_ROADBLOCK_H
