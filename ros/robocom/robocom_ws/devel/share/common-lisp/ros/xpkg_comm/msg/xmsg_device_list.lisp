; Auto-generated. Do not edit!


(cl:in-package xpkg_comm-msg)


;//! \htmlinclude xmsg_device_list.msg.html

(cl:defclass <xmsg_device_list> (roslisp-msg-protocol:ros-message)
  ((dev_count
    :reader dev_count
    :initarg :dev_count
    :type cl:fixnum
    :initform 0)
   (dev_list
    :reader dev_list
    :initarg :dev_list
    :type (cl:vector xpkg_comm-msg:xmsg_device)
   :initform (cl:make-array 0 :element-type 'xpkg_comm-msg:xmsg_device :initial-element (cl:make-instance 'xpkg_comm-msg:xmsg_device))))
)

(cl:defclass xmsg_device_list (<xmsg_device_list>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <xmsg_device_list>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'xmsg_device_list)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name xpkg_comm-msg:<xmsg_device_list> is deprecated: use xpkg_comm-msg:xmsg_device_list instead.")))

(cl:ensure-generic-function 'dev_count-val :lambda-list '(m))
(cl:defmethod dev_count-val ((m <xmsg_device_list>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:dev_count-val is deprecated.  Use xpkg_comm-msg:dev_count instead.")
  (dev_count m))

(cl:ensure-generic-function 'dev_list-val :lambda-list '(m))
(cl:defmethod dev_list-val ((m <xmsg_device_list>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:dev_list-val is deprecated.  Use xpkg_comm-msg:dev_list instead.")
  (dev_list m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <xmsg_device_list>) ostream)
  "Serializes a message object of type '<xmsg_device_list>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_count)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'dev_list))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'dev_list))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <xmsg_device_list>) istream)
  "Deserializes a message object of type '<xmsg_device_list>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_count)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'dev_list) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'dev_list)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'xpkg_comm-msg:xmsg_device))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<xmsg_device_list>)))
  "Returns string type for a message object of type '<xmsg_device_list>"
  "xpkg_comm/xmsg_device_list")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'xmsg_device_list)))
  "Returns string type for a message object of type 'xmsg_device_list"
  "xpkg_comm/xmsg_device_list")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<xmsg_device_list>)))
  "Returns md5sum for a message object of type '<xmsg_device_list>"
  "2ceb7f0b4db86b40356e12aab2f69511")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'xmsg_device_list)))
  "Returns md5sum for a message object of type 'xmsg_device_list"
  "2ceb7f0b4db86b40356e12aab2f69511")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<xmsg_device_list>)))
  "Returns full string definition for message of type '<xmsg_device_list>"
  (cl:format cl:nil "uint8 dev_count~%xmsg_device[] dev_list~%~%================================================================================~%MSG: xpkg_comm/xmsg_device~%uint8 dev_class~%uint8 dev_type~%uint8 dev_number~%uint8 dev_enable~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'xmsg_device_list)))
  "Returns full string definition for message of type 'xmsg_device_list"
  (cl:format cl:nil "uint8 dev_count~%xmsg_device[] dev_list~%~%================================================================================~%MSG: xpkg_comm/xmsg_device~%uint8 dev_class~%uint8 dev_type~%uint8 dev_number~%uint8 dev_enable~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <xmsg_device_list>))
  (cl:+ 0
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'dev_list) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <xmsg_device_list>))
  "Converts a ROS message object to a list"
  (cl:list 'xmsg_device_list
    (cl:cons ':dev_count (dev_count msg))
    (cl:cons ':dev_list (dev_list msg))
))
