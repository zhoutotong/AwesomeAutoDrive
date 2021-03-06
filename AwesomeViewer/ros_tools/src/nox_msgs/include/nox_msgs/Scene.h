// Generated by gencpp from file nox_msgs/Scene.msg
// DO NOT EDIT!


#ifndef NOX_MSGS_MESSAGE_SCENE_H
#define NOX_MSGS_MESSAGE_SCENE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <nox_msgs/Obstacle.h>
#include <nox_msgs/GuideLine.h>
#include <nox_msgs/Vehicle.h>

namespace nox_msgs
{
template <class ContainerAllocator>
struct Scene_
{
  typedef Scene_<ContainerAllocator> Type;

  Scene_()
    : header()
    , id(0)
    , obstacles()
    , guideLines()
    , egoVehicle()  {
    }
  Scene_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , id(0)
    , obstacles(_alloc)
    , guideLines(_alloc)
    , egoVehicle(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint64_t _id_type;
  _id_type id;

   typedef std::vector< ::nox_msgs::Obstacle_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::nox_msgs::Obstacle_<ContainerAllocator> >::other >  _obstacles_type;
  _obstacles_type obstacles;

   typedef std::vector< ::nox_msgs::GuideLine_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::nox_msgs::GuideLine_<ContainerAllocator> >::other >  _guideLines_type;
  _guideLines_type guideLines;

   typedef  ::nox_msgs::Vehicle_<ContainerAllocator>  _egoVehicle_type;
  _egoVehicle_type egoVehicle;





  typedef boost::shared_ptr< ::nox_msgs::Scene_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nox_msgs::Scene_<ContainerAllocator> const> ConstPtr;

}; // struct Scene_

typedef ::nox_msgs::Scene_<std::allocator<void> > Scene;

typedef boost::shared_ptr< ::nox_msgs::Scene > ScenePtr;
typedef boost::shared_ptr< ::nox_msgs::Scene const> SceneConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nox_msgs::Scene_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nox_msgs::Scene_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::nox_msgs::Scene_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nox_msgs::Scene_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::Scene_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nox_msgs::Scene_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::Scene_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nox_msgs::Scene_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nox_msgs::Scene_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cd56dd96367d03ff950754f3ee247ffc";
  }

  static const char* value(const ::nox_msgs::Scene_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcd56dd96367d03ffULL;
  static const uint64_t static_value2 = 0x950754f3ee247ffcULL;
};

template<class ContainerAllocator>
struct DataType< ::nox_msgs::Scene_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nox_msgs/Scene";
  }

  static const char* value(const ::nox_msgs::Scene_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nox_msgs::Scene_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"\n"
"uint64        id\n"
"Obstacle[]    obstacles\n"
"GuideLine[]   guideLines\n"
"Vehicle       egoVehicle\n"
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
"MSG: nox_msgs/Obstacle\n"
"Header header\n"
"\n"
"uint64 id                       # 障碍物ID（由LoMap生成）\n"
"\n"
"Trajectory prediction           # 障碍物预测路径（静态障碍物为空，或只有一个点）\n"
"\n"
"geometry_msgs/Pose pose         # 障碍物位姿\n"
"\n"
"geometry_msgs/Vector3 length    # 障碍物包围在x, y, z方向的长度（该方向是障碍物本身的坐标系）\n"
"\n"
"geometry_msgs/Polygon vertexes  # 障碍物顶点\n"
"\n"
"float64 speed                   # 障碍物速度，秒速\n"
"\n"
"float64 confidence              # 障碍物可靠性\n"
"\n"
"uint32 type                     # 障碍物类型\n"
"\n"
"Overlap[] overlaps              # 障碍物的覆盖情况（给地图使用）\n"
"\n"
"# -----------------------------------\n"
"# 障碍物类型枚举: TODO\n"
"\n"
"uint32 UNKNOWN = 0\n"
"\n"
"# -----------------------------------\n"
"================================================================================\n"
"MSG: nox_msgs/Trajectory\n"
"# Description a trajectory with time and position information\n"
"\n"
"Header header\n"
"\n"
"TrajectoryPoint[] points\n"
"================================================================================\n"
"MSG: nox_msgs/TrajectoryPoint\n"
"# Description the point on a trajectory\n"
"\n"
"PathPoint info\n"
"float64 v\n"
"float64 a\n"
"float64 t\n"
"================================================================================\n"
"MSG: nox_msgs/PathPoint\n"
"# Description the point on a path\n"
"\n"
"geometry_msgs/Pose pose\n"
"float64 kappa\n"
"float64 dkappa\n"
"float64 s\n"
"float64 width   # 路点的宽度（指车道宽度）\n"
"Bound   bound   # 路点的边界（指整个路的边界，相对于该点的横向距离）\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
"\n"
"================================================================================\n"
"MSG: nox_msgs/Bound\n"
"float64 lower # lower bound\n"
"float64 upper # upper bound\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3\n"
"# This represents a vector in free space. \n"
"# It is only meant to represent a direction. Therefore, it does not\n"
"# make sense to apply a translation to it (e.g., when applying a \n"
"# generic rigid transformation to a Vector3, tf2 will only apply the\n"
"# rotation). If you want your data to be translatable too, use the\n"
"# geometry_msgs/Point message instead.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"================================================================================\n"
"MSG: geometry_msgs/Polygon\n"
"#A specification of a polygon where the first and last points are assumed to be connected\n"
"Point32[] points\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point32\n"
"# This contains the position of a point in free space(with 32 bits of precision).\n"
"# It is recommeded to use Point wherever possible instead of Point32.  \n"
"# \n"
"# This recommendation is to promote interoperability.  \n"
"#\n"
"# This message is designed to take up less space when sending\n"
"# lots of points at once, as in the case of a PointCloud.  \n"
"\n"
"float32 x\n"
"float32 y\n"
"float32 z\n"
"================================================================================\n"
"MSG: nox_msgs/Overlap\n"
"uint64 id       # 覆盖信息本身的ID\n"
"uint64 on       # 被覆盖物的ID\n"
"uint8 type      # 被覆盖物的类型\n"
"float64 start   # 被覆盖的范围起始（时间或距离，由语境定义）\n"
"float64 end     # 被覆盖的范围终止\n"
"\n"
"# -----------------------------------\n"
"# Type to overlap\n"
"\n"
"uint8 UNKNOWN = 0\n"
"uint8 LANE = 1\n"
"\n"
"# -----------------------------------\n"
"================================================================================\n"
"MSG: nox_msgs/GuideLine\n"
"# Description a guide line with a lot of guide information for vehicle\n"
"\n"
"uint64           id\n"
"Path             path\n"
"SpeedControl[]   speed\n"
"StopLine[]       stop\n"
"Boundary[]       boundary\n"
"bool             passable\n"
"================================================================================\n"
"MSG: nox_msgs/Path\n"
"PathPoint[] points\n"
"================================================================================\n"
"MSG: nox_msgs/SpeedControl\n"
"# Description of the speed limitation on the map\n"
"\n"
"uint64  id\n"
"float64 s_start\n"
"float64 s_end\n"
"float64 v_upper\n"
"float64 v_lower\n"
"================================================================================\n"
"MSG: nox_msgs/StopLine\n"
"# Description of the stop line on the map\n"
"\n"
"uint64  id\n"
"float64 s\n"
"================================================================================\n"
"MSG: nox_msgs/Boundary\n"
"# Description of a boundary along a guide line\n"
"\n"
"uint64    id\n"
"Bound     s          # 边界在引导线上附着的位置\n"
"Function  func       # 描述边界的数学函数\n"
"bool      passable   # 可通行的\n"
"================================================================================\n"
"MSG: nox_msgs/Function\n"
"# Description of a math function\n"
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
"MSG: nox_msgs/Vehicle\n"
"# Description the state of a vehicle\n"
"\n"
"nav_msgs/Odometry     odometry\n"
"geometry_msgs/Vector3 length\n"
"uint64                id\n"
"\n"
"================================================================================\n"
"MSG: nav_msgs/Odometry\n"
"# This represents an estimate of a position and velocity in free space.  \n"
"# The pose in this message should be specified in the coordinate frame given by header.frame_id.\n"
"# The twist in this message should be specified in the coordinate frame given by the child_frame_id\n"
"Header header\n"
"string child_frame_id\n"
"geometry_msgs/PoseWithCovariance pose\n"
"geometry_msgs/TwistWithCovariance twist\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseWithCovariance\n"
"# This represents a pose in free space with uncertainty.\n"
"\n"
"Pose pose\n"
"\n"
"# Row-major representation of the 6x6 covariance matrix\n"
"# The orientation parameters use a fixed-axis representation.\n"
"# In order, the parameters are:\n"
"# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)\n"
"float64[36] covariance\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/TwistWithCovariance\n"
"# This expresses velocity in free space with uncertainty.\n"
"\n"
"Twist twist\n"
"\n"
"# Row-major representation of the 6x6 covariance matrix\n"
"# The orientation parameters use a fixed-axis representation.\n"
"# In order, the parameters are:\n"
"# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)\n"
"float64[36] covariance\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Twist\n"
"# This expresses velocity in free space broken into its linear and angular parts.\n"
"Vector3  linear\n"
"Vector3  angular\n"
;
  }

  static const char* value(const ::nox_msgs::Scene_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nox_msgs::Scene_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.id);
      stream.next(m.obstacles);
      stream.next(m.guideLines);
      stream.next(m.egoVehicle);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Scene_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nox_msgs::Scene_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nox_msgs::Scene_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "id: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.id);
    s << indent << "obstacles[]" << std::endl;
    for (size_t i = 0; i < v.obstacles.size(); ++i)
    {
      s << indent << "  obstacles[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::nox_msgs::Obstacle_<ContainerAllocator> >::stream(s, indent + "    ", v.obstacles[i]);
    }
    s << indent << "guideLines[]" << std::endl;
    for (size_t i = 0; i < v.guideLines.size(); ++i)
    {
      s << indent << "  guideLines[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::nox_msgs::GuideLine_<ContainerAllocator> >::stream(s, indent + "    ", v.guideLines[i]);
    }
    s << indent << "egoVehicle: ";
    s << std::endl;
    Printer< ::nox_msgs::Vehicle_<ContainerAllocator> >::stream(s, indent + "  ", v.egoVehicle);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NOX_MSGS_MESSAGE_SCENE_H
