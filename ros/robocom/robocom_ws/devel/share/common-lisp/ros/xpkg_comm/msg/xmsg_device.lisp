; Auto-generated. Do not edit!


(cl:in-package xpkg_comm-msg)


;//! \htmlinclude xmsg_device.msg.html

(cl:defclass <xmsg_device> (roslisp-msg-protocol:ros-message)
  ((dev_class
    :reader dev_class
    :initarg :dev_class
    :type cl:fixnum
    :initform 0)
   (dev_type
    :reader dev_type
    :initarg :dev_type
    :type cl:fixnum
    :initform 0)
   (dev_number
    :reader dev_number
    :initarg :dev_number
    :type cl:fixnum
    :initform 0)
   (dev_enable
    :reader dev_enable
    :initarg :dev_enable
    :type cl:fixnum
    :initform 0))
)

(cl:defclass xmsg_device (<xmsg_device>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <xmsg_device>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'xmsg_device)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name xpkg_comm-msg:<xmsg_device> is deprecated: use xpkg_comm-msg:xmsg_device instead.")))

(cl:ensure-generic-function 'dev_class-val :lambda-list '(m))
(cl:defmethod dev_class-val ((m <xmsg_device>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:dev_class-val is deprecated.  Use xpkg_comm-msg:dev_class instead.")
  (dev_class m))

(cl:ensure-generic-function 'dev_type-val :lambda-list '(m))
(cl:defmethod dev_type-val ((m <xmsg_device>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:dev_type-val is deprecated.  Use xpkg_comm-msg:dev_type instead.")
  (dev_type m))

(cl:ensure-generic-function 'dev_number-val :lambda-list '(m))
(cl:defmethod dev_number-val ((m <xmsg_device>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:dev_number-val is deprecated.  Use xpkg_comm-msg:dev_number instead.")
  (dev_number m))

(cl:ensure-generic-function 'dev_enable-val :lambda-list '(m))
(cl:defmethod dev_enable-val ((m <xmsg_device>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:dev_enable-val is deprecated.  Use xpkg_comm-msg:dev_enable instead.")
  (dev_enable m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <xmsg_device>) ostream)
  "Serializes a message object of type '<xmsg_device>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_class)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_enable)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <xmsg_device>) istream)
  "Deserializes a message object of type '<xmsg_device>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_class)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dev_enable)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<xmsg_device>)))
  "Returns string type for a message object of type '<xmsg_device>"
  "xpkg_comm/xmsg_device")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'xmsg_device)))
  "Returns string type for a message object of type 'xmsg_device"
  "xpkg_comm/xmsg_device")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<xmsg_device>)))
  "Returns md5sum for a message object of type '<xmsg_device>"
  "fb7e43db7d28a3165b8781af2a5c7ea9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'xmsg_device)))
  "Returns md5sum for a message object of type 'xmsg_device"
  "fb7e43db7d28a3165b8781af2a5c7ea9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<xmsg_device>)))
  "Returns full string definition for message of type '<xmsg_device>"
  (cl:format cl:nil "uint8 dev_class~%uint8 dev_type~%uint8 dev_number~%uint8 dev_enable~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'xmsg_device)))
  "Returns full string definition for message of type 'xmsg_device"
  (cl:format cl:nil "uint8 dev_class~%uint8 dev_type~%uint8 dev_number~%uint8 dev_enable~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <xmsg_device>))
  (cl:+ 0
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <xmsg_device>))
  "Converts a ROS message object to a list"
  (cl:list 'xmsg_device
    (cl:cons ':dev_class (dev_class msg))
    (cl:cons ':dev_type (dev_type msg))
    (cl:cons ':dev_number (dev_number msg))
    (cl:cons ':dev_enable (dev_enable msg))
))
