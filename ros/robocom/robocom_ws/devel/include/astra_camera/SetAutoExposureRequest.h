// Generated by gencpp from file astra_camera/SetAutoExposureRequest.msg
// DO NOT EDIT!


#ifndef ASTRA_CAMERA_MESSAGE_SETAUTOEXPOSUREREQUEST_H
#define ASTRA_CAMERA_MESSAGE_SETAUTOEXPOSUREREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace astra_camera
{
template <class ContainerAllocator>
struct SetAutoExposureRequest_
{
  typedef SetAutoExposureRequest_<ContainerAllocator> Type;

  SetAutoExposureRequest_()
    : enable(false)  {
    }
  SetAutoExposureRequest_(const ContainerAllocator& _alloc)
    : enable(false)  {
  (void)_alloc;
    }



   typedef uint8_t _enable_type;
  _enable_type enable;





  typedef boost::shared_ptr< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> const> ConstPtr;

}; // struct SetAutoExposureRequest_

typedef ::astra_camera::SetAutoExposureRequest_<std::allocator<void> > SetAutoExposureRequest;

typedef boost::shared_ptr< ::astra_camera::SetAutoExposureRequest > SetAutoExposureRequestPtr;
typedef boost::shared_ptr< ::astra_camera::SetAutoExposureRequest const> SetAutoExposureRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator1> & lhs, const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator2> & rhs)
{
  return lhs.enable == rhs.enable;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator1> & lhs, const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace astra_camera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8c1211af706069c994c06e00eb59ac9e";
  }

  static const char* value(const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8c1211af706069c9ULL;
  static const uint64_t static_value2 = 0x94c06e00eb59ac9eULL;
};

template<class ContainerAllocator>
struct DataType< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "astra_camera/SetAutoExposureRequest";
  }

  static const char* value(const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool enable\n"
;
  }

  static const char* value(const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.enable);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetAutoExposureRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::astra_camera::SetAutoExposureRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::astra_camera::SetAutoExposureRequest_<ContainerAllocator>& v)
  {
    s << indent << "enable: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.enable);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ASTRA_CAMERA_MESSAGE_SETAUTOEXPOSUREREQUEST_H
