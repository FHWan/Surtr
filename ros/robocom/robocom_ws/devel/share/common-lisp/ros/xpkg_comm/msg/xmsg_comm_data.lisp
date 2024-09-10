; Auto-generated. Do not edit!


(cl:in-package xpkg_comm-msg)


;//! \htmlinclude xmsg_comm_data.msg.html

(cl:defclass <xmsg_comm_data> (roslisp-msg-protocol:ros-message)
  ((id_c
    :reader id_c
    :initarg :id_c
    :type cl:fixnum
    :initform 0)
   (id_t
    :reader id_t
    :initarg :id_t
    :type cl:fixnum
    :initform 0)
   (id_n
    :reader id_n
    :initarg :id_n
    :type cl:fixnum
    :initform 0)
   (id_f
    :reader id_f
    :initarg :id_f
    :type cl:fixnum
    :initform 0)
   (len
    :reader len
    :initarg :len
    :type cl:fixnum
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 8 :element-type 'cl:fixnum :initial-element 0))
   (time
    :reader time
    :initarg :time
    :type cl:real
    :initform 0))
)

(cl:defclass xmsg_comm_data (<xmsg_comm_data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <xmsg_comm_data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'xmsg_comm_data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name xpkg_comm-msg:<xmsg_comm_data> is deprecated: use xpkg_comm-msg:xmsg_comm_data instead.")))

(cl:ensure-generic-function 'id_c-val :lambda-list '(m))
(cl:defmethod id_c-val ((m <xmsg_comm_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:id_c-val is deprecated.  Use xpkg_comm-msg:id_c instead.")
  (id_c m))

(cl:ensure-generic-function 'id_t-val :lambda-list '(m))
(cl:defmethod id_t-val ((m <xmsg_comm_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:id_t-val is deprecated.  Use xpkg_comm-msg:id_t instead.")
  (id_t m))

(cl:ensure-generic-function 'id_n-val :lambda-list '(m))
(cl:defmethod id_n-val ((m <xmsg_comm_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:id_n-val is deprecated.  Use xpkg_comm-msg:id_n instead.")
  (id_n m))

(cl:ensure-generic-function 'id_f-val :lambda-list '(m))
(cl:defmethod id_f-val ((m <xmsg_comm_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:id_f-val is deprecated.  Use xpkg_comm-msg:id_f instead.")
  (id_f m))

(cl:ensure-generic-function 'len-val :lambda-list '(m))
(cl:defmethod len-val ((m <xmsg_comm_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:len-val is deprecated.  Use xpkg_comm-msg:len instead.")
  (len m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <xmsg_comm_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:data-val is deprecated.  Use xpkg_comm-msg:data instead.")
  (data m))

(cl:ensure-generic-function 'time-val :lambda-list '(m))
(cl:defmethod time-val ((m <xmsg_comm_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader xpkg_comm-msg:time-val is deprecated.  Use xpkg_comm-msg:time instead.")
  (time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <xmsg_comm_data>) ostream)
  "Serializes a message object of type '<xmsg_comm_data>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_c)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_t)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_n)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_f)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'len)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'time)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'time) (cl:floor (cl:slot-value msg 'time)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <xmsg_comm_data>) istream)
  "Deserializes a message object of type '<xmsg_comm_data>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_c)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_t)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_n)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_f)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'len)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i 8)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'time) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<xmsg_comm_data>)))
  "Returns string type for a message object of type '<xmsg_comm_data>"
  "xpkg_comm/xmsg_comm_data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'xmsg_comm_data)))
  "Returns string type for a message object of type 'xmsg_comm_data"
  "xpkg_comm/xmsg_comm_data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<xmsg_comm_data>)))
  "Returns md5sum for a message object of type '<xmsg_comm_data>"
  "9bb3169c96726b4ca470a5d97bf0777b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'xmsg_comm_data)))
  "Returns md5sum for a message object of type 'xmsg_comm_data"
  "9bb3169c96726b4ca470a5d97bf0777b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<xmsg_comm_data>)))
  "Returns full string definition for message of type '<xmsg_comm_data>"
  (cl:format cl:nil "uint8 id_c~%uint8 id_t~%uint8 id_n~%uint8 id_f~%uint8 len~%uint8[8] data~%time time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'xmsg_comm_data)))
  "Returns full string definition for message of type 'xmsg_comm_data"
  (cl:format cl:nil "uint8 id_c~%uint8 id_t~%uint8 id_n~%uint8 id_f~%uint8 len~%uint8[8] data~%time time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <xmsg_comm_data>))
  (cl:+ 0
     1
     1
     1
     1
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <xmsg_comm_data>))
  "Converts a ROS message object to a list"
  (cl:list 'xmsg_comm_data
    (cl:cons ':id_c (id_c msg))
    (cl:cons ':id_t (id_t msg))
    (cl:cons ':id_n (id_n msg))
    (cl:cons ':id_f (id_f msg))
    (cl:cons ':len (len msg))
    (cl:cons ':data (data msg))
    (cl:cons ':time (time msg))
))
