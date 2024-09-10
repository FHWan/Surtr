// Generated by gencpp from file astra_camera/GetVersionResponse.msg
// DO NOT EDIT!


#ifndef ASTRA_CAMERA_MESSAGE_GETVERSIONRESPONSE_H
#define ASTRA_CAMERA_MESSAGE_GETVERSIONRESPONSE_H


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
struct GetVersionResponse_
{
  typedef GetVersionResponse_<ContainerAllocator> Type;

  GetVersionResponse_()
    : version()
    , core_version()  {
    }
  GetVersionResponse_(const ContainerAllocator& _alloc)
    : version(_alloc)
    , core_version(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _version_type;
  _version_type version;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _core_version_type;
  _core_version_type core_version;





  typedef boost::shared_ptr< ::astra_camera::GetVersionResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::astra_camera::GetVersionResponse_<ContainerAllocator> const> ConstPtr;

}; // struct GetVersionResponse_

typedef ::astra_camera::GetVersionResponse_<std::allocator<void> > GetVersionResponse;

typedef boost::shared_ptr< ::astra_camera::GetVersionResponse > GetVersionResponsePtr;
typedef boost::shared_ptr< ::astra_camera::GetVersionResponse const> GetVersionResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::astra_camera::GetVersionResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::astra_camera::GetVersionResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::astra_camera::GetVersionResponse_<ContainerAllocator1> & lhs, const ::astra_camera::GetVersionResponse_<ContainerAllocator2> & rhs)
{
  return lhs.version == rhs.version &&
    lhs.core_version == rhs.core_version;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::astra_camera::GetVersionResponse_<ContainerAllocator1> & lhs, const ::astra_camera::GetVersionResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace astra_camera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::astra_camera::GetVersionResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::astra_camera::GetVersionResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::astra_camera::GetVersionResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::astra_camera::GetVersionResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::astra_camera::GetVersionResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::astra_camera::GetVersionResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::astra_camera::GetVersionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9dcb65d43afc4a7688056ebe631dc337";
  }

  static const char* value(const ::astra_camera::GetVersionResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9dcb65d43afc4a76ULL;
  static const uint64_t static_value2 = 0x88056ebe631dc337ULL;
};

template<class ContainerAllocator>
struct DataType< ::astra_camera::GetVersionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "astra_camera/GetVersionResponse";
  }

  static const char* value(const ::astra_camera::GetVersionResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::astra_camera::GetVersionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string version\n"
"string core_version\n"
;
  }

  static const char* value(const ::astra_camera::GetVersionResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::astra_camera::GetVersionResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.version);
      stream.next(m.core_version);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetVersionResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::astra_camera::GetVersionResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::astra_camera::GetVersionResponse_<ContainerAllocator>& v)
  {
    s << indent << "version: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.version);
    s << indent << "core_version: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.core_version);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ASTRA_CAMERA_MESSAGE_GETVERSIONRESPONSE_H
