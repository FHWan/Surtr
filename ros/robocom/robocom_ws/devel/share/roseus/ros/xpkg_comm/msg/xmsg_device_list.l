;; Auto-generated. Do not edit!


(when (boundp 'xpkg_comm::xmsg_device_list)
  (if (not (find-package "XPKG_COMM"))
    (make-package "XPKG_COMM"))
  (shadow 'xmsg_device_list (find-package "XPKG_COMM")))
(unless (find-package "XPKG_COMM::XMSG_DEVICE_LIST")
  (make-package "XPKG_COMM::XMSG_DEVICE_LIST"))

(in-package "ROS")
;;//! \htmlinclude xmsg_device_list.msg.html


(defclass xpkg_comm::xmsg_device_list
  :super ros::object
  :slots (_dev_count _dev_list ))

(defmethod xpkg_comm::xmsg_device_list
  (:init
   (&key
    ((:dev_count __dev_count) 0)
    ((:dev_list __dev_list) (let (r) (dotimes (i 0) (push (instance xpkg_comm::xmsg_device :init) r)) r))
    )
   (send-super :init)
   (setq _dev_count (round __dev_count))
   (setq _dev_list __dev_list)
   self)
  (:dev_count
   (&optional __dev_count)
   (if __dev_count (setq _dev_count __dev_count)) _dev_count)
  (:dev_list
   (&rest __dev_list)
   (if (keywordp (car __dev_list))
       (send* _dev_list __dev_list)
     (progn
       (if __dev_list (setq _dev_list (car __dev_list)))
       _dev_list)))
  (:serialization-length
   ()
   (+
    ;; uint8 _dev_count
    1
    ;; xpkg_comm/xmsg_device[] _dev_list
    (apply #'+ (send-all _dev_list :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _dev_count
       (write-byte _dev_count s)
     ;; xpkg_comm/xmsg_device[] _dev_list
     (write-long (length _dev_list) s)
     (dolist (elem _dev_list)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _dev_count
     (setq _dev_count (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; xpkg_comm/xmsg_device[] _dev_list
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _dev_list (let (r) (dotimes (i n) (push (instance xpkg_comm::xmsg_device :init) r)) r))
     (dolist (elem- _dev_list)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get xpkg_comm::xmsg_device_list :md5sum-) "2ceb7f0b4db86b40356e12aab2f69511")
(setf (get xpkg_comm::xmsg_device_list :datatype-) "xpkg_comm/xmsg_device_list")
(setf (get xpkg_comm::xmsg_device_list :definition-)
      "uint8 dev_count
xmsg_device[] dev_list

================================================================================
MSG: xpkg_comm/xmsg_device
uint8 dev_class
uint8 dev_type
uint8 dev_number
uint8 dev_enable

")



(provide :xpkg_comm/xmsg_device_list "2ceb7f0b4db86b40356e12aab2f69511")


