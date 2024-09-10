;; Auto-generated. Do not edit!


(when (boundp 'xpkg_comm::xmsg_device)
  (if (not (find-package "XPKG_COMM"))
    (make-package "XPKG_COMM"))
  (shadow 'xmsg_device (find-package "XPKG_COMM")))
(unless (find-package "XPKG_COMM::XMSG_DEVICE")
  (make-package "XPKG_COMM::XMSG_DEVICE"))

(in-package "ROS")
;;//! \htmlinclude xmsg_device.msg.html


(defclass xpkg_comm::xmsg_device
  :super ros::object
  :slots (_dev_class _dev_type _dev_number _dev_enable ))

(defmethod xpkg_comm::xmsg_device
  (:init
   (&key
    ((:dev_class __dev_class) 0)
    ((:dev_type __dev_type) 0)
    ((:dev_number __dev_number) 0)
    ((:dev_enable __dev_enable) 0)
    )
   (send-super :init)
   (setq _dev_class (round __dev_class))
   (setq _dev_type (round __dev_type))
   (setq _dev_number (round __dev_number))
   (setq _dev_enable (round __dev_enable))
   self)
  (:dev_class
   (&optional __dev_class)
   (if __dev_class (setq _dev_class __dev_class)) _dev_class)
  (:dev_type
   (&optional __dev_type)
   (if __dev_type (setq _dev_type __dev_type)) _dev_type)
  (:dev_number
   (&optional __dev_number)
   (if __dev_number (setq _dev_number __dev_number)) _dev_number)
  (:dev_enable
   (&optional __dev_enable)
   (if __dev_enable (setq _dev_enable __dev_enable)) _dev_enable)
  (:serialization-length
   ()
   (+
    ;; uint8 _dev_class
    1
    ;; uint8 _dev_type
    1
    ;; uint8 _dev_number
    1
    ;; uint8 _dev_enable
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _dev_class
       (write-byte _dev_class s)
     ;; uint8 _dev_type
       (write-byte _dev_type s)
     ;; uint8 _dev_number
       (write-byte _dev_number s)
     ;; uint8 _dev_enable
       (write-byte _dev_enable s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _dev_class
     (setq _dev_class (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dev_type
     (setq _dev_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dev_number
     (setq _dev_number (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dev_enable
     (setq _dev_enable (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get xpkg_comm::xmsg_device :md5sum-) "fb7e43db7d28a3165b8781af2a5c7ea9")
(setf (get xpkg_comm::xmsg_device :datatype-) "xpkg_comm/xmsg_device")
(setf (get xpkg_comm::xmsg_device :definition-)
      "uint8 dev_class
uint8 dev_type
uint8 dev_number
uint8 dev_enable

")



(provide :xpkg_comm/xmsg_device "fb7e43db7d28a3165b8781af2a5c7ea9")


